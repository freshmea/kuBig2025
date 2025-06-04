#include <cctype>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>

using namespace std;

void test_function(list<int> &students);

int main()
{
    list<int> students;
    string student;
    char temp;
    int grade;

    FILE *fp = fopen("/home/aa/kuBig2025/stl/1000.txt", "r");

    while (fread(&temp, sizeof(char), 1, fp))
    {

        if (isdigit(temp))
            student.push_back(temp);
        else if (!student.empty())
        {
            grade = stoi(student);
            students.push_back(grade);
            student.clear();
        }
    }
    fclose(fp);
    // ifstream fin("/home/aa/kuBig2025/stl/10.txt");
    // while (fin >> grade)
    //     students.push_back(grade);
    // fin.close();

    for (auto v : students)
        cout << v << endl;

    auto count = students.size();

    // vector 의 연산 시간!!
    double begin = clock();
    test_function(students);
    double end = clock();

    cout << "벡터를 연산하는 시간은" << count << "데이터 사이즈" << endl;
    cout << "지워진 데이터의 숫자는" << count - students.size() << endl;
    cout << (end - begin) / CLOCKS_PER_SEC << "초" << endl;
}

void test_function(list<int> &students)
{
    list<int>::iterator it = students.begin();
    while (it != students.end())
    {
        if (*it < 60)
        {
            it = students.erase(it);
        }
        else
        {
            ++it;
        }
    }
}