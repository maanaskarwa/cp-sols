#include <bits/stdc++.h>
#define ld long double

using namespace std;

const double eps = 1e-8;
double x,y, x_1,y_1,val;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  int m,n;
  cin >> m;
  bool possible;
  while (m--) {
    cin >> x>>y;
    cin >> n;
    possible = false;
    while (n--) {
      cin >> x_1 >> y_1;
      if (!possible) {
        y_1 -= y, x_1 -=x;
        // check if dist is less than 8
        // can check square of distances as well
        val = y_1 * y_1 + x_1*x_1 - 64;
        if (val < eps) {
          possible=true;
        }
      }
    }
    if (possible) cout << "light a candle\n";
    else cout << "curse the darkness\n";
  }
}