/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>
using namespace std;

template<class T>
int sgn(T x) { return (x > 0) - (x < 0); }

template<class T>
struct Point {
    typedef Point P;
    T x, y;

    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}

    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }

    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }

    P operator+(P p) const { return P(x + p.x, y + p.y); }

    P operator-(P p) const { return P(x - p.x, y - p.y); }

    P operator*(T d) const { return P(x * d, y * d); }

    P operator/(T d) const { return P(x / d, y / d); }

    T dot(P p) const { return x * p.x + y * p.y; }

    T cross(P p) const { return x * p.y - y * p.x; }

    T cross(P a, P b) const { return (a - *this).cross(b - *this); }

    T dist2() const { return x * x + y * y; }

    double dist() const { return sqrt((double) dist2()); }

    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }

    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }

    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
      return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }

    friend ostream &operator<<(ostream &os, P p) {
      return os << "(" << p.x << "," << p.y << ")";
    }
};

typedef Point<double> P;
double segDist(P& s, P& e, P& p) {
  if (s==e) return (p-s).dist();
  auto d = (e-s).dist2(), t = min(d,max(.0,(p-s).dot(e-s)));
  return ((p-s)*d-(e-s)*t).dist()/d;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  int n;
  cin >> n;
  int x1, y1, x2, y2, x3, y3, x4, y4;
  while (n--) {
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    if ((x1 == x3 && y1 == y3) || (x2 == x3 && y2 == y3) || (x1 == x4 && y1 == y4) ||
        (x2 == x4 && y2 == y4)) { //endpoints touch
      cout << "0.00\n";
      continue;
    }
    Point<double> a1(x1, y1), a2(x2, y2), b1(x3, y3), b2(x4, y4);
    if ((a1.cross(b1, b2) * a2.cross(b1, b2) < 0) && (b1.cross(a1,a2)*b2.cross(a1,a2) < 0)) {
      //line segments intersect
      // logic: a1 and a2 are on opposite sides of line b1 b2
      // and b1 & b2 are on opposite sides of line a1 a2
      cout << "0.00\n";
      continue;
    }
    // template to find distance between a point and a line segment
    // we are guaranteed no intersection, answer is just min
    double d1 = segDist(a1,a2,b1);
    double d2 = segDist(a1,a2,b2);
    double d3 = segDist(b1,b2,a1);
    double d4 = segDist(b1,b2,a2);
    cout << fixed << setprecision(2) << min(min(d1,d2),min(d3,d4)) << "\n";
  }

}