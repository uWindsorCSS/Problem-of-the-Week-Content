#include <iostream>
#include <unordered_map>
#include <vector>

class User
{
    std::vector<User*> friends;
    std::vector<int> notifications;
    std::unordered_map<int, int> votes;

public:
    void add_friend(User *f);
    std::vector<User*>& get_friends();
    void add_vote(int p, int v);
    std::unordered_map<int, int>& get_votes();
    std::vector<int>& find_notifications(std::unordered_map<int, bool> posts, int t);
};

void User::add_friend(User *f)
{
    friends.push_back(f);
}

std::vector<User*>& User::get_friends()
{
    return friends;
}

void User::add_vote(int p, int v)
{
    votes[p] = v;
}

std::unordered_map<int, int>& User::get_votes()
{
    return votes;
}

std::vector<int>& User::find_notifications(std::unordered_map<int, bool> posts, int t)
{
    for (auto p : posts)
    {
        int net = 0;

        for (auto f : get_friends())
        {
            auto& votes = f->get_votes();

            if (votes.find(p.first) != votes.end())
                net += votes[p.first];
        }

        if (net >= t)
            notifications.push_back(p.first);
    }

    return notifications;
}

void get_users(std::unordered_map<int, User*>& users, int n)
{
    for (int i = 0; i < n; i++)
    {
        int a, b;
        std::cin >> a >> b;

        // If either of the users have not been encountered before, create them.
        if (users.find(a) == users.end())
            users[a] = new User();
        if (users.find(b) == users.end())
            users[b] = new User();

        users[a]->add_friend(users[b]);
        users[b]->add_friend(users[a]);
    }
}

void get_posts(std::unordered_map<int, User*>& users,
               std::unordered_map<int, bool>& posts,
               int n)
{
    for (int i = 0; i < n; i++)
    {
        int u, p, v;
        std::cin >> u >> p >> v;

        posts[p] = true;

        if (users.find(u) == users.end())
            users[u] = new User();

        users[u]->add_vote(p, v);
    }
}

int main(int argc, char *argv[])
{
    int n;

    // Get the friend relationships of the users.
    std::cin >> n;
    std::unordered_map<int, User*> users;
    get_users(users, n);

    // Get the votes on the various posts.
    std::cin >> n;
    std::unordered_map<int, bool> posts;
    get_posts(users, posts, n);

    int u, t;
    std::cin >> u >> t;
    // Find the notifications for user u that pass the threshold t.
    for (auto p : users[u]->find_notifications(posts, t))
        std::cout << p << std::endl;

    // Free the user objects created.
    for (auto u : users)
        delete u.second;

    return 0;
}