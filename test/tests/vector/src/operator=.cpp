// vector assignment
#include <iostream>
#include HEADER_FILE

int main ()
{
  NAMESPACE::vector<int> foo (3,0);
  NAMESPACE::vector<int> bar (5,0);

  bar = foo;
  foo = NAMESPACE::vector<int>();

  std::cout << "Size of foo: " << int(foo.size()) << '\n';
  std::cout << "Size of bar: " << int(bar.size()) << '\n';
  return 0;
}