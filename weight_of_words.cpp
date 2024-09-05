/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <map>
#include <cmath>

using namespace std;

map<int, string> weight_map = {
  {0, ""},
  {1,  "a"},
  {2,  "b"},
  {3,  "c"},
  {4,  "d"},
  {5,  "e"},
  {6,  "f"},
  {7,  "g"},
  {8,  "h"},
  {9,  "i"},
  {10, "j"},
  {11, "k"},
  {12, "l"},
  {13, "m"},
  {14, "n"},
  {15, "o"},
  {16, "p"},
  {17, "q"},
  {18, "r"},
  {19, "s"},
  {20, "t"},
  {21, "u"},
  {22, "v"},
  {23, "w"},
  {24, "x"},
  {25, "y"},
  {26, "z"}
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  short l, w;
  cin >> l >> w;

  // too large - all z will not be enough. to small - all a will be too large
  if (w > 26 * l || w < l) {
    cout << "impossible";
    return 0;
  }

  /*
   * Logic: output as many Zs as possible. We need to ensure we left enough weight for the other letters.
   * "Worst case": we only have enough left for As after the Zs.
   * Let num of valid Zs be n. Then, worst case, weight left is equal to number of spaces left
   * w - 26n = l - n
   * n = (w - l)/25
   * n must always be smaller than this since we can output a heavier letter than A at the end if needed.
   */

  int num_z = (int) floor((w - l) / 25);
  for (int i = 1; i <= num_z; ++i) {
    cout << "z";
  }
  // output 1 A less, accounting for whatever letter is needed at the end to hit the sum
  for (int i = 1; i <= l - num_z - 1; ++i) {
    cout << "a";
  }

  if (w - (26*num_z) - (l - num_z - 1) >= 0 && (l - num_z - 1 >= 0)) // check if you outputted any As and have any weight left to output
    cout << weight_map[w - (26 * num_z) - (l - num_z - 1)];
  cout << "\n";
  return 0;
}

/*
 * Problem Statement: https://open.kattis.com/problems/weightofwords
 * Justin likes to play a game called “Weight of Words.” In this game, a player must find words of a given length and a given weight.
 * The weight of a word is the sum of the weights of its letters. Letters are English lowercase characters from ‘a’ to ‘z’ and have weights from 1 to 26.
 *
 * You are asked to write an AI that can play this game!
 *
 * Input:
 * The input consists of a single line with two integers l (o < l <= 40) and w (0 < w <= 1000).
 *
 * Output:
 * Output a string of length l with weight w consisting of lowercase English letters if it exists, otherwise output impossible. If more than one string exists, you may output any of them.

Sample Input 1
11 131

Sample Output 1
programming

Sample Input 2
7 96

Sample Output 2
contest

Sample Input 3
26 677

Sample Output 3
impossible
 */