/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <algorithm>

#define ll long long
#define u unsigned

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int shop_sizes[n];
    int joe_sizes[m];
    for (int i = 0; i < n; ++i) cin >> shop_sizes[i];
    sort(shop_sizes, shop_sizes + n);
    for (int i = 0; i < m; ++i) cin >> joe_sizes[i];
    u ll sum = 0;
    for (int i = 0; i < m; ++i) {
        int target = joe_sizes[i];
        int lower = 0;
        int higher = n - 1;
        //binary search ensures that we either have the index of the element itself or the index of the next element (smallest element larger than what Joe needs)
        while (lower < higher) { // note lower = higher when loop terminates
            int mid = lower + (higher - lower) / 2;
            if (shop_sizes[mid] < target) lower = mid + 1;
            else higher = mid;
        }
        sum += (shop_sizes[lower] - target); // Wasted paint
    }
    cout << sum << "\n";
    return 0;
}

/* Problem Statement: https://open.kattis.com/problems/roompainting
 *
 * Joe’s landlord has allowed him to paint his room any colour that he wants, even multiple colours. Joe has come up with a very colourful design. Now he needs to buy the paint.
 * Being a struggling student, Joe does not want to waste any money, so he has calculated the exact amount that he needs of each colour down to the microlitre.
 * To his surprise, however, the local paint shop is unwilling to sell him a can of exactly 3.141592 litres of red paint. No, the shop has a set of specific paint can sizes.
 * The shop has almost unlimited amount of paint of each color, so each can can be filled with whatever colour Joe wishes and the shop has unlimited number of cans of each size.
 *
 * Joe has no choice but to buy a little bit more paint than he really needs. Still, he would like to minimize the amount of paint wasted.
 * In addition, he does not want to buy more than one can of any given colour.
 *
 * Input:
 * The first line of input contains two integers 1 <= n <= 100000 and 1 <= m <= 100000, the number of paint can sizes offered by the paint shop, and the number of colours that Joe needs.
 * Each of the next n lines contains the size of a can offered by the paint shop, in microlitres. Each can contains no more than 1000 litres.
 * Each of the next m lines contains the number of microlitres that Joe needs of a given colour. It is guaranteed that for each colour, the paint shop sells a can large enough to satisfy Joe’s needs.
 *
 * Output:
 * Output a single line, the total number of microlitres of paint wasted if Joe buys, for each colour, the smallest can that satisfies his needs.

Sample Input 1
3 2
5
7
9
6
8

Sample Output 1
2
 */