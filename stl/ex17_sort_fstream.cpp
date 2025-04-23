#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student
{
public:
    string name;
    int sub1;
    int sub2;
    int sub3;
    int sub4;
    int sub5;
};

int main()
{
    ifstream file("/home/aa/kuBig2025/stl/10.txt");
    vector<Student> students;

    string name;
    int s1, s2, s3, s4, s5;

    while (file >> name >> s1 >> s2 >> s3 >> s4 >> s5)
    {
        students.push_back({name, s1, s2, s3, s4, s5});
    }
    file.close();
    for (const auto &student : students)
        cout << student.name << " ";
    cout << endl;
    return 0;
}