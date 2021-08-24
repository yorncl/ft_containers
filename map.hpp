#ifndef FT_MAP_HPP
#define FT_MAP_HPP
#include "btree.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"
#include <limits>
#include <memory>

namespace ft {

template <class Key,                      // map::key_type
          class T,                        // map::mapped_type
          class Compare = std::less<Key>, // map::key_compare
          class Alloc =
              std::allocator<ft::pair<const Key, T> > // map::allocator_type
          >
class map {
public:
  typedef map<Key, T, Compare, Alloc> _Self;
  // Member types

  typedef Key key_type;
  typedef T mapped_type;
  typedef ft::pair<const key_type, mapped_type> value_type;
  typedef Compare key_compare;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  // Comparison member
  class value_compare {


  protected:
    Compare comp;
    value_compare(Compare c) : comp(c) {}

  public:
  value_compare() : comp() {}
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool operator()(const value_type &x, const value_type &y) const {
      return comp(x.first, y.first);
    }
  };

  typedef ft::btree<value_type, value_compare> tree_type;
  typedef typename tree_type::_node *node_pointer;
  typedef typename tree_type::_node node_type;
  typedef typename tree_type::_BtreeIterator iterator;
  typedef typename tree_type::_ConstBtreeIterator const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::ptrdiff_t difference_type;
  typedef unsigned long size_type;

  key_compare _comp;
  allocator_type _alloc;

  tree_type _tree;

  // constructor
  map(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type()) {
    _comp = comp;
    _alloc = alloc;
    _tree = tree_type(true, _alloc);
  }
  template <class InputIterator>
  map(InputIterator first, InputIterator last,
      const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type(), REQUIRE_ITER(InputIterator)) {
    _comp = comp;
    _alloc = alloc;
    _tree._alloc = _alloc;
    while (first != last) {
      value_type pair = ft::make_pair(first->first, first->second);
      _tree.insert(pair);
      first++;
    }
  }
  map(const map &x) { _tree = x._tree; }

  // ~map
  ~map() {}

  // operator=
  map &operator=(const map &x) {
    _tree = x._tree;
    return *this;
  }

  // begin
  iterator begin() { return iterator(_tree.first(), &_tree); }
  const_iterator begin() const { return const_iterator(_tree.first(), &_tree); }

  // end
  iterator end() {
    iterator it(_tree.last(), &_tree);
    it++;
    return it;
  }
  const_iterator end() const {
    const_iterator it(_tree.last(), &_tree);
    it++;
    return it;
  }

  // rbegin
  reverse_iterator rbegin() {
    iterator it = iterator(_tree.last(), &_tree);
    return reverse_iterator(it);
  }
  const_reverse_iterator rbegin() const {
    const_iterator it = const_iterator(_tree.last(), &_tree);
    return const_reverse_iterator(it);
  }

  // rend
  reverse_iterator rend() {
    iterator it = begin();
    it--;
    return reverse_iterator(it);
  }
  const_reverse_iterator rend() const {
    const_iterator it = begin();
    it--;
    return const_reverse_iterator(it);
  }

  // empty
  bool empty() const { return _tree._size == 0; }

  // size
  size_type size() const { return _tree._size; }

  // max_size
  size_type max_size() const {
			return std::numeric_limits<difference_type>::max() / (sizeof(node_type) + sizeof(value_type));
  }

  // operator[]
  mapped_type &operator[](const key_type &k) {

    value_type pair = ft::make_pair<const key_type, mapped_type>(k, mapped_type());
    node_pointer ptr = _tree.search_node(_tree._root, pair);
    if (ptr == NULL)
      _tree.insert(pair);
    ptr = _tree.search_node(_tree._root, pair);
    reference ref = *ptr->_data;
    return ref.second;
  }

  // insert
  pair<iterator, bool> insert(const value_type &val) {
    iterator it = find(val.first);
    if (it != end())
      return ft::make_pair<iterator, bool> (it, false);
    _tree.insert(val);
    return ft::make_pair<iterator, bool>(find(val.first), true);
  }

  iterator insert(iterator position, const value_type &val) {
    (void) position;
    return insert(val).first;
  }

  template <class InputIterator>
  void insert(InputIterator first, InputIterator last, REQUIRE_ITER(InputIterator)) {
    while (first != last)
      _tree.insert(*first++);
  }

