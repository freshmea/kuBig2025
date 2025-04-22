#include <array>
#include <deque>
#include <iostream>
using namespace std;

int main()
{
    // array
    // 고정 크기 배열. STL 중 속도가 가장 빠르다. 그냥 배열 보다는 살짝 느림.
    array<int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (const auto &x : arr)
        cout << x << " ";
    cout << endl;

    // deque -> 많은 메버 함수가 정의
    // 동적 크기, 양쪽 삽입/삭제 가능
    deque<int> dq = {1, 2, 3};
    dq.push_back(4);
    dq.push_front(0);
    dq.emplace_back(5);
    dq.emplace_front(-1);
    dq.insert(dq.begin() + 3, 2.5);

    for (const auto &v : dq)
        cout << v << " ";
    cout << endl;

    dq.pop_back();
    dq.pop_front();

    for (const auto &v : dq)
        cout << v << " ";
    cout << endl;
    return 0;
}