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

typedef struct {
    int time;
    double factor;
} shieldStuff;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll x, y, plain_time;
  // time = y
  cin >> x >> y;
  ll x_abs = abs(x);
  plain_time = y; //find time spent outside all shields
  int n;
  cin >> n;
  shieldStuff shields[n];
  for (int i = 0; i < n; ++i) {
    int y_start, y_end;
    double factor;
    cin >> y_start >> y_end >> factor;
    shields[i] = shieldStuff{
      .time = y_end - y_start,
      .factor = factor
    };
    plain_time -= (y_end - y_start);
  }
  double low = 0, high = 100000000;
  double speed;
  for (int i = 0; i < 100; i++) {
    speed = (low + high) / 2;
    ld x_covered = speed * plain_time;
    for (auto shield: shields) x_covered += speed * shield.time * shield.factor;
    if (x_covered > x_abs) high = speed;
    else low = speed;
  }
  if (x < 0) cout << fixed << setprecision(10) << -speed;
  else cout << fixed << setprecision(10) << speed;
}

// x can be negative x abs is just abs of that
// x covered is the x covered going at tht speed