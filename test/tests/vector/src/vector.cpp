// constructing vectors
#include <iostream>
#include HEADER_FILE

int main ()
{
  // constructors used in the same order as described above:
  NAMESPACE::vector<int> first;                                // empty vector of ints
  NAMESPACE::vector<int> second (4,100);                       // four ints with value 100
  NAMESPACE::vector<int> third (second.begin(),second.end());  // iterating through second
  NAMESPACE::vector<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  NAMESPACE::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are:";
  for (NAMESPACE::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}