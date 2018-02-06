#include <iostream>

int main(){

	int N, S, C;

	std::cin >> N;

	int holes[N];

	for (int i = 0; i < N; i++){
		std::cin >> holes[i];
	}

	std::cin >> C >> S;
	int pairs = 0;
	for (int i = 0; i < N - 1; i++){
		for (int j = i + 1; j < N; j++){
			if (holes[i] + holes[j] == S) pairs++;
		}
	}

	if (pairs >= C) std::cout << "True" << std::endl;
	else std::cout << "False" << std::endl;

}