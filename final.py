import os, random

dia = .4

def move(pos):
    for i in range(len(pos)):
        temp = []
        position = pos[i]
        x = position[0]
        y = position[1]
        r = position[2]
        for j in range(len(pos)):
            if j == i:
                continue
            position = pos[j]
            x1 = position[0]
            y1 = position[1]
            r1 = position[2]
            dist = (((x1-x)**2 + (y1-y)**2))**.5
            temp.append(dist-dia)
	temp.append(1.8-y)
	temp.append(y+1.8)
        min_dist = min(temp)
        mx = min_dist * (random.random()-.5)
        my = min_dist * (random.random()-.5)
        pos[i][0] += mx
        pos[i][1] += my

    return pos


with open('../Data/Input0.txt') as Data:
    data = Data.read()

pos = []

obstacles = data.split("\n")

for obstacle in obstacles:
    data = obstacle.split(" ")
    temp = []
    try:
	#print data[2]
        temp.append(float(data[0].strip()))
        temp.append(float(data[1].strip()))
        temp.append(float(data[2].strip()))
        pos.append(temp)
    except:
        pass

arr = move(pos)

with open('../Data/Input0.txt', 'w') as Data:
    for row in arr:
        Data.write(str(10 + row[0]) + " " + str(row[1]) + " " + str(row[2]) + "\n")
