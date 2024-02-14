package main

import (
	"fmt"
)

const WordToCheck string = "check"

func main() {
	var t int
	fmt.Scanf("%d\n", &t)

	input := make([]string, t)
	for i := 0; i < t; i++ {
		var T string
		fmt.Scanf("%s\n", &T)
		input[i] = T
	}

	for i := 0; i < t; i++ {
		if len(input[i]) != 7 {
			fmt.Println("No")
			continue
		} else {
			var flag bool = true
			var bT []byte = []byte(input[i])
			var bWordToCheck []byte = []byte(WordToCheck)

			sol := map[byte]byte{}
			for j := 0; j < 7; j++ {
				sol[bT[j]] += 1
			}

			check := map[byte]byte{}
			for j := 0; j < 7; j++ {
				check[bWordToCheck[j]] += 1
			}

			for j := 0; j < 7; j++ {
				if sol[bWordToCheck[j]] != check[bWordToCheck[j]] {
					flag = false
				} else {
					continue
				}
			}

			if flag == false {
				fmt.Println("No")
				continue
			} else {
				fmt.Println("Yes")
			}
		}
	}
}
