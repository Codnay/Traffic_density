import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits import mplot3d
"""
ax = plt.gca()
data = {"Threads":[2,3,4,5,6,7,8], "Runtime(s)": [286,273,273,277,286,311,332], "Baseline(s)":[352,352,352,352,352,352,352]}

df = pd.DataFrame(data,columns =["Threads","Runtime(s)","Baseline(s)"])

df.plot(x="Threads", y = "Runtime(s)", kind = "line", color= 'blue', ax = ax)
df.plot(x="Threads", y = "Baseline(s)", kind = "line", color= 'red', ax = ax)
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