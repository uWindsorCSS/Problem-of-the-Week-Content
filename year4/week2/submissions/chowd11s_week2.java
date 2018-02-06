/*
	potw2.java
	Shahir Chowdhury
	2017-11-21
*/

import java.util.*;

public class potw2{
	public static void main (String[] args){
		Scanner kb = new Scanner(System.in);

		int N = kb.nextInt();
		int reads[] = new int[N];
		boolean truth = false;
		int truthPos = -1;

		for (int i = 0;i < N;i++){
			reads[i] = kb.nextInt();
		}
		for (int i = 0;i < N;i++){
			truth = eyeFind(reads, i);
			if (truth == true){
				truthPos = i;
				break;
			}
		}

		System.out.println(truthPos);
	}

	public static boolean eyeFind(int reads[], int pos){
		int sum1 = 0;
		int sum2 = 0;

		for (int i = 0; i < pos;i++){
			sum1 += reads[i];
		}
		for (int i = pos + 1; i < reads.length;i++){
			sum2 += reads[i];
		}

		if (sum1 == 0 && sum2 == 0){
			return true;
		}

		else if (sum1 == 0){
			sum2 = sum2 / (reads.length - 1 - pos);	// subtract 1 from the length of the array to account for the list indices starting at 0
			return sum2 * 0.85 >= reads[pos];
		}
		else if (sum2 == 0){
			sum1 = sum1 / pos;
			return sum1 * 0.85 >= reads[pos];
		}

		sum1 = sum1 / pos;
		sum2 = sum2 / (reads.length - 1 - pos );

		return (sum1 * 0.85 >= reads[pos] && sum2 * 0.85 >= reads[pos]);
	}
}