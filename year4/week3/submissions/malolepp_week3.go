/*POTW #3 - Fall 2017
Post Notification
Patrick Malolepszy */
package main

import (
	"fmt"
)

// postNotification returns a slice of posts which should be notified to the given user.
func postNotification(friends, likes, dislikes map[int][]int, user, threshold int) []int {

	friendsOfUser := friends[user]
	postCounts := make(map[int]int)

	// for each friend, count their likes/dislikes
	for i := range friendsOfUser {
		currentFriend := friendsOfUser[i]
		likedPosts := likes[currentFriend]
		dislikedPosts := dislikes[currentFriend]
		for j := range likedPosts {
			postCounts[likedPosts[j]]++
		}
		for k := range dislikedPosts {
			postCounts[dislikedPosts[k]]--
		}
	}

	// find all posts which have like/dislike ratio above threshold
	var notifications []int
	for k := range postCounts {
		if postCounts[k] >= threshold {
			notifications = append(notifications, k)
		}
	}

	return notifications
}

// using main to handle io
func main() {
	var n, m, a, b, x, y, z, u, t int
	friends := make(map[int][]int)

	// input all friendships
	fmt.Scan(&n)
	for i := 0; i < n; i++ {
		fmt.Scan(&a, &b)
		friends[a] = append(friends[a], b)
		friends[b] = append(friends[b], a)
	}

	// input all likes/dislikes
	fmt.Scan(&m)
	likes := make(map[int][]int)
	dislikes := make(map[int][]int)
	for i := 0; i < m; i++ {
		fmt.Scan(&x, &y, &z)
		if z == 1 {
			likes[x] = append(likes[x], y)
		} else {
			dislikes[x] = append(dislikes[x], y)
		}
	}

	// input user, and post like/dislike threshold
	fmt.Scan(&u, &t)

	// output notifications
	notifications := postNotification(friends, likes, dislikes, u, t)
	for i := range notifications {
		fmt.Println(notifications[i])
	}
}
