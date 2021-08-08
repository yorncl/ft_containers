// vector::rbegin/rend
#include <iostream>
#include HEADER_FILE

int main ()
{
  NAMESPACE::vector<int> myvector (5);  // 5 default-constructed ints

  int i=0;

  NAMESPACE::vector<int>::reverse_iterator rit = myvector.rbegin();
  for (; rit!= myvector.rend(); ++rit)
    *rit = ++i;

  std::cout << "myvector contains:";
  for (NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}