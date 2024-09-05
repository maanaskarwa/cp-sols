/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
#define ld long double
#define u unsigned
#define DEBUG false
#define PANIC {return 2;}

using namespace std;

const int mxN = 10e7 + 1;
short mobius[mxN];
int lowestPrimeFactor[mxN]; // 0 if prime, else lowest prime factor

// returns the number of coprime pairs in ranges [1,p] and [1,q]. Choose one number from each range
ll query(ll p, ll q) {
  /*
   * mobius (i) = -1 if a product of odd number of distinct primes, +1 if product of even number of distinct primes, 0 if a prime occurs twice
   *
   * Lets take 2,3,6 to understand what this thing does
   *
   * If 2 nos are coprime, gcd = 1.
   * So we find the bad pairs - choose numbers divisible by a prime, eg 2 from each pair and multiply number of ways
   * But we overcount, since we count 6 for primes 2 and 3 and it gets subtracted twice. So, inclusion exclusion
   *
   * The summary of the entire inclusion exclusion is the essence of the mobius function - boiling down to -1, +1, 0
   *
   * ans = total - bad
   *     = pq - p/2.q/2 - p/3.q/3 -... + p/(2.3).q/(2.3) + ... and so on
   *
   * Note that there are not p/(2.2) or such cases here. That's why mobius = 0 if a prime occurs more than once
   *
   */
  if (!p || !q) return 0;
  ll ans = p * q;
  ll m = min(p, q);
  for (int i = 2; i <= m; ++i)
    ans += mobius[i] * (p / i) * (q / i);
  return ans;
}

// compute mobius function from 1 to m
void precompute(int m) {
  memset(lowestPrimeFactor, 0, (m + 1) * sizeof(lowestPrimeFactor[0]));
  memset(mobius, 0, (m + 1) * sizeof(mobius[0]));
  mobius[1] = 1;
  for (int i = 2; i <= m; i++) {
    if (!lowestPrimeFactor[i]) {
      lowestPrimeFactor[i] = i;
      for (int j = i << 1; j <= m; j += i) { if (!lowestPrimeFactor[j]) lowestPrimeFactor[j] = i; }
      mobius[i] = -1;
    }
  }
  for (int i = 2; i <= m; i++) {
    if (mobius[i] == -1) continue;
    mobius[i] = [](int x) -> short {
        int cnt = 0;
        while (x > 1) {
          int k = 0, d = lowestPrimeFactor[x];
          if (!d) return -1;
          while (x % d == 0) {
            x /= d;
            ++k;
            if (k > 1) return 0;
          }
          ++cnt;
        }
        if (cnt & 1) return -1;
        return 1;
    }(i);
  }
}

// debugging purposes
//ll slowCompute(int a, int b, int c, int d) {
//  ll ans = 0;
//  for (int i = a; i <= b; i++) for (int j = c; j <= d; j++) if (gcd(i, j) == 1) ans++;
//  return ans;
//}

int main() {
  // can find number of coprime pairs if we set starting num to 1. so, find the answers u need using inclusion-exclusion
  // can visualize as areas

  /*
   * d|           X       X
   *  |
   * c|           X       X
   *  |
   *  _______________________
   *              a       b
   *
   *  We want area within 4 Xs, we have a way of finding area of a rectangle starting at origin.
   */

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int a, b, c, d;
  cin >> a >> b >> c >> d;
  precompute(max(b, d));
  cout << query(b, d) - query(b, c - 1) - query(a - 1, d) + query(a - 1, c - 1);
}