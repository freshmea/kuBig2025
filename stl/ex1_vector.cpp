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

    // for 문을 쓰는 첫 번째
    for (int i = 0; i < v.size(); ++i)
    {
        cout << "v 의 " << i + 1 << " 번째 원소는 :" << v[i] << endl;
    }
    return 0;
}