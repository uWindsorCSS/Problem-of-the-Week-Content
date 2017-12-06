// POTW #4 - Fall 2017
// BlackboardApi - https://potw.cs.uwindsor.ca/problem/2017/4/
// Patrick Malolepszy
package main

import (
	"fmt"
)

// Reads input for the blackboard api potw.
// Returns the number of courses available and the number of courses required
func readPotwInput(graph map[int][]int) (int, int) {
	var requiredCourses, dependencies, a, b int
	courseSet := make(map[int]bool)
	fmt.Scan(&requiredCourses, &dependencies)

	for i := 0; i < dependencies; i++ {
		fmt.Scan(&a, &b)
		courseSet[a] = true
		courseSet[b] = true
		graph[b] = append(graph[b], a)
	}

	return requiredCourses, len(courseSet)
}

// Determines if one can graduate given a set of courses dependencies as an adjacency matrix,
// and the number of required courses needed to graduate.
// Returns true if graduation is possible, false otherwise.
func canGraduate(requiredCourses, numOfCourses int, courseGraph map[int][]int) bool {
	impossibleCourses := findNodesInCycle(courseGraph)
	addDependents(impossibleCourses, courseGraph)
	possibleCourses := numOfCourses - len(impossibleCourses)
	if requiredCourses > possibleCourses {
		return false
	} else {
		return true
	}
}

// Returns a set of all nodes which are in cycles in a directed graph.
func findNodesInCycle(graph map[int][]int) map[int]bool {

	// sets to keep track of each node's state
	unvisited := make(map[int]bool)
	visiting := make(map[int]bool)
	visited := make(map[int]bool)

	// set of nodes which are in cycles
	cycleNodeSet := make(map[int]bool)

	// add all nodes to the unvisited set
	for k := range graph {
		unvisited[k] = true
	}

	// while there are nodes to be visited
	for len(unvisited) > 0 {

		// get a random unvisited node
		var start int
		for k := range unvisited {
			start = k
			break
		}

		// check for cycle
		path := make(map[int]int)
		if hasCycle(start, unvisited, visiting, visited, graph, path) {
			for k, v := range path {
				cycleNodeSet[k] = true
				cycleNodeSet[v] = true
			}
		}
	}

	return cycleNodeSet
}

// Preforms a depth first search to find cycles in a graph.
// If a cycle is found, the nodes of the cycle are given in the path.
func hasCycle(curr int, unvisited, visiting, visited map[int]bool, graph map[int][]int, path map[int]int) bool {

	// have we been here before?
	if visited[curr] {
		return false
	}

	// update current vertex states
	delete(unvisited, curr)
	visiting[curr] = true

	// for each child,
	children := graph[curr]
	for i := range children {
		next := children[i]
		if unvisited[next] { // if child is unvisited, we need to recurse onto it
			path[next] = curr
			if hasCycle(next, unvisited, visiting, visited, graph, path) {
				return true
			}
		} else if visiting[next] { // if child is also in visiting state we have found a cycle.
			return true
		}
	}

	// no more children to explore out of this vertex
	delete(visiting, curr)
	visited[curr] = true
	return false
}

// Adds all dependent courses to courses.
func addDependents(courses map[int]bool, graph map[int][]int) {
	for k := range courses {
		dfs(k, courses, graph)
	}
}


func dfs(curr int, courses map[int]bool, graph map[int][]int) {
	courses[curr] = true
	children := graph[curr]
	for k := range children {
		if !courses[children[k]] {
			dfs(children[k], courses, graph)
		}
	}
}

func main() {
	courseGraph := make(map[int][]int)
	requiredCourses, courses := readPotwInput(courseGraph)

	if canGraduate(requiredCourses, courses, courseGraph) {
		fmt.Println("Good")
	} else {
		fmt.Println("Bad")
	}
}
