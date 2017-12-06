#
# The Blackboard API
# POTW Year 4 Week 4
#
# Joel Rorseth
#

from collections import defaultdict

def main():

    c = int(input())
    n = int(input())

    # Create directed graph (DAG in good case)
    adj = defaultdict(set)

    for i in range(n):
        a, b = [int(n) for n in input().split(" ")]
        adj[a].add(b)

    # For each node, we'll track visited nodes while we traverse all
    # related nodes in DFS, looking for already visited nodes (a cycle!)

    visited = set()
    path = set()

    # DFS
    def dfs(node):

        # When we see a repeat node in DFS path, this is a cycle (False)
        if node in path: return False
        if node in visited: return True

        path.add(node)

        for neighbor in adj[node]:
            if not dfs(neighbor): return False

        # DFS complete for node, add to permanantly visited
        path.discard(node)
        visited.add(node)

        return True


    # Do this DFS cycle search for every node
    courses = list(adj.keys())
    print("Good") if all([dfs(node) for node in courses]) else print("Bad")


main()
