/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
#define ld long double
#define u unsigned
#define DEBUG false
using namespace std;

typedef struct customStackStruct {
  int s[100000] = {-1};
  int size = 0;
  int top = -1;

  void push(int number) {
    s[size++] = number;
    top = number;
#if DEBUG
    s[size] = -1;
#endif
  }

  void pop() {
    top = s[--size - 1];
#if DEBUG
    s[size] = -1;
#endif
  }

  [[nodiscard]] bool empty() const {
    return !size;
  }

  void clear() {
    size = 0;
  }
} customStack;

ll n, hist[100000], startIndex = 1000001, endIndex, tmpStartIndex;
customStack s; //monotonically increasing(non-decreasing) stack
ll maxArea = 0, tmpArea;

int main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> hist[i];
  ll tp;
  int i = 0;
  // understanding of algorithm for max rectangular area taken from https://www.geeksforgeeks.org/largest-rectangular-area-in-a-histogram-using-stack/
  // Obviously tweaked to support storing starting and ending index

#define FIND_MAX_AREA {                                                                                                                                       \
  /* numbers were increasing/stable, now new entry is decreasing. So we find area corresponding to our peak */                                                \
  tp = s.top;                                                                                                                                                 \
  s.pop();                                                                                                                                                    \
  tmpStartIndex = s.empty() ? 0 : s.top + 1; /* element at index s.top will be smaller/eq to our rectangles height. So, rectangle starts after it. */         \
  tmpArea = hist[tp] * ((i - 1) - tmpStartIndex + 1); /* we have hit a "peak". So i-1 is part of the rectangle since it's the peak. height * (x2 - x1 + 1) */ \
  if (maxArea < tmpArea) {                                                                                                                                    \
    maxArea = tmpArea;                                                                                                                                        \
    endIndex = i;                                                                                                                                             \
    startIndex = tmpStartIndex;                                                                                                                               \
  } else if (maxArea == tmpArea) {                                                                                                                            \
    if (tmpStartIndex < startIndex) {                                                                                                                         \
      endIndex = i;                                                                                                                                           \
      startIndex = tmpStartIndex;                                                                                                                             \
    }                                                                                                                                                         \
  }                                                                                                                                                           \
}

  while (i < n) {
    if (s.empty() || hist[s.top] <= hist[i]) {
      s.push(i);
      ++i;
    } else FIND_MAX_AREA
  }

  // we could have leftover elements. Compute for each of them. Note that i = n for all these elements, i.e. this height would be valid all the way to the end.
  // eg 2 3 4 5 4. u could make rectangles of height 2 and 3 and 4 that have different starting pts but all end at the end
  while (!s.empty()) FIND_MAX_AREA

  //1-indexing startIndex & endIndex
  cout << startIndex + 1 << " " << endIndex << " " << maxArea;
  return 0;
}