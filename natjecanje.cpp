/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned short n, s, r;
    cin >> n >> s >> r;
    unsigned short ans = 0;
    map<short, bool> damaged, reserve;
    for (short i = 0; i < s; ++i) {
        unsigned short a;
        cin >> a;
        damaged[a] = true;
    }
    for (short i = 0; i < r; ++i) {
        unsigned short a;
        cin >> a;
        if (damaged[a]) { // If a team both has a damaged boat and a reserve, it will use reserver for itself
            damaged[a] = false;
        } else {
            reserve[a] = true;
        }
    }
    for (short i = 1; i <= n; ++i) { // 1-based indexing
        if (damaged[i]) {
            // since we're iterating from left to right, we check the left boat first. Needed for cases like RDRD, where ans should be 0.
            if (reserve[i - 1]) {
                reserve[i - 1] = false;
            } else if (reserve[i + 1]) {
                reserve[i + 1] = false;
            } else {
                ++ans;
            }
        }
    }
    cout << ans << "\n";
    return 0;
}

/* Problem Statement: https://open.kattis.com/problems/natjecanje
 *
 * As you know, a kayaking competition is going on as we speak. Unfortunately strong winds have damaged a few kayaks, and the race starts in 5 minutes!
 * Fortunately, some teams have brought reserve kayaks. Since kayaks are bulky and hard to carry, teams are willing to lend kayaks to opposing teams if and only if they are starting immediately next to them.
 * For example, team with the starting number 4 will lend its reserve kayak only to teams 3 and 5.
 * Of course if some team did bring a reserve and its kayak was damaged, they will use it themselves and not lend it to anyone.
 *
 * You as the organizer now need to know, what is the minimal number of teams that cannot start the race, not even in borrowed kayaks.
 *
 * Input:
 * The first line of input contains three integers N (2 <= N <= 10), total number of teams,
 * S (2 <= S <= N), number of teams with damaged kayaks and
 * R (1 <= R <= N), number of teams with reserve kayaks.
 * The second line contains exactly S numbers, the starting numbers of teams with damaged kayaks. The second line will not contain duplicates.
 * The third line contains exactly R numbers, the starting numbers of teams with reserve kayaks. The third line will not contain duplicates
 *
 * Output:
 * The first and only line of output should contain the smallest number of teams that cannot start the competition.

Sample Input 1
5 2 3
2 4
1 3 5

Sample Output 1
0

Sample Input 2
5 2 1
2 4
3

Sample Output 2
1
*/