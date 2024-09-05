/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
#define ld long double
#define u unsigned
#define vi vector<int>
#define vvi vector<vi>
#define pb(n) push_back((n));
#define pii pair<int,int>

#define DEBUGGING false
#define PANIC {throw "unhandled behavior\n";}
#define PANICLN(msg) {throw ((msg) + "\n");}

#define ENABLE_FACTORIALS true
#if ENABLE_FACTORIALS
#define PRECOMPUTE_FACTORIALS_TILL 2501
#define FACTORIALS_WITH_MODULO true
#endif

#define ENABLE_MODEXP false

//todo. add storing as vec<int>, as matrix, etc. add scc, topo sort etc
#define ENABLE_GRAPH false

#define ENABLE_LIS false

#define ENABLE_PREALLOCATED_STACK false

#define PRECISION(n) fixed << setprecision((n))

using namespace std;

#if ENABLE_GRAPH
#endif

#if ENABLE_PREALLOCATED_STACK
typedef struct customStackStruct {
  int s[100000] = {-1};
  int size = 0;
  int top = -1;

  void push(int number) {
    s[size++] = number;
    top = number;
#if DEBUG
    s[size] = -1;
#endif
  }

  void pop() {
    top = s[--size - 1];
#if DEBUG
    s[size] = -1;
#endif
  }

  [[nodiscard]] bool empty() const {
    return !size;
  }

  void clear() {
    size = 0;
  }
} customStack;
#endif

#if ENABLE_LIS
/*
 * O(nlogn) ENABLE_LIS, taken from https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
 * Modified to allow non-decreasing
 */

int ceil_index_for_non_decreasing(vector<int> &v, int l, int r, int key) {
  while (r - l > 1) {
    int m = l + (r - l) / 2;
    if (v[m] > key) //was >=. Want the highest index in case a num repeats
      r = m;
    else
      l = m;
  }
  return r;
}

int longest_non_decreasing_subsequence_length(vector<int> &v) {
  if (v.empty())
    return 0;
  vector<int> tail(v.size(), 0);
  int length = 1;
  tail[0] = v[0];
  for (size_t i = 1; i < v.size(); i++) {
    if (v[i] < tail[0]) {
      tail[0] = v[i];
    }
    else if (v[i] >= tail[length - 1]) { // was >.
      tail[length++] = v[i];
    }
    else {
      tail[ceil_index_for_non_decreasing(tail, -1, length - 1, v[i])] = v[i];
    }
  }
  return length;
}

int ceil_index_for_strictly_increasing(vector<int> &v, int l, int r, int key) {
  while (r - l > 1) {
    int m = l + (r - l) / 2;
    if (v[m] >= key)
      r = m;
    else
      l = m;
  }
  return r;
}

/*
 * O(nlogn) ENABLE_LIS, taken from https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
 */
int longest_increasing_subsequence_length(vector<int> &v) {
  if (v.empty())
    return 0;
  vector<int> tail(v.size(), 0);
  int length = 1;
  tail[0] = v[0];
  for (size_t i = 1; i < v.size(); i++) {
    if (v[i] < tail[0]) {
      tail[0] = v[i];
    }
    else if (v[i] > tail[length - 1]) {
      tail[length++] = v[i];
    }
    else {
      tail[ceil_index_for_strictly_increasing(tail, -1, length - 1, v[i])] = v[i];
    }
  }
  return length;
}
#endif

#if ENABLE_FACTORIALS

ll modExp(ll base, ll exp, ll mod) {
  ll res = 1;
  while (exp > 0) {
    if (exp & 1) res = (res * base) % mod;
    exp = exp >> 1;
    base = (base * base) % mod;
  }
  return res;
}

