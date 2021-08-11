#ifndef BTREE_HPP

#include <stdlib.h>
#include <iostream>

namespace ft
{

  template<class T, typename Compare>
  class btree
  {


    public:
    typedef struct s_node
    {
      s_node(T data = T())
      {
        _data = data;
      }
      struct s_node* parent = NULL;
      struct s_node* left = NULL;
      struct s_node* right = NULL;
      T _data;
    } _node;


    _node* _root;
    _node* _null_node;
    size_t _size;
    bool _unique;

    static bool equal(T& x, T& y, Compare cmp = Compare{}) { return !cmp(x, y) && !cmp(y, x);}

    btree(bool unique = true)
    {
      _size = 0;
      _root = NULL;
      
      _unique = unique; 
    }

    void insert(T data, Compare cmp = Compare{})
    {
      _node* n = new _node(data);
      if (_root == NULL) 
      {
        _root = n;
        _size = 1;
        return ;
      }
      _node* curr = _root;
      _node** next;
      while (1)
      { 
        if(equal(n->_data, curr->_data) && _unique == true)
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
    }

    _node* search_node(_node* root, T& data, Compare cmp = Compare{})
    {
      
        while (root && !equal(data, root->_data))
          if (cmp(data, root->_data))
              root = root->left;
          else
              root = root->right;

        return root;
    }


    _node* transplant(_node* u, _node* v)
    {
      if (u->parent == NULL)
        _root = v;
      else if (u->parent->left == u)
        u->parent->left = v;
      else
        u->parent->right = v;
      if (v)
        v->parent = u->parent;
      return v;
    }
    
    void remove(T data, Compare cmp = Compare{})
    {

      // Base case
      if (_root == NULL)
        return; 
      //Searching the node to remove
      _node* n = _root;
      while (n && !equal(data, n->_data))
      {
        if (cmp(data, n->_data))
          n = n->left; 
        else
          n = n->right;
      }

      // if n is null then no matching node encountered
      if (n == NULL)
        return;

      _node* x; // reference to the new node 

      if (n->left == NULL)
        x = transplant(n, n->right);
      else if (n->right == NULL)
        x = transplant(n, n->left);
      else 
      {
        _node* tmp = n->right;
        while (tmp->left)
         tmp = tmp->left;
        x = tmp->right; 
        if (tmp != n->right)
        {
          if (x)
            x->parent = tmp->parent;
          tmp->parent->left = NULL;
          tmp->right = n->right;
          n->right->parent = tmp;
        }
        tmp->left = n->left;
        tmp->parent = n->parent;
        n->left->parent = tmp;
        if (n == _root)
          _root = tmp; 
      }
    }
  };
} // namespace ft
#endif // !BTREE_HPP
