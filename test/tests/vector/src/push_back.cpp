// vector::push_back
#include <iostream>
#include HEADER_FILE

int main ()
{
  NAMESPACE::vector<int> myvector;

  std::cout << "Please enter some integers (enter 0 to end):\n";

  int arr[] = { 234, 23, 56, 88, 994, 720, 23423423, 679, 658, 800};
  int i = 0;
  while (i < 10)
  {
    myvector.push_back (arr[i]);
    i++;
  }
  std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";

  return 0;
}
