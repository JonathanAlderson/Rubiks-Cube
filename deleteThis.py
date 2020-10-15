import time

def x(n):
    n = n % 1080
    return 8 -min(max(0,n - 330)*0.1, 4) - min(max(0,n - 690)*0.1, 8) + min(max(0,n - 960)*0.1, 12)


for i in range(3000):
    print("i = ", i, " ",x(i))
    time.sleep(0.02)
