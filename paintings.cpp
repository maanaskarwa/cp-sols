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

int testCases, n, m;
unordered_map<string, int> colorToIndex;
string inputcolors[13];
bool hideous[13][13];

vector<int> paintingColors(13), firstPainting(13);
bool containedInPainting[13];

ll paintingCount = 0;

string temp1, temp2;

//maintain possible colors forming a painting in paintingColors. add elements to vec if the color is allowed to be added
void solve() {
  if (paintingColors.size() == n) { //we've reached a full painting. increment count and handle if first such painting
    //since we are iterating over the colors in descending order of preference, the first full painting will be the most favorite one,
    // since the most preferred will have been presented the earliest in the painting
    if (DEBUG) {
      cout << "sequence: ";
      for (auto &c: paintingColors) {
        cout << inputcolors[c] << " ";
      }
      cout << "\n";
    }
    paintingCount++;
    if (firstPainting.empty()) {
      for (auto &c: paintingColors) firstPainting.push_back(c);
    }
    return;
  }
  for (int index = 0; index < n; index++) {
    if (containedInPainting[index]) continue; //already took this color, do not want to repeat
    int s = paintingColors.size();
    if (s > 0 && hideous[index][paintingColors[s - 1]]) continue; //skip hideous pairs
    containedInPainting[index] = true; //add this color to the painting
    paintingColors.push_back(index);
    solve(); //recursively check all possible paintings that have this color at this spot
    paintingColors.pop_back();
    containedInPainting[index] = false; //done with paintings that have this color at this spot
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> testCases;
  while (testCases--) {
    memset(hideous, false, sizeof(hideous));
    memset(containedInPainting, false, sizeof(containedInPainting));
    paintingColors.clear();
    firstPainting.clear();
    paintingCount = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> temp1;
      inputcolors[i] = temp1;
      colorToIndex[temp1] = i;
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
      cin >> temp1 >> temp2;
      int t1 = colorToIndex[temp1];
      int t2 = colorToIndex[temp2];
      hideous[t1][t2] = true;
      hideous[t2][t1] = true;
    }
    solve();
    cout << paintingCount << "\n";
    for (auto &c: firstPainting) {
      cout << inputcolors[c] << " ";
    }
    cout << "\n";
  }
  return 0;
}