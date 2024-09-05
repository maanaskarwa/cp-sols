/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  string s;

  cin >> s;
  int n = s.length();
  int costToMakeMaskOfLength[n];

  for (int i = 0; i < n; i++)
    cin >> costToMakeMaskOfLength[i];

  int inputAsInt = 0;
  for (int i = 0; i<n;i++)
    if (s[i] == '1')
      inputAsInt |= 1 << (n-1-i);

  int upperBound = 1 << (n-1);
  int maskINeed = ((1<<n)-1) & ~inputAsInt;

  //mask, length. Maintain set so that you do not count cost twice
  // need pair since we need the mask and the length to uniquely identify a mask.
  // since 111 and 000111 are equivalent as integers
  set<pair<int,int>> items;
  int ans = 1e5;
  // brute force - check all possible subsets. 1s in the bitmask imply
  // starting new substring that continues till the next 1 or till string is over
  for (int i = 1; i < upperBound; i++) {
    items.clear();
    int prevEnd = 0;
    int endOfCurrentMask;
    int split = i;
    while (split) {
      endOfCurrentMask = __builtin_ctz(split);
      int len = endOfCurrentMask - prevEnd+1; // length of current subset
      int m = (maskINeed >> prevEnd) & ((1<<len) - 1); // mask. Right shift by previous mask
      items.insert({m,len});
      prevEnd = endOfCurrentMask+1;
      split -= (1<<endOfCurrentMask);
    }

    //last subset - from last 1 till end
    int mFinal = (maskINeed >> prevEnd) & ((1<<n)-1);
    int lenFinal = n - prevEnd;
    items.insert({mFinal,lenFinal});

    int sum = 0;
    for (auto const& it: items) {
      sum += costToMakeMaskOfLength[it.second-1];
    }
    ans = min(sum,ans);
  }

  // since starting mask from 1, min with using just 1 mask of entire length
  cout << min(ans, costToMakeMaskOfLength[n-1]);
}