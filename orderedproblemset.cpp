/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */
#include <bits/stdc++.h>

using namespace std;
int n, difficulties[50];

int mx(int l, int r) { //helper func, find max in given range inclusive
  if (l < 0)
    l = 0;
  if (r >= n)
    r = n - 1;
  int mx = -1;
  for (int i = l; i <= r; i++)
    mx = max(mx, difficulties[i]);
  return mx;
}

int mn(int l, int r) { //helper func, find min in given range inclusive
  if (l < 0)
    l = 0;
  if (r >= n)
    r = n - 1;
  int mn = 1e9;
  for (int i = l; i <= r; i++)
    mn = min(mn, difficulties[i]);
  return mn;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> difficulties[i];

  bool valueExists = false;
  for (int k = 2; k <= n; k++) {
    if (n % k == 0) {
      int elementsPerSet = n / k;

      bool valid = true;
      for (int section = 1; section < k && valid; section++)
        //if (max of prev section > min of current section) invalid
        if (mx((section - 1) * elementsPerSet, section * elementsPerSet - 1) >
            mn(section * elementsPerSet, (section + 1) * elementsPerSet - 1))
          valid = false;

      if (valid) {
        valueExists = true;
        cout << k << "\n";
      }
    }
  }

  if (!valueExists)
    cout << "-1\n";
}