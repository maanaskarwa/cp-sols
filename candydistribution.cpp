/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
using namespace std;

ll euclid(ll a, ll b, ll &x, ll &y) {//kactl template. returns GCD and sets x and y such that ax + by = 1
  if (!b) return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

#define IMPOSSIBLE {cout << "IMPOSSIBLE\n";}
ll t, k, c, x, y, g;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    cin >> k >> c;
    if (c == 1) cout << k + 1 << "\n"; //1 candy per bag, need k+1 bags
    else if (k == 1) cout << "1\n"; // only 1 kid. give c-1 candies
    else if (!(k & 1 || c & 1)) IMPOSSIBLE  // 2 even numbers cant have gcd 1. cut down unnecessary gcd computation
    else {
      g = euclid(k, c, x, y);
      if (g != 1 || y > 1000000000) IMPOSSIBLE
      else if (y > 0) cout << y << "\n";
      else cout << y+k << "\n"; // adjust y to be min possible +ve value
      /*
       * Logic: we have a,b s.t
       * ax + by = 1
       * can adjust our ans by doing
       * a(x-b) + b(y+a) = 1. (Adding and subtracting ab basically)
       * Or (a+y)x + (b-x)y = 1. Same principle
       *
       * In this case, we need to make the number of candy bags aka coefficient of y +ve
       * we have xk + yc = 1
       * (x-c)k + (y+k)c = 1
       * So we output y+k.
       * Am still trying to fully grasp exactly why y+k > 0 when y < 0, but you can use this to play with the coefficients
       */
    }
  }
}