#define MODULO 1000000007
ll factorial[PRECOMPUTE_FACTORIALS_TILL + 1];
#if FACTORIALS_WITH_MODULO
ll inverseFactorialModNum[PRECOMPUTE_FACTORIALS_TILL + 1];
#define choose(n, r) ((!(r) || ((n)==(r))) ? 1 : (n) < (r) ? 0 : (factorial[(n)] * ((inverseFactorialModNum[(n) - (r)] * inverseFactorialModNum[(r)]) % MODULO)) % MODULO)
#define permute(n, r) ((!(r)) ? 1 : ((n)==(r)) ? (factorial[(n)]) : (n) < (r) ? 0 : (factorial[(n)] * (inverseFactorialModNum[(n) - (r)])) % MODULO)

#else
#define choose(n, r) ((!(r) || ((n)==(r))) ? 1 : (n) < (r) ? 0 : ((factorial[(n)] / ([factorial(n) - (r)] ))  / factorial[(r)]))
#endif

#define modInv(num, mod) modExp((num), ((mod) - 2), (mod))

ll euclid(ll a, ll b, ll &x, ll &y) {//kactl template. returns GCD and sets x and y (ax + by = 1)
  if (!b) return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

void precomputeFactorials() {
  u ll fact = 1;
  factorial[0] = 1;
  for (int i = 1; i <= PRECOMPUTE_FACTORIALS_TILL; ++i) {
    fact *= i;
#if FACTORIALS_WITH_MODULO
    if (fact > MODULO) fact %= MODULO;
#endif
    factorial[i] = fact;
  }
#if FACTORIALS_WITH_MODULO
  ll inverseFact = modInv(fact, MODULO);
  factorial[PRECOMPUTE_FACTORIALS_TILL] = inverseFact;
  for (int i = PRECOMPUTE_FACTORIALS_TILL - 1; i >= 0; --i) {
    inverseFact *= (i + 1);
    if (inverseFact > MODULO) inverseFact %= MODULO;
    inverseFactorialModNum[i] = inverseFact;
  }
#endif
}

#elif ENABLE_MODEXP
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
#define MODULO 1000000007
ll euclid(ll a, ll b, ll &x, ll &y) {//kactl template. returns GCD and sets x and y (ax + by = 1)
  if (!b) return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}
#endif

int n, k;

/*
 * Choose p colors in kCp ways
 * Then choose the root in p ways. Each following node will have p-1 options (all except parent)
 */
ll waysInPColors(int p) {
  if (p <= 1) //no way since adjacent nodes will have same color
    return 0;
  ll ans =  (modExp(p-1, n-1, MODULO) * ((choose(k,p) * p)%MODULO))%MODULO;
  return ans;
}

/*
 * Observation: The arrangement of the tree doesn't matter, since the only constraint we
 * need to consider is the colors of a child wrt its parent
 *
 * Can think of it as adding a node to an existing tree. U can add in k-1 ways (any color except of parent)
 *
 * So, a tree is irrelevant. Any tree will return the same answer. So reduces to a line of n nodes
 */
int main() {
#if ENABLE_FACTORIALS
#if PRECOMPUTE_FACTORIALS_TILL > 0
  precomputeFactorials();
#endif
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  cin >> n >> k;
  if (k > n) {
    cout << 0;
    return 0;
  } else if (k == n) {
    cout << factorial[n];
    return 0;
  }
  ll ans = 0;
  short constantFactor = 1;
  /*
   * Inclusion-exclusion. ways(p) - ways(p-1) + ways(p-2)... till ways(2)
   *
   * Why? eg colors R, G, B, P
   * 5 nodes. In ways(p), we count RGRGR once. In ways(p-1) it is counted multiple times, since
   * we count it when we exclude B, and when we exclude P
   */
  for (int colors = k; colors >=2; --colors) {
    if (constantFactor==1) //alternate between +- till 2
      ans = (ans + waysInPColors(colors))%MODULO;
    else
      ans = (MODULO + ans - waysInPColors(colors))%MODULO;
    constantFactor *= -1;
  }
  cout << ans;
}