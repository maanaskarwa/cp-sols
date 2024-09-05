#include <iostream>
#include <map>
#include <cstring>

#define ll long long
#define ld long double
#define u unsigned

using namespace std;

int c, n, d;

ll prefix_sum[50001], ans = 0;

int remainder_count[1000000];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> c;
  while (c--) {
    memset(remainder_count, 0, sizeof(remainder_count));
    remainder_count[0] = 1;
    ans = 0;
    cin >> d >> n;
    prefix_sum[0] = 0;
    for (int i = 0; i < n; ++i) {
      int p;
      cin >> p;
      prefix_sum[i + 1] = prefix_sum[i] + p;
      remainder_count[prefix_sum[i+1] % d]++;
    }
    for (int i = 0; i < d; ++i) {
      int r = remainder_count[i];
      ans += r*(r-1)/2;
    }
    cout << ans << "\n";
  }
  return 0;
}