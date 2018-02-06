/* UWindsor CS POTW 2017
 * Week 7 - Damn Autocorrect
 * Adam Vandolder
 * github.com/avandolder */

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

bool similar(std::string s1, std::string s2)
{
	// Words of different length are never similar.
	if (s1.size() != s2.size())
		return false;
	
	// The words should differ by exactly one character.
	bool char_differs = false;
	for (int i = 0, j = 0; i < s1.size(); ++i, ++j)
		if (std::toupper(s1[i]) != std::toupper(s2[j]))
		{
			if (char_differs)
				return false;
			else
				char_differs = true;
		}
	
	return char_differs;
}

bool autocorrect(std::vector<std::string> dictionary, std::string word)
{
	// If word is similar to any of those in the dictionary, then it can be
	// autocorrected.
	for (auto s : dictionary)
		if (similar(s, word))
			return true;
	
	return false;
}

std::vector<std::string> get_dictionary()
{
	int n;
	std::cin >> n;
	std::vector<std::string> dict(n);
	
	for (int i = 0; i < n; i++)
		std::cin >> dict[i];
	
	return dict;
}

int main(int argc, char *argv[])
{
	auto dict = get_dictionary();
	
	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		std::string word;
		std::cin >> word;
		
		std::cout << (autocorrect(dict, word) ? "Yes" : "No") << std::endl;
	}
	
	return 0;
}
