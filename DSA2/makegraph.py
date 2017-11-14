import random

N = 100
for n in range(N):
    num_neighbors = random.randint(0,10)
    for m in range(num_neighbors):
        neighbor = random.randint(0,N-1)
        weight = random.randint(1,1000)
        print('v'+str(n) + ' ' + 'v'+str(neighbor) + ' ' + str(weight) + '\n')
  
