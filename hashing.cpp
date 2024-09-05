/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
#define u unsigned

u ll modExp(u ll base, u ll exp, u ll mod) {
  u ll res = 1;
  while (exp > 0) {
    if (exp & 1)
      res = (res * base) % mod;
    exp = exp >> 1;
    base = (base * base) % mod;
  }
  return res;
}

#define modInv(num, mod) modExp((num), ((mod) - 2), (mod))

using namespace std;
const u ll modulo1 = 1e9 + 7;
const u ll modulo2 = 1e9 + 9;

// hash from 0 to index inclusive
u ll rollingHashSum[300000][2];
u ll invPowMod[300000][2];
string s;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  cin >> s;
  int len = s.length();

  const u ll alphabetSize = 26;

  u ll powerModulo, invPowerModulo;
  invPowMod[0][0] = 1, invPowMod[0][1] = 1;
  rollingHashSum[0][0] = s[0] - 'a' + 1, rollingHashSum[0][1] = s[0] - 'a' + 1;

  u ll modulo = modulo1;
  for (int j = 0; j <= 1; j++) {
    // find hash using 2 different primes, at ending just bit shift one of them while outputting ans
    // using all digits of int64 that way without risking overflow
    powerModulo = 1, invPowerModulo = 1;
    u ll invPow = modInv(alphabetSize, modulo);
    for (int i = 1; i < len; i++) {
      powerModulo *= alphabetSize;
      if (powerModulo > modulo) powerModulo %= modulo;

      rollingHashSum[i][j] = (rollingHashSum[i - 1][j] + powerModulo * (s[i] - 'a' + 1)) % modulo;

      invPowerModulo *= invPow;
      if (invPowerModulo > modulo) invPowerModulo %= modulo;
      invPowMod[i][j] = invPowerModulo;
    }
    modulo = modulo2;
  }


  u ll ans1, ans2;
  int q, l, r;
  cin >> q;
  while (q--) {
    cin >> l >> r;
    if (l == 0) { // include from start
      ans1 = (rollingHashSum[r - 1][0]);
      ans2 = (rollingHashSum[r - 1][1]);
    } else {
      // do not include r in the ans per the definition of substring given
      ans1 = (((modulo1 + rollingHashSum[r - 1][0] - rollingHashSum[l - 1][0]) % modulo1) * invPowMod[l][0]) % modulo1;
      ans2 = (((modulo2 + rollingHashSum[r - 1][1] - rollingHashSum[l - 1][1]) % modulo2) * invPowMod[l][1]) % modulo2;
    }
    cout << (ans1 << 32) + ans2 << "\n";
  }
}

#undef ll
#undef u