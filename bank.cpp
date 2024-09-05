/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> actions_at_time;

bool add_value(int time, int value) {
    if (time < 0) return false;
    if (actions_at_time[time] == 0) {
        actions_at_time[time] = value;
        return true;
    }
    return add_value(time - 1, value);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t;
    cin >> n >> t;
    actions_at_time.reserve(t);
    pair<int, int> people[n]; // <value, time>
    for (int i = 0; i < n; ++i) cin >> people[i].first >> people[i].second;
    // sort in descending order based on money
    sort(people, people + (sizeof(people) / sizeof(people[0])), [](const pair<int, int> &p1, const pair<int, int> &p2) {
        return p1.first > p2.first;
    });
    int number_people_served = 0;
    int ans = 0;
    // Greedy assumption: Each person should be served as late as possible, since somebody with 40 mins can be served any time from 0 to 40, but somebody with 0 needs to be served now.
    // Looping through array sorted in descending order of money, place them as late as possibly allowed. If spot already occupied, try one lower recursively
    for (int i = 0; i < n && number_people_served <= t; ++i) {
        if (add_value(people[i].second, people[i].first)) {
            ans += people[i].first;
            ++number_people_served;
        }
    }
    cout << ans << "\n";
    return 0;
}

/* Problem Statement: https://open.kattis.com/problems/bank
 *
 * Oliver is a manager of a bank near KTH and wants to close soon. There are many people standing in the queue wanting to put cash into their accounts after they heard that the bank increased interest rates.
 * However, there are too many people and only one counter is open which can serve one person per minute.
 * Greedy as Oliver is, he would like to select some people in the queue, so that the total amount of cash stored by these people is as big as possible and that money then can work for the bank overnight.
 *
 * There is a problem, though. Some people don’t have the time to wait until the bank closes because they have to run somewhere else, so they have to be served before a certain time, after which they just leave.
 * Oliver also turned off the infrared door sensor outside the bank, so that no more people can enter, because it’s already too crowded in the hall.
 *
 * Task:
 * Help Oliver calculate how much cash he can get from the people currently standing in the queue before the bank closes by serving at most one person per minute
 *
 * Input:
 * The first line of input contains two integers N (1 <= N <= 10000) and T (1 <= T <= 47), the number of people in the queue and the time in minutes until Oliver closes the bank.
 * Then follow N lines, each with 2 integers ci and ti, denoting the amount of cash in Swedish crowns person i has and the time in minutes from now after which person i leaves if not served. Note that it takes one minute to serve a person and you must begin serving a person at time ti at the latest.
 * You can assume that 1 <= ci <= 100000 and 0 <= ti < T.
 *
 * Output:
 * Output one line with the maximum amount of money you can get from the people in the queue before the bank closes.

Sample Input 1
4 4
1000 1
2000 2
500 2
1200 0

Sample Output 1
4200

Sample Input 2
3 4
1000 0
2000 1
500 1

Sample Output 2
3000
 */