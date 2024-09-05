/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ld long double
#define pii pair<int,int>
#define PRECISION(n) fixed << setprecision((n))

using namespace std;

ld xInit, yInit;
pair<ld, ld> coords[20];
const ld inf = 1e9;

int n;
// distance having covered points in the bitmask and having gone back home
vector<ld> distHavingCoveredMask(1 << 20, inf);
pair<ld, ld> initialPos;
// precompute distances between points
ld distanceFromInitial[20], distanceBetweenPoints[20][20];

ld pointDist(const pair<ld, ld> &p1, const pair<ld, ld> &p2) {
  return sqrtl(((p1.first - p2.first) * (p1.first - p2.first)) + (p1.second - p2.second) * (p1.second - p2.second));
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  cin >> xInit >> yInit;
  initialPos = {xInit, yInit};
  cin >> n;
  ld maxDist = 0, d, t1, t2;
  pair<ld, ld> c;

  for (int i = 0; i < n; i++) {
    cin >> t1 >> t2;
    c = {t1, t2};
    coords[i] = c;
    d = pointDist(initialPos, c);
    distanceFromInitial[i] = d;
    maxDist = max(maxDist, d); // store max distance of a point from starting location
    distHavingCoveredMask[1 << i] = 2 * d;
  }

  for (int i = 0; i < n; i++) { //precompute distances between points
    for (int j = i + 1; j < n; j++) {
      d = pointDist(coords[i], coords[j]);
      distanceBetweenPoints[i][j] = d;
      distanceBetweenPoints[j][i] = d;
    }
  }

  distHavingCoveredMask[0] = 0; //base case
  int upperBound = (1 << n) - 1;
  for (int i = 0; i <= upperBound; i++) {
    int pointsToVisit = upperBound & ~i; // unvisited points
    int indexOfP, p;
    while (pointsToVisit) {
      indexOfP = __builtin_ctz(pointsToVisit);
      p = 1 << indexOfP;
      pointsToVisit -= p;
      //take one chicken, drop in a point, come back home
      distHavingCoveredMask[i | p] = min(distHavingCoveredMask[i | p], distHavingCoveredMask[i] +
                                                                       2 * distanceFromInitial[indexOfP]);
    }

    pointsToVisit = upperBound & ~i;
    while (pointsToVisit) {
      // take 2 chickens and visit all pairs of unvisited points
      indexOfP = __builtin_ctz(pointsToVisit), p = 1 << indexOfP;
      pointsToVisit -= p;
      int pointsToVisit2 = pointsToVisit;
      int indexOfP1, p1;
      while (pointsToVisit2) {
        indexOfP1 = __builtin_ctz(pointsToVisit2), p1 = 1 << indexOfP1;
        pointsToVisit2 -= p1;
        distHavingCoveredMask[i | p | p1] = min(distHavingCoveredMask[i | p | p1], distHavingCoveredMask[i] +
                                                                                   distanceFromInitial[indexOfP] +
                                                                                   distanceBetweenPoints[indexOfP][indexOfP1] +
                                                                                   distanceFromInitial[indexOfP1]);
      }
    }
  }
  //greedy - we visit the farthest point last. that way, we don't need to come back and traverse the longest distance
  cout << PRECISION(7) << distHavingCoveredMask[upperBound] - maxDist;
}