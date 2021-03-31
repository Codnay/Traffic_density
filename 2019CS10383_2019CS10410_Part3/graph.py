import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

s = input("Enter the name of csv file: ")
X = input("Enter the column head name for x-axis: ")
Y = input("Enter the column head name for y-axis: ")
data = pd.read_csv(s)

df = pd.DataFrame(data)

df.plot(x=X, y = Y, kind = "line")

plt.show()

"""

fig = plt.figure()
ax = plt.axes(projection = '3d')

ax.set_xlabel("Utility(\%error)")
ax.set_ylabel("Runtime(s)")
ax.set_zlabel("Parameter")

x = [0,1.12,1.67,2.63,3.28,3.95,4.75,5.60,6.90,8.31,9.21,10.94]
y = [373,257,237,228,221,217,217,211,198,198,195,193]
z = [1,2,3,4,5,6,7,8,10,12,14,16]

ax.plot3D(x,y,z, 'blue')
plt.show()
"""
"""
"Utility(\%error)":['0\n(x = 1)','1.12\n(x = 2)','1.67\n(x = 3)','2.63\n(x = 4)','3.28\n(x = 5)','3.95\n(x = 6)','4.75\n(x = 7)','5.60\n(x = 8)','6.90\n(x = 10)','8.31\n(x = 12)',
'9.21\n(x = 14)','10.94\n(x = 16)']
"""
