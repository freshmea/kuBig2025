#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main()
{
    vector<int> v1;                        // int형 벡터
    vector<string> v2;                     // string형 벡터
    vector<char> v3;                       // char형 벡터
    vector<double> v4;                     // double형 벡터
    vector<bool> v5;                       // bool형 벡터
    vector<int> v6(10);                    // 크기가 10인 int형 벡터
    vector<int> v7(10, 5);                 // 크기가 10이고 모든 원소가 5인 int형 벡터
    vector<int> v8{1, 2, 3, 4, 5};         // 초기화 리스트를 이용한 int형 벡터
    vector<int> v9 = {1, 2, 3, 4, 5};      // 초기화 리스트를 이용한 int형 벡터
    vector<int> v10(v9);                   // v9를 복사한 int형 벡터
    vector<int> v11(v9.begin(), v9.end()); // v9의 모든 원소를 복사한 int형 벡터
    vector<int> v12(v9.size());            // 크기가 v9와 같은 int형 벡터
    vector<int> v13(v9.size(), 0);         // 크기가 v9와 같고 모든 원소가 0인 int형 벡터
    for (auto i : v9)                      // v9의 모든 원소를 출력
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}