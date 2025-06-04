// 표준 입력을 받아서 (영어문장) -this is a apple.
// 단어 별 등장 횟수를 출력하는 프로그램.

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream> //string - stream
#include <string>
#include <unordered_map>
using namespace std;

string clean_word(const string &word)
{
    string cleaned;
    for (char ch : word)
    {
        if (isalpha(ch) || isdigit(ch))
            cleaned += tolower(ch);
    }
    return cleaned;
}

int main()
{
    string line;
    getline(cin, line);

    unordered_map<string, int> word_count;
    istringstream iss(line);
    string word;

    while (iss >> word)
    {
        string cleaned = clean_word(word);
        if (!cleaned.empty())
        {
            word_count[cleaned]++; // word_count[key] = value;
        }
    }
    for (const auto &[key, value] : word_count)
        cout << key << " : " << value << endl;
}
