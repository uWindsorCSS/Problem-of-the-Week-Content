#include <cctype>
#include <iostream>
#include <string>
using namespace std;

// A trie-like structure with a backtracking search
class Trie {
	private:
		Trie *contents[26];
		bool end;
	public:
		Trie() {
			end = false;
			for(auto &i: contents) {
				i = nullptr;
			}
		}
		void insert(string s) {
			if(s.length() == 0) {
				end = true;
				return;
			}
			int n = toupper(s[0]) - 'A';
			if(contents[n] == nullptr) {
				contents[n] = new Trie();
			}
			return contents[n]->insert(s.substr(1));
		}
		// Is the verbatim word in the trie?
		bool find(string s) {
			if(s.length() == 0) {
				return end;
			}
			int n = toupper(s[0]) - 'A';
			if(contents[n] == nullptr) {
				return false;
			}
			return contents[n]->find(s.substr(1));
		}
		// Is some variation of it?
		bool search(string s, int errs=0) {
			if(errs > 1) {
				return false;
			}
			if(s.length() == 0) {
				return end && errs == 1;
			}
			int n = toupper(s[0]) - 'A';
			for(int i = 0; i < 26; ++i) {
				if(contents[i] == nullptr) {
					continue;
				}
				if(contents[i]->search(s.substr(1), i == n ? errs : errs+1)) {
					return true;
				}
			}
			return false;
		}
};

int main(int argc, char **argv) {
	ios_base::sync_with_stdio(false);
	Trie *words = new Trie;
	string buffer;
	getline(cin, buffer);
	int n = stoi(buffer);
	for(int i = 0; i < n; ++i) {
		getline(cin, buffer);
		words->insert(buffer);
	}
	getline(cin, buffer);
	n = stoi(buffer);
	for(int i = 0; i < n; ++i) {
		getline(cin, buffer);
		cout << (!words->find(buffer) && words->search(buffer) ? "Yes" : "No") << endl;
	}
	return 0;
}
