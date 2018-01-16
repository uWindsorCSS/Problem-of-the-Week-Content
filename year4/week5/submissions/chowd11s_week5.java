import java.util.*;

public class potw5{
	public static void main(String[] args){
		Scanner kb = new Scanner(System.in);	//getting all input
		int R = kb.nextInt();
		int C = kb.nextInt();
		ArrayList<String> words = new ArrayList<String>();
		Node grid[][] = new Node[R][C];
		for (int i = 0;i < R;i++){
			for (int j = 0;j < C;j++){
				grid[i][j] = new Node(kb.next().toUpperCase(), i, j, 0);
			} 
		}

		int N = kb.nextInt();
		for (int i = 0;i < N;i++){
			words.add(kb.next());
		}

		ArrayList<String> foundWords = new ArrayList<String>();
		Stack<Node> search = new Stack<Node>();
		ArrayList<Node> path = new ArrayList<Node>();
		ArrayList<Node> visited = new ArrayList<Node>();
		boolean found;
		boolean moved = false;
		String currword;
		int origx;
		int origy;
		int x;
		int y;
		int pos;

		for (int h = 0;h < words.size();h++){
			found = false;
			currword = words.get(h).toUpperCase();
			x = 0;
			y = 0;
			origx = 0;
			origy = 0;
			pos = 0;
			while (x != R){
				if (grid[x][y].check(currword.substring(pos, pos + 1))){
					resetGrid(grid, R, C);
					grid[x][y].setPos(pos + 1);
					search.clear();
					search.push(grid[x][y]);	//once we've found the first letter, prepare a DFS for the rest of the word
					path.clear();
					visited.clear();
					origx = x;
					origy = y;
					while (search.empty() == false){
						Node curr = search.pop();
						x = curr.getX();
						y = curr.getY();
						path.add(curr);
						pos = curr.getPos();
						if (pos == currword.length()){
							found = true;
							break;
						}
						moved = false;
						String currlet = currword.substring(pos, pos + 1);

						//check above
						if (x != 0 && path.contains(grid[x - 1][y]) != true && visited.contains(grid[x - 1][y]) != true && grid[x - 1][y].check(currlet)){
							grid[x - 1][y].setPos(pos + 1);
							search.push(grid[x - 1][y]);
							moved = true;
						}
						//check down
						if (x != R - 1 && path.contains(grid[x + 1][y]) != true && visited.contains(grid[x + 1][y]) != true && grid[x + 1][y].check(currlet)){
							grid[x + 1][y].setPos(pos + 1);
							search.push(grid[x + 1][y]);	
							moved = true;
						}
						//check left
						if (y != 0 && path.contains(grid[x][y - 1]) != true && visited.contains(grid[x][y - 1]) != true && grid[x][y - 1].check(currlet)){
							grid[x][y - 1].setPos(pos + 1);
							search.push(grid[x][y - 1]);
							moved = true;
						}
						//check right
						if (y != C - 1 && path.contains(grid[x][y + 1]) != true && visited.contains(grid[x][y + 1]) != true && grid[x][y + 1].check(currlet)){
							grid[x][y + 1].setPos(pos + 1);
							search.push(grid[x][y + 1]);
							moved = true;
						}
						//backtrack
						if (moved == false){
							visited.add(path.remove(path.size() - 1));
						}
					}
					if (search.empty()){
						x = origx;
						y = origy;
					}
				}
				if (found == false){
					pos = 0;
					if (y < C){
						y++;
					}
					if (y == C){
						x++;
						y = 0;
					}
				}
				else{
					break;
				}
			}
			if (found == true){
				foundWords.add(words.get(h));
			}
		}
		radixSort(foundWords);
		/*Test code to make sure my sort gave the same expected result as the java collections arraylist sort
		for (int i = 0;i < foundWords.size();i++){ 
			foundWords.set(i, foundWords.get(i).toUpperCase());
		}
		Collections.sort(foundWords);
		for (int i = 0;i < foundWords.size();i++){
			System.out.println(foundWords.get(i));
		}*/
	}

	public static void resetGrid(Node [][]grid, int R, int C){
		for (int i = 0;i < R;i++){
			for (int j = 0;j < C;j++){
				grid[i][j].resetPos();
			}
		}
	}

	/* Really messy radix sort because I did it looking at wikipedia's ambiguous pseudocode trying to be smart
	its my first time doing radix sort and I got it to work without a detailed guide, so I feel kinda proud,
	but I doubt its O(mn) */
	public static List<String>[] listToBuckets(ArrayList<String> list, int base, int iteration){
		ArrayList<String>[] buckets = new ArrayList[base];
		for (int i = 0;i < buckets.length;i++){
			buckets[i] = new ArrayList();
		}

		for (int i = 0;i < list.size();i++){
			String currword = list.get(i);
			int digit = (int)(Character.toUpperCase(currword.charAt(currword.length() - 1 - iteration))); //
			buckets[90 - digit].add(currword);	//ASCII value of Z is 90
		}
		return buckets;
	}

	public static ArrayList<String> bucketsToList(List<String>[] buckets){
		ArrayList<String> list = new ArrayList<String>();
		for (int i = 0;i < buckets.length;i++){
			for (int j = 0;j < buckets[i].size();j++){
				list.add(buckets[i].get(j));
			}
		}
		return list;
	}

	public static void radixSort(ArrayList<String> foundWords){
		int longest = 0;
		for (int i = 0;i < foundWords.size();i++){
			if (foundWords.get(i).length() > longest){
				longest = foundWords.get(i).length();
			}
		}
		for (int i = 0;i < foundWords.size();i++){
			if (foundWords.get(i).length() < longest){
				int diff = longest - foundWords.get(i).length();
				for (int j = 0;j < diff;j++){
					String currword = foundWords.get(i);
					//pad right with @ for words smaller than the longest word to place them last depending on the iteration
					foundWords.set(i, currword + "@");
				}
			}
		}
		for (int i = 0;i<longest;i++){
			foundWords = bucketsToList(listToBuckets(foundWords, 27, i));
		}

		for (int i = 0;i < foundWords.size();i++){
			foundWords.set(i,foundWords.get(i).replace("@", ""));
		}

		for (int i = foundWords.size();i > 0 ;i--){
			System.out.println(foundWords.get(i - 1));
		}
	}
}

class Node{	//store the information of each letter in the grid 
	String c;	//letter being stored
	int x;		//x coordinate
	int y;		//y coordinate
	int pos;	//position in the word currently being searched
	public Node(String c, int x, int y, int pos){
		this.c = c;
		this.x = x;
		this.y = y;
		this.pos = pos;	//need to know the letter that was being searched for when looking at a given node
	}

	public boolean check(String c){
		if (c.equals(this.c) == true){
			return true;
		}
		return false;
	}

	public int getX(){
		return x;
	}

	public int getY(){
		return y;
	}

	public int getPos(){
		return pos;
	}

	public void setPos(int pos){
		this.pos = pos;
	}

	public void resetPos(){
		pos = 0;
	}

	public String toString(){
		return c;
	}
}