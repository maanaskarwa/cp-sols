/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
#define ld long double
#define u unsigned
#define DEBUG false
#define PANIC {throw "unhandled behavior\n";}
#define PANICLN(msg) {throw ((msg) + "\n");}


using namespace std;
ll factorialModNum[1000001], inverseFactorial[1000001];
#define MODULO 1000000007

ll modExp(ll base, ll exp, ll mod) {
  ll res = 1;
  while (exp > 0) {
    if (exp & 1) res = (res * base) % mod;
    exp = exp >> 1;
    base = (base * base) % mod;
  }
  return res;
}

#define modInv(num, mod) modExp((num), ((mod) - 2), (mod))

#define choose(n, r) ((!(r) || ((n)==(r))) ? 1 : (n) < (r) ? 0 : (factorialModNum[(n)] * ((inverseFactorial[(n) - (r)] * inverseFactorial[(r)]) % MODULO)) % MODULO)

int main() {

  //precompute factorials and inverses mod that prime
  // note: previously, was doing modExp in the for loop itself to find the inverse of each factorial
  // this is slow. instead, do modExp once for the max, and then keep mutiplying and modding by i
  // since 1/n! * (n) = 1/(n-1)!. So invFac(n-1) = (n * invFac(n)) % MOD
  // n vs n log p - significant
  ll fact = 1;
  factorialModNum[0] = 1;
  inverseFactorial[0] = 1;
  for (int i = 1; i <= 1000000; ++i) {
    fact *= i;
    if (fact > MODULO) fact %= MODULO;
    factorialModNum[i] = fact;
  }
  ll inverseFact = modInv(fact, MODULO);
  factorialModNum[1000000] = inverseFact;
  for (int i = 999999; i >=0; --i) {
    inverseFact *= (i+1);
    if (inverseFact > MODULO) inverseFact %= MODULO;
    inverseFactorial[i] = inverseFact;
  }

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int x_min, y_min, n;
  cin >> n >> x_min >> y_min;
  if (n < x_min || n < y_min) {
    cout << "0\n";
    return 0;
  }

  //logic - you can get there in a certain number of "steps"
  //each step covers a certain x and y, both more than their respective minimums
  // extremes - get there in 1 step. hop n,n. Other extreme is to use as many steps as possible

  ll ans = 0;

  ll max_x_steps = n/x_min, max_y_steps = n/y_min;
  ll actual_min = min(max_x_steps,max_y_steps); //cannot use morre steps since you will end up moving less than min allowed distance in some step
  for (int steps = 1; steps <= actual_min; steps++) {
    // ways to cover x distance in given steps * ways to cover y distance in given steps
    // distribute the min required distance in each step. now, you have a certain "distance" remaining. distribute it in the given steps. Bars & stars analogy

    // number of sols to a_1 + a_2 + ... + a_steps = n - steps*min_distance. a_i can be 0 aka min step
    ll numX = choose(n-steps*(x_min-1) - 1,steps - 1); ll numY = choose(n-steps*(y_min-1) - 1,steps - 1);
    ans += numX * numY;
    if (ans > MODULO) ans %= MODULO;
  }

  cout << ans;

}