#ifndef BTREE_HPP

#include "utils.hpp"
#include <stdlib.h>

namespace ft {

template <class T, typename Compare = std::less<T>,
          typename Alloc = std::allocator<T> >
class btree {
public:
  typedef Alloc allocator_type;
  typedef T *pointer;
  typedef T &reference;

  allocator_type _alloc;

  static pointer copy_data(reference src, allocator_type &alloc) {
    pointer data = alloc.allocate(1);
    alloc.construct(data, src);
    return data;
  }

  static pointer create_data(reference src, allocator_type &alloc) {
    pointer data = alloc.allocate(1);
    alloc.construct(data, src);
    return data;
  }

  static void destroy_data(pointer data, allocator_type &alloc) {
    alloc.destroy(data);
    alloc.deallocate(data, 1);
  }

  typedef struct s_node {
    s_node(reference data, allocator_type &alloc = allocator_type()) {
      _data = create_data(data, alloc);
      parent = NULL;
      left = NULL;
      right = NULL;
    }
    s_node(const struct s_node &src) {
      parent = src.parent;
      left = src.left;
      right = src.right;
      _data = src._data;
    }
    s_node *parent;
    s_node *left;
    s_node *right;
    pointer _data;
  } _node;

  static _node *next(_node *n, const btree* tree) {
    if (!n)
      return tree->first();
    if (n->right) {
      n = n->right;
      while (n->left)
        n = n->left;
      return n;
    }
    while (true) {
      if (n == NULL || n->parent == NULL)
        return NULL;
      if (n->parent->left == n)
        return n->parent;
      n = n->parent;
    }
    return NULL;
  }
  static _node *prev(_node *n, const btree* tree) {
    if (!n)
      return tree->last();
    if (n->left) {
      n = n->left;
      while (n->right)
        n = n->right;
      return n;
    }
    while (true) {
      if (n == NULL || n->parent == NULL)
        return NULL;
      if (n->parent->right == n)
        return n->parent;
      n = n->parent;
    }
    return NULL;
  }

  
  template<class NodePointer, class TreePointer>
  class _BtreeIteratorBase
  {

    public:

    NodePointer _n;
    TreePointer _tree;

    typedef ft::bidirectional_iterator_tag iterator_category;

    template<class U, class V>
		bool operator==(_BtreeIteratorBase<U, V> other) const {return _n == other._n;}
    template<class U, class V>
		bool operator!=(_BtreeIteratorBase<U, V> other) const {return _n != other._n;}
    virtual ~_BtreeIteratorBase() {}
  };

  class _BtreeIterator : public _BtreeIteratorBase<_node*, btree*> {
  public:
    typedef _BtreeIterator _Self;
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;


    _BtreeIterator() { this->_n = NULL; this->_tree = NULL; }
    _BtreeIterator(const _node *p, const btree* tree) { this->_n = const_cast<_node*>(p); this->_tree = const_cast<btree*>(tree); }
    _BtreeIterator(const _BtreeIterator &it) { this->_n = it._n; this->_tree = it._tree; }
    _Self operator++(int) {
      _Self tmp = *this;
      this->_n = next(this->_n, this->_tree);
      return tmp;
    }
    _Self operator--(int) {
      _Self tmp = *this;
      this->_n = prev(this->_n, this->_tree);
      return tmp;
    }
    _Self &operator++() {
      this->_n = next(this->_n, this->_tree);
      return *this;
    }
    _Self &operator--() {
      this->_n = prev(this->_n, this->_tree);
      return *this;
    }
    reference operator*() const { return *this->_n->_data; }
    pointer operator->() const { return this->_n->_data; }
    ~_BtreeIterator() {}
  };

  class _ConstBtreeIterator : public _BtreeIteratorBase<const _node*, const btree*> {
  public:
    typedef _ConstBtreeIterator _Self;
    typedef std::ptrdiff_t difference_type;
    typedef const T value_type;
    typedef const T *pointer;
    typedef const T &reference;
    typedef ft::bidirectional_iterator_tag iterator_category;

    _ConstBtreeIterator() { this->_n = NULL; this->_tree = NULL; }
    _ConstBtreeIterator(const _node *p, const btree* tree) { this->_n = p; this->_tree = const_cast<const btree*>(tree);}
    _ConstBtreeIterator(const _BtreeIterator &it) { this->_n = it._n; this->_tree = it._tree;}
    _ConstBtreeIterator(const _ConstBtreeIterator &it) { this->_n = it._n; this->_tree = it._tree;}
    _Self operator++(int) {
      _Self tmp = *this;
      this->_n = const_cast<const _node*>(next(const_cast<_node*>(this->_n), this->_tree));
      return tmp;
    }
    _Self operator--(int) {
      _Self tmp = *this;
      this->_n = const_cast<const _node*>(prev(const_cast<_node*>(this->_n), this->_tree));
      return tmp;
    }
    _Self &operator++() {
      this->_n = const_cast<const _node*>(next(const_cast<_node*>(this->_n), this->_tree));
      return *this;
    }
    _Self &operator--() {
      this->_n = const_cast<const _node*>(prev(const_cast<_node*>(this->_n), this->_tree));
      return *this;
    }
    reference operator*() const { return *this->_n->_data; }
    pointer operator->() const { return this->_n->_data; }
    ~_ConstBtreeIterator() {}
  };

