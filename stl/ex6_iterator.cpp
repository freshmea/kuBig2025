#include <iostream>
#include <vector>
using namespace std;

// class A :
// public :
//     class B :

int main()
{
    vector<int>::iterator it;
    vector<int> test_vector = {1, 2, 3, 4, 5, 6};

    for (it = test_vector.begin(); it != test_vector.end(); ++it)
    {
        cout << *it << endl;
    }

    return 0;
}