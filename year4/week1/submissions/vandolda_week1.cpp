/* UWindsor POTW 2017
 * Week 1 - Squirrel Frenzy
 * Adam Vandolder */

#include <cmath>
#include <iostream>

int main(int argc, char *argv[])
{
    int n;
    std::cin >> n;

    int holes[n];
    for (int i = 0; i < n; i++)
        std::cin >> holes[i];

    int c, s;
    std::cin >> c >> s;

    // std::cout << c << " " << s << std::endl;

    // Create an array containing the number of holes with h chestnuts in them,
    // 1 <= h <= 50.
    int holes_with_h[50] = {0};
    int max_h = 0;
    for (int h : holes)
    {
        if (h > max_h)
            max_h = h;

        holes_with_h[h-1]++;

        // std::cout << h << " ";
    }

    // std::cout << std::endl;

    // Calculate the number of unique pairs that sum to S.
    int pairs = 0;
    for (int i = std::ceil(s / 2.0); i <= max_h; i++)
    {
        if (s == 2*i)
        {
            // If i is exactly half of S, then all holes with i chestnuts form
            // unique pairs with all other holes with i chestnuts. This results
            // in a number of pairs equal to the sum of 1 to j, or j*(j+1) / 2.
            int j = holes_with_h[i - 1] - 1;
            pairs += j * (j + 1) / 2;
        }
        else if (s - i > 0)
            // Otherwise, the number of unique pairs is the product of the
            // number of holes with i nuts and those with s-i nuts.
            pairs += holes_with_h[(s - i) - 1] * holes_with_h[i - 1];

        // std::cout << i << " " << pairs << " " << holes_with_h[i - 1] << " "
                //   << holes_with_h[(s - i) - 1] << std::endl;
    }

    if (pairs >= c)
        std::cout << "True" << std::endl; // << " " << pairs << std::endl;
    else
        std::cout << "False" << std::endl; // << " " << pairs << std::endl;
}