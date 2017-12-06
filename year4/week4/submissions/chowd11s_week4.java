/*
 * potw4.java
*/
import java.util.*;

public class potw4{
	public static void main (String[] args){
		ArrayList <Course> courses = new ArrayList <Course>();
		Scanner kb = new Scanner (System.in);
		int C = kb.nextInt();
		int N = kb.nextInt();
		boolean possible = true;
		int curr;
		int fulfilled = 0; 
		for (int i = 0;i < N;i++){
			int a = kb.nextInt();
			int b = kb.nextInt();
			courses.add(new Course(a, b));
		}

		ArrayList<Integer> visited = new ArrayList<Integer>();
		ArrayList<Course> prereqs = new ArrayList<Course>();
		StackGeneric <Integer> visiting = new StackGeneric<Integer>();

		//add all courses that are prequisites to another course to its prerequisite list
		for (int i = 0;i < courses.size();i++){
			for (int j = 0;j < courses.size();j++){
				if (courses.get(i).getc1() == courses.get(j).getc1() && courses.get(i) != courses.get(j)){
					courses.get(i).addPrereq(courses.get(j).getc2());
				}
			}
		}

		//add to the prerequisites list courses that have no prerequisites to begin with
		for (int i = 0;i < courses.size();i++){
			int temp = courses.get(i).getc2();
			prereqs.add(new Course(temp));
			for (int j = 0;j < courses.size();j++){
				if (courses.get(j).getc1() == temp){
					prereqs.remove(prereqs.size() - 1);
					break;
				}
			}
		}

		if (courses.size() + prereqs.size() < C){
			possible = false;
		}

		//depth first search, trying each possible prereq as a starting point
		if (possible != false){
			for (int i = 0;i < prereqs.size();i++){
				visiting.push(prereqs.get(i).getc1()); //push the first course being taken onto the stack

				//keep discovering new courses for as long as there are courses to discover
				while(visiting.isEmpty() == false){
					curr = visiting.pop();
					fulfilled++;
					visited.add(curr);
					//push onto the stack any courses the current course being analyzed allows us to take
					for (int j = 0;j < courses.size();j++){
						Course temp = courses.get(j);
						/* add the next course to visit to the visiting list only if:
							1)it is connected to the current course
							2)the next course hasn't already been visited
							3)all of the courses's prerequisites have been visited, making any course in a cycle or a child of a cycle impossible to reach */
						if (temp.getc2() == curr && visited.contains(temp.getc1()) == false && visited.containsAll(temp.getPrereqs())){
							visiting.push(temp.getc1());
						}
					}
					//stop searching once a solution has been found
					if (fulfilled >= C){
						i = prereqs.size();	
						break;
					}
				}
			}
		}

		if (fulfilled >= C){
			System.out.println("Good");
		}
		else{
			System.out.println("Bad");
		}	
	}
}

class Course{
	int c1;
	ArrayList<Integer> prereqs = new ArrayList<Integer>();
	public Course(int c1, int c2){
		this.c1 = c1;
		prereqs.add(c2);
	}
	public Course (int c1){
		this.c1 = c1;
	}

	public int getc1(){
		return c1;
	}

	//return the first listed prereq for the course, specified by the input
	public int getc2(){
		return prereqs.get(0);
	}

	public void addPrereq(int c){
		prereqs.add(c);
	}

	public boolean inPrereqs(int c){
		if (prereqs.contains(c)){
			return true;
		}
		return false;
	}

	public boolean noPrereqs(){
		return prereqs.size() == 0;
	}

	public ArrayList<Integer> getPrereqs(){
		return prereqs;
	}

	public boolean compareOp(Course other){
		if (other.c1 == c1 && other.prereqs.get(0) == prereqs.get(0)) {
			return true;
		}
		return false;
	}
}

class StackGeneric<T>{
	private class StackNode<T>{
		private T data;
		private StackNode<T> next;

		public StackNode(T data, StackNode<T> next){
			this.data = data;
			this.next = next;
		}

		public StackNode(){
			this.data = null;
			this.next = null;
		}

		public void setNext(StackNode<T> next){
			this.next = next;
		}

		public StackNode<T> getNext(){
			return next;
		}

		public void setData(T data){
			this.data = data;
		}

		public T getData(){
			return data;
		}
	}

	private StackNode<T> head;
	private int size = 0;

	public StackGeneric(){
		head = null;
	}

	public void push(T data){
		StackNode<T> newNode = new StackNode<T>(data, head);
		head = newNode; 
		size++;
	}

	public T pop(){
		StackNode<T> temp = head;
		head = head.getNext();
		size--;
		return temp.getData();
	}

	public T top(){
		return head.data;
	}

	public int getSize(){
		return size;
	}

	public boolean isEmpty(){
		return head == null;
	}

	public void empty(){
		head = null;
	}

	private StackNode<T> find(T data){
		StackNode<T> curr = head;
		while (curr != null){
			if (curr.data == data){
				return curr;
			}
			curr = curr.next;
		}
		return null;
	}

	public T findData(T data){
		return find(data).data;
	}

	public boolean contains(T data){
		return (find(data) != null);
	}

	@Override
	public String toString(){
		StackNode<T> curr = head;
		String result = "";
		int num = 0;

		if (isEmpty()){
			result += "The stack is empty!";
		}
		while (curr != null){
			result += "Item #" + num + ": " + curr.data + "\n";
			curr = curr.next;
		}

		return result;
	}
}