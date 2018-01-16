/* UWindsor CS POTW 2017
 * Week 5 - Snake Word Search
 * Adam Vandolder
 * github.com/avandolder
 *
 * C++14 compliant. Should compile on g++ 5 and up with -std=c++14 flag. */

#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// Define a single node of a Trie data structure.
struct TrieNode
{
    typedef std::shared_ptr<TrieNode> Ptr;

    bool empty() { return children.empty(); }
    bool is_end() { return !key.empty(); }
    bool has_child(char c) { return children.find(c) != children.end(); }
    void add_child(char c) { children[c] = std::make_shared<TrieNode>(); }
    auto get_child(char c) { return children[c]; }
    void remove_child(char c) { children.erase(c); }
    void add_key(std::string key) { this->key = key; }
    auto get_key() { return key; }
    void remove_key() { key.clear(); }

private:
    std::unordered_map<char, TrieNode::Ptr> children;
    std::string key;
};

// Define a basic Trie, with insertion and deletion abilities.
class Trie
{
    TrieNode::Ptr root;

public:
    Trie() : root(std::make_shared<TrieNode>()) {};

    void insert(std::string key);
    void remove(std::string key) { remove_helper(key, root, 0); }
    bool remove_helper(std::string key, TrieNode::Ptr node, int depth);
    auto get_root() { return root; }
    bool has_child(char c) { return root->has_child(c); }
    auto get_child(char c) { return root->get_child(c); }
};

// Insert a key into a trie.
void Trie::insert(std::string key)
{
    auto node = get_root();

    for (char c : key)
    {
        c = std::toupper(c);

        if (!node->has_child(c))
            node->add_child(c);

        node = node->get_child(c);
    }

    node->add_key(key);
}

// Recursive helper function that removes a key from a trie.
bool Trie::remove_helper(std::string key, TrieNode::Ptr node, int depth)
{
    char c = std::toupper(key[depth]);

    if (depth == key.size())
    {
        node->remove_key();
        return node->empty();
    }

    if (remove_helper(key, node->get_child(c), depth + 1))
    {
        node->remove_child(c);
        return !node->is_end() && node->empty();
    }

    return false;
}

// Implement a basic hashing function for pairs of integers. Used in DFS.
struct CellHasher {
    std::size_t operator()(const std::pair<int, int> &val) const {
        return val.first*31 + val.second;
    }
};

// Iterate through the grid, performing DFS whenever a character in the
// trie is found.
std::vector<std::string> find_words(auto& grid, Trie& words)
{
    std::vector<std::string> found;

    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[i].size(); j++)
            if (words.has_child(grid[i][j]))
            {
                std::unordered_set<std::pair<int, int>, CellHasher> visited;
                dfs(grid, words, found,
                    words.get_child(grid[i][j]),
                    visited, std::make_pair(i, j));
            }

    return found;
}

// Perform a depth-first search on the grid for all words starting from node.
void dfs(
    auto &grid, Trie& words, auto& found, auto node, auto& visited, auto cell)
{
    visited.insert(cell);

    if (node->is_end())
    {
        found.push_back(node->get_key());
        words.remove(node->get_key());
    }

    for (auto adj : get_adjacent(grid, node, cell))
        if (visited.find(adj.second) == visited.end())
            dfs(grid, words, found, adj.first, visited, adj.second);
}

// Find all adjacent cells that contain letters that are children of node.
std::vector<std::pair<TrieNode::Ptr, std::pair<int, int>>> get_adjacent(
    auto& grid, auto node, auto cell)
{
    std::vector<std::pair<TrieNode::Ptr, std::pair<int, int>>> adj;
    int i = cell.first, j = cell.second;

    if (j < grid[i].size()-1 && node->has_child(grid[i][j + 1]))
        adj.push_back(std::make_pair(node->get_child(grid[i][j + 1]),
                                     std::make_pair(i, j + 1)));

    if (j >= 1 && node->has_child(grid[i][j - 1]))
        adj.push_back(std::make_pair(node->get_child(grid[i][j - 1]),
                                     std::make_pair(i, j - 1)));

    if (i < grid.size()-1 && node->has_child(grid[i + 1][j]))
        adj.push_back(std::make_pair(node->get_child(grid[i + 1][j]),
                                     std::make_pair(i + 1, j)));

    if (i >= 1 && node->has_child(grid[i - 1][j]))
        adj.push_back(std::make_pair(node->get_child(grid[i - 1][j]),
                                     std::make_pair(i - 1, j)));

    return adj;
}

// Read in the letters that make up the grid that will be searched.
auto get_grid()
{
    int r, c;
    std::cin >> r >> c;

    std::vector<std::vector<char>> grid(r, std::vector<char>(c));
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            std::cin >> grid[i][j];

    return grid;
}

// Read in the words that will be searched for, storing them in a trie.
auto get_words()
{
    int n;
    Trie words;

    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::string key;
        std::cin >> key;
        words.insert(key);
    }

    return words;
}

// Determine whether one string is less than another, case-insensitively.
// Necessary to be able to sort the strings before the final output.
bool istrlt(const std::string& s1, const std::string& s2)
{
    auto itr1 = s1.begin(), itr2 = s2.begin();
    for (; itr1 != s1.end() && itr2 != s2.end(); itr1++, itr2++)
        if (std::tolower(*itr1) < std::tolower(*itr2))
            return true;
        else if (std::tolower(*itr1) > std::tolower(*itr2))
            return false;

    if (itr1 != s1.end())
        return false;

    return true;
}

int main()
{
    auto grid = get_grid();
    auto words = get_words();
    std::vector<std::string> found = find_words(grid, words);

    sort(found.begin(), found.end(), istrlt);
    for (auto& s : found)
        std::cout << s << std::endl;

    return 0;
}