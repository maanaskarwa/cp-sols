/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <queue>

#define ll long long
#define u unsigned

using namespace std;

bool possible_in_days(ll days, vector<pair<ll,ll>> *investments, int n, int money_needed) {
    // make a priority queue sorting by the return on investment given the number of days
    auto compare = [&days](const pair<ll,ll> p1, const pair<ll, ll> p2) {
        return (p1.second * days) - p1.first < (p2.second * days) - p2.first;
    };
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, decltype(compare)> investment_queue(compare);
    for (int i = 0; i < n; ++i) {
        investment_queue.push((*investments)[i]);
    }
    ll money_earned = 0;
    for (int i = 0; i < n; ++i) {
        pair<ll, ll> investment = investment_queue.top();
        investment_queue.pop();
        money_earned += (investment.second * days) - investment.first;
        if (money_earned >= money_needed) return true;
    }
    return money_earned >= money_needed;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, money_needed;
    cin >> n >> money_needed;
    vector<pair<ll, ll>> investments; //<ci, pi>
    investments.reserve(n);
    for (int i = 0; i < n; ++i) {
        int pi, ci;
        cin >> pi >> ci;
        pair<ll, ll> investment = {ci, pi};
        investments.push_back(investment);
    }
    ll low = 1;
    /* Logic for high:
     * Let's define the worst investment as the longest time it takes to earn a certain amount of money.
     * The worst investment would be c_i = 10^9, p_i = 1.
     * The longest time it could take is when you need to repay 10^9 euros. So you need to earn 2 * 10^9, which will take 2 * 10^9 days
     * Assuming each investment is as bad as this one, this is the longest possible time.
     * Max number of iterations is log(2 * 10^9)/log (2) = ~31
     */
    ll high = 2000000000;
    while (low < high) {
        ll mid = low + (high - low) / 2;
        if (!possible_in_days(mid, &investments, n, money_needed)) low = mid + 1;
        else high = mid;
    }
    cout << low << "\n";
    return 0;
}

/* Problem description: https://open.kattis.com/problems/financialplanning
 *
 * Being a responsible young adult, you have decided to start planning for retirement.
 * Doing some back-of-the-envelope calculations, you figured out you need at least M euros to retire comfortably.
 * You are currently broke, but fortunately a generous gazillionaire friend has offered to lend you an arbitrary amount of money (as much as you need), without interest, to invest in the stock market.
 * After making some profit you will then return the original sum to your friend, leaving you with the remainder.
 *
 * Available to you are n investment opportunities, the i-th of which costs c_i euros. You also used your computer science skills to predict that the i-th investment will earn you p_i euros per day.
 * What is the minimum number of days you need before you can pay back your friend and retire?
 * You can only invest once in each investment opportunity, but you can invest in as many different investment opportunities as you like.
 *
 * For example, consider the first sample. If you buy only the second investment (which costs 15 euros) you will earn 10 euros per day.
 * After two days you will have earned 20 euros, exactly enough to pay off your friend (from whom you borrowed 15 euros) and retire with the remaining profit (5 euros).
 * There is no way to make a net amount of 5 euros in a single day, so two days is the fastest possible.
 *
 * Input:
 * The first line contains the number of investment options n (1 <= n <= 10^5) and the minimum amount of money you need to retire (1 <= M <= 10^9).
 * Then, n lines follow. Each line i has two integers: the daily profit of this investment p_i and its initial cost c_i. (1 <= c_i, p_i <= 10^9).
 *
 * Output:
 * Print the minimum number of days needed to recoup your investments and retire with at least M euros, if you follow an optimal investment strategy.

Sample Input 1
2 5
4 10
10 15

Sample Output 1
2

Sample Input 2
4 10
1 8
3 12
4 17
10 100

Sample Output 2
6

Sample Input 3
3 5
4 1
9 10
6 3

Sample Output 3
1
 */