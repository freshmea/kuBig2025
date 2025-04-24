#include <chrono>
#include <future>
#include <iostream>
using namespace std;

int slowAdd(int a, int b)
{
    this_thread::sleep_for(chrono::seconds(2));
    return a + b;
}

int main()
{
    future<int> result = async(slowAdd, 2, 3);
    cout << "계산 중 ..." << endl;
    cout << "결과 : " << result.get() << endl;
    return 0;
}