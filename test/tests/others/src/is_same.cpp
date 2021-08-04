#include HEADER_FILE
#include <iostream>

typedef struct s_dummy
{
  int member;
} t_dummy;

int main (void)
{
  // True
  std::cout << NAMESPACE::is_same<char, char>::value << std::endl;
  std::cout << NAMESPACE::is_same<int, int>::value << std::endl;
  std::cout << NAMESPACE::is_same<t_dummy, t_dummy>::value << std::endl;
  
  // False
  std::cout << NAMESPACE::is_same<char, int>::value << std::endl;
  std::cout << NAMESPACE::is_same<t_dummy, char>::value << std::endl;
}
