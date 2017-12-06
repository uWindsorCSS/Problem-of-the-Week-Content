// Week4.java
// Nicholas Culmone

import java.util.*;

public class Week4{
	public static void main(String[]args){
		Scanner kb = new Scanner(System.in);

		int c = kb.nextInt();
		kb.nextLine();

		int n = kb.nextInt();
		kb.nextLine();

		Graph courses = new Graph();

		for(int i=0;i<n;i++){
			int t1 = kb.nextInt();
			int t2 = kb.nextInt();
			kb.nextLine();

			if(courses.get(t1) == null) courses.add(t1);
			if(courses.get(t2) == null) courses.add(t2);

			courses.addPre(t1,t2);
			courses.addPost(t2,t1);
		}

		int visited = 0;

		for(Node node : courses.getNodes()){
			if(node.getPre().size() == 0){
				Queue<Node> q = new LinkedList<Node>();
				q.add(node);

				while(q.size() > 0){
					Node v = q.remove();

					boolean preDone = true;
					for(Node p : v.getPre()){
						if(p.getVisited() == false) preDone = false;
					}

					if(v.getVisited() == false && preDone){
						v.setVisited(true);
						visited ++;

						for(Node w : v.getPost()){
							q.add(w);
						}
					}
				}
			}
		}

		if(visited >= c) System.out.println("Good");
		else System.out.println("Bad");
	}
}

class Graph{
	private ArrayList<Node> nodes;
	int size;

	public Graph(){
		nodes = new ArrayList<Node>();
		size = 0;
	}

	public void add(int n){
		Node node = new Node(n);
		nodes.add(node);
		size ++;
	}

	public void addPre(int s, int e){
		get(s).addPre(get(e));
	}
	public void addPost(int s, int e){
		get(s).addPost(get(e));
	}
	public Node get(int v){
		for(Node n : nodes){
			if(n.getVal() == v) return n;
		}
		return null;
	}
	public ArrayList<Node> getNodes(){
		return nodes;
	}
}

class Node{
	private int val;
	private ArrayList<Node> pre;
	private ArrayList<Node> post;
	private boolean visited;

	public Node(int val){
		this.val = val;
		pre = new ArrayList<Node>();
		post = new ArrayList<Node>();
		visited = false;
	}

	public void addPre(Node c){
		pre.add(c);
	}
	public void addPost(Node c){
		post.add(c);
	}
	public int getVal(){
		return val;
	}
	public ArrayList<Node> getPre(){
		return pre;
	}
	public ArrayList<Node> getPost(){
		return post;
	}
	public void setVisited(boolean v){
		visited = v;
	}
	public boolean getVisited(){
		return visited;
	}
}