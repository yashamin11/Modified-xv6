import matplotlib.pyplot as plt


x1 = []
y1 =[]
for i in range(500,2500):
	x1.append(i)
for i in range(500,2245):
	y1.append(0)
for i in range(2245,2247):
	y1.append(1)
for i in range(2247,2251):
	y1.append(2)
for i in range(2251,2270):
	y1.append(3)
for i in range(2270,2500):
	y1.append(4)


plt.plot(x1, y1, label="PID : 12")

x2 = []
y2 =[]
for i in range(500,2500):
	x2.append(i)
for i in range(500,1145):
	y2.append(0)
for i in range(1145,1147):
	y2.append(1)
for i in range(1147,1151):
	y2.append(2)
for i in range(1151,1159):
	y2.append(3)
for i in range(1159,1435):
	y2.append(4)
for i in range(1435,1443):
	y2.append(3)
for i in range(1443,1475):
	y2.append(4)
for i in range(1475,2500):
	y2.append(3)


plt.plot(x2, y2, label="PID : 7")

x3 = []
y3 =[]
for i in range(500,2500):
	x3.append(i)
for i in range(500,1360):
	y3.append(0)
for i in range(1360,1362):
	y3.append(1)
for i in range(1362,1366):
	y3.append(2)
for i in range(1366,1382):
	y3.append(3)
for i in range(1382,1575):
	y3.append(4)
for i in range(1575,1583):
	y3.append(3)
for i in range(1583,1615):
	y3.append(4)
for i in range(1615,1623):
	y3.append(3)
for i in range(1623,1655):
	y3.append(4)
for i in range(1655,1663):
	y3.append(3)
for i in range(1663,1695):
	y3.append(4)
for i in range(1695,1703):
	y3.append(3)
for i in range(1703,2500):
	y3.append(4)


plt.plot(x3, y3, label="PID : 8")

x4 = []
y4 =[]
for i in range(500,2500):
	x4.append(i)
for i in range(500,2500):
	y4.append(0)

plt.plot(x4, y4, label="PID : 13")

plt.yticks([0,1,2,3,4])
plt.xlabel('Ticks')
plt.ylabel('Queue-Number')
plt.legend()
plt.show()