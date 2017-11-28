######################
#### INPUT ###########
######################

n = int(input())

# get all the friends
friends = {}
for i in range(0, n):
    lines = input().split(' ');
    if int(lines[0]) in friends:
        friends[int(lines[0])].append(int(lines[1]))
    else:
        friends[int(lines[0])] = [int(lines[1])]

    if int(lines[1]) in friends:
        friends[int(lines[1])].append(int(lines[0]))
    else:
        friends[int(lines[1])] = [int(lines[0])]

m = int(input())
# store all the like/dislikes
posts = {}
for i in range(0, m):
    lines = input().split(' ')

    # check if post has been added already
    if int(lines[1]) in posts:

        # check post has been disliked
        if (int(lines[2]) == -1):
            posts[int(lines[1])]['dislikes'].append(int(lines[0]))
        # check if post has been liked
        elif (int(lines[2]) == 1):
            posts[int(lines[1])]['likes'].append(int(lines[0]))

    # post has not already been added
    else:

        posts[int(lines[1])] = {'likes': [], 'dislikes': []}

        # check post has been disliked
        if (int(lines[2]) == -1):
            posts[int(lines[1])]['dislikes'].append(int(lines[0]))
        # check if post has been liked
        elif (int(lines[2]) == 1):
            posts[int(lines[1])]['likes'].append(int(lines[0]))


lines = input().split(' ');
u = int(lines[0])
t = int(lines[1])

#print(friends)
#print(posts)

################
#### LOGIC #####
################


# The algorithm should determine all posts that have been liked by at least t of u's friends.

for post in posts:
    total = 0
    for f in friends[u]:
        try:
            posts[post]['likes'].index(f)
            total += 1
            continue
        except:
            total = total

        try:
            posts[post]['dislikes'].index(f)
            total -= 1
        except:
            total = total
    if (total >= t):
        print(post)
