/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

//Estimating area of circle
int main() {
    int totalDots, dotsInCircle;
    double radius;
    while (true) {
        cin >> radius >> totalDots >> dotsInCircle;
        if (radius == 0.0f && totalDots == 0 && dotsInCircle == 0) break;
        // Since dots are randomly assigned, we can approximate their ratio to the ratio of areas of the circle and square.
        // dotsInCircle/totalDots = estimatedCircleArea/squareArea.
        // used setprecision(6) since max accepted error was the 5th decimal.
        cout << endl << fixed << setprecision(6) << M_PI * radius * radius
        << " " << 4.0f * radius * radius * dotsInCircle / totalDots;
    }
    return 0;
}

/* Problem Statement: https://open.kattis.com/problems/estimatingtheareaofacircle
 *
 * One way to estimate the area of a circle is to draw a square that just encompasses the circle and mark points randomly (with uniform probability) with a marker.
 * Then, when you get tired of marking points, count up the number of points that you marked that landed in the circle and divide it by the total number of points that you marked.
 * That gives you an idea of how large the circle is relative to the square. Your job is to judge how accurate this is for given circles and experiment outcomes.
 *
 * Input:
 * Input contains up to 1000 test cases, one test case per line.
 * Each line has three space-separated numbers:r m c, where
 * 0 <= r <= 1000 is a real number with at most 5 digits past the decimal indicating the true radius of the circle,
 * m is an integer indicating the total number of marked points, and
 * c is an integer indicating the number of marked points that fall in the circle.
 * Input ends with a line containing three zeros, which should not be processed.
 *
 * Output:
 * For each test case, print a line containing two numbers: the true area of the circle and the estimate according to the experiment.
 * Both numbers may have a relative error of at most 10^-5.

Sample Input 1
1.0 100 75
10.0 5000 4023
3.0 21 17
0 0 0

Sample Output 1
3.141592654 3
314.1592654 321.84
28.27433388 29.14285714

 */