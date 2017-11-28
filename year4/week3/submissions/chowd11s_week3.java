/*
	potw3.java
	Shahir Chowdhury
	2017-11-26
*/
import java.util.*;

public class potw3{
	private class Person{
		private int label;
		private ArrayList<Integer> friendships = new ArrayList<Integer>();

		public Person(int label){
			this.label = label;
		}

		public int getLabel(){
			return label;
		}

		public void addFriend(int x){
			friendships.add(x);
		}

		public ArrayList<Integer> getFriendShips(){
			return friendships;
		}
	}

	private class Post{
		private int label;
		private int likes = 0;
		private ArrayList<Integer> likers  = new ArrayList<Integer>();
		private ArrayList<Integer> dislikers = new ArrayList<Integer>();

		public Post(int label){
			this.label = label;
		}

		public int getLabel(){
			return label;
		}

		public void addLiker(int x){
			likers.add(x);
		}

		public void addDisliker(int x){
			dislikers.add(x);
		}

		public ArrayList<Integer> getLikers(){
			return likers;
		}

		public ArrayList<Integer> getDislikers(){
			return dislikers;
		}
	}
	public static void main (String[] args){
		potw3 potw3 = new potw3();
		Scanner kb = new Scanner (System.in);
		int n = kb.nextInt();
		ArrayList<Person> people = new ArrayList<Person>();
		ArrayList<Post> posts = new ArrayList<Post>();
		boolean oldAPerson = false;
		boolean oldBPerson = false;
		boolean oldPost = false;

		//store all the people and their friends
		for (int i = 0;i < n;i++){
			int a = kb.nextInt();
			int b = kb.nextInt();
			if (people.isEmpty()){ 
				Person newguy = potw3.new Person(a);
				Person otherguy = potw3.new Person(b);
				newguy.addFriend(b);
				otherguy.addFriend(a);
				people.add(newguy);
				people.add(otherguy);
			}
			else{
				for (int j = 0;j < people.size();j++){
					if (people.get(j).getLabel() == a){
						people.get(j).addFriend(b);
						oldAPerson = true;
					}
					if (people.get(j).getLabel() == b){
						people.get(j).addFriend(a);
						oldBPerson = true;
					}
				}
				if (oldAPerson == false){
					people.add(potw3.new Person(a));
					people.get(people.size() - 1).addFriend(b);
				}
				if (oldBPerson == false){
					people.add(potw3.new Person(b));
					people.get(people.size() - 1).addFriend(a);
				}
				oldAPerson = false;
				oldBPerson = false;
			}
		}

		//store all posts and their likers and dislikers
		int m = kb.nextInt();

		for (int i = 0;i < m;i++){
			int x = kb.nextInt();
			int y = kb.nextInt();
			int z = kb.nextInt();
			if (posts.isEmpty()){
				Post newPost = potw3.new Post(y);
				if (z == 1){
					newPost.addLiker(x);
				}
				else{
					newPost.addDisliker(x);
				}
				posts.add(newPost);
			}
			else{
				for (int j = 0;j < posts.size();j++){
					if (posts.get(j).getLabel() == y){
						if (z == 1){
							posts.get(j).addLiker(x);
						}
						else{
							posts.get(j).addDisliker(x);
						}
						oldPost = true;
					}
				}
				if (oldPost == false){
					Post newPost = potw3.new Post(y);
					if (z == 1){
						newPost.addLiker(x);
					}
					else{
						newPost.addDisliker(x);
					}
					posts.add(newPost);
				}
				oldPost = false;	
			}
		}

		//get the user and the threshhold
		int u = kb.nextInt();
		int t = kb.nextInt();
		ArrayList<Post> important = new ArrayList<Post>();
		Person target = null;
		for (int i = 0;i < people.size();i++){
			if (people.get(i).getLabel() == u){
				target = people.get(i);
				break;
			}
		}
		
		//test each post to see if it has more likes than dislikes by friends of the target user
		for (int i = 0;i < posts.size();i++){
			int likes = 0;
			int dislikes = 0;
			Post temp = posts.get(i);
			ArrayList<Integer> likers = temp.getLikers();
			ArrayList<Integer> dislikers = temp.getDislikers();
			for (int j = 0;j < likers.size();j++){
				if (target.getFriendShips().size() > 0){
					if (target.getFriendShips().contains(likers.get(j))){
						likes++;
					}
				}
			}
			for (int j = 0;j< dislikers.size();j++){
				if (target.getFriendShips().size() > 0){
					if (target.getFriendShips().contains(dislikers.get(j))){
						dislikes++;
					}
				}
			}
			if ((likes - dislikes) >= t){
				important.add(temp);
			}
		}
		for (int i = 0;i < important.size();i++){
			System.out.println(important.get(i).getLabel());
		}
	}
}