import pandas as pd
from sklearn.preprocessing import StandardScaler, OneHotEncoder
from sklearn.compose import ColumnTransformer

class DataProcessor:
    def __init__(self):
        self.raw_data = None
        self.processed_data = None
        self.preprocessor = None

    def load_data(self, file_path):
        """Load data from CSV file path or file-like object"""
        self.raw_data = pd.read_csv(file_path)
        self._process_data()  # Process data immediately
        return self.raw_data

    def _process_data(self):
        """Process raw data using standardization for numerical and one-hot encoding for categorical"""
        if self.raw_data is None:
            return

        # Define numerical/categorical columns
        num_cols = self.raw_data.select_dtypes(include=['number']).columns
        cat_cols = self.raw_data.select_dtypes(include=['object']).columns

        # Create preprocessing pipeline
        self.preprocessor = ColumnTransformer([
            ('num', StandardScaler(), num_cols),
            ('cat', OneHotEncoder(sparse_output=False), cat_cols)
        ])

        # Process data
        processed_array = self.preprocessor.fit_transform(self.raw_data)
        
        # Get feature names
        num_features = num_cols.tolist()
        
        # Handle the case where there are no categorical columns
        if len(cat_cols) > 0:
            cat_features = self.preprocessor.named_transformers_['cat'].get_feature_names_out(cat_cols)
            all_features = num_features + cat_features.tolist()
        else:
            all_features = num_features

        # Create processed DataFrame
        self.processed_data = pd.DataFrame(processed_array, columns=all_features)

    def get_processed_columns(self):
        """Returns list of processed column names"""
        if self.processed_data is not None:
            return self.processed_data.columns.tolist()
        return []