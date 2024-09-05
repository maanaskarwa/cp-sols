/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    unsigned long m, n;
    cin >> n >> m;
    int fish_weights[n];
    for (int i = 0; i < n; ++i) cin >> fish_weights[i];
    sort(fish_weights, fish_weights + n);
    map<unsigned long long, unsigned long long> price_to_quantity_map; // store number of people willing to sell at a certain price
    while (m--) {
        unsigned long long count;
        int price;
        cin >> count >> price;
        price_to_quantity_map[price] += count;
    }
    unsigned long long ans = 0;
    //Greedy assumption: choosing the highest price each time will lead to overall max. So, iterating backwards through map
    for (auto it = price_to_quantity_map.rbegin(); it != price_to_quantity_map.rend(); ++it) {
        unsigned long long price = it->first;
        unsigned long long count = it->second;
        bool out_of_fish = false;
        for (int i = 0; i < count; ++i) {
            ans += price * fish_weights[n - 1];
            if (n == 1) {
                out_of_fish = true;
                break;
            }
            --n;
        }
        if (out_of_fish) break;
    }
    cout << ans << "\n";
    return 0;
}

/* Problem Statement: https://open.kattis.com/problems/fishmongers
 *
 * You fish fish.
 * You hate fish.
 * You love monies.
 * Therefore sell fish.
 * To fishmongers.
 * For maximum profit.
 *
 * Input:
 * The first line of input contains two integers n (1 <= n <= 100000), the number of fish you have to sell,
 * and m (1 <= m <= 100000), the number of fishmongers.
 * On the second line follows n space-separated integers w1, w2, w3, ..., wn, the weight of each of your fish in kilograms (1 <= wi <= 100000).
 * Finally, there are m lines, the j’th of which consisting of two integers xj (1 <= xj <= 100000) and pj (1 <= pj <= 100000),
 * respectively indicating how many fish the j’th fishmonger wants to buy and how many monies he will pay per kilogram.
 *
 * Output:
 * A single integer, the maximum number of monies you can obtain by selling your fish to the fishmongers.

Sample Input 1
4 3
1 2 7 5
2 4
1 5
3 3

Sample Output 1
66
 */