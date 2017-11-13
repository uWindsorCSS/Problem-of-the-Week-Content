N = int(input())
arr1 = input().split(' ')
C,S = input().split()
C = int(C);
S = int(S);

for i in range(0, N-1):
	for j in range(i+1, N):
		if(int(arr1[i])+int(arr1[j]) == int(S)):
			C -= 1
	if(C == 0):
		print("True")
		break

if(C != 0):
	print("False")