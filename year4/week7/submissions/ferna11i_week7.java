import java.util.Scanner;

public class POTW_Week7 {
    public static void main(String[] args){
        String dictionary[],words[];
        int dict_size = 0,no_words = 0;
        double weight;

        Scanner sc = new Scanner(System.in);

        //------- Get the Dictionary words ------------------
        dict_size = Integer.parseInt(sc.nextLine());
        dictionary = new String[dict_size];
        for(int i=0; i< dict_size; i++){
            dictionary[i] = sc.nextLine().toUpperCase();
        }

        //------- Get the Words for Autocorrect test case ----
        no_words = Integer.parseInt(sc.nextLine());
        words = new String[no_words];
        for(int i=0; i< no_words; i++){
            words[i] = sc.nextLine().toUpperCase();
        }

        //------ Validate and print results ------------------
        for(int i=0; i< no_words; i++){
            weight = ((double)100 / words[i].length());
            System.out.println(wordMatch(words[i],dictionary,weight) ? "Yes" : "No");
        }
    }

    public static boolean wordMatch(String word,String dictionary[], double weight){
        double percentage = 0;

            for(int i=0; i<dictionary.length; i++){
                if(word.length() != dictionary[i].length()){
                    continue;
                }else{
                    for(int j=0; j<dictionary[i].length(); j++){
                        if(word.charAt(j) == dictionary[i].charAt(j)){
                            percentage += weight; //Increase the resembance percentage
                        }
                    }

                    if(Math.round(percentage + weight) == 100){ //Check if the word is off by one letter
                        return true; //This means only one character is different
                    }
                    percentage = 0; //reset percentage
                }
            }
        return false;
    }
}