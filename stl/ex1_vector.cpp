#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(11);
    v.push_back(111);
    v.push_back(1238);
    // cout << "v 의 첫번째 원소는 : " << v[0] << endl;
    // cout << "v 의 두번째 원소는 : " << v[1] << endl;
    // cout << "v 의 세번째 원소는 : " << v[2] << endl;
    // vector<int>::iterator it;
    auto it = v.begin() + 2;
    v.erase(it); // 111 삭제
    v.at(0) = 2; // 원소에 접근해서 변경.

    // for 문을 쓰는 첫 번째
    for (auto i = 0; i < v.size(); ++i)
    {
        cout << "v 의 " << i + 1 << " 번째 원소는 :" << v.at(i) << endl;
    }
    return 0;
}