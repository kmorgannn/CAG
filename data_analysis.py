
import pandas as pd
import matplotlib.pyplot as plt

# data = pd.read_csv('generated_savannah_data.csv', names=['pH', 'dissolved_oxygen'])
data = pd.read_csv('generated_tift_data.csv', names=['soil_moisture', 'temperature', 'light'])

print(data.describe())

column = 'soil_moisture'

# Run these one at a time if running from the command line
data[column].value_counts(sort=False).plot(kind='pie')
plt.show()

data[column].plot(kind='hist', label=column, legend=True)
plt.show()

data[column].plot(kind='line', legend=True)
plt.xlabel('Observation Number')
plt.show()
