class PostQualifier:

    def __init__(self, u, t):
        self.number = u
        self.threshold = t
        self.friends = set()
        self.post_like_counts = {}

    def collect_friends(self, friend_edges):
        for friendship in friend_edges:
            if friendship[0] == self.number:
                self.friends.add(friendship[1])
            elif friendship[1] == self.number:
                self.friends.add(friendship[0])

    def map_relevant_post_likes(self, likes_edges):
        for like in likes_edges:
            if like[0] in self.friends:
                self.post_like_counts[like[1]] = self.post_like_counts[like[1]] + like[2] if like[1] in self.post_like_counts else like[2]

    def determine_qualifying_posts(self):
        for post, count in self.post_like_counts.items():
            if count >= self.threshold:
                print(post)

def main():
    friend_edges = []
    likes_edges = []
    N = int(input())
    for x in range(N):
        friend_edges.append(list(map(int, input().split())))
    M = int(input())
    for x in range(M):
        likes_edges.append(list(map(int, input().split())))
    u,t = map(int, input().split())

    pq = PostQualifier(u, t)
    pq.collect_friends(friend_edges)
    pq.map_relevant_post_likes(likes_edges)
    pq.determine_qualifying_posts()

if __name__ == '__main__': main()
