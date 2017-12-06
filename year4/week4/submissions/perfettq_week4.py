from collections import defaultdict

def has_cycle(graph, start):
    to_visit = [(start, set())]
    while len(to_visit) != 0:
        v, seen = to_visit.pop()
        if v in seen:
            return True
        seen.add(v)
        to_visit.extend([
            (u, seen.copy())
            for u in graph.get(v, [])
        ])
    return False

def main():
    _ = int(input())
    relationships = int(input())
    prereq_graph = defaultdict(set)
    for _ in range(relationships):
        a, b = input().split(" ")
        prereq_graph[a].add(b)
    cyclic = any(
        has_cycle(prereq_graph, parent)
        for parent in prereq_graph.keys()
    )
    print("Good" if not cyclic else "Bad")

main()