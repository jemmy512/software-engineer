#include <iostream>

using namespace std;

/* a x b = LCM(a, b) * GCD(a, b)
 * LCM(a, b) = (a x b) / GCD(a, b) */

/* GCD of two numbers
 * https://www.geeksforgeeks.org/program-to-find-gcd-or-hcf-of-two-numbers/ */

// Greatest Common Divisor
long long gcd(long long int a, long long int b) {
    while (b != 0) {
        auto t = b;
        b = a % b;
        a = t;
    }

    return a;
}

// Least Common Multiple
long long lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

// Driver program to test above function
int main() {
    int a = 15, b = 20;
    cout <<"LCM of " << a << " and " << b << " is " << lcm(a, b);

    return 0;
}
