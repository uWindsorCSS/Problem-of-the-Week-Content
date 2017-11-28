//Hassan Arshad
import java.util.*;
import java.io.*;

public class Week3{
	public static void main(String[] args){
		int m, i, n, u, t;
		Scanner kb = new Scanner(System.in);

		m = kb.nextInt();

		int[] f1 = new int[m];
		int[] f2 = new int[m];

		//store the firendships
		for(i = 0; i < m; i++){
			f1[i] = kb.nextInt();
			f2[i] = kb.nextInt();
		}

		n = kb.nextInt();

		//store the liked/disliked posts by different users
		int[] cons = new int[n*2];

		for(i = 0; i < n*2; i+=2){
			cons[i] = kb.nextInt();

			//if a like the post number will be positive otherwise it will be negative
			cons[i+1] = kb.nextInt() * kb.nextInt();	
		}

		u = kb.nextInt();
		t = kb.nextInt();

		List<Integer> fr = new ArrayList<Integer>();

		//store all the specified user's friends in an arraylist
		for(i = 0; i < m; i++){
			if(f1[i] == u){
				fr.add(f2[i]);
			}
			else if(f2[i] == u){
				fr.add(f1[i]);
			}
		}

		i = 0;
		int postnum, count = 0;

		//go through the cons array and find which post should be printed
		while(i < n*2){
			if(fr.contains(cons[i])){

				if(cons[i+1] < 0){
					count-=2;
					cons[i+1] *= -1;
				}
				postnum = cons[i+1];
				count++;

				for(int j = i+2; j < n*2; j+=2){
					if(fr.contains(cons[j])){
						if(cons[j+1] == postnum){
							count++;
							cons[j] = -1;
						}
						if(cons[j+1] == postnum*-1){
							count--;
							cons[j] = -1;
						}
					}
					else{
						cons[j] = -1;
					}
				}
				if(count >= t){
					System.out.println(postnum);
				}
				count = 0;

			}
			i+=2;
		}
	}
}