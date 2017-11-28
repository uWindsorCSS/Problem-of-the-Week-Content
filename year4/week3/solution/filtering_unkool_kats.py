#
# POTW Year 4 Week 3 - Filtering Unkool Kats
# Joel Rorseth
#

from collections import defaultdict

# This problem is not especially difficult. You must, in some way,
# read in and store ALL info before filtering. Most of the work
# is reading and storing in proper data structures


def main():

    n = int(input())
    friends = defaultdict(set)

    # Read in all friendships
    # We do not yet know the user we will actually care about

    for i in range(n):
        a, b = [int(n) for n in input().split(' ')]
        friends[a].add(b)
        friends[b].add(a)

    # We will have 2 maps, mapping users to posts if liked or disliked
    m = int(input())
    likes = defaultdict(set)
    dislikes = defaultdict(set)

    # Read in all social interactions
    for j in range(m):
        user, post, vote = [int(n) for n in input().split(' ')]
        likes[post].add(user) if vote == 1 else dislikes[post].add(user)

    # Read in user of interest and like threshold
    user, thresh = [int(n) for n in input().split(' ')]

    # You may (safely) calculate ratio only for posts that were liked
    # Any exlusivly disliked will never make the cut anyway

    for post, likers in likes.items():

        n_likers = len([l for l in likers if l in friends[user]])
        n_dislikers = len([l for l in dislikes[post] if l in friends[user]])

        # Avoid counting posts that have no interactions
        if (n_likers == 0 and n_dislikers == 0):
            continue

        if (n_likers - n_dislikers >= thresh):
            print(post)

main()
