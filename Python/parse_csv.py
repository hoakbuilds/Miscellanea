import pandas as pd
import matplotlib as plt
import numpy as np
from ta import *

# Load datas
df = pd.read_csv('datas.csv', sep=',')
to_date = pd.read_csv('btc_hpd.csv', sep=',')
# Clean nan values
df = utils.dropna(df)
to_date = utils.dropna(to_date)

#print df
print(df.columns)
print(df)

#print coindesk
print(to_date.columns)
print(to_date)
# Add bollinger band high indicator filling Nans values
df['bb_high_indicator'] = bollinger_hband_indicator(df["Close"], n=20, ndev=2, fillna=True)

# Add bollinger band low indicator filling Nans values
df['bb_low_indicator'] = bollinger_lband_indicator(df["Close"], n=20, ndev=2, fillna=True)


#add bband to coindesk dataset
to_date['bb_high_indicator'] = bollinger_hband_indicator(to_date["Close Price"], n=20, ndev=2, fillna=True)

# Add bollinger band low indicator filling Nans values
to_date['bb_low_indicator'] = bollinger_lband_indicator(to_date["Close Price"], n=20, ndev=2, fillna=True)


print(to_date.columns)
print(len(to_date.columns))
print(to_date.loc[to_date['bb_high_indicator'] == 1])
for value in to_date.loc[to_date['bb_low_indicator'] == 1]:
    print(value)

print(to_date[2689:2698])
"""
print(df.columns)
print(len(df.columns))
print(df.loc[df['bb_high_indicator'] == 1])
print(df.loc[df['bb_low_indicator'] == 1])
"""
