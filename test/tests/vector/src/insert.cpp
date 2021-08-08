// inserting into a vector
#include <iostream>
#include HEADER_FILE

void print(
  NAMESPACE::vector<int>& myvector)
{
  std::cout << "myvector contains:" << std::endl;
  NAMESPACE::vector<int>::iterator it;
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it << std::endl;
  std::cout << '\n';
}

int main ()
{
  NAMESPACE::vector<int> myvector (3,100);
  NAMESPACE::vector<int>::iterator it;
  print(myvector);

  it = myvector.begin();
  it = myvector.insert ( it , 200 );
  print(myvector);


  myvector.insert (it,2,300);
  print(myvector);

  // "it" no longer valid, get a new one:
  it = myvector.begin();
  print(myvector);

  NAMESPACE::vector<int> anothervector (2,400);
  myvector.insert (it+2,anothervector.begin(),anothervector.end());
  print(myvector);

  int myarray [] = { 501,502,503 };
  myvector.insert (myvector.begin(), myarray, myarray+3);
  print(myvector);


  return 0;
}