  // erase
  void erase(iterator position) { _tree.remove(*position); }
  size_type erase(const key_type &k) {

    if (_tree._root == NULL)
      return 0;
    value_type p = ft::make_pair<const key_type, mapped_type>(k, mapped_type());
    if (find(k) == end())
      return 0;
    _tree.remove(p);
    return 1;
  }
  void erase(iterator first, iterator last) {
    iterator next = first;
    if (next != end())
      next++;
    while (first != last)
    {
      _tree.remove(*first);
      first = next;
      if (next != end())
        next++;
    }
  }

  // swap
  void swap(map &x) {
    _tree.swap(x._tree);
    allocator_type tmpalloc = _alloc;
    key_compare tmpcomp = _comp;
    _alloc = x._alloc;
    _comp = x._comp;
    x._alloc = tmpalloc;
    x._comp = tmpcomp;
  }

  // clear
  void clear() { _tree.destroy(); }

  // key_comp
  key_compare key_comp() const { return key_compare(); }

  // value_comp
  value_compare value_comp() const { return value_compare(); }

  // find
  iterator find(const key_type &k) {
    value_type p = ft::make_pair<const key_type, mapped_type>(k, mapped_type());
    node_pointer node = _tree.search_node(_tree._root, p);
    if (node == NULL)
      return end();
    return iterator(node, &_tree);
  }
  const_iterator find(const key_type &k) const {
    value_type p = ft::make_pair<const key_type, mapped_type>(k, mapped_type());
    node_pointer node = _tree.search_node(_tree._root, p);
    if (node == NULL)
      return end();
    return const_iterator(node, &_tree);
  }

  // count
  size_type count(const key_type &k) const {
    value_type search = ft::make_pair<const key_type, mapped_type>(k, mapped_type());
    return _tree.count(search);
  }

  // lower_bound
  iterator lower_bound(const key_type &k) {
    iterator it = begin();
    while (it != end() && _comp(it->first, k))
      it++;
    return it;
  }
  const_iterator lower_bound(const key_type &k) const {
    const_iterator it = begin();
    while (it != end() && _comp(it->first, k))
      it++;
    return it;
  }

  // upper_bound
  iterator upper_bound(const key_type &k) {
    iterator it = lower_bound(k);
    if (it == begin() && _comp(k, it->first))
      return it;
    if (it != end())
      it++;
    return it; // technically it's not end(), but it's the same it terms of the pointer value 
  }
  const_iterator upper_bound(const key_type &k) const {
    const_iterator it = lower_bound(k);
    if (it == begin() && _comp(k, it->first))
      return it;
    if (it != end())
      it++;
    return it; // technically it's not end(), but it's the same it terms of the pointer value 
  }

  // equal_range
  ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const {
    return ft::make_pair(lower_bound(k), upper_bound(k));
  }
  ft::pair<iterator, iterator> equal_range(const key_type &k) {
    return ft::make_pair(lower_bound(k), upper_bound(k));
  }
};
  // operators
  template <class T, class Alloc>
  bool operator==(const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
  {
    if (lhs.size() != rhs.size())
      return false;
    typename map<T,Alloc>::const_iterator it1 = lhs.begin();
    typename map<T,Alloc>::const_iterator it2 = rhs.begin();
    while (it1 != lhs.end() && it2 != rhs.end())
    {
      if (*it1 != *it2)
        return false;
      it1++;
      it2++;
    }
    return (it1 == lhs.end() && it2 == rhs.end());
  }
  template <class T, class Alloc>
  bool operator!=(const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
  {
    return !(lhs == rhs);
  }
  template <class T, class Alloc>
  bool operator<(const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
  {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  }
  template <class T, class Alloc>
  bool operator<= (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
  {
    return !(rhs < lhs);
  }
  template <class T, class Alloc>
  bool operator> (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
  {
    return rhs < lhs;
  }
  template <class T, class Alloc>
  bool operator>= (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
  {
    return !(lhs < rhs);
  }
  template <class T, class Alloc>
  void swap (map<T,Alloc>& x, map<T,Alloc>& y)
  {
    x.swap(y);
  }
  } // namespace ft

#endif // MAP_HPP
