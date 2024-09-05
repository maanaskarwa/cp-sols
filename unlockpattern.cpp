/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ld long double
#define pii pair<int,int>


#define PRECISION(n) fixed << setprecision((n))
using namespace std;

int pattern[3][3];

ld distances(pii a, pii b) {
  return sqrtl(powl(a.first-b.first,2)+powl(a.second-b.second,2));
}

pii numPosition(int num) {
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (pattern[i][j] == num)
        return {i,j};
  return {0,0};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);

  for (int i = 0; i < 3;i++)
    for (int j = 0; j < 3; j++)
      cin >> pattern[i][j];
  ld ans = 0;
  //add dist between 1&2, 2&3, so on
  for (int i = 2; i <= 9; i++) {
    auto curpos = numPosition(i);
    auto prev = numPosition(i - 1);
    ans += distances(curpos, prev);
  }
  cout <<PRECISION(10)<< ans;

}

#undef ld
#undef pii
#undef PRECISION