//
// Squirrel Frenzy
// uWindsor POTW 2017 Week 1
//

#include <iostream>
#include <set>
#include <unordered_map>
#include <utility>


// Solution - O(n)
void find_pairs(std::unordered_map<int,int> & chestnuts, int c, int s) {

    int pairs_found = 0;

    std::unordered_map<int, int> used;
    std::set<std::pair<int,int>> pairs{};

    // Iterate over each hole - O(n)
    for (const auto & hole: chestnuts) {
       
        int nuts = hole.first;
        int count = hole.second;

        // If any hole has 'difference' chestnuts, add pair (sorted) - O(1)
        if (chestnuts.find(s-nuts) != chestnuts.end()) {
            if (nuts < (s-nuts)) pairs.insert({nuts, s-nuts});
            if (nuts > (s-nuts)) pairs.insert({s-nuts, nuts});
        }
    }


    // Iterate over each unique pair - O(p) where p is number of pairs
    for (const auto & pair: pairs) 
        pairs_found += chestnuts[pair.first] * chestnuts[pair.second];
     
    std::cout << ((pairs_found >= c) ? "True" : "False") << std::endl;
}


int main() {

    std::unordered_map<int,int> chestnuts;
    int n, c, s, h;

    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        
        std::cin >> h;
        chestnuts[h]++;
    }

    std::cin >> c >> s;
    find_pairs(chestnuts, c, s);
}
