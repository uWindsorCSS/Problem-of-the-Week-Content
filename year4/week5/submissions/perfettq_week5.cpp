#include <string.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <unordered_map>
#include <vector>

// An empty list of pairs.
static const std::vector<std::pair<int, int>> kEmptyLocationVector;

// Two pairs are neighbours if they differ by 1 in one dimension and zero in the
// other.
bool neighbours(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
  int row_diff = std::abs(p1.first - p2.first);
  int col_diff = std::abs(p1.second - p2.second);
  // This seems like it could be row_diff ^ col_diff, but situations like
  // row_diff = 2 and col_diff = 3 break that.
  return (row_diff == 0 && col_diff == 1) || (row_diff == 1 && col_diff == 0);
}

// Look up |key| and |map| and return |def| if it is not found.
template <typename Map>
const typename Map::mapped_type& get_or_default(
    const Map& map, const typename Map::key_type& key,
    const typename Map::mapped_type& def) {
  const auto iter = map.find(key);
  return iter == map.end() ? def : iter->second;
}

// Convert the input string to upper case.
std::string to_uppercase(const std::string& input) {
  std::string output;
  output.resize(input.size(), 0);
  std::transform(input.begin(), input.end(), output.begin(),
                 [](const char c) { return std::toupper(c); });
  return output;
}

// Try to spell the word using all neighbouring positions of the next character.
// Stop once you've reached the end of the word.
bool can_spell_word(
    const std::string& word, const unsigned current_index,
    std::set<std::pair<int, int>>& used, const std::pair<int, int>& current_pos,
    const std::unordered_map<char, std::vector<std::pair<int, int>>>
        inverted_index) {
  if (current_index == word.size() - 1) {
    return true;
  }

  const auto next_index = current_index + 1;
  const auto& next_positions =
      get_or_default(inverted_index, word[next_index], kEmptyLocationVector);
  for (const auto& position : next_positions) {
    if (!used.count(position) && neighbours(current_pos, position)) {
      used.insert(position);
      if (can_spell_word(word, next_index, used, position, inverted_index)) {
        return true;
      }
      used.erase(position);
    }
  }

  return false;
}

// Kicks off the recursive calls.
bool can_spell_word(
    const std::string& word,
    const std::unordered_map<char, std::vector<std::pair<int, int>>>
        inverted_index) {
  const auto& positions =
      get_or_default(inverted_index, word.front(), kEmptyLocationVector);
  return std::any_of(
      positions.begin(), positions.end(),
      [&word, &inverted_index](const std::pair<int, int>& position) {
        std::set<std::pair<int, int>> used{position};
        return can_spell_word(word, 0, used, position, inverted_index);
      });
}

template <template <class> class Compare>
struct CaseInsensitiveCompare {
  bool operator()(const std::string& s1, const std::string& s2) const {
    for (unsigned current_index = 0;
         current_index < s1.size() && current_index < s2.size();
         ++current_index) {
      const char a = std::tolower(s1[current_index]);
      const char b = std::tolower(s2[current_index]);
      if (a != b) {
        return cmp_(a, b);
      }
    }

    const auto end = std::min(s1.size(), s2.size());
    const char a = std::tolower(s1[end]);
    const char b = std::tolower(s2[end]);
    return cmp_(a, b);
  }

  Compare<char> cmp_;
};

int main() {
  int rows, cols;
  std::cin >> rows >> cols;

  std::unordered_map<char, std::vector<std::pair<int, int>>> inverted_index;
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      char c;
      std::cin >> c;
      inverted_index[c].push_back({row, col});
    }
  }

  std::set<std::string, CaseInsensitiveCompare<std::less>> ordered_results;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::string word;
    std::cin >> word;
    if (can_spell_word(to_uppercase(word), inverted_index)) {
      ordered_results.insert(word);
    }
  }

  std::copy(ordered_results.begin(), ordered_results.end(),
            std::ostream_iterator<std::string>(std::cout, "\n"));
}