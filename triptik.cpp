/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define vi vector<int>
#define pii pair<int,int>
using namespace std;

const int mxn = 1e5;
int n, k;

//for coordinate compression
map<int, int> positionToIndexWhichIsAlsoPriority;

// used to cut down unnecessary queries on seg tree
int minCoord, maxCoord;

struct SegmentTreeNode {
    pii positionToPriority[4] = {{0, -1}, {0, -1}, {0, -1}, {0, -1}};
};

struct SegmentTree {
  // position to priority. upto k points in each list
  typedef SegmentTreeNode T;

  T res;
  int l, r, aPriority, bPriority;
  T combine(const T &a, const T &b) {
    // combine using 2 pointer approach. all lists
    // are sorted in descending order of priority
    for (l = 0, r = 0; l + r < k;) {
      aPriority = a.positionToPriority[l].second, bPriority= b.positionToPriority[r].second;
      if (aPriority >= 0 || bPriority >= 0) {
        if (aPriority >= 0 && bPriority >= 0) {
          if (aPriority > bPriority) {
            res.positionToPriority[l+r] = a.positionToPriority[l];
            l++;
          } else if (aPriority < bPriority) {
            res.positionToPriority[l+r] = b.positionToPriority[r];
            r++;
          } else {
            res.positionToPriority[l+r] = b.positionToPriority[r];
            l++, r++;
          }
        } else if (aPriority >= 0) {
          res.positionToPriority[l+r] = a.positionToPriority[l];
          l++;
        } else {
          res.positionToPriority[l+r] = b.positionToPriority[r];
          r++;
        }
      } else {
        res.positionToPriority[l+r] = {0,-1}; // null terminate res kind of
        break;
      }
    }
//    assert(res.size() <= k);
    return res;
  }


  T s[mxn<<1 | 1];// = vector<T>((mxn << 1) | 1); //2*mxn + 1

  void build() {
    // bottom up populate.
    // populate leaves, then work up
    // also store min and max coords, need for queries
    int index = n;
    for (auto const &p: positionToIndexWhichIsAlsoPriority) {
      s[index].positionToPriority[0] = {p.first, p.second};
      index++;
    }
    for (index = n - 1; index > 0; index--) {
      s[index] = combine(s[index * 2], s[index * 2 + 1]);
    }
    s[0] = s[1];
  }

  T query(int b, int e) { // query [b, e)
    if (b == e) return {};
    T ra = {}, rb = {};
    for (b += n, e += n; b < e; b >>= 1, e >>= 1) {
      if (b & 1) ra = combine(ra, s[b++]);
      if (e & 1) rb = combine(s[--e], rb);
    }
    return combine(ra, rb);
  }

  int mid;
  int indexOfCoordinate(int coordinate, bool trueForReturnLowerFalseForHigher) {
    /*
     *
     */

    l = n, r = (n << 1) - 1;
    while (l <= r) {
      mid = (l + r) >> 1;
      if (s[mid].positionToPriority[0].first == coordinate) {
        return mid-n;
      } else if (s[mid].positionToPriority[0].first > coordinate) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    return trueForReturnLowerFalseForHigher ? r - n : l - n;

  }

  T compressedQuery(int l1, int r1) {
    if (r1 == l1) {
      int index = indexOfCoordinate(l1, true);
      auto val = s[index+n];
      if (val.positionToPriority[0].first == l1 && val.positionToPriority[0].second >= 0) { // if zooming in on a coordinate with non existent viewport return empty
        return val;
      }
      return {};
    }
    if (r1 < minCoord || l1 > maxCoord) //querying outside valid coordinates
      return {};
    if (r1 > maxCoord && l1 < minCoord) { //querying entire space
      return s[0];
    }
    if (r1 > maxCoord) { // right limited to n
      return query(indexOfCoordinate(l1, false), n);
    }
    if (l1 < minCoord) { //left limited to 0
      return query(0, indexOfCoordinate(r1, true) + 1);
    }
    return query(indexOfCoordinate(l1, false), indexOfCoordinate(r1, true) + 1);
  }
};

SegmentTree tree;

struct State {
  int steps;
  int position;
  int zoomExponent; //allow upto -1.
  int priority;
};

queue<State> bfsQueue;
const int maxZoom = 29;
//maintain all visited states.
// a valid state has a position and a zoom
vector<vector<bool>> visitedPositionAndZoomExponent(mxn + 1, vector<bool>(maxZoom + 1, false));
SegmentTreeNode queryPoints;
State bfsTop;

//store ans
vi numOfStepsToViewPort(mxn + 1, -1);

/*
 * Logic: We will BFS over a graph of states. a state contains the center of the viewport and the zoom
 * we can express zoom as exponenent of 2. note that max useful zoom is log_2(2 * 1e8) ~ 28
 * So zooms between 0 and 29 are valid
 *
 * How do we find the connected vertices for each vertex of the graph?
 * Zoom level +- 1 are always connected (unless you are at min max zoom)
 *
 * Points you can visit are connected.
 * Finding these in O(n) is too slow, use segment tree for range queries
 * Merge operation between 2 ranges is choosing top k points between 2 ranges
 *
 * When you reach a point, mark it.
 */

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  cin >> n >> k;
  for (int i = 0,tmp; i < n; i++) {
    cin >> tmp;
    // coordinate compression since original number of points won't fit in
    // any data structure
    positionToIndexWhichIsAlsoPriority[tmp] = i;
  }

