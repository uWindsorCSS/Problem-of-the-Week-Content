import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;


public class Main{
    public static void main(String[]args){
        Scanner kb = new Scanner(System.in);
        int n= kb.nextInt();
        kb.nextLine();
        Map<Integer, User>map=new HashMap<>();
        String line;
        String[]split;
        int a,b,c;

		for(int i=0;i<n;i++){
		    line=kb.nextLine();
		    split=line.split(" ");
		    a=Integer.parseInt(split[0]);
		    b=Integer.parseInt(split[1]);
            if(!map.containsKey(a)){
                map.put(a, new User(a));
            }

		    if(!map.containsKey(b)){
                map.put(b, new User(b));
            }
            map.get(a).addFriend(map.get(b));
            map.get(b).addFriend(map.get(a));

		}
		n=kb.nextInt();
        kb.nextLine();
        Map<Integer, Post>map2=new HashMap<>();
        ArrayList<Integer>postids=new ArrayList<>();
        for(int i=0;i<n;i++){
            line=kb.nextLine();
            split=line.split(" ");
            a=Integer.parseInt(split[0]);
            b=Integer.parseInt(split[1]);
            c=Integer.parseInt(split[2]);
            if(!map2.containsKey(b)){
                map2.put(b,new Post((b)));
                postids.add(b);
            }

            if(c==1){
                map2.get(b).like(map.get(a));
            }
            else{
                map2.get(b).dislike(map.get(a));
            }

        }
        Post tmp;
        int count;
        line=kb.nextLine();
        split=line.split(" ");
        a=Integer.parseInt(split[0]);
        b=Integer.parseInt(split[1]);
        for(int p: postids){
            tmp=map2.get(p);
            tmp.valid(map.get(a),b);

        }
    }
}
class User{
    private int id;
    private ArrayList<User>friends;

    public User(int n){
        id=n;
        friends=new ArrayList<>();
    }

    public void addFriend(User u){
        friends.add(u);
    }
    public int getId(){
        return id;
    }

    public ArrayList<User> getFriends() {
        return friends;
    }
}
class Post{
    private int id, count;
    private ArrayList<User>likedby=new ArrayList<>();
    private ArrayList<User>dislikedby=new ArrayList<>();
    public Post(int n){
        id=n;
    }
    public void like(User u){
        likedby.add(u);
    }
    public void dislike(User u){
        dislikedby.add(u);
    }
    public void valid(User u, int n){
        count=0;
        for(User user : u.getFriends()){
            if(likedby.contains(user))
                count++;
            else if(dislikedby.contains(user))
                count--;
        }
        if(count>=n)
            System.out.println(id);
    }
}