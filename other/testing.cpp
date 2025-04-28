// #include <cstdio>
#include <iostream>
#include <vector>

int main()
{
    // float x = 0.7;
    // float y = 0.6;
    // printf("%.16f\n", x + y);

    using namespace std;

    vector<int> v = {10, 20, 30, 40};

    auto vbegin = v.begin();
    auto vend = v.end();

    cout << *vbegin << '\n';
    cout << *vend << '\n';

    return 0;
}
