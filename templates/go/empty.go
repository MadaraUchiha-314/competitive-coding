package main

import (
	"fmt"
)

func input() {}

func solve() {}

func main() {
	var t int
	_, err := fmt.Scanf("%d", &t)
	if err != nil {
		fmt.Println("Error while scanning test cases.", err)
	}
	for i := 0; i < t; i++ {
		input()
		solve()
	}
}