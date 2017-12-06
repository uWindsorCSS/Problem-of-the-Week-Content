/* POTW #2 - Fall 2017
Eye of the Storm
Patrick Malolepszy */

package main

import "fmt"

func stormEye(pressures []float32) int {

	n := len(pressures)

	// single measurement defaults to eye of the storm.
	if n == 1 {
		return 0
	}

	var sumLeft, sumRight, avgLeft, avgRight float32
	for i := 1; i < n; i++ {
		sumRight += pressures[i]
	}

	// case for first number (only check right average)
	avgRight = sumRight / float32(n-1)
	if pressures[0] <= avgRight*0.85 {
		return 0
	}

	// look at each pressure and compare with left & right averages
	for i := 1; i < n-1; i++ {
		sumLeft += pressures[i-1]
		sumRight -= pressures[i]
		avgLeft = sumLeft / float32(i)
		avgRight = sumRight / float32(n-i-1)
		if pressures[i] <= avgLeft*0.85 && pressures[i] <= avgRight*0.85 {
			return i
		}
	}

	// case for last number (only check left average)
	sumLeft += pressures[n-2]
	avgLeft = sumLeft / float32(n-1)
	if pressures[n-1] <= avgLeft*0.85 {
		return n - 1
	}

	// no eye found
	return -1
}

func main() {
	var n int
	fmt.Scan(&n)
	pressures := make([]float32, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&pressures[i])
	}
	fmt.Println(stormEye(pressures))
}