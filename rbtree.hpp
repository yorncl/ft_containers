#ifndef RBTREE_HPP

#include <stdlib.h>
#include <iostream>

template<class T, typename Compare>
class rbtree
{


  public:
  typedef struct s_node
  {
    s_node(T data)
    {
      _data = data;
    }
    struct s_node* parent = NULL;
    struct s_node* left = NULL;
    struct s_node* right = NULL;
    T _data;
    enum { RED, BLACK } colour = RED;
  } _node;


  _node* _root;
  size_t _size;
  bool _unique;

  rbtree(bool unique = true)
  {
    _size = 0;
    _root = NULL;
    _unique = unique;
  }

  void rotateLeft(_node* n)
  {
    _node* y = n->right;
    std::cout << y->_data << " data " << std::endl;
    n->right = y->left;
    if (y->left)
      y->left->parent = n;
    y->parent = n->parent;
    
    if (n->parent == NULL)
      _root = y;
    else if (n->parent->left == n)
      n->parent->left = y;
    else
      n->parent->right = y;

    y->left = n;
    std::cout << y->left->_data << std::endl;
    n->parent = y;
  }

  void rotateRight(_node* n)
  {
    /* std::cout << "Rotate right" << std::endl; */
    _node* y = n->left;
    n->right = y->right;
    if (y->right)
      y->right->parent = n;
    y->parent = n->parent;
    
    if (n->parent == NULL)
      _root = y;
    else if (n->parent->left == n)
      n->parent->left = y;
    else
      n->parent->right = y;

    y->right = n;
    n->parent = y;
  }

  void fix_insertion(_node* x)
  {
    while (x->parent && x->parent->colour == _node::RED)
    {
      if (x->parent->parent->left == x->parent) // Left 
      {
        if (x->parent->parent->right == NULL || x->parent->parent->right->colour == _node::BLACK)
        {
            if (x->parent->right == x) //R
            { 
              std::cout << "R";
              x = x->parent;
              rotateLeft(x);
            }
            else
              std::cout << "L";
            std::cout << "L"<< std::endl;
            x->parent->colour = _node::BLACK;
            x->parent->parent->colour = _node::RED;
            rotateRight(x->parent->parent);
        }
        else
        {
          std::cout << "LEFT NO RT" << std::endl;
          x->parent->colour = _node::BLACK;
          x->parent->parent->right->colour = _node::BLACK;
          x->parent->parent->colour = _node::RED;
          x = x->parent->parent;
        }
      }
      else // Right
      {

        if (x->parent->parent->left == NULL || x->parent->parent->left->colour == _node::BLACK)
        {
            if (x->parent->left == x) //L
            { 
              std::cout << "L";
              x = x->parent;
              rotateRight(x);
            }
            else
              std::cout << "R";
            std::cout << "R" << std::endl;
            x->parent->colour = _node::BLACK;
            x->parent->parent->colour = _node::RED;
            rotateLeft(x->parent->parent);

        }
        else
        {
          std::cout << "RIGHT NO RT" << std::endl;
          x->parent->colour = _node::BLACK;
          x->parent->parent->left->colour = _node::BLACK;
          x->parent->parent->colour = _node::RED;
          x = x->parent->parent;
        }
      }
    }
    _root->colour = _node::BLACK;
  }

  void insert(T data, Compare cmp = Compare{})
  {
    _node* n = new _node(data);
    if (_root == NULL) 
    {
      _root = n;
      _root->colour = _node::BLACK;
      _size = 1;
      return ;
    }
    _node* curr = _root;
    _node** next;
    while (1)
    { 
      if(n->_data == curr->_data && _unique == true)
      {
        delete n;
        return;
      }
      if (cmp(n->_data, curr->_data)) // go left cause n comes before curr
        next = &curr->left;
      else
        next = &curr->right;
      if (*next == NULL)
      {
        *next = n;
        n->parent = curr;
        _size++;
        break;
      }
      curr = *next;
    }
    if (n->parent == _root)
      return ;
    fix_insertion(n);
  }
};

#endif // !RBTREE_HPP
