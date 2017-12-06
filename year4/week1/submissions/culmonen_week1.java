// Week1.java
// Nicholas Culmone

import java.util.*;

public class Week1{
	public static void main(String[]args){
		Scanner kb = new Scanner(System.in);

		int n = kb.nextInt();
		kb.nextLine();

		int[]holes = new int[n];
		for(int i=0;i<n;i++){
			holes[i] = kb.nextInt();
		}
		kb.nextLine();

		int c = kb.nextInt();
		int s = kb.nextInt();
		int count = 0;

		for(int i=0;i<n-1;i++){
			for(int j=i+1;j<n;j++){
				if(holes[i] + holes[j] == s){
					count ++;
					if(count == c){
						System.out.println("True");
						return;
					}
				}
			}
		}
		System.out.println("False");
	}
}