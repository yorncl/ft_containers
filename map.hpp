#ifndef FT_MAP_HPP
#define FT_MAP_HPP
#include "btree.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"
#include <map>
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
  typedef ft::reverse_iterator<_Self> reverse_iterator;
  typedef ft::const_reverse_iterator<_Self> const_reverse_iterator;
  // Comparison member
  class value_compare {
    friend class map;

  protected:
    Compare comp;
    value_compare(Compare c) : comp(c) {}

  public:
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool operator()(const value_type &x, const value_type &y) const {
      return comp(x.first, y.first);
    }
  };

  struct pair_pointer_compare {
    bool operator()(const pointer x, const pointer y,
                    value_compare cmp = value_compare()) const {
      return cmp(*x, *y);
    }
  };
  typedef ft::btree<pointer, pair_pointer_compare> tree_type;
  typedef typename tree_type::_node *node_pointer;
  typedef typename tree_type::_BtreeIterator iterator;
  typedef typename tree_type::_ConstBtreeIterator const_iterator;
  typedef
      typename ft::iterator_traits<iterator>::difference_type difference_type;
  typedef difference_type size_type;

  key_compare _comp;
  allocator_type _alloc;

  tree_type _tree;

  // constructor
  explicit map(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type()) {
    _comp = comp;
    _alloc = alloc;
    _tree = ft::btree<pointer, pair_pointer_compare>(true, _alloc);
  }
  template <class InputIterator>
  map(InputIterator first, InputIterator last,
      const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type()) {
    _comp = comp;
    _alloc = alloc;
    _tree._alloc = _alloc;
    while (first != last) {
      pointer ptr = create_pair(*first);
      _tree.insert(ptr, _comp);
      first++;
    }
    _tree = _Self(true, _alloc);
  }
  map(const map &x) { _tree = x._tree; }

  // ~map
  ~map() { _tree.destroy(); }

  // operator=
  map &operator=(const map &x) { _tree = x._tree; }

  // begin
  iterator begin() { iterator(_tree.first()); }
  const_iterator begin() const { const_iterator(_tree.begin()); }

  // end
  iterator end() {
    iterator it(_tree.last());
    it++;
    return it;
  }
  const_iterator end() const {
    const_iterator it(_tree.last());
    it++;
    return it;
  }

  // rbegin
  reverse_iterator rbegin() {
    iterator it = end();
    return reverse_iterator(it);
  }
  const_reverse_iterator rbegin() const {
    const_iterator it = end();
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
  size_type max_size() const {}

  // operator[]
  mapped_type &operator[](const key_type &k) {

    value_type pair = ft::make_pair<key_type, mapped_type>(k, mapped_type());
    node_pointer ptr = _tree.search_node(_tree._root, pair);
    reference ref = *ptr->_data;
    return ref.second;
  }

  // insert
  pair<iterator, bool> insert(const value_type &val) { (void)val; }
  iterator insert(iterator position, const value_type &val) {
    (void)position;
    (void)val;
  }
  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    (void)first;
    (void)last;
  }

  // erase
  void erase(iterator position) { (void)position; }
  size_type erase(const key_type &k) { (void)k; }
  void erase(iterator first, iterator last) {
    (void)first;
    (void)last;
  }

  // swap
  void swap(map &x) { (void)x; }

  // clear
  void clear() { _tree.destroy(); }

  // key_comp
  key_compare key_comp() const { return key_compare(); }

  // value_comp
  value_compare value_comp() const { return value_compare(); }

  // find
  iterator find(const key_type &k) { (void)k; }
  const_iterator find(const key_type &k) const { (void)k; }

  // count
  size_type count(const key_type &k) const { (void)k; }

  // lower_bound
  iterator lower_bound(const key_type &k) { (void)k; }
  const_iterator lower_bound(const key_type &k) const { (void)k; }

  // upper_bound
  iterator upper_bound(const key_type &k) { (void)k; }
  const_iterator upper_bound(const key_type &k) const { (void)k; }

  // equal_range
  pair<const_iterator, const_iterator> equal_range(const key_type &k) const {
    (void)k;
  }
  pair<iterator, iterator> equal_range(const key_type &k) { (void)k; }
};
} // namespace ft

#endif // MAP_HPP
