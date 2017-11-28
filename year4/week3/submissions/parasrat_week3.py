N = int(input())
readings = input().split()
readings = [int(i) for i in readings]
ordered = readings.copy()
worked = False
if(N-1 = 0):
    print(-1)
else:
    for i in range(1,N-1):
        if((sum(readings[0:i])+sum(readings[i+1:N]))/(N-1) *.85 >= readings[i]):
            print(i)
            worked = True
            break
    if(worked):
        pass
    elif(sum(readings[0:N-1])/(N-1)*.85 >= readings[N-1]):
        print(N-1)
    elif(sum(readings[1:N])/(N-1)*.85 >= readings[0]):
        print(0)
    else:
        print(-1)