#include <iostream>
#include <string>
using namespace std;

class MyData
{
private:
    string *data_;
    bool owns_data_; // ✅ 소유권 여부

public:
    // 포인터 생성자
    explicit MyData(string *ptr)
        : data_(ptr), owns_data_(true)
    {
        if (!ptr)
        {
            throw runtime_error("nullptr 전달: 이미 소유권이 이전된 포인터입니다");
        }
        cout << "MyData: 소유권 획득" << endl;
    }

    // rvalue string 생성자
    MyData(string &&str) noexcept
        : data_(new string(move(str))), owns_data_(true)
    {
        cout << "MyData(string&&): 문자열 이동 생성자 호출" << endl;
    }

    // 이동 생성자
    MyData(MyData &&other) noexcept
        : data_(other.data_), owns_data_(other.owns_data_)
    {
        other.data_ = nullptr;
        other.owns_data_ = false;
        cout << "MyData: 이동 생성자 호출" << endl;
    }

    // 이동 대입 연산자
    MyData &operator=(MyData &&other) noexcept
    {
        if (this != &other)
        {
            if (owns_data_)
                delete data_;
            data_ = other.data_;
            owns_data_ = other.owns_data_;
            other.data_ = nullptr;
            other.owns_data_ = false;
            cout << "MyData: 이동 대입 연산자 호출" << endl;
        }
        return *this;
    }

    // 소멸자
    ~MyData()
    {
        if (owns_data_)
        {
            cout << "MyData: 소멸자 호출, 메모리 해제" << endl;
            delete data_;
        }
        else
        {
            cout << "MyData: 소멸자 호출, 소유권 없음" << endl;
        }
    }

    const string &get_data() const
    {
        return *data_;
    }

    void print() const
    {
        if (data_)
            cout << "데이터: " << *data_ << endl;
        else
            cout << "데이터 없음" << endl;
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
    string *str = new string("Hello");
    MyData d1(str);
    MyData d2(move(str)); // move 의 의미가 rvalue 를 넘긴다.! 소유권을 넘기는 것을 X
    str = nullptr;

    // MyData d3(move(str));  // 실행 안됨.
    MyData d3(move(d2));

    // useMydata(d1); // 실행 안됨
    // useMyData(move(d2)); // 실행 암된 d2 가 d3 로 이동
    useMyData(move(d3));
    // referenceMyData(d1);
    // d1을 참조해서 delete가 두번 일어나게 됨.
    return 0;
}