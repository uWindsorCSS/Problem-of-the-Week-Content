import heapq as hq
N = int(input())
holes = input().split()
C,S = [int(i) for i in input().split()]
holes = [int(i) for i in holes]

holes.sort()
counter = 0
for i in range(N):
    for y in range(N-1,i,-1):
        if(holes[i] + holes[y] == S):
            counter += 1
        elif(holes[i] + holes[y] < S):
            break
    if(counter == C):
        break
if(counter == C):
    print("True")
else:
    print("False")