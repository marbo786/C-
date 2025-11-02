from data_processor import DataProcessor  
from sports_regressor import SportsRegressor

class SportsChatbot:
    def __init__(self):
        self.data_processor = None
        self.model = None
        self.step = 0  # Initialize step for walkthrough
        self.last_metrics = {}

        self.faq = {
            "normalization": "Normalization scales features to have zero mean and unit variance, making models converge faster and perform better.",
            "missing values": "Missing values are handled using imputation, often by filling them with the mean (for numbers) or 'Unknown' (for categories).",
            "feature engineering": "Feature engineering creates new features by combining or transforming existing ones to help the model capture patterns better.",
            "data summary": self.get_data_summary,
            "model accuracy": self.get_model_accuracy,
            "help": "Try asking about: 'data summary', 'model accuracy', or ask about preprocessing like 'missing values'."
        }

    def connect_to_data(self, data_processor):
        self.data_processor = data_processor

    def connect_to_model(self, model):
        self.model = model

    def get_response(self, user_input):
        user_input = user_input.lower()

        if self.data_processor is None:
            return "Please upload data first!"
        
        # Check for walkthrough
        if "start walkthrough" in user_input:
            self.step = 1
            return "Step 1: Please upload your CSV file using the upload section above."
        
        if self.step == 1 and "upload" in user_input:
            self.step = 2
            return "Step 2: Your data is uploaded. Now go to the 'Regression Modeling' tab and choose your target column."
        
        if self.step == 2 and "target" in user_input:
            self.step = 3
            return "Step 3: Select the regression model you want to use from the dropdown and click 'Train Model'."
        
        if self.step == 3 and "train" in user_input:
            self.step = 0
            return "Walkthrough complete! You can now make predictions using your model."
            
        # Add error handling for missing data/model
        if "data summary" in user_input:
            if self.data_processor is None or self.data_processor.raw_data is None:
                return "Please upload data first!"
            
        if "model accuracy" in user_input:
            if self.model is None or not hasattr(self.model, 'metrics'):
                return "No trained model exists yet!"
        
        # Check for FAQ matches first
        for key in self.faq:
            if key in user_input:
                if callable(self.faq[key]):
                    return self.faq[key]()
                return self.faq[key]
        
        # Data-related queries
        if "data" in user_input or "dataset" in user_input:
            return self.get_data_summary()
        
        # Model-related queries
        if "model" in user_input or "accuracy" in user_input or "metrics" in user_input:
            return self.get_model_accuracy()
        
        return "I'm not sure how to help with that. Try asking about your data or model, or type 'help' for suggestions."

    def get_data_summary(self):
        if self.data_processor is None or self.data_processor.raw_data is None:
            return "No data loaded yet. Please upload a CSV file first."
        
        df = self.data_processor.raw_data
        return f"Your dataset has {len(df)} rows and {len(df.columns)} columns. Columns: {', '.join(df.columns)}"

    def get_model_accuracy(self):
        if self.model is None or not hasattr(self.model, 'metrics') or not self.model.metrics:
            return "No model trained yet. Please train a model first."
        
        metrics = self.model.metrics
        return (f"Model metrics: R² = {metrics.get('R²', 0):.2f}, "
                f"RMSE = {metrics.get('RMSE', 0):.2f}, "
                f"MAE = {metrics.get('MAE', 0):.2f}")
    
    def interpret_metrics(self, metrics):
        self.last_metrics = metrics
        messages = []
        if 'R²' in metrics:
            r2 = metrics['R²']
            messages.append(f"Your R² score of {r2:.2f} means the model explains {r2*100:.0f}% of the variance.")
        if 'RMSE' in metrics:
            rmse = metrics['RMSE']
            messages.append(f"Your RMSE of {rmse:.2f} suggests the predictions are off by about {rmse:.2f} units on average.")
        if 'MAE' in metrics:
            mae = metrics['MAE']
            messages.append(f"The MAE of {mae:.2f} indicates an average absolute error of {mae:.2f} units.")
        return " ".join(messages) if messages else "No metrics available."