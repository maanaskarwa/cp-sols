/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ld long double
#define PRECISION(n) fixed << setprecision((n))

using namespace std;

int n;
int helium[200001];//store helium in each canister

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);

  ld ans = 1;

  cin >> n;
  for (int i = 1, tmp; i <= n; i++) {
    cin >> tmp;
    // if a canister is empty, a balloon will never be filled
    if (tmp==0) {
      ans = 0;
    }
    helium[i]=tmp;
  }

  sort(helium+1, helium + n+1);

  for (int i = n; i>=1;i--) {
    auto b = helium[i];
    if (b > i) { // more in canister than corresponding balloon
      cout << "impossible";
      return 0;
    } else if (b < i) {
      ans = min(ans, (ld) b/(i) ); //fraction filled up
    }
  }
  cout << PRECISION(10)<<ans;
}

#undef ld
#undef PRECISION