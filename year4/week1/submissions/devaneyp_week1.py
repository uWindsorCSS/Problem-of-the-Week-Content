    

N = int(input())
holes = list(map(int, input().split()))
C, S = list(map(int, input().split()))
bucket = [0] * 51
for x in holes:
    bucket[x] += 1
total = 0
for i in range(1, S//2+1):
    if i != S/2:
        total += bucket[i] * bucket[S-i]
    else:
        total += bucket[i] * (bucket[i] - 1) / 2
print(total >= C)

    