  _node *_root;
  _node *_null_node;
  size_t _size;
  bool _unique;
  Compare _cmp;

  static bool equal(T &x, T &y) {
    Compare cmp;
    return !cmp(x, y) && !cmp(y, x);
  }

  _node *_deep_copy(_node *target) {
    if (target == NULL)
      return NULL;
    _node *cpy = new _node(*target->_data, _alloc);
    if (target->left) {
      cpy->left = _deep_copy(target->left);
      cpy->left->parent = cpy;
    }
    if (target->right) {
      cpy->right = _deep_copy(target->right);
      cpy->right->parent = cpy;
    }
    return cpy;
  }

  void _destroy_single(_node *n)
  {
    destroy_data(n->_data, _alloc);
    delete n;
  }

  void _destroy(_node *n) {

    _node *r, *l;

    if (!n)
      return;

    l = n->left;
    r = n->right;
    _destroy_single(n);
    if (l)
      _destroy(l);
    if (r)
      _destroy(r);
  }

  static void replace_node(_node* dest, _node* src)
  {
    src->right = dest->right;
    src->left = dest->left;
    src->parent = dest->parent;
    if (src->left)
      src->left->parent = src;
    if (src->right)
      src->right->parent = src;
    if (dest->parent)
    {
      if (dest->parent->left == dest)
        dest->parent->left = src;
      else
        dest->parent->right = src;
    }
  }

  void destroy() {
    _destroy(_root);
    _root = NULL;
    _size = 0;
  }

  btree(bool unique = true, allocator_type alloc = allocator_type()) {
    _size = 0;
    _root = NULL;
    _unique = unique;
    _alloc = alloc;
  }

  btree(btree &src) {
    _root = _deep_copy(src._root);
    _size = src._size;
    _alloc = src._alloc;
  }

  ~btree() { _destroy(_root); }

  btree &operator=(const btree &src) {
    destroy();
    _size = src._size;
    _root = _deep_copy(src._root);
    _alloc = src._alloc;
    return *this;
  }

  void swap(btree& x)
  {
    _node* tmproot = _root;
    size_t tmpsize = _size;
    allocator_type tmpalloc = _alloc;
    Compare tmpcmp = _cmp;
    bool tmpunique = _unique;

    _root = x._root;
    _size = x._size;
    _alloc = x._alloc;
    _cmp = x._cmp;
    _unique = x._unique;

    x._root = tmproot;
    x._size = tmpsize;
    x._alloc = tmpalloc;
    x._cmp = tmpcmp;
    x._unique = tmpunique;
  }

  static size_t _count(_node *n, T& data)
  {
    size_t count = 0;
    if (n == NULL)
      return count;
    if (equal(*n->_data, data))
      count = 1;
    if (n->left)
      count += _count(n->left, data);
    if (n->right)
      count += _count(n->right, data);
    return count;
  }

  size_t count(T& data) const
  {
    return _count(_root, data);
  }

  void insert(T data) {
    _node *n = new _node(data, _alloc);
    if (_root == NULL) {
      _root = n;
      _size = 1;
      return;
    }
    _node *curr = _root;
    _node **next;
    while (1) {
      if (equal(*n->_data, *curr->_data) && _unique == true) {
        return;
      }
      if (_cmp(*n->_data, *curr->_data)) // go left cause n comes before curr
        next = &curr->left;
      else
        next = &curr->right;
      if (*next == NULL) {
        *next = n;
        n->parent = curr;
        _size++;
        break;
      }
      curr = *next;
    }
    if (n->parent == _root)
      return;
  }

  _node *search_node(_node *root, T &data) const {

    if (!root)
      return NULL;
    while (root && !equal(data, *root->_data))
      if (_cmp(data, *root->_data))
        root = root->left;
      else
        root = root->right;

    return root;
  }

  _node *first() const {
    if (!_root)
      return NULL;
    _node *n = _root;
    while (n->left)
      n = n->left;
    return n;
  }

  _node *last() const {
    if (!_root)
      return NULL;
    _node *n = _root;
    while (n->right)
      n = n->right;
    return n;
  }

  _node *transplant(_node *u, _node *v) {
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

  void remove(T data) {

    // Base case
    if (_root == NULL)
      return;
    // Searching the node to remove
    _node *n = _root;
    while (n && !equal(data, *n->_data)) {
      if (_cmp(data, *n->_data))
      {
        n = n->left;
      }
      else
      {
        n = n->right;
      }
    }

    // if n is null then no matching node encountered
    if (n == NULL)
      return;

    _node *x; // reference to the new node

    if (n->left == NULL)
      x = transplant(n, n->right);
    else if (n->right == NULL)
      x = transplant(n, n->left);
    else {
      _node *tmp = n->right;
      while (tmp->left)
        tmp = tmp->left;
      x = tmp->right;
      if (tmp != n->right) {
        if (x)
          x->parent = tmp->parent;
        tmp->parent->left = NULL;
        tmp->right = n->right;
        n->right->parent = tmp;
      }
      tmp->left = n->left;
      n->left->parent = tmp;
      transplant(n, tmp) ;
      if (n == _root)
        _root = tmp;
    }
    destroy_data(n->_data, _alloc);
    delete n;
    _size--;
  }
};
} // namespace ft
#endif // !BTREE_HPP
