#include "data_process.hpp"
#include <iostream>
using namespace std;
int main()
{
    vector<string> words = {"apple", "ant", "banana", "bear", "cat"};
    DataProcessor processor(words);

    auto sorted = processor.sort_by_length();
    cout << "original sequence : " << endl;
    for (const auto &word : processor.data_)
        cout << word << endl;

    cout << "Sorted by length : " << endl;
    for (const auto &word : sorted)
        cout << word << endl;

    cout << "Filtered by prefix : " << endl;
    auto filtered = processor.filter_by_prefix("b");
    for (const auto &word : filtered)
        cout << word << endl;

    return 0;
}