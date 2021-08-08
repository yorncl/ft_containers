// swap (vector overload)
#include <iostream>
#include HEADER_FILE

int main ()
{
  NAMESPACE::vector<int> foo (3,100);   // three ints with a value of 100
  NAMESPACE::vector<int> bar (5,200);   // five ints with a value of 200

  foo.swap(bar);

  std::cout << "foo contains:";
  for (NAMESPACE::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "bar contains:";
  for (NAMESPACE::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
