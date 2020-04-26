import pandas as pd 

heads = ['num', 'img1', 'img2', 'surf', 'hist', 'comb']
#df = pd.read_csv('/home/dhan/myprog/c_cpp/mycpp11/libs/opencv4/surf/output.csv', names=heads, skipinitialspacebool=True)
df = pd.read_csv('/home/dhan/myprog/c_cpp/mycpp11/libs/opencv4/surf/output.csv', header=0, names=heads, skipinitialspace=True)
print(df['comb'].mean())
