// vector assign
#include <iostream>
#include HEADER_FILE

int main ()
{
  NAMESPACE::vector<int> first;
  NAMESPACE::vector<int> second;
  NAMESPACE::vector<int> third;

  first.assign (7,100);             // 7 ints with a value of 100

  NAMESPACE::vector<int>::iterator it;
  it=first.begin()+1;

  second.assign (it,first.end()-1); // the 5 central values of first

  int myints[] = {1776,7,4};
  third.assign (myints,myints+3);   // assigning from array.

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of third: " << int (third.size()) << '\n';
  return 0;
}