/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#define ll long long
#define u unsigned

#include <iostream>
#include <map>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // comparator for priority queue: minimize a+d
    auto compare = [](const pair<u ll, u ll> &p1, const pair<u ll, u ll> &p2) {
        return p1.first + p1.second > p2.first + p2.second;
    };
    u int h, c;
    u ll ans = 0;
    cin >> h >> c;
    // using priority queue since I need the min a+d in each iteration
    priority_queue<pair<u ll, u ll>, vector<pair<u ll, u ll>>, decltype(compare)> annoyance(compare); //<annoyance, increase>
    for (int i = 0; i < c; ++i) {
        unsigned int initial_annoyance, annoyance_increase;
        cin >> initial_annoyance >> annoyance_increase;
        pair<u ll, u ll> v;
        //handle that the base value of minimum annoyance is max of initial annoyance
        if (initial_annoyance > ans) ans = initial_annoyance;
        v.first = initial_annoyance;
        v.second = annoyance_increase;
        annoyance.push(v);
    }
    for (u int i = 0; i < h; ++i) {
        pair<u ll, u ll> v = annoyance.top();
        annoyance.pop();
        // a += d
        v.first += v.second;
        if (v.first > ans) ans = v.first;
        annoyance.push(v);
    }
    cout << ans << "\n";
    return 0;
}

/* Problem Statement: https://open.kattis.com/problems/annoyedcoworkers
 *
 * It’s another day in the office, and you’re a mastermind of not doing any work yourself.
 * Instead, you’ll go to your coworkers for “help,” but secretly have them do all the work.
 * You’ve determined that the more one of your coworkers helps you, the more annoyed they become. You’ve also been able to determine how much more annoyed a coworker gets everytime you ask them for help.
 * At the beginning of the day, a coworker is initially a annoyed at you. That’s their annoyance level.
 * Everytime you ask them for help though, they become d more annoyed at you – their annoyance level a increases by a constant amount d so that a = a + d.
 *
 * You want to complete a project of h tasks solely with “help” from your coworkers, but you need to be careful not to annoy any of them too much.
 *
 * What’s the best you can do?
 *
 * Input:
 * The first line contains 2 integers h and c, where h (1 <= h <= 100000) is the number of times you have to ask for help to complete the project,
 * and c (1 <= c <= 100000) denotes the number of coworkers you have.
 * Each of the following c lines contains two positive integers a and d, representing a coworker whose initial annoyance level is a and who is getting more annoyed at you by an increase of d every time you ask them for help (1 <= a,d <= 10^9).
 *
 * Output:
 * Output a single number, which is the maximum annoyance level any coworker has at you provided you use an optimal strategy to minimize this level. (In other words, of all possible strategies, choose one that minimizes the annoyance level of the worker or workers who are most annoyed at you at the end.)
 *
 * Sample Input 1 Explanation:
 * You have 4 coworkers and you need to ask for help 4 times. Initially, their annoyance levels are 1,2,3,4, the increases are 2,3,4,5.
 * One optimal solution is to ask for help twice from coworker 1, once from coworker 2, and once from coworker 3, in which case the final annoyance levels are: 5,5,7,4.
 * The coworker that is most annoyed at you is coworker 3, whose annoyance level at you is 7.
 * Or, you could ask coworker 1 for help 3 times and coworker 2 once, leaving you with 7,5,3,4. Both strategies yield the same minimal maximum amount.

Sample Input 1
4 4
1 2
2 3
3 4
4 5

Sample Output 1
7

Sample Input 2
3 2
1 1000
1000 1

Sample Output 2
1002

Sample Input 3
5 2
1 1
2 2

Sample Output 3
5
 */