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

//store all nums in input, and most recent 3 numbers separately. Used for determining what "state" the array is in
int input[1000001], currentNum = 0, prev1 = 0, prev2 = 0;
ll n, currentMountainTopIndex = 10e7, currentMaxSeqLength = -1;
// valid mountainTop simply indicates that we have encountered a mountain top. Used to check when
bool validMountainTop = false, validOnWayDown = false;

/*
 * Maintain state of array. Possible states:
 * / : continuously increasing. potentially part of a seq. No separate action needed however, since we validate on the "downhill" path
 * \/ : was decreasing, hit a min, now increasing. marks the end of a potential seq and the start of a new one
 * _/ : prev2 == prev1, current is larger. start of new potential seq
 * /\ : mountain top. so now, on the way "down", we can take steps to check if it is a palindrome etc etc by comparing input terms to their "mirror" about the mountain top
 * \ : continuously decreasing. if a mountain top was recorded before this, we will be checking for the palindrome property at each step
 * -\ : prev2 == prev1, current is smaller. no action
 * /- : prev1 == current, prev2 is smaller. no action
 * -- : all equal. no action
 *
 * Based on these states, we can check sequences accordingly. Note that we can only recognize states after we have all 3 numbers, so currentNum is the rightmost input, prev1 is the middle, prev2 is the left
 *
 * Edge cases: Combinations of 1) sequences of length 3, 2) located in absolute beginning/ending
 *
 */

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  if (n < 3) { //edge case
    cout << -1;
    return 0;
  }
  cin >> currentNum;
  prev2 = currentNum;
  input[0] = currentNum;
  cin >> currentNum;
  prev1 = currentNum;
  input[1] = currentNum;
  for (int i = 2; i < n; i++) {
    cin >> currentNum;
    input[i] = currentNum;

    // Have commented out states where no action is needed

    if (currentNum > prev1) {
      //if (prev1 > prev2) {
      //  /* / : No action */
      //} else
      if (prev1 < prev2) {
        /* \/ */
        if (validMountainTop) { // if we have encountered a mountain top before hitting this "valley", it means this could be the end of a sequence
          if (validOnWayDown) { //valid on way down checks all entries after a mountain top with their mirrors across the mountain top to check if the palindrome condition is met. If valid so far, capture seq length
            currentMaxSeqLength = max(currentMaxSeqLength, ((i - 1 - currentMountainTopIndex) << 1) + 1);
          }
        }
        //reset variables. mountain top will be reassigned the next time we hit a mountain top
        validOnWayDown = false;
        validMountainTop = false;
      }
      //else {
      //  /* _/ : No action */
      //}
    } else if (currentNum < prev1) {
      if (prev1 > prev2) {
        /* /\ */
        currentMountainTopIndex = i - 1;
        validMountainTop = true;
        validOnWayDown = true;
        // at mountain top, just need to check other side
        if (prev2 != currentNum) {
          validOnWayDown = false;
        }
      } else if (prev1 < prev2) {
        /* \  */
        if (validMountainTop && validOnWayDown) {
          bool sequenceOver = false;
          ll indexToCheck = (currentMountainTopIndex<<1) - i;
          if (indexToCheck < 0) { // cases like 3 4 3 2 1. For last 2 inputs, no mirror exists
            sequenceOver = true;
          } else if (input[indexToCheck] != input[i]) {
            validOnWayDown = false; //palindrome condition broken
            sequenceOver = true;
          }

          if (sequenceOver) {
            if (validOnWayDown) {
              currentMaxSeqLength = max(currentMaxSeqLength, ((i - 1 - currentMountainTopIndex) << 1) + 1); //draw logic out on pen paper
            }
            validOnWayDown = false;
            validMountainTop = false;
          }
        } else {
          validOnWayDown = false;
          validMountainTop = false;
        }
      }
      //else {
      //  /* -\ : No action*/
      //}
    } else {
      if (prev1 > prev2) {
        /* /- : No action*/
      } else if (prev1 < prev2) {
        /* \_ */
        if (validOnWayDown) {
          currentMaxSeqLength = max(currentMaxSeqLength, ((i - 1 - currentMountainTopIndex) << 1) + 1);
        }
        validOnWayDown = false;
        validMountainTop = false;
      }
      //else {
      //   /* __ : No action*/
      //}
    }
    prev2 = prev1;
    prev1 = currentNum;
  }
  if (validMountainTop && prev1 < prev2 && validOnWayDown) {
    currentMaxSeqLength = max(currentMaxSeqLength, ((n - 1 - currentMountainTopIndex) << 1) + 1);
  }
  // sequence will always have to be odd. No other way to satisfy mountain and palindrome properties. Kattis will throw run time in this case now since we're returning status code 2
  if ((currentMaxSeqLength & 1) == 0) return 2;
  cout << currentMaxSeqLength;
  return 0;
}