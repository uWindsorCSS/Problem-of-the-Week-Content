import java.util.*;

public class Problem1 {
    public static void main(String[]args){
        
        // input

        Scanner scan = new Scanner(System.in);

        int num = scan.nextInt();
        int[] numNuts = new int[num];

        for (int i = 0; i < num; i++){
            numNuts[i] = scan.nextInt();
        }

        int C = scan.nextInt();
        int S = scan.nextInt();

        // Now find if there are C unique pairs which sum to S

        for ( int i = 0; i < numNuts.length-1; i++){
            for (int j = i+1; j < numNuts.length; j++ ){
                if (C == 0) break;
                if (numNuts[i] + numNuts[j] == S){
                    C--;
                }
            }
        }

        if (C == 0) System.out.println("True");
        else System.out.println("False");

    }
}