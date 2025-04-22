#include <iostream>
using namespace std;

int main()
{
    double pi = 3.1415926535;
    auto calc = [&pi](int r) -> double
    {
        pi = 30;
        return pi * r * r; };
    cout << "면적은 " << calc(3) << endl;
    cout << "Pi 의 값은 : " << pi << endl;

    int sum = 0;
    auto calc2 = [&sum](int x, int y)
    { sum = x + y; };
    calc2(2, 3);
    cout << "합은 : " << sum << endl;
    return 0;
}