#include HEADER_FILE
#include <iostream>


typedef struct s_nonintegral
{
  int member;
} t_nonintegral;

int main(void)
{


  std::cout << NAMESPACE::is_integral<char>::value << std::endl;
  std::cout << NAMESPACE::is_integral<bool>::value << std::endl;
  std::cout << NAMESPACE::is_integral<wchar_t>::value << std::endl;
  std::cout << NAMESPACE::is_integral<int>::value << std::endl;
  std::cout << NAMESPACE::is_integral<long>::value << std::endl;
  std::cout << NAMESPACE::is_integral<long long >::value << std::endl;
  std::cout << NAMESPACE::is_integral<char16_t>::value << std::endl;
  std::cout << NAMESPACE::is_integral<char32_t>::value << std::endl;
  std::cout << NAMESPACE::is_integral<short>::value << std::endl;
  std::cout << NAMESPACE::is_integral<t_nonintegral>::value << std::endl;
}
