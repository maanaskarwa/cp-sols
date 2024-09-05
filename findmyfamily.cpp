/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
#define vi vector<int>

using namespace std;

const int mxn = 3e5;
int n;
int heights[mxn], maxToRight[mxn];
vi answerIndices;
set<int> elementsToLeft;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  int k;
  cin >> k;
  answerIndices.reserve(k);
  int count = 0;
  for (int i = 1; i <= k; i++) {
    cin >> n;
    memset(maxToRight, 0, n * sizeof(maxToRight[0]));
    elementsToLeft.clear();
    for (int j = 0; j < n; j++) cin >> heights[j];
    int prevMax = heights[n - 1], curMax;
    maxToRight[n - 1] = prevMax;
    for (int j = n - 2; j >= 0; j--) { //find max element to right
      curMax = max(prevMax, heights[j]);
      maxToRight[j] = curMax;
      prevMax = curMax;
    }
    elementsToLeft.insert(heights[0]);
    const _Rb_tree_const_iterator<int> end = elementsToLeft.end();
    _Rb_tree_const_iterator<int> nextLargestElement;
    for (int j = 1, element; j < n - 1; j++) {
      element = heights[j];
      // we need to check if there is a single element on the left that's larger than
      // the current number and
      // we need to find a pair such that right > left > element
      // we have max number on right. if min number larger on left is less, we have a pair
      nextLargestElement = elementsToLeft.upper_bound(element);
      elementsToLeft.insert(element);
      if (nextLargestElement != end && *nextLargestElement < maxToRight[j + 1]) { // check if we have a pair
        count++;
        answerIndices.push_back(i);
        break;
      }
    }
  }
  cout << count << "\n";
  for (auto c: answerIndices) cout << c << "\n"; //output valid indices
}