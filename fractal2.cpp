/*
*Author: Maanas Karwa
*It is ok to share my code anonymously for educational purposes
**/

#include <bits/stdc++.h>

#define ll long long
#define ld long double
#define u unsigned

using namespace std;

template<class T>
struct Point {
    typedef Point P;
    T x, y;

    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}

    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }

    P operator+(P p) const { return P(x + p.x, y + p.y); }

    P operator-(P p) const { return P(x - p.x, y - p.y); }

    P operator*(T d) const { return P(x * d, y * d); }

    P operator/(T d) const { return P(x / d, y / d); }

    T cross(P p) const { return x * p.y - y * p.x; }

    T cross(P a, P b) const { return (a - *this).cross(b - *this); }

    T dist2() const { return x * x + y * y; }

    T dist() const { return sqrtl((T) dist2()); }

    // angle to x-axis in interval [-pi, pi]
    T angle() const { return atan2l(y, x); }

    P unit() const { return *this / dist(); } // makes dist()=1
};

ld angle(Point<ld> a, Point<ld> b) {
  return b.angle() - a.angle();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  int c;
  cin >> c;
  while (c--) {
    int n, d;
    double f;
    const double eps = 1e-12;

    cin >> n;
    Point<ld> originalPoints[n];
    ld originalDistanceBetweenPointIAndIPlus1[n - 1];
    ld angleBetweenPointIMinus1IAndIPlus1[n]; // point i is the vertex of the angle
    ld totalInitialDistance = 0; //length of the original fractal unit
    for (int i = 0; i < n; i++) {
      int x, y;
      cin >> x >> y;
      originalPoints[i] = Point<ld>(x, y);
    }
    for (int i = 0; i < n - 1; i++) {
      ld dist = (originalPoints[i + 1] - originalPoints[i]).dist();
      originalDistanceBetweenPointIAndIPlus1[i] = dist;
      totalInitialDistance += dist;
    }
    for (int i = 1; i < n - 1; i++)
      angleBetweenPointIMinus1IAndIPlus1[i] = angle(originalPoints[i] - originalPoints[i - 1],
                                                    originalPoints[i + 1] - originalPoints[i]);
    ld originalDistanceBetweenFirstAndLastPoint = (originalPoints[n - 1] - originalPoints[0]).dist();
    ld angleBetweenLastAndFirstPointWRTFirstAndSecondPoint = angle((originalPoints[n - 1] - originalPoints[0]),
                                                                   (originalPoints[1] - originalPoints[0]));
    ld alpha = angleBetweenLastAndFirstPointWRTFirstAndSecondPoint; //angle to move into next fractal dimension

    cin >> d >> f;
    Point<ld> position = originalPoints[0];
    ld currentAngle = (originalPoints[1] - originalPoints[0]).angle(); // angle wrt x axis
    ld distanceTraversed = 0;
    ld totalFractalLengthAtDepthD = totalInitialDistance * powl(totalInitialDistance / originalDistanceBetweenFirstAndLastPoint, d - 1);
    ld targetDistance = f * totalFractalLengthAtDepthD;
    ld scalingDownFactor = 1; //used to determine the dimensions etc of the current fractal we are on
    for (int depth = 1; depth <= d; depth++) {
      for (int i = 0; i < n - 1; i++) {
        ld lengthOfThisSegment = (originalDistanceBetweenPointIAndIPlus1[i] / scalingDownFactor);
        ld lengthOfThisSegmentAtDepthD = (lengthOfThisSegment *
                                          powl(totalInitialDistance / originalDistanceBetweenFirstAndLastPoint,
                                               d - depth));
        if (targetDistance > lengthOfThisSegmentAtDepthD + distanceTraversed - eps) { // we can walk it
          distanceTraversed += lengthOfThisSegmentAtDepthD;
          position = position + Point<ld>(lengthOfThisSegment * cosl(currentAngle),
                                          lengthOfThisSegment * sinl(currentAngle));
          // face next line in the fractal
          currentAngle += angleBetweenPointIMinus1IAndIPlus1[i + 1];
        } else {
          if (depth != d) {
            currentAngle += alpha; //enter next fractal depth

            // new lengths will by scaled down by this ratio
            scalingDownFactor *= originalDistanceBetweenFirstAndLastPoint / originalDistanceBetweenPointIAndIPlus1[i];
          }
          break;
        }
      }
    }
    ld distanceToStillMove = targetDistance - distanceTraversed;
    if (distanceToStillMove > eps) //ending distance to move
      position = position + Point<ld>(distanceToStillMove * cosl(currentAngle), distanceToStillMove * sinl(currentAngle));
    cout << fixed << setprecision(10) << position.x << " " << position.y << "\n";
  }
}

#undef ll
#undef ld
#undef u


/*
 * Our strategy is to "walk" the fractal.
 * We can define a unit of the fractal by considering its base axis to be the line connecting the first and last points.
 * The length of the unit is the sum of the line segments
 * That ratio remains constant no matter how you scale up/down the fractal or rotate it.
 * We can use this ratio to zoom out of depths of fractals and compute how much length a given line segment would contribute in the final fractal
 * We have 2 properties: a position, and an orientation. when we move, the orientation controls the direction we move in.
 * At any point, our orientation must be towards the next point we are considering jumping to.
 * If the distance contributed by the segments between our current location and that point is less than the fraction of length we have to cover, we can move to that point directly
 * If it isn't we need to look at a smaller distance to cover, i.e. a point at the next depth of the fractal. We may need to change our orientation accordingly (called alpha in code).
 * At the end, we might have to walk a little bit along our current path (when all fractal depths have been exhausted and we still have to cover some distance)
 */