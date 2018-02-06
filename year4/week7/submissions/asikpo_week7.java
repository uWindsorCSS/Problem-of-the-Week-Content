import java.util.*;

public class Autocorrect {
	private static ArrayList<String> dictionary;
	
	public static boolean autoCorrect(String typedWord){
		int charDifference = 0;
		for(String word: dictionary){
			if(word.length() != typedWord.length()){
				continue;
			}
			// check for character difference
			for(int i=0; i<word.length(); i++){
				if(word.toLowerCase().charAt(i) != typedWord.toLowerCase().charAt(i)){
					charDifference++;
				}
			}
			if(charDifference == 1){
				return true;
			}
			charDifference = 0;
		}
		return false;
	}
	
	public static void main(String[] args) {
		int dictionarySize;
		int wordSize;
		String output = "";
		dictionary = new ArrayList<String>();
		
		Scanner reader = new Scanner(System.in);
		dictionarySize = reader.nextInt();
		
		// read dictionary words
		for(int i = 1; i<=dictionarySize; i++){
			String dicWord = reader.next();
			dictionary.add(dicWord);
		}

		wordSize = reader.nextInt(); // read input word size
		
		for(int i=1; i<=wordSize; i++){
			String typedWord = reader.next();
			if(autoCorrect(typedWord)){
				output += "Yes" + "\n";
			}
			else{
				output += "No" + "\n";
			}
		}
		
		System.out.println("\n" + output);
	}

}