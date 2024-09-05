/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
#define u unsigned
using namespace std;
ll d, cur_price, prev_price, ans = 100; //ans is 100 initially since she has $100

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> d;
  cin >> prev_price; //can do this because if d is 1, she will never sell. so we do not need to iterate at all
  for (int i = 0; i < d - 1; i++) {
    cin >> cur_price;
    if (cur_price > prev_price) //she would have profited by buying yesterday and selling today.
      // Can also write in 1 line as max(0, <below num>). Would emulate her buying and selling for net 0.
      ans += (cur_price - prev_price) * //profit per stock sold
        (min(ans / prev_price, (ll) 100000)); //number of stocks she would have. total money/price she sold them for yesterday. upperbounded by 100000 since max stocks of company
    prev_price = cur_price;
  }
  cout << ans;
  return 0;
}