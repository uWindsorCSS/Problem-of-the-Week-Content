#include <iostream>
#include <vector>
#include <unordered_map>


// Solution - O(n)
void find_pairs(std::vector<int> & chestnuts, int c, int s) {

    int pairs_found = 0;
    std::unordered_map<int, int> seen;

    // Iterate over each hole - figure out how many holes seen so far combine
    // to make pair with current that sums to S

    for (const auto hole: chestnuts) {
 
        pairs_found += seen[s - hole];
        seen[hole] += 1;
    }

    std::cout << (pairs_found >= c ? "True" : "False") << std::endl;
}


int main() {

    std::vector<int> chestnuts;
    int n, c, s, h;

    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        
        std::cin >> h;
        chestnuts.push_back(h);
    }

    std::cin >> c >> s;
    find_pairs(chestnuts, c, s);
}