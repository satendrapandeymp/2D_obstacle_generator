import numpy as np
import random

corridor = [-14.7,14.7]
length   = [-14.7,14.7]

'''
with open("Source/Declearation.cpp") as temp:
    text = temp.read()
    text = text.split("const int total_obstacles = ")[1]
    text = text.split(";")[0]
'''
text = "2"

total_obs = int(text)

count = 0

while(count < 10000):
    count += 1
    posx = []
    posy = []
    distance = []
    rad = []

    x_cord = np.random.uniform(corridor[0],  corridor[1], total_obs)
    y_cord = np.random.uniform(length[0]  ,  length[1]  , total_obs)

    for i in range(total_obs):
        posx.append(x_cord[i])
        posy.append(y_cord[i])

    # Find min_dist obstacle for each obstacle
    for i in range(total_obs):
        min_dist = 300
        xown = posx[i]
        yown = posy[i]
        for j in range(total_obs):
            x = posx[j]
            y = posy[j]
            dist = (xown-x)**2 + (yown-y)**2
            if i!=j and dist < min_dist:
                min_dist = dist
        distance.append(min_dist**.5)

    num = min(distance)

    if num > .7:
        break

    print count

vel = []
x_vel = np.random.uniform(-.1, .1, total_obs)
y_vel = np.random.uniform(-.1, .1, total_obs)

for i in range(total_obs):
    dic = {"vx":x_vel[i], "vy":y_vel[i]}
    vel.append(dic)



with open('data.txt', 'w') as out:
    for i in range(total_obs):
        out.write(str(posx[i]) + " " + str(posy[i]) + " " + str(vel[i]['vx']) + " " + str(vel[i]['vy']) + "\n")
