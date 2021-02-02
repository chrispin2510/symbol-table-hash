#include "hash_set.h"
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::boolalpha;

int main()
{
    hash_set_t* set = new hash_set_t;
    hash_set_init(set);

    for (data_t i = 1; i < 12; i++)
    {
       hash_set_add(set, i);
    }
    cout << boolalpha << hash_set_contains(set, 1) << endl;
    cout << boolalpha << hash_set_contains(set, 5) << endl;
    cout << boolalpha << hash_set_contains(set, 11) << endl;
    cout << boolalpha <<  hash_set_contains(set, -1) << endl;
    cout << boolalpha << hash_set_contains(set, 9) << endl;
    cout << boolalpha << hash_set_contains(set, 10) << endl;
    hash_set_free(set);
}