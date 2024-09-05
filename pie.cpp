/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <cmath>
#include <iostream>
#include <iomanip>

#define ld long double

using namespace std;

int t, n, f;
ld vol_by_pi[10000], min_vol, max_vol;

/*
 * BSTA. Kept pi out of all computations, used r^2 * h instead to avoid precision issues.
 */

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    min_vol = 2e9, max_vol = 0;
    cin >> n >> f;
    for (int i = 0; i < n; ++i) {
      int r;
      cin >> r;
      ld v_by_pi = powl(r, 2);
      vol_by_pi[i] = v_by_pi;
      min_vol = min(min_vol, v_by_pi);
      max_vol = max(max_vol, v_by_pi);
    }
    ld low = min_vol/(f+1), high = max_vol;
    /* max_vol can be pi * 10^4 * 10^8 at max.
     * Assuming pi as 4, that's 4*10^12. ceil of log base 2 of this number is 42.
     */
    for (int i = 0; i < 42 && low < high; ++i) {
      ld mid = (low + high) / 2;
      int piece_count = 0;
      for (int j = 0; j < n; ++j) {
        ld v = vol_by_pi[j];
        piece_count += floor(v / mid); // number of pieces of given vol we can get from this pie
      }
      if (piece_count < f + 1) high = mid; // try smaller piece
      else low = mid; // try larger piece
    }
    cout << setprecision(12) << M_PI * low << "\n";
  }
  return 0;
}