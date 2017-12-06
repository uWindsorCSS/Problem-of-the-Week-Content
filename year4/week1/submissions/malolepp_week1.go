// University of Windsor Problem of the Week
// Fall 2017 - Problem 1
// Patrick Malolepszy
// malolepp@uwindsor.ca
package main

import (
	"fmt"
)

func main() {
	var n, c, s, temp int
	chestnutCounts := make(map[int]int)
	count := 0

	fmt.Scan(&n)

	for i := 0; i < n; i++ {
		fmt.Scan(&temp)
		chestnutCounts[temp]++
	}

	fmt.Scan(&c, &s)

	for key := range chestnutCounts {
		lookingFor := s - key
		if chestnutCounts[lookingFor] > 0 {
			count++
		}
		if count >= c {
			fmt.Println("True")
			return
		}
	}

	fmt.Println("False")
}