  maxCoord = positionToIndexWhichIsAlsoPriority.rbegin()->first, minCoord=positionToIndexWhichIsAlsoPriority.begin()->first;
  int maxDelta = maxCoord-minCoord;
  int actualMaxZoom=0;
  while (maxDelta) {
    actualMaxZoom++;
    maxDelta >>= 1;
  }

  tree.build();
  // assign so that you can use it in bfs although no viewport at 0
//  positionToIndexWhichIsAlsoPriority[0] = n;

  bfsQueue.push({0, 0, 0,n});
  visitedPositionAndZoomExponent[n][0] = true;

  while (!bfsQueue.empty()) {
    bfsTop = bfsQueue.front();
    bfsQueue.pop();

    int compressedCoord = bfsTop.priority;
    int zoomOffset = 1 << bfsTop.zoomExponent;
    int l = bfsTop.position - zoomOffset, r = bfsTop.position + zoomOffset;
    queryPoints = tree.compressedQuery(l, r); // options to move viewport
    for (auto const &positionAndPriority: queryPoints.positionToPriority) {
      if (positionAndPriority.second < 0) // points are over
        break;
      if (positionAndPriority.first == bfsTop.position) { // can see own self
        if (numOfStepsToViewPort[compressedCoord] == -1 || numOfStepsToViewPort[compressedCoord] > bfsTop.steps) {
          numOfStepsToViewPort[compressedCoord] = bfsTop.steps;
        } // note that you might not see yourself if you are surrounded by higher prioirity points
        // the solution is over when you are centered and can see yourself
        continue;
      }
      if (!visitedPositionAndZoomExponent[positionAndPriority.second][bfsTop.zoomExponent]) {
        bfsQueue.push({bfsTop.steps + 1, positionAndPriority.first, bfsTop.zoomExponent,positionAndPriority.second});
        visitedPositionAndZoomExponent[positionAndPriority.second][bfsTop.zoomExponent] = true;
      }
    }

    if (bfsTop.zoomExponent <= actualMaxZoom &&
        !visitedPositionAndZoomExponent[compressedCoord][bfsTop.zoomExponent + 1]) { //zoom out
      bfsQueue.push({bfsTop.steps + 1, bfsTop.position, bfsTop.zoomExponent + 1, compressedCoord});
      visitedPositionAndZoomExponent[compressedCoord][bfsTop.zoomExponent + 1] = true;
    }
    if (bfsTop.zoomExponent > 0 &&
        !visitedPositionAndZoomExponent[compressedCoord][bfsTop.zoomExponent - 1]) { //zoom in
      bfsQueue.push({bfsTop.steps + 1, bfsTop.position, bfsTop.zoomExponent - 1,compressedCoord});
      visitedPositionAndZoomExponent[compressedCoord][bfsTop.zoomExponent - 1] = true;
    }
    if (bfsTop.zoomExponent == 0) {
      if (numOfStepsToViewPort[compressedCoord] == -1 ||
          numOfStepsToViewPort[compressedCoord] > bfsTop.steps + 1)
        numOfStepsToViewPort[compressedCoord] = bfsTop.steps + 1; //zoom in to 0.5 you can only see yourself
    }
  }

  for (int i = 0; i < n; i++)
    cout << numOfStepsToViewPort[i] << "\n";
}

#undef vi
#undef pii