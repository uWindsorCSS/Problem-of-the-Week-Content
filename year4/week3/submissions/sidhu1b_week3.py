users = {}
posts = {}

N = int(input()) #input
for i in range(N):
	a,b = [int(j) for j in input().split()]
	if(a in users):
		users[a].append(b)
	else:
		users[a] = [b]

	if(b in users):
		users[b].append(a)
	else:
		users[b] = [a]

M = int(input()) 
for i in range(M):
	x,y,z = [int(j) for j in input().split()]
	if(y in posts):
		posts[y].append((x,z))
	else:
		posts[y] = [(x,z)]

U,T = [int(i) for i in input().split()] #end of input

friends = users[U]
likesCounter = 0
dislikesCounter = 0

for key, value in posts.items():
	
	likesCounter = 0
	dislikesCounter = 0

	for i in range(len(value)):
		if(value[i][0] in friends):
			if(value[i][1] == -1):
				dislikesCounter += 1
			else:
				likesCounter += 1
		if((likesCounter - dislikesCounter) >= T):
			print(key)
			break
