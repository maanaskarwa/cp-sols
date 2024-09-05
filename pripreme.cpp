/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
#define ld long double
#define u unsigned
#define DEBUG false
using namespace std;
u ll n, num, greatest=0, sum = 0;

/*
 * If the longest time taken is longer than all the other times combined, the ans will be 2 * longest
 * Visualize:
 * a (24) |________________________........................
 * b (2)  |                    ..                      __
 * c (20) |....................    ____________________
 * Basically, every other team can be fit in in the remaining slots since their cumulative time per task is less than the max.
 *
 * Otherwise, the longest time is the sum of all times. In this case, the longest time person will have to wait as well
 * a (24) |________________________ ........................
 * b (5)  |                    .....                   _____
 * c (20) |....................    ____________________
 */
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> num;
    sum += num;
    greatest = max(greatest, num);
  }
  cout << max(sum, greatest << 1);
  return 0;
}