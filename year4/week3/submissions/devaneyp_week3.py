friendships = {}
n = int(input())
for _ in range(n):
	a, b = [int(x) for x in input().split()]
	if a not in friendships:
		friendships[a] = {}
	if b not in friendships:
		friendships[b] = {}
	friendships[a][b] = 0
	friendships[b][a] = 0
posts = []
m = int(input())
for _ in range(m):
	posts.append([int(x) for x in input().split()])
u, t = [int(x) for x in input().split()]
postWeights = {}
for post in posts:
	if post[0] in friendships[u]:
		postWeights[post[1]] = postWeights.get(post[1], 0) + post[2]
for p in filter(lambda x: postWeights[x] >= t, postWeights):
	print(p)