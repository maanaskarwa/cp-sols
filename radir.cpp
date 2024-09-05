#include <iostream>
#include <cstring>

#define ll long long
#define ld long double
#define u unsigned

using namespace std;

int p,n;
bool hasCard[5][14];

bool check() {
  for (int i = 1; i <= 4; ++i) {
    for (int j = 2; j <= 12; ++j) {
      if (hasCard[i][j-1] && hasCard[i][j] && hasCard[i][j+1]) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(hasCard, false, sizeof(hasCard));
  cin >> n >> p;
  for (int i = 0; i < p; ++i) {
    int suit, number;
    cin >> suit >> number;
    hasCard[suit][number] = true;
  }
  if (n == p) {cout << (check() ? "1" : "neibb"); return 0;}
  for (int i = 1; i <= n-p; ++i) {
    int suit, number;
    cin >> suit >> number;
    hasCard[suit][number] = true;
    if (check()) { cout << i; return 0;}
  }
  cout << "neibb";
  return 0;
}