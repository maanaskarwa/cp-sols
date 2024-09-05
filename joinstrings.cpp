/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct custom_node {
    string value;
    vector<custom_node *> children;
    /* eg a,b,c,d with formulae 3 2, 4 1, and 3 4.
     * c->[b->nullptr, d->[a->nullptr,],] structure at end
     * Chose a list of children instead of a single child because of time complexity optimization.
     * pushing and popping in a list has O(1), whereas if I used a single child custom_node, I would have to iterate recursively to add a new leaf.
     */
};

void print_data(custom_node *node) {
    // LTR printing. In above case, would print 'c', recurse over b (printing 'b'), then d (printing 'da').
    cout << node->value;
    for (auto& c : node->children) {
        print_data(c);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned int n;
    cin >> n;
    if (n == 1) { //Edge case. No formulae input.
        string s;
        cin >> s;
        cout << s << "\n";
    } else {
        custom_node s[n];
        for (int i = 0; i < n; ++i) cin >> s[i].value;
        unsigned int a, b;
        for (; n > 1; --n) {
            cin >> a >> b;
            // using children as a queue (LIFO). pushing to back, printing from front.
            s[a - 1].children.push_back(&(s[b - 1]));
            // print data in last loop. s[a-1] is the "head".
            if (n == 2) print_data(&s[a - 1]);
        }
        return 0;
    }
}

/* Problem Statement: https://open.kattis.com/problems/joinstrings
 *
 * You are given a collection of N non-empty strings, denoted by S1, S2, ..., SN.
 * Then you are given N - 1 operations which you execute in the order they are given.
 * The ith operation is has the following format: ‘a b’ (1-based indexing, without the quotes), which means that you have to make the following changes:
 * 1. Sa = Sa + Sb, i.e. concatenate ath string and bth string and store the result in ath string,
 * 2. Sb = "", i.e. make the bth string empty, after doing the previous step.
 *
 * You are ensured that after the ith operation, there will be no future operation that will be accessing Sb.
 * Given these operations to join strings, print the last string that will remain at the end of this process.
 *
 * Input:
 * The first line contains an integer N (1 <= N <= 10^5) denoting the number of strings given.
 * Each of the next N lines contains a string denoting the Si. All the characters in the string Si are lowercase alphabets from ‘a’ to ‘z’.
 * The total number of characters over all the strings is at most 10^6.
 * After these N strings, each of the next N - 1 lines contain two integers a and b, such that a != b and 1 <= a,b <= N denoting the ith operation.
 *
 * Output:
 * Print the last string which remains at the end of the n - 1 operations.
 *
 * Warning:
 * The I/O files are large. Please use fast I/O methods.

Sample Input 1
4
cute
cat
kattis
is
3 2
4 1
3 4

Sample Output 1
kattiscatiscute

Sample Input 2
3
howis
this
practicalexam
1 2
1 3

Sample Output 2
howisthispracticalexam
 *
 * */