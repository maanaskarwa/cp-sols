/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <cstring>

using namespace std;

int f, l, bytes_saved[80], line[200], num_lines = 0, ans = 0, ans_index = 1;

/*
 * Observations:
 * 1. No need to compute anything for tab length 1, so our computation is between 2 and 79.
 * 2. If a tab is longer than the number of spaces we cannot optimize that line.
 * 3. Multiple files have nothing to do with the q. We simply need an array of each line's spaces.
 */

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(bytes_saved, 0, sizeof(bytes_saved));
  memset(line, 0, sizeof(line));
  cin >> f;
  for (int i = 0; i < f; ++i) {
    cin >> l;
    while (l--) cin >> line[num_lines++];
  }

  /*
   * Instead of looping thru each tab space and checking each line, we can flip the for loops and set the upper limit
   * to that line's length.
   *
   * Bytes used for tab length t = line/t (directly saved) + line%t leftover spaces
   */

  for (int j = 0; j < num_lines; ++j)
    for (int i = 2; i <= line[j]; ++i)
      bytes_saved[i] += line[j] - ((line[j] / i) + (line[j] % i));

  for (int i = 2; i <= 79; ++i) {
    if (bytes_saved[i] > ans) {
      ans = bytes_saved[i];
      ans_index = i;
    }
  }
  cout << ans_index << "\n" << ans;
  return 0;
}

/*
 * https://open.kattis.com/problems/tabsandspaces
 *
 * Picture this. Your favourite code repository hosting site is hosting a conference at Chalmers. And you’ve gone to it.
 * They’ve talked about a bunch of fun stuff like merge conflicts, accidentally discarding your changes and someone force-pushing their commit over yours so that all your work just goes to waste.
 * They also brought up the importance of efficient text compression. Something about how if everyone indented their code with tabs instead of spaces, they would save a colossal amount of space. But at that point you weren’t really concentrating, since you knew there was going to be free lunch and you were starving.
 *
 * After you get home, you check your own code. You realise, it’s all indented with spaces! And every single space takes up a whole byte. A whole byte! Disgusted by this pointless waste of storage space, you convert all of your files to use tabs for indentation.
 * But then you start to think. What if…tabs weren’t specifically four spaces wide? What if you could save even more space if tabs were some other width? You immediately get to work solving this problem.
 *
 * Input
 * The input begins with one number F, the amount of files in your project. Then follow F files. Each file begins with a number L, the lines in your program. Each following “line” is represented by a number N, the amount of spaces used to indent that line.
 * Your project can have up to 10 files, each with up to 20 lines. Oh, and your project is written in Python, so the line length can be up to 80 of which 79 characters can be spaces. (You’re a PEP abiding code golfer.)
 *
 * Output:
 * Print two numbers, one on each line. First the width of your custom tab symbol in spaces, then the total amount of space saved in bytes.
 *
 * Things to note
 * Your code still has to look the same after you’ve substituted some of the spaces with tabs. If you find two or more tab sizes that save the same amount of space, pick the smaller one. Tabs also have to be at least one space wide.

Sample Input 1
2
2
0
4
2
0
4

Sample Output 1
4
6

Sample Input 2
1
8
0
0
0
4
8
8
8
8

Sample Output 2
8
28
 */