#include <iostream>
#include <string>
#include <vector>

using namespace std;
// using std::cout;
// using std::endl;

int main()
{
    vector<string> sv;
    string name;

    cout << "이름을 5개 입력 하시오! " << endl;
    for (int i = 0; i < 5; ++i)
    {
        cout << i + 1 << ">>";
        getline(cin, name);
        sv.push_back(name);
    }
    name = sv.at(0);
    for (int i = 0; i < sv.size(); ++i)
    {
        if (name < sv[i]) // string 의 비교 연산자 오버라이딩..
            name = sv[i];
    }
    cout << "사전에서 가장 뒤에 나오는 이름은: " << name << endl;
    return 0;
}