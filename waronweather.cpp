/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
#define ld long double
using namespace std;

struct Point {
    ld x, y, z;
};

const ld eps2 = 1e-16;
const ld earthRadius2 = powl(20000/M_PI,2);

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  int k, m;
  ld x, y, z;
  Point missiles[100], coords[100];
  bool hit[100];
  while (true) {
    memset(hit, false, sizeof(hit));
    cin >> k >> m;
    if (m == 0 && k == 0)break;
    for (int i = 0; i < k; i++) {
      cin >> x >> y >> z;
      missiles[i] = {x, y, z};
    }
    for (int i = 0; i < m; i++) {
      cin >> x >> y >> z;
      coords[i] = {x, y, z};
    }
    for (int i = 0; i < k; i++) {
      Point missileCoord = missiles[i];
      // if a point can be hit, its distance is less than tangent distance
      // since tangent is the farthest point we can see
      // it can also be done using angles - but same logic of tangents
      ld tangentDist2 = (pow(missileCoord.x, 2) + pow(missileCoord.y, 2) + pow(missileCoord.z, 2) - earthRadius2);
      for (int j = 0; j < m; j++) {
        if (!hit[j]) {
          Point locationCoord = coords[j];
          ld distFromMissile2 = (pow(locationCoord.x-missileCoord.x, 2) + pow(locationCoord.y-missileCoord.y, 2) + pow(locationCoord.z-missileCoord.z, 2));
          hit[j] = distFromMissile2 - tangentDist2 < eps2;
        }
      }
    }
    int ans = 0;
    for (int i = 0; i < k; i++) if (hit[i]) ans++;
    cout << ans << "\n";
  }
}

#undef ll
#undef ld