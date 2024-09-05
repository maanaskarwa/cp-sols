/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <cstring>

using namespace std;

int custom_closest_to_1000(int i1, int i2) {
  if (abs(i1 - 1000) < abs(i2 - 1000) || (abs(i1 - 1000) == abs(i2 - 1000) && i1 > i2)) return i1;
  return i2;
}

int weights[1000];
short n;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (short i = 0; i < n; ++i) cin >> weights[i];
  if (n == 1) {
    cout << weights[0];
  } else {
    // DP. if sum possible, true. else false
    bool weight_possible[2001]; // should be able to handle index 1000 + 1000
    memset(weight_possible, false, sizeof(weight_possible));
    int ans = 2000;
    for (int weight: weights) {
      for (int i = 2000; i >= 1; --i) {
        if (weight_possible[i] && (i + weight <= 2000)) {
          weight_possible[i + weight] = true;
          // compare ans to both the new values
          ans = custom_closest_to_1000(ans, custom_closest_to_1000(i, i + weight));
        }
      }
      //update later because in cases like 500, 500 will be set to true and 500 + 500 will be set to true (false positive)
      weight_possible[weight] = true;
    }
    cout << ans;
  }
  return 0;
}


/*
 * Problem Statement: https://open.kattis.com/problems/walrusweights
 *
 * Wallace the Weightlifting Walrus is training for a contest where it will have to lift 1000 kg.
 * Wallace has some weight plates lying around, possibly of different weights, and its goal is to add some of the plates to a bar so that it can train with a weight as close as possible to 1000 kg.
 * In case there exist two such numbers which are equally close to 1000 (e.g. 998 and 1002), Wallace will pick the greater one (in this case 1002).
 * Help Wallace the Weightlifting Walrus and tell it which weight it will have to lift.
 *
 * Input:
 * The first line of the input contains the number of plates n (1 <= n <= 1000). Each of the following n lines contains one positive integer less than or equal to 1000, denoting the weight of each plate.
 *
 * Output:
 * Output one integer, the combined weight closest to 1000.

Sample Input 1
4
900
500
498
4

Sample Output 1
1002

Sample Input 2
1
1

Sample Output 2
1

 *
 */