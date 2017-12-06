/*
	potw1.java
	Shahir Chowdhury
	2017-11-21
*/

import java.util.*;

public class potw1{
	public static void main (String[] args){
		Scanner kb = new Scanner(System.in);
		int N = kb.nextInt();
		int[] nuts = new int[N];

		for (int i = 0;i < N;i++){
			nuts[i] = kb.nextInt();
		}
		int C = kb.nextInt();
		int S = kb.nextInt();
		int c = 0;

		for (int i = 0;i < N - 1;i++){
			for (int j = i + 1;j < N;j++){
				if (nuts[i] + nuts[j] == S){
					c++;
				}
			}
		}
		if (c >= C){
			System.out.println("True");
		}
		else{
			System.out.println("False");
		}
	}
}