
/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

/*
 * Comparators for min and max priority queues
 */

auto min_compare = [](const pair<int, int> &p1, const pair<int, int> &p2) {
    if (p1.first != p2.first) return p1.first > p2.first;
    return p1.second > p2.second;
};
auto max_compare = [](const pair<int, int> &p1, const pair<int, int> &p2) {
    if (p1.first != p2.first) return p1.first < p2.first;
    return p1.second < p2.second;
};

/*
 * Logic:
 * Maintain a priority queue of the min and the max samples within the "window", check if it's valid silence
 * Run an m-width window through each iteration
 * A hashmap would have been more efficient, I wasn't able to figure out my comparators though.
 */

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, c;

  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(min_compare)> min_sound(
    min_compare); //pair<value, index>
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(max_compare)> max_sound(
    max_compare); //pair<value, index>

  bool silence_exists = false;
  cin >> n >> m >> c;
  int samples[n];
  for (int i = 0; i < n; ++i) {
    int sample;
    cin >> sample;
    samples[i] = sample;
    if (i < m-1) {
      // prep for first iteration. We need all of our sliding window values ready except the last one
      // The "last" or right-most one is what makes this window different from the previous
      min_sound.emplace(sample, i);
      max_sound.emplace(sample, i);
    }
  }
  for (int i = 0, j = i + m - 1; j < n; ++i, ++j) {

    // have to clear junk values till only the current window remains
    // if statement not enough, need while because we could accidentally uncover an invalid input by only popping the top
    while (min_sound.top().second < i) {
      min_sound.pop();
    }
    while (max_sound.top().second < i) {
      max_sound.pop();
    }
    min_sound.emplace(samples[j], j);
    max_sound.emplace(samples[j], j);
    if (max_sound.top().first - min_sound.top().first <= c) {
      if (!silence_exists) silence_exists = true;
      cout << i + 1 << "\n";
    }
  }
  if (!silence_exists) cout << "NONE";
  return 0;
}