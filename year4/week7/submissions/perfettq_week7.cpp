#include <algorithm>
#include <experimental/optional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

// Some aliases for using std::optional. optional is out of experimental as of
// C++17, but I wasn't sure how updated the graders compiler would be.
template <typename T>
using Optional = std::experimental::optional<T>;
const auto Empty = std::experimental::nullopt;

// Attempt to fetch the value from |map| associated with |key|. If no value
// is associated with |key|, |default_value| will be returned. Note that this
// function returns a const& to the mapped type, so ensure the default value
// is not a temporary.
template <typename Map>
const typename Map::mapped_type& find_or_default(
    const Map& map, const typename Map::key_type& key,
    const typename Map::mapped_type& default_value) {
  const auto it = map.find(key);
  return it == map.end() ? default_value : it->second;
}

// A trie node. Each entry in the map represents and edge labeled with a
// character.
struct TrieNode {
  TrieNode() : word_end(false) {}

  std::unordered_map<char, std::unique_ptr<TrieNode>> children;
  bool word_end;
};

// The main Trie class.
class Trie {
 public:
  using ConstStringIter = std::string::const_iterator;

  // Insert a sequence of characters into the trie.
  void insert(ConstStringIter first, ConstStringIter last) {
    auto* current = &root_;
    for (/* empty */; first != last; ++first) {
      current = current->children.emplace(*first, std::make_unique<TrieNode>())
                    .first->second.get();
    }
    current->word_end = true;
  }

  void insert(const std::string& s) { insert(s.begin(), s.end()); }

  // Check if a string exists in the trie which is exactly one character edit
  // away from the input string. Note that inserts and deletes are not allowed,
  // only changes. For example "helr" would be considered "off by one" of
  // "helo", but not "hel" or "helrr".
  Optional<std::string> off_by_one(const std::string& s) const {
    std::string path_buffer;
    return off_by_one(&root_, path_buffer, 0, s.begin(), s.end());
  }

 private:
  Optional<std::string> off_by_one(const TrieNode* current,
                                   std::string& path_buffer, int changes,
                                   ConstStringIter first,
                                   ConstStringIter last) const {
    // Quick bail to prevent this function from going too deep into the Trie
    // when we already know such a word does not exist.
    if (changes > 1) {
      return Empty;
    }

    // If the end of the word is reached, check that the current node is a word
    // end, and exactly 1 change has been made along this path.
    if (first == last) {
      return current->word_end && changes == 1
                 ? Optional<std::string>(path_buffer)
                 : Empty;
    }

    // If the current node has an edge for the character, then continue down the
    // path without registering a change.
    if (const auto& child =
            find_or_default(current->children, *first, nullptr)) {
      path_buffer.push_back(*first);
      return off_by_one(child.get(), path_buffer, changes, ++first, last);
    }

    // Otherwise, try all children of the current node and register that this
    // charcter was changed.
    for (const auto& edge : current->children) {
      path_buffer.push_back(edge.first);
      if (const auto result = off_by_one(edge.second.get(), path_buffer,
                                         changes + 1, std::next(first), last)) {
        return result;
      }
      path_buffer.pop_back();
    }

    return Empty;
  }

  TrieNode root_;
};

// Convert the input string to lowercase in place.
void convert_to_lower_case(std::string* s) {
  std::transform(s->begin(), s->end(), s->begin(),
                 [](const char c) { return std::tolower(c); });
}

int main() {
  int dictionary_size;
  std::cin >> dictionary_size;

  Trie dictionary;
  std::string word;
  for (int i = 0; i < dictionary_size; ++i) {
    std::cin >> word;
    convert_to_lower_case(&word);
    dictionary.insert(word);
  }

  int n_queries;
  std::cin >> n_queries;
  for (int i = 0; i < n_queries; ++i) {
    std::cin >> word;
    convert_to_lower_case(&word);

    std::cout << (dictionary.off_by_one(word) ? "Yes" : "No") << std::endl;
  }
}