/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

using namespace std;

int n, k;
int studentAnswers[1000];
string s;
int studentAns;
int maxLowestScore = 0;
int upperBound, lowestScore, correctAnswers;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);

  cin >> n >> k;
  getline(cin, s);

  for (int i = 0; i < n; i++) {
    getline(cin, s);
    studentAns = 0;
    for (int j = 0; j < k; j++) {
      if (s[j] == 'T')
        studentAns += 1 << (k - 1 - j); // convert student answer string to bitmask
    }
    studentAnswers[i] = studentAns;
  }
  upperBound = (1 << k) - 1;
  for (int ansKey = 0; ansKey <= upperBound; ansKey++) { //brute force - check all ans keys represented as bit strings
    lowestScore = 11; // 10 qs, score of 11 is like infinity
    for (int i = 0; i < n; i++) {
      correctAnswers = k - __builtin_popcount(ansKey ^ studentAnswers[i]); //total qs minus incorrect
      // popcount counts number of 1s in number. XOR(^) will only leave 1s where student answers differ from ans key
      lowestScore = min(lowestScore, correctAnswers);
    }
    maxLowestScore = max(maxLowestScore, lowestScore);
  }
  cout << maxLowestScore;
}