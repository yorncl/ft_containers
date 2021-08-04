#include <iostream>
#include HEADER_FILE
#include <functional>
 
int main()
{
    int n = 1;
    int a[5] = {1, 2, 3, 4, 5};
 
    // build a pair from two ints
    NAMESPACE::pair<int, int> p1 = NAMESPACE::make_pair(n, a[1]);
    std::cout << "The value of p1 is "
              << "(" << p1.first << ", " << p1.second << ")\n";
 
    // build a pair from a reference to int and an array (decayed to pointer)
    NAMESPACE::pair<int, int*> p2 = NAMESPACE::make_pair(n, a);
    n = 7;
    std::cout << "The value of p2 is "
              << "(" << p2.first << ", " << *(p2.second + 2) << ")\n";
}

