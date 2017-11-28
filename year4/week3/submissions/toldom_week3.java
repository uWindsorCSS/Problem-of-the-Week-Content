//UWindsor POTW3 - UNKoolKatz
//Created by Marcus Toldo on Monday, November 19, 2017
//Last edited on Thursday, November 23, 2017

import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int numberOfInputs = sc.nextInt();
        int first, second;
        ArrayList<KoolKat> KoolKatz = new ArrayList<>();

        /* Populates group members and adds
        each persons corresponding friendships*/
        for (int i = 0; i < numberOfInputs; i++) {

            first = sc.nextInt();
            second = sc.nextInt();

            //Do twice
            for (int j = 0; j < 2; j++) {
                if (j == 0) {
                    CheckAdd(first, second, KoolKatz);
                } else {
                    CheckAdd(second, first, KoolKatz);
                }
            }
        }

        int usr;
        int postNum;
        int like;
        numberOfInputs = sc.nextInt();

        for (int i = 0; i < numberOfInputs; i++){
            usr = sc.nextInt();
            postNum = sc.nextInt();
            like = sc.nextInt();

            for (KoolKat temp : KoolKatz) {
                if (temp.ID == usr) {
                    temp.AddPost(postNum, like);
                }
            }
        }

        int keyUser = sc.nextInt();
        int threshold = sc.nextInt();

        for (KoolKat temp : KoolKatz) {

            if (temp.ID == keyUser) {
                temp.DetermineNotifications(threshold, KoolKatz);
            }
        }
    }

    /*
    Input: Recieves two ints (the person and their friend), as well as the AL of group members as input
    Output: void fn
    Purpose: Checks if the person is already a member of the group or not, if not will add them and set up
    friendships, if they are will just set up the friendship
     */
    private static void CheckAdd(int person, int friend, ArrayList<KoolKat> KoolKatz) {

        boolean isIn = false;

        for (KoolKat temp : KoolKatz) {
            if (temp.ID == person) {
                isIn = true;
            }
        }

        if (isIn) {
            for (KoolKat temp : KoolKatz) {
                if (temp.ID == person) {
                    temp.AddFriend(friend);
                    break;
                }
            }
        } else {
            KoolKat temp = new KoolKat(person);
            temp.AddFriend(friend);
            KoolKatz.add(temp);
        }

    }
}

class KoolKat {

    private ArrayList<Integer> friends = new ArrayList<>();
    private ArrayList<Integer> likedPosts = new ArrayList<>();
    private ArrayList<Integer> dislikedPosts = new ArrayList<>();
    int ID;

    KoolKat(int ID) {
        this.ID = ID;
    }

    void AddFriend(int f) {
        friends.add(f);
    }

    void AddPost(int p, int l) {

        if (l == 1) {
            likedPosts.add(p);
        } else {
            dislikedPosts.add(p);
        }
    }

    void DetermineNotifications(int t, ArrayList<KoolKat> KoolKatz) {

        ArrayList<Integer> friendsLikedPosts = new ArrayList<>();
        ArrayList<Integer> friendsDislikedPosts = new ArrayList<>();
        ArrayList<Integer> worthyPosts = new ArrayList<>();
        ArrayList<Integer> unworthyPosts = new ArrayList<>();

        for (int i : friends) {
            for (KoolKat temp : KoolKatz) {
                if (temp.ID == i) {
                    friendsLikedPosts.addAll(temp.likedPosts);
                    friendsDislikedPosts.addAll(temp.dislikedPosts);
                }
            }
        }

        int count = 0;

        for (int i : friendsLikedPosts) {

            if (!worthyPosts.contains(i) && !unworthyPosts.contains(i)) {
                for (int j : friendsLikedPosts) {
                    if (i == j) {
                        count++;
                    }
                }

                for (int j : friendsDislikedPosts) {
                    if (i == j) {
                        count--;
                    }
                }

                if (count >= t) {
                    worthyPosts.add(i);
                } else {
                    unworthyPosts.add(i);
                }

                count = 0;
            }
        }

        for (int i : worthyPosts) {
            System.out.print(i + "\n");
        }
    }
}
