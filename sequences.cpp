/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
#define ld long double
#define u unsigned
#define DEBUG false

#define MODULONUM 1000000007

using namespace std;

ll modExp2(ll exp) {
  ll res = 1, base = 2;
  while (exp) {
    if (exp & 1)
      res = (res * base) % MODULONUM;
    exp = exp >> 1;
    base = (base * base) % MODULONUM;
  }
  return res;
}


int main() {
  ll prevZeroCount = 0, prevOneCount = 0, prevQMarkCount = 0;
  ll curZeroCount = 0, curOneCount = 0, curQMarkCount = 0;
  ll ans = 0;
#define HANDLE_CURRENT_NUM_ZERO \
  if (!prevQMarkCount) {/*no ?s, straight product with number of 1s. In each case, multiply with number of q marks to the right*/ \
    ans = (ans + prevOneCount) % MODULONUM; \
  } else { \
    /*ignoring the mods, this is saying ans += (2^(prevQ-1))(prevQ+(2*prev1))*/ \
    ans = (ans + (modExp2(prevQMarkCount - 1) * ((prevQMarkCount + (prevOneCount << 1))))) % MODULONUM;\
  }
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  char c;
  while (true) {
    c = getchar();
    if (c == '0') {
      curZeroCount = prevZeroCount + 1;
      HANDLE_CURRENT_NUM_ZERO
    } else if (c == '1') { // no action except incrementing count
      curOneCount = prevOneCount + 1;
    } else if (c == '?') { //treat as 0
      // could be a 0 or 1, so previous ans gets multiplied by 2
      ans <<= 1;
      curQMarkCount = prevQMarkCount + 1;
      HANDLE_CURRENT_NUM_ZERO
    } else break;
    prevQMarkCount = curQMarkCount;
    prevOneCount = curOneCount;
    prevZeroCount = curZeroCount;
  }
  cout << ans % MODULONUM;
  return 0;
}

// Old logic. New one is single pass

///*
// * Author: Maanas Karwa
// * It is ok to share my code anonymously for educational purposes
// * */
//
//#include <bits/stdc++.h>
//
//#define ll long long
//#define ld long double
//#define u unsigned
//#define DEBUG false
//
//#define MODULONUM 1000000007
//
//using namespace std;
//
//ll modExp2(ll exp) {
//  ll res = 1, base = 2;
//  while (exp > 0) {
//    if (exp & 1)
//      res = (res * base) % MODULONUM;
//    exp = exp >> 1;
//    base = (base * base) % MODULONUM;
//  }
//  return res;
//}
//
//string input;
//ll prevZeroCount = 0, prevOneCount = 0, prevQMarkCount = 0;
//ll curZeroCount = 0, curOneCount = 0, curQMarkCount = 0;
//ll ans = 0;
//ll totalQMarkCount = 0;
//
///*
// * Logic for finding number of inversions: Find contribution of each element to the final ans.
// * 1s do not contribute to any inversions (stay wherever they are)
// * 0s do contribute. A 0 cannot have any 1s to the left. So for each 0, the number of 1s to the left is the number of inversions
// * A ? can behave as a 0 and a 1. So in terms of contribution, the only value is when it's a 0
// *
// * To find the contribution of a 0, we need to know the following:
// * 1. The number of 1s to the left (to find number of inversions)
// * 2. The number of ?s to the left (to find number of inversions, since ?s can behave as 1s)
// * 3. The number of ?s to the right (let k be the contribution of a 0 to the answer. Note that we have accounted for all cases of 1s and ?s to the left in this ans.
// *    How many times should we count this contribution? The number of times it occurs, which is determined by the remaining ?s. If there are p ?s, the contribution will be added 2^p times since
// *    that is the number of sequences possible)
// *
// * Given these 3 numbers, here's the formula:
// * if there are no ?s on the left, the number of inversions is just the number of 1s
// * else, we will simulate each ? being a 0 or 1. As a 0, it won't have any contribution to the inversions. As a 1, it will have 1.
// * Let q be num of ?s, n be number of 1s. The number of 1s will be n at a minimum, and n+q at a maximum
// * qC0(0 + n) + qC1(1 + n) + qC2(2 + n) + qC3(3 + n) + ... + qCq(q+n)
// *
// * For any qCy, we are basically choosing y ? marks out of q to be our 1s. In that situation, the total number of 1s is y + n. Hence all terms are of the form qCy(y + n)
// * sum(qCy(y+n)) - do this on paper, comes out to be q.2^(q-1) + n.2^q
// * Since we need to do mod exp of 2^q, we do not want to compute it twice. Rewrite as (2^(q-1)).(q+2n)
// * And multiply this with 2^(numRightQMarks) before adding, since those are the number of cases
// */
//int main() {
//  ios_base::sync_with_stdio(false);
//  cin.tie(nullptr);
//  cin >> input;
//  int inputLen = input.length();
//  for (auto c: input) {
//    if (c == '?')
//      totalQMarkCount++; //will use totalQMarkCount to find the number of q marks to the right, since we are storing a cumulative sum of q marks to the left already
//  }
//#define HANDLE_CURRENT_NUM_ZERO \
//  if (prevQMarkCount == 0) {/*no ?s, straight product with number of 1s. In each case, multiply with number of q marks to the right*/ \
//    ans = (ans + ((prevOneCount * modExp2(totalQMarkCount - curQMarkCount)) % MODULONUM)) % MODULONUM; \
//  } else { \
//    /*ignoring the mods, this is saying ans += (2^(prevQ-1))(prevQ+(2*prev1))*/ \
//    ans = (ans + ((((modExp2(prevQMarkCount - 1) * ((prevQMarkCount + (prevOneCount * 2)) % MODULONUM)) % MODULONUM) * \
//                   modExp2(totalQMarkCount - curQMarkCount)) % MODULONUM)) % MODULONUM;\
//  }
//
//  for (int i = 0; i < inputLen; i++) {
//    char c = input[i];
//    if (c == '0') {
//      curZeroCount = prevZeroCount + 1;
//      HANDLE_CURRENT_NUM_ZERO
//    } else if (c == '1') { // no action except incrementing count
//      curOneCount = prevOneCount + 1;
//    } else if (c == '?') { //treat as 0
//      curQMarkCount = prevQMarkCount + 1;
//      HANDLE_CURRENT_NUM_ZERO
//    } else return 2;
//    prevQMarkCount = curQMarkCount;
//    prevOneCount = curOneCount;
//    prevZeroCount = curZeroCount;
//  }
//  cout << ans % MODULONUM;
//  return 0;
//}