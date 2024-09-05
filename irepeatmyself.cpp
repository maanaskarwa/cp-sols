/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>
using namespace std;
const int mxn=200;
int n;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  cin >> n;
  string s;
  getline(cin, s); // scan entire line super helpful do not forget
  while (n--) {
    getline(cin, s);
    int length = s.length();
    for (int i = 1; i <= length; i++) { // brute force, try all lengths from 1 till string length
      bool works = true;
      string candidate = s.substr(0,i);
      int candidateLen = candidate.length();
      for (int j = 0; j < length; j++) {
        if (s[j] != candidate[j % candidateLen]) { // character in original string does not match corresponding char in pattern
          works = false;
          break;
        }
      }
      if (works) {
        cout << i << "\n";
        break;
      }
    }
  }
}