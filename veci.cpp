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

//q effectively reduces to finding next permutation of a number
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int nums[6];
  int index=0;
  char c;
  while(true) { //store in array
    c = getchar();
    if (c < '0' || c > '9') break;
    nums[index++] = c - '0';
  }
  if (!next_permutation(nums, nums + index)) {
    cout << 0; // digits are non-increasing
    return 0;
  }
  int *ptr = nums; //output as many digits as were present in input
  while (index--) cout << *(ptr++);
  return 0;
}