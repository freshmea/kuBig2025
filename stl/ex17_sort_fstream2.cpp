#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Student
{
private:
    string name_;
    vector<int> scores_;

public:
    Student(const string &name, const vector<int> scores) : name_(name), scores_(scores) {}

    int totalScore() const
    {
        return accumulate(scores_.begin(), scores_.end(), 0);
    }
    int averageScore() const
    {
        return totalScore() / scores_.size();
    }
    void print() const
    {
        cout << "이름 : " << name_ << endl;
        cout << "점수 : ";
        for (const auto &v : scores_)
            cout << v << " ";
        cout << endl;
        cout << "총점 : " << totalScore() << endl;
        cout << "총점 : " << averageScore() << endl;
        cout << "-----------------------------------------" << endl;
    }
};

int main()
{
    ifstream file("/home/aa/kuBig2025/stl/10.txt");
    vector<Student> students;

    string line, name;
    vector<int> scores;
    int score;

    while (getline(file, line))
    {
        istringstream iss(line);
        iss >> name;
        while (iss >> score)
            scores.push_back(score);
        students.emplace_back(name, scores);
        scores.clear();
    }
    file.close();

    sort(students.begin(), students.end(), [](const Student &a, const Student &b)
         { return a.averageScore() < b.averageScore(); });

    for (const auto &student : students)
        student.print();
    return 0;
}