#include <stdio.h>
#include <numeric>

long long _gcd(long long a, long long b) {
    while (b != 0) {
        auto t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long long lcm(long long a, long long b) {
    return a / _gcd(a, b) * b;
}

int main()
{
    int N;
    scanf("%d", &N);
    long long num = 0, den = 1;
    long long numerator, denominator, divisor, multiple;

    while (N--) {
        scanf("%lld/%lld", &numerator, &denominator);

        num = num * denominator + numerator * den;
        den *= denominator;

        divisor = std::gcd(num, den);
        num /= divisor;
        den /= divisor;
    }

    long long cut = num;

    if (num < 0)
        cut = -num;

    if (cut % den == 0) {
        printf("%lld\n", num / den);
    } else {
        cut = cut % den;

        if (num < 0)
            cut = -cut;

        long long quotient = num / den;
        divisor = std::gcd(cut, den);
        cut /= divisor, den /= divisor;

        if (quotient != 0 && cut != 0)
            printf("%lld% lld/%lld\n", quotient, cut, den);
        if (quotient == 0 && cut != 0)
            printf("%lld/%lld\n", cut, den);
    }

    return 0;
}