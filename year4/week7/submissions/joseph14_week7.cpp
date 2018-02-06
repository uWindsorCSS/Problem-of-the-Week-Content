#include <iostream>
#include <algorithm>

int check(std::string main, std::string toCheck){
	int differences = 0;
	if (main.length() != toCheck.length()) return 0;

	transform(main.begin(), main.end(), main.begin(), ::toupper);
	transform(toCheck.begin(), toCheck.end(), toCheck.begin(), ::toupper);
	if (main == toCheck) return 0;

	for (int i = 0; i < main.length(); i++){
		char mainChar = main.at(i);
		char toCheckChar = toCheck.at(i);
		if (mainChar != toCheckChar) differences++;
	}

	if (differences <= 1) return 1;
	else return 0;
}

int main(){
	
	int N = 0, M = 0;
	std::cin >> N;
	std::string dictionary[N];
	int goodOrBad = 0;

	for (int i = 0; i < N; i++){
		std::cin >> dictionary[i];
	}

	std::cin >> M;
	std::string words[M];
	for (int i = 0; i < M; i++){
		std::cin >> words[i];
	}

	for (int i = 0; i < M; i++){
		for (int j = 0; j < N; j++){
			goodOrBad += check(dictionary[j], words[i]);
		}
		if (goodOrBad > 0) std::cout << "Yes" << std::endl;
		else std::cout << "No" << std::endl;
		goodOrBad = 0;
	}
}
