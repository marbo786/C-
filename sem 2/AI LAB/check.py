import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report


# load dataset

data = pd.read_csv("tips.csv")

## printing data

data.head()

## tail() , #data.shape , #data.describe , #data.country.unique() , #data.sort_value('age') ,idxmin(), idxmax()	Returns the index of min/max

## adding a new coloumn to the dataset data["new"] = data["age"] / data["salary"]

#Selecting columns

data.iloc[5:9,0:4]  #selects 5th to 8th row and 0 to 4th column

data.iloc[:, ['name','age']]  # Rows (inclusive), columns 'Name' and 'Age'


# 2. Null values and Duplicates

df.isnull().sum()   # method to find all the nan values in each columns
df.duplicated().sum()


#droping row or column with nan value  --- inplace modifies the original DataFrame directly

df.dropna(axis=1, inplace = True)



# Cleaning: Drop duplicates and fill missing 'age' with mean
df = df.drop_duplicates()
df['age'] = df['age'].fillna(df['age'].mean())



df.groupby('Department')['Salary'].agg(['min', 'max', 'mean']) ## aggregate function here (multiple)



# Check for categorical variables (few unique values hence likely categorical)
print(df.nunique())


# (Assume 'sex', 'cp', 'fbs', 'restecg', 'exang', 'slope', 'thal' are categorical)
categorical = ['sex', 'cp', 'fbs', 'restecg', 'exang', 'slope', 'thal']
df[categorical] = df[categorical].apply(LabelEncoder().fit_transform)



# Split data into features and target
X = df.drop('target', axis=1)   # we are selecting all the coloumns except target
y = df['target']


# Normalize features
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)


# Train-test split (80%-20%)
X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.2, random_state=42)


# Model training
model = RandomForestClassifier(random_state=42)
model.fit(X_train, y_train)

# Prediction
y_pred = model.predict(X_test)


# evaluating results 

print(classification_report(y_test, y_pred))



# to visualize data as a scatterplot

X = tips_data['total_bill']
Y = tips_data['tip']

# plot the scatter plot
plt.scatter(X,Y)

# add the axes labels to the plot
plt.xlabel('total_bill')
plt.ylabel('tip')

# display the plot
plt.show()



# bar plot to get the count of smokers and non-smokers in the data

# kind='bar' plots a bar plot
# 'rot = 0' returns the categoric labels horizontally

tips_data.smoker.value_counts().plot(kind='bar', rot = 0) 

df.groupby('Gender')['Age'].mean().plot(kind='bar')

# display the plot
plt.show()



# plot the histogram
# specify the number of bins, using 'bins' parameter --- bins are like towers 

plt.hist(tips_data['tip'], bins= 5)

plt.title('Distribution of tip amount')
plt.xlabel('tip')
plt.ylabel('Frequency')


plt.show()


