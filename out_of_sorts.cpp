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
    int n;
    u ll m, a, c, x_0;
    cin >> n >> m >> a >> c >> x_0;
    u ll x[n];
    x[0] = (a * x_0 + c) % m;
    for (int i = 1; i < n; ++i) {
        x[i] = (a * x[i - 1] + c) % m;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int lower = 0;
        int higher = n - 1;
        // Equality added because her algo allows it (since we are checking at mid directly)
        while (lower <= higher) {
            int mid = (lower + higher) / 2; // followed her algorithm exactly
            if (x[mid] == x[i]) {
                ++ans;
                break;
            } else if (x[mid] < x[i]) lower = mid + 1;
            else higher = mid - 1;
        }
    }
    cout << ans << "\n";
    return 0;
}

/* Problem Statement: https://open.kattis.com/problems/outofsorts
 *
 * Ann Logan is fascinated with finite sequences of integers. She is particularly interested in sequences of the form x_1, x_2,...,x_n where:
 * x_i = (a x_(i-1) + c) % m, (mod m)
 * n, m, a, c are positive integer constants
 * x_0 is a non-negative constant
 * all n values are unique
 *
 * For example, if n = 5, m = 8, a = 1, c = 3, and x_0 = 3,
 * the sequence is 6, 1, 4, 7, 2.
 * Note that she does not consider the initial value x_0 to be part of the sequence.
 *
 * Ann wants to be able to quickly determine, for any integer value, whether or not it appears within a finite sequence of this form. Given values of n,m,a,c and x_0, she plans to follow this list of steps:
 * 1. Generate the sequence and store it in an array.
 * 2. Sort the array.
 * 3. Perform a binary search of the array for each integer of interest to her.
 *
 * Ann’s search algorithm, while not the most efficient possible, is pretty straightforward and understandable to anyone familiar with binary search:
 * after calculating the midpoint mid at each step of the calculation (using mid = (low+high)/2), she first checks whether or not the value at location mid is equal to the search value x. If not, she then narrows the search according to whether x is strictly less than or strictly greater than the value at location mid.
 * Unfortunately, Ann is absent-minded and she lost her list of steps. She managed to remember the first and last step, but …she forgot to sort the array before performing her binary search! Needless to say, this means that many values that are in the (unsorted) array will not be found by a binary search, although surprisingly some can.
 * In the example above, both 4 and 7 can be found with Ann’s binary search. How many values can be found for various sequences? Don’t botch it up!
 *
 * Input:
 * Input consists of a line containing five integers n, m, a, c, x_0 (1 <= n <= 10^6), (1 <= m,a,c <= 2^31 - 1), (0 <= x_0 <= 2^31 - 1)
 * where n is the length of the sequence and m, a, c, x_0 are the constants used for generating the sequence. All values in the generated sequence are guaranteed to be unique.
 *
 * Output:
 * Output the number of sequence values that could be found using Ann’s version of binary search, assuming she forgot to sort the sequence.

Sample Input 1
5 8 1 3 3

Sample Output 1
2

Sample Input 2
6 10 1234567891 1 1234567890

Sample Output 2
6
*/