/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
#define u unsigned
#define vi vector<int>

u ll modExp(u ll base, u ll exp, u ll mod) {
  u ll res = 1;
  while (exp > 0) {
    if (exp & 1)
      res = (res * base) % mod;
    exp = exp >> 1;
    base = (base * base) % mod;
  }
  return res;
}

#define modInv(num, mod) modExp((num), ((mod) - 2), (mod))

using namespace std;
const u ll modulo1 = 1e9 + 7;
const u ll modulo2 = 1e9 + 9;

string s;
string substr;
unordered_map<u ll, vi > indicesOfSmallStrings;
u ll rollingHashSumOfMainString[200000][2]; // only use for big cases. big defined
u ll powMod[200000][2];
u ll invPowMod[200000][2];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  cin >> s;
  int len = s.length();
  int bigQuerySize = sqrt(len) / 20; // experimentally found, no logic
  substr.resize(len); //preallocation

  const u ll alphabetSize = 26;

  u ll powerModulo, invPowerModulo;
  invPowMod[0][0] = 1, invPowMod[0][1] = 1, powMod[0][0] = 1, powMod[0][1] = 1;
  rollingHashSumOfMainString[0][0] = s[0] - 'a' + 1, rollingHashSumOfMainString[0][1] = s[0] - 'a' + 1;
//precompute rolling hash of big string
  u ll modulo = modulo1;
  for (int j = 0; j <= 1; j++) {
    powerModulo = 1, invPowerModulo = 1;
    u ll invPow = modInv(alphabetSize, modulo);
    for (int i = 1; i < len; i++) {
      powerModulo *= alphabetSize;
      if (powerModulo > modulo) powerModulo %= modulo;
      powMod[i][j] = powerModulo;

      rollingHashSumOfMainString[i][j] = (rollingHashSumOfMainString[i - 1][j] + powerModulo * (s[i] - 'a' + 1)) % modulo;

      invPowerModulo *= invPow;
      if (invPowerModulo > modulo) invPowerModulo %= modulo;
      invPowMod[i][j] = invPowerModulo;
    }
    modulo = modulo2;
  }

  //preprocess possible smaller queries
  for (int subLen = 1; subLen <= bigQuerySize; subLen++) {
    for (int i = subLen - 1; i < len; i++) {
      u ll ans1, ans2;
      if (i == subLen - 1) {
        ans1 = rollingHashSumOfMainString[i][0];
        ans2 = rollingHashSumOfMainString[i][1];
      } else {
        ans1 = (((modulo1 + rollingHashSumOfMainString[i][0] - rollingHashSumOfMainString[i - subLen][0]) % modulo1) *
                invPowMod[i - subLen + 1][0]) % modulo1;
        ans2 = (((modulo2 + rollingHashSumOfMainString[i][1] - rollingHashSumOfMainString[i - subLen][1]) % modulo2) *
                invPowMod[i - subLen + 1][1]) % modulo2;
      }

      auto mainStringHash = (ans1 << 32) + ans2;
      indicesOfSmallStrings[mainStringHash].push_back(i - subLen + 1);
    }
  }

  int q, index;
  cin >> q;
  for (int ansIndex = 0; ansIndex < q; ansIndex++) {
    cin >> substr >> index;
    int subLen = substr.length()/*strlen(substr)*/;

    u ll prevRollingHashSumOfSubstring0 = substr[0] - 'a' + 1, prevRollingHashSumOfSubstring1 = substr[0] - 'a' + 1;
    u ll rollingHashSumOfSubstring0 = prevRollingHashSumOfSubstring0, rollingHashSumOfSubstring1 = prevRollingHashSumOfSubstring1;

    for (int i = 1; i < subLen; i++) {
      rollingHashSumOfSubstring0 = (prevRollingHashSumOfSubstring0 + powMod[i][0] * (substr[i] - 'a' + 1)) % modulo1;
      prevRollingHashSumOfSubstring0 = rollingHashSumOfSubstring0;

      rollingHashSumOfSubstring1 = (prevRollingHashSumOfSubstring1 + powMod[i][1] * (substr[i] - 'a' + 1)) % modulo2;
      prevRollingHashSumOfSubstring1 = rollingHashSumOfSubstring1;
    }

    u ll substrHash = (rollingHashSumOfSubstring0 << 32) + rollingHashSumOfSubstring1;

    if (subLen > bigQuerySize) { //compute using rolling hash O(n)
      u ll mainStringHash;

      int freqOfSubstring = 0;
      for (int i = subLen - 1; i < len; i++) {
        u ll ans1, ans2;
        if (i == subLen - 1) {
          ans1 = rollingHashSumOfMainString[i][0];
          ans2 = rollingHashSumOfMainString[i][1];
        } else {
          ans1 = (((modulo1 + rollingHashSumOfMainString[i][0] - rollingHashSumOfMainString[i - subLen][0]) % modulo1) *
                  invPowMod[i - subLen + 1][0]) % modulo1;
          ans2 = (((modulo2 + rollingHashSumOfMainString[i][1] - rollingHashSumOfMainString[i - subLen][1]) % modulo2) *
                  invPowMod[i - subLen + 1][1]) % modulo2;
        }

        mainStringHash = (ans1 << 32) + ans2;
        if (mainStringHash == substrHash) {
          freqOfSubstring++;
          if (freqOfSubstring == index) {
            cout << (i - subLen + 1) + 1 << "\n";
            break;
          }
        }
      }
      if (freqOfSubstring != index)
        cout << "-1\n";
    } else { //already computed, O(1) kinda
      auto indexInfo = indicesOfSmallStrings.find(substrHash);
      if (indexInfo == indicesOfSmallStrings.end() || indexInfo->second.size() < index) {
        // either does not exist or not enough substrings exist
        cout << "-1\n";
      } else
        cout << indexInfo->second[index - 1] + 1 << "\n";
      // 1-indexing handling
    }
  }
}

#undef ll
#undef u