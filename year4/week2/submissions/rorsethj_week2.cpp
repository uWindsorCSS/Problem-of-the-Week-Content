//
// Joel Rorseth
// POTW Year 4 Week 2 - Eye of the Storm
//

#include <iostream>
#include <vector>


int main() {

    int n;
    std::cin >> n;

    std::vector<unsigned int> readings(n);

    int left_sum = 0, right_sum = 0;

    // Read in all readings left to right
    // Since we start at left, left sum is 0 and right sum is sum of list
    for (int j = 0; j < n; ++j) {

        std::cin >> readings[j];        
        right_sum += readings[j];
    }


    // Test each reading as potential eye of storm
    for (int i = 0; i < n; ++i) {

        // Decrement current reading from right sum since we are testing it
        auto reading = readings[i];
        right_sum -= reading;

        // Check both sides for their average, then determine if reading is at least 15% lower
        // Assume average of readings before and after input are indeed > 15% than reading

        auto left_cond = (i == 0) ? true : ((left_sum / i) * 0.85 >= reading);
        auto right_cond = (i == n-1) ? true : ((right_sum / (n-i-1)) * 0.85 >= reading);
        
        if (left_cond && right_cond) {
            std::cout << i << std::endl;
            return 0;
        }

        left_sum += reading;
    }

    std::cout << -1 << std::endl;
    return 0;
}
