#include HEADER_FILE
#include <iostream>
#include <typeinfo>

int main(void)
{

  std::cout << "T* specialization" << std::endl;
  typedef NAMESPACE::iterator_traits<int*> traits_int;
  std::cout << (typeid(traits_int::difference_type) == typeid(std::ptrdiff_t)) << std::endl;
  std::cout << (typeid(traits_int::value_type) == typeid(int)) << std::endl;
  std::cout << (typeid(traits_int::pointer) == typeid(int*)) << std::endl;
  std::cout << (typeid(traits_int::reference) == typeid(int&)) << std::endl;
  std::cout << (typeid(traits_int::iterator_category) == typeid(NAMESPACE::random_access_iterator_tag)) << std::endl;
  
  std::cout << "const T* specialization" << std::endl;
  typedef NAMESPACE::iterator_traits<const int*> traits_const_int;
  std::cout << (typeid(traits_const_int::difference_type) == typeid(std::ptrdiff_t)) << std::endl;
  std::cout << (typeid(traits_const_int::value_type) == typeid(int)) << std::endl;
  std::cout << (typeid(traits_const_int::pointer) == typeid(const int*)) << std::endl;
  std::cout << (typeid(traits_const_int::reference) == typeid(const int&)) << std::endl;
  std::cout << (typeid(traits_const_int::iterator_category) == typeid(NAMESPACE::random_access_iterator_tag)) << std::endl;

}
