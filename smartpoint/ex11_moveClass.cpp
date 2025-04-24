#include <iostream>
#include <memory>
#include <string>
using namespace std;

class MyData
{
private:
    string data_;

public:
    MyData(const string &d) : data_(d)
    {
        cout << "복사 생성자 호출" << endl;
    }
    MyData(const MyData &data) : data_("100")
    {
    }
    MyData(const string &&d) noexcept : data_(move(d))
    {
        cout << "이동 생성자 호출" << endl;
    }
    const string &get_data()
    {
        return data_;
    }
};

void useMyData(MyData &&data)
{
    cout << "복사 이동한 MyData" << endl;
    cout << data.get_data() << endl;
}
void referenceMyData(MyData &data)
{
    cout << "레퍼런스 data" << endl;
    cout << data.get_data() << endl;
}

int main()
{
    string str = "Hello";
    MyData d1(str);
    MyData d2(move(str));
    // MyData d3(move(str)); // 안 만들어짐 ??
    // useMydata(d1);
    useMyData(move(d2));
    // useMyData(move(d2)); // 안 되야 정상인데 ??
    referenceMyData(d1);
    return 0;
}