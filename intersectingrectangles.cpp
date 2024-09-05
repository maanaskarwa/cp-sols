/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>
using namespace std;

typedef struct {
  int x;
  int ySmall;
  int yBig;
  bool startOfPoint;
} point;

auto compare = [](point p1, point p2) {
  return p1.x < p2.x;
};

set<point, decltype(compare)> pointEvents(compare);
set<pair<int, int>> yIntervals, reverseyIntervals;
int n;
int x1, y11, x2, y2; //apparently y1 is a reserved variable name


/*
 * Logic: Kinds of intersections: (maybe don't do this in real contests)
 *         |-------|       |------------|         |---------------|              |---------------|
 * |-------+----|  |       |       |----+--|      |          |----+---|     |----+---|           |
 * |       |----+--|       |-------+----|  |      |          |----+---|     |----+---|           |
 * |---------------|   ,           |-------|   ,  |---------------|      ,       |---------------|    ,
 *
 *     |--------|          |--------------|            |-------|
 *  |--+--------+--|       |              |       |----+-------+-----|
 *  |  |--------+  |       |    |-----|   |       |    |       |     |
 *  |              |       |----+-----+---|       |----+-------+-----|
 *  |--------------|   ,        |-----|        ,       |-------|
 *
 *
 *  Sort by the x-coordinates and line sweep. Start of a rectangle is an event, end of rectangle is an event
 *  At each event, check if the given rectangle's y-interval overlaps with the y-intervals of the currently open rectangles
 *  Open Rectangle = have handled starting event, have not seen end event yet
 *
 *  kinds of overlaps: Given input:           -------          ------     -----------
 *                     Overlapping intervals:     ------  , -----      ,     -----
 *
 *                     Note that       ------
 *                                 -------------- need not overlap. Eg:   |--------------------------
 *                                                                        |  |-----
 *                                                                        |  |-----
 *                                                                        |---------------------------
 *                            but ----------------- will.      |-------------------
 *                                   ----------           |----+----------
 *                                                        |    |
 *                                                        |----+----------
 *                                                             |-------------------
 */

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  set<pair<int, int>> s;
  cin >> n;

  while (n--) {
    cin >> x1 >> y11 >> x2 >> y2;
    pointEvents.insert({x1, y11, y2, true});
    pointEvents.insert({x2, y11, y2, false});
  }

#define ANS  \
{            \
  cout << 1; \
  return 0;  \
}

#define PANIC  \
{            \
  return 2;  \
}

#define SOLVE \
auto upperBound = yIntervals.upper_bound(interval); /* find next pair that starts after given y-interval start */\
  if (upperBound != yIntervals.end() && upperBound->first <= interval.second) ANS /* if the interval's start is before our interval ends, overlap */\
  auto reverseupperBound = reverseyIntervals.upper_bound(reverseinterval);\
  if (reverseupperBound != reverseyIntervals.end() && reverseupperBound->first <= reverseinterval.second) ANS

  for (auto &event: pointEvents) {
    // use reverse interval to find    --------- cases. Upper bound on regular interval will not be able to find these. So, invert all intervals
    //                              ------
    pair<int,int> interval = {event.ySmall, event.yBig}, reverseinterval = {-event.yBig, -event.ySmall};

    if (event.startOfPoint) {
      // check for current intervals, then insert existing one so that you dont get a false +ve
      SOLVE

      if (!yIntervals.insert(interval).second) PANIC
      if (!reverseyIntervals.insert(reverseinterval).second) PANIC
    } else {
      if (!yIntervals.erase(interval)) PANIC
      if (!reverseyIntervals.erase(reverseinterval)) PANIC

      // remove current intervals first. same logic, false positive
      SOLVE
    }
  }
  cout << 0;
}