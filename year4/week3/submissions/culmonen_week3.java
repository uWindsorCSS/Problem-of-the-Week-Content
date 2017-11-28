// Week3.java
// Nicholas Culmone

import java.util.*;

public class Week3{
	public static void main(String[]args){
		Map<Integer,ArrayList<Integer>> people = new HashMap<Integer,ArrayList<Integer>>();
		Map<Integer,ArrayList<Integer>> likes = new HashMap<Integer,ArrayList<Integer>>();
		Map<Integer,ArrayList<Integer>> dislikes = new HashMap<Integer,ArrayList<Integer>>();
		Map<Integer,Integer> posts = new HashMap<Integer,Integer>();

		Scanner kb = new Scanner(System.in);

		int n = kb.nextInt();
		kb.nextLine();

		int a,b;
		for(int i=0;i<n;i++){
			a = kb.nextInt();
			b = kb.nextInt();
			kb.nextLine();

			if(people.get(a) == null) people.put(a,new ArrayList<Integer>());
			if(people.get(b) == null) people.put(b,new ArrayList<Integer>());

			people.get(a).add(b);
			people.get(b).add(a);
		}

		int m = kb.nextInt();
		kb.nextLine();

		int g,p,s;
		for(int i=0;i<m;i++){
			g = kb.nextInt();
			p = kb.nextInt();
			s = kb.nextInt();
			kb.nextLine();

			if(likes.get(g) == null) likes.put(g, new ArrayList<Integer>());
			if(dislikes.get(g) == null) dislikes.put(g, new ArrayList<Integer>());

			if(s == 1) likes.get(g).add(p);
			else if(s == -1) dislikes.get(g).add(p);
		}

		int guy = kb.nextInt();
		int thresh = kb.nextInt();

		for(int i : people.get(guy)){
			if(likes.get(i) == null) likes.put(i, new ArrayList<Integer>());
			if(dislikes.get(i) == null) dislikes.put(i, new ArrayList<Integer>());

			for(int j : likes.get(i)){
				if(posts.get(j) == null) posts.put(j,0);
				posts.put(j, posts.get(j) + 1);
			}
			for(int j : dislikes.get(i)){
				if(posts.get(j) == null) posts.put(j,0);
				posts.put(j, posts.get(j) - 1);
			}
		}

		for(Map.Entry<Integer,Integer> entry : posts.entrySet()){
			if(entry.getValue() >= thresh) System.out.println(entry.getKey());
		}
	}
}