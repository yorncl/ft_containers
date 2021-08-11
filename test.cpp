

#include "btree.hpp"
#include <functional>
#include <iostream>

#define REDC "\033[0;31m"
#define NC "\033[0m"

/* #define ft::btree<int, std::less<>>::_node::BLACK color_black */
/* #define ft::btree<int, std::less<>>::_node::RED color_red */

void printr(ft::btree<int, std::less<> >::_node *n, int level)
{
  if (!n)
    return;
  if (n->right)
    printr(n->right, level + 1);
  int i = -1;
  while(++i < level)
    std::cout << "       ";
  std::cout << n->_data << std::endl;
  std::cout << std::endl;

  if (n->left)
    printr(n->left, level + 1);
}

void print_tree(ft::btree<int, std::less<> >& tree)
{
  printr(tree._root->right, 1);
  if (tree._root)
    std::cout << tree._root->_data  << std::endl;
  else
    std::cout << "Oh oh, root is empty !" << std::endl;
  printr(tree._root->left, 1);
}

int main(void)
{

  ft::btree<int, std::less<> > tree;
  tree.insert(3);
  print_tree(tree);
  std::cout << "----------------------" << std::endl;
  tree.insert(5);
  print_tree(tree);
  std::cout << "----------------------" << std::endl;
  tree.insert(1);
  print_tree(tree);
  std::cout << "----------------------" << std::endl;
  tree.insert(6);
  tree.insert(2);
  tree.insert(4);
  tree.insert(7);
  tree.insert(7);
  tree.insert(7);
  tree.insert(7);
  print_tree(tree);
  
  std::cout << "============= DELETION ===============" << std::endl;
  tree.remove(7);
  print_tree(tree);
  std::cout << "----------------------" << std::endl;
  tree.remove(3);
  print_tree(tree);
  std::cout << "----------------------" << std::endl;
  tree.remove(4);
  print_tree(tree);
  std::cout << "----------------------" << std::endl;
  tree.remove(1);
  print_tree(tree);
}
