/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
#define ld long double
#define u unsigned
#define DEBUG false
using namespace std;

ll modExp(ll base, ll exp, ll mod) { //template to compute modular exponentiation in O(log(exp))
  ll res = 1;
  while (exp > 0) {
    if (exp & 1) res = (res * base) % mod;
    exp = exp >> 1;
    base = (base * base) % mod;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  ll d;
  cin >> t;
  while (t--) {
    cin >> d;
    // ans is 8 * (9^(d-1)). First digit can't be 0 or 9, others can be anything from 0-8
#define MODULO 1000000007
    cout << (modExp(9, d - 1, MODULO) * 8) % MODULO << "\n";
  }

  return 0;
}