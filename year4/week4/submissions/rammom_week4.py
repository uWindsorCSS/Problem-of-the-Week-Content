## Disregard the inefficient code below, it works so that counts for something.

C = int(input())
N = int(input())

graph = {}
# get the input and build the graph
for i in range(0, N):
	(a, b) = input().split(" ")
	(a, b) = (int(a), int(b))

	if (a in graph):
		graph[a].append(b)
	else:
		graph[a] = [b]
	if (b not in graph):
		graph[b] = []

## now we have the input,
# pull out dfs and look for that cycle!

def dfs_visit(graph, currentNode, visited, courses_taken, instack):
	visited.append(currentNode)
	instack.append(currentNode)
	for arg in graph[currentNode]:
		if (arg not in visited):
			dfs_visit(graph, arg, visited, courses_taken, instack)
		if (arg in instack):
			# cycle detected!
			return
	instack.remove(currentNode)
	if (currentNode not in courses_taken):
		courses_taken.append(currentNode)
	if (len(courses_taken) >= C):
		print("Good")
		exit(0)

def dfs(graph):

	courses_taken = []

	for node in graph:
		visited = []
		instack = []
		dfs_visit(graph, node, visited, courses_taken, instack)

	print("Bad")

dfs(graph)
