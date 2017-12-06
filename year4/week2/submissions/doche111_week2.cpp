/* Austin G. Docherty 18/11/2017
   POTW 2017 Week 2 - Eye of the Storm
*/

#include <iostream>

int main() {

	int n;
	std::cin >> n;

	float r[n];
	std::cin >> r[0];

	int i;
	for(i = 1; i < n; i++) {
		std::cin >> r[i]; 
		r[i] += r[i-1];
	}

	if( n == 1) {
		std::cout << 0 << std::endl;
		return 0;
	}	
	
	float k;
	float j;

	j = (n - 1)*(r[0])*(1 / (r[n - 1] - r[0]));
	
	if(j <= 0.85f) {
			std::cout << 0 << std::endl;
			return 0;
		}

	for(i = 1; i < n - 1; i++) {

		k = (i)*(((r[i] / r[i - 1]) - 1));
		j = (n - i - 1)*(r[i] - r[i - 1])*(1 / (r[n - 1] - r[i]));

		if(k <= 0.85f && j <= 0.85f) {
			std::cout << i << std::endl;
			return 0;
		}
	}

	k = (n-1)*(((r[n - 1] / r[n - 2]) - 1));

	if(k <= 0.85f) {
			std::cout << n - 1 << std::endl;
			return 0;
		}

	std::cout << -1 << std::endl;
}