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

char currentChar, prevChar = 0, input[100000];
bool alreadyContains[26]; // use array instead of set, input is fixed and limited
int n = 0; //stores reduced length of input
u ll ans = 0;

/*
 * Only 26 possible ways to end a sequence (a - z)
 * For each possible ending, loop through the input. Maintain a set of letters you've seen.
 * In the sample input abbcccddddeeeee, the 10 itineraries in the ans are: ab, abbc, abbcccd, abbcccdddde, bc, bcccd, bcccdddde, cd, cdddde, de
 * Note that if there are consecutive letters and you take the first, you have to take them all. So consecutive same letters can actually be reduced to just one letter.
 * 
 * So count number of sequences ending with a, b,.. so on.
 */

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(alreadyContains,false, sizeof(alreadyContains));
  memset(input,0, sizeof(input));
  while (true) {
    currentChar = (char) getchar();
    if (currentChar < 'a' || currentChar > 'z') break;
    if (prevChar == currentChar) { //ignore consecutive same letters
      continue;
    } else {
      input[n++] = currentChar;
      prevChar = currentChar;
    }
  }
  for (char c = 'a'; c <= 'z'; c++) { //check for sequences ending with each letter
    memset(alreadyContains, false, sizeof(alreadyContains));
    for (auto& ch:input) {
      if (ch ==0) break;
      if (ch == c) { //assuming this is the end of a sequence, add the number of letters we visited between this c and the prev one (if any)
        for (auto contains: alreadyContains) if (contains) ++ans;
        memset(alreadyContains, false, sizeof(alreadyContains)); //reset
      } else alreadyContains[ch - 'a']=true;
    }
  }
  cout << ans;
  return 0;
}