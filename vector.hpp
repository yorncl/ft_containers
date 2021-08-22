#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP
#include <memory>
#include <limits>
#include <exception>
#include <stdexcept>

#include "utils.hpp"
#include "reverse_iterator.hpp"

#define SCALING_FACTOR 2
#define INIT_CAPACITY 0

namespace ft
{

	template < class T > class _ConstVectorIterator;

	template < class T > class _VectorIterator
	{
		public:
		typedef _VectorIterator<T>	_Self;
		typedef std::ptrdiff_t		difference_type;
		typedef T					value_type;
		typedef T*					pointer;
		typedef T&					reference;
    typedef std::random_access_iterator_tag iterator_category;
    
		pointer _el;
		
		explicit _VectorIterator(){_el = NULL;}
		explicit _VectorIterator(const pointer p){_el = p;}
		_VectorIterator(const _VectorIterator<T> &it){_el = it._el;}
		_VectorIterator(const _ConstVectorIterator<T> &it){_el = const_cast<pointer>(it._el);}
		_Self operator++(int) {_Self tmp = *this; _el++ ; return tmp;}
		_Self operator--(int) {_Self tmp = *this; _el--; return tmp;}
		_Self& operator++() {_el++; return *this;}
		_Self& operator--() {_el--; return *this;}
		_Self& operator+=(int x) {_el += x; return *this;}
		_Self& operator-=(int x) {_el -= x; return *this;}
		_Self operator+(int a) const { return _Self(_el + a); }
		_Self operator-(int a) const { return _Self(_el - a); }
		difference_type operator-(_Self a) const { return _el - a._el; }
		bool operator==(_Self other) const {return _el == other._el;}
		bool operator!=(_Self other) const {return _el != other._el;}
		bool operator<(_Self other) const {return _el < other._el;}
		bool operator>(_Self other) const {return _el > other._el;}
		bool operator<=(_Self other) const {return _el <= other._el;}
		bool operator>=(_Self other) const {return _el >= other._el;}
		reference operator[] (int i) { return _el[i]; }
		reference operator*() const {return *_el;}
		pointer operator->() const {return _el;}
		~_VectorIterator(){}
	};


	template < class T > class _ConstVectorIterator
	{	
		public:
		typedef _ConstVectorIterator<T>	_Self;
		typedef std::ptrdiff_t		difference_type;
		typedef const T					value_type;
		typedef const T*					pointer;
		typedef const T&					reference;
    typedef std::random_access_iterator_tag iterator_category;

		pointer _el;
		
		explicit _ConstVectorIterator(){_el = NULL;}
		explicit _ConstVectorIterator(pointer p){_el = p;}
		_ConstVectorIterator(const _VectorIterator<T> &it){_el = it._el;}
		_ConstVectorIterator(const _ConstVectorIterator<T> &it){_el = it._el;}
		_Self operator++(int) {_Self tmp = *this; _el++ ; return tmp;}
		_Self operator--(int) {_Self tmp = *this; _el--; return tmp;}
		_Self& operator++() {_el++; return *this;}
		_Self& operator--() {_el--; return *this;}
		_Self& operator+=(int x) {_el += x; return *this;}
		_Self& operator-=(int x) {_el -= x; return *this;}
		_Self operator+(int a) const {return _Self(_el + a);}
		_Self operator-(int a) const {return _Self(_el - a);}
		difference_type operator-(_Self a) const { return _el - a._el; }
		bool operator==(_Self other) const {return _el == other._el;}
		bool operator!=(_Self other) const {return _el != other._el;}
		bool operator<(_Self other) const {return _el < other._el;}
		bool operator>(_Self other) const {return _el > other._el;}
		bool operator<=(_Self other) const {return _el <= other._el;}
		bool operator>=(_Self other) const {return _el >= other._el;}
		reference operator[] (int i) { return _el[i]; }
		reference operator*() const {return *_el;}
		pointer operator->() const {return _el;}
		~_ConstVectorIterator(){}
	};

	template < class T, class Alloc = std::allocator<T> > class vector // generic template
	{
		public:
		//Member types
		typedef vector<T, Alloc> _Self;
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef _VectorIterator<T> iterator;
		typedef _ConstVectorIterator<T> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename std::ptrdiff_t difference_type;
		typedef size_t size_type;

		typedef struct s_data_block
		{
			size_t size;
			size_t capacity;
			pointer data;
		} _Block;

		allocator_type arr_alloc;
		_Block _storage;


		private:

		pointer blockAllocation(size_t capacity)
		{
			pointer ptr = arr_alloc.allocate(capacity * sizeof(T));
			for (size_t i = 0; i < capacity; i++)
				arr_alloc.construct(&ptr[i], T());
			return ptr;
		}

		// create a block with n size
		_Block initBlock(size_t n)
		{
			_Block b;
			b.size = n;
			if (b.size == 0)
				b.capacity = INIT_CAPACITY;
			else
				b.capacity = n * SCALING_FACTOR;
			b.data = blockAllocation(b.capacity);
			return b;
		}

		// copy into new
		_Block copyBlock(const _Block& src)
		{
			_Block b = initBlock(src.size);
			for (size_t i = 0; i < src.size; i++)
				b.data[i] = src.data[i];
			return b;
		}

		// copy and erase
		void copyBlock(const _Block& src, _Block& dest)
		{
			_Block b = copyBlock(src);
			destroyBlock(dest);
			dest = b;
		}

		void reallocateBlock(_Block& b)
		{
      if (b.capacity == 0)
			  reallocateBlock(b, 1);
      else
			  reallocateBlock(b, b.capacity * SCALING_FACTOR);
		}

		void reallocateBlock(_Block& src, size_t capacity)
		{
			_Block b;

			b.capacity = capacity;
			b.size = src.size;
			b.data = blockAllocation(b.capacity);
			for (size_t i = 0; i < src.size; i++)
				b.data[i] = src.data[i];
			destroyBlock(src);
			src = b;
		}

		// destroy block
		void destroyBlock(_Block& b)
		{
			for (size_t i = 0; i < b.capacity; i++)
				arr_alloc.destroy(&_storage.data[i]);
			arr_alloc.deallocate(b.data, b.capacity * sizeof(T));
			b.size = 0;
			b.capacity = 0;
		}


		public:
		// constructor
		explicit vector (const allocator_type& alloc = allocator_type())
		{
			arr_alloc = alloc;
			_storage = initBlock(0);
		}
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		{
			arr_alloc = alloc;
			_storage = initBlock(n);
			pointer ptr = _storage.data;
			while (n--)
			{
				*ptr = val;
				ptr++;
			}
			
		}
		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), REQUIRE_ITER(InputIterator))
		{
			arr_alloc = alloc;
			size_t n = 0;

			for (InputIterator f = first; f != last; f++)
				n++;
			_storage = initBlock(n);
			pointer ptr = _storage.data;
			for (; first != last; first++)
			{
				*ptr = *first;
				ptr++;
			}
		}
		vector (const vector& x)
		{
			_storage = copyBlock(x._storage);
		}

		// ~vector
		~vector()
		{
			destroyBlock(_storage);
		}

		// operator=
		vector& operator= (const vector& x)
		{
			copyBlock(x._storage, _storage);
			return *this;
		}

		// begin
		iterator begin()
		{
			return iterator(_storage.data);
		}
		const_iterator begin() const
		{
			return const_iterator(_storage.data);
		}

		// end
		iterator end()
		{
			return iterator(&_storage.data[_storage.size]);
		}
		const_iterator end() const
		{
			return const_iterator(&_storage.data[_storage.size]);
		}
		// rbegin
		reverse_iterator rbegin()
		{
			return reverse_iterator(iterator(&_storage.data[_storage.size - 1]));
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(const_iterator(&_storage.data[_storage.size - 1]));
		}

		// rend
		reverse_iterator rend()
		{
			return reverse_iterator(iterator(_storage.data - 1));
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(const_iterator(_storage.data - 1));
		}

		// size
		size_type size() const
		{
			return _storage.size;
		}

		// max_size
		size_type max_size() const
		{
			return std::numeric_limits<difference_type>::max() / (sizeof(T));
		}

		// resize
		void resize (size_type n, value_type val = value_type())
		{
			size_t old = _storage.size;

			if (n == _storage.size)
				return;
			else if (n > _storage.size)
			{
				reallocateBlock(_storage, n * SCALING_FACTOR);
				_storage.size = n;
				for (size_t i = old; i < n; i++)
					_storage.data[i] = val;
			}
			else
			{
				_storage.size = n;
				for (size_t i = n; i < old; i++)
					arr_alloc.destroy(&_storage.data[i]);
			}
		}

		// capacity
		size_type capacity() const
		{
			return _storage.capacity;
		}

		// empty
		bool empty() const
		{
			return _storage.size == 0;
		}

		// reserve
		void reserve (size_type n)
		{
      if (_storage.capacity > n)
        return ;
      if (n > max_size())
        throw std::length_error("n larger than vector::max_size()");
      reallocateBlock(_storage, n);
		}

		// operator[]
		reference operator[] (size_type n)
		{
			return _storage.data[n];
		}
		const_reference operator[] (size_type n) const
		{
			return _storage.data[n];
		}

		// at
		reference at (size_type n)
		{
			if (n >= _storage.size)
				throw std::out_of_range("Index out of vector's range");
			return _storage.data[n];
		}
		const_reference at (size_type n) const
		{
			if (n >= _storage.size)
				throw std::out_of_range("Index out of vector's range");
			return _storage.data[n];
		}

		// front
		reference front()
		{
			return _storage.data[0];
		}
		const_reference front() const
		{
			return _storage.data[0];
		}

		// back
		reference back()
		{
			return _storage.data[_storage.size - 1];
		}
		const_reference back() const
		{
			return _storage.data[_storage.size - 1];
		}

		// assign
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last, REQUIRE_ITER(InputIterator))
		{
			size_t n = 0;
			for (InputIterator i = first; i != last; i++)
				n++;
			destroyBlock(_storage);
			_storage = initBlock(n);
			for (size_t i = 0; i < n ; i++)
			{
				_storage.data[i] = *first;
				first++;
			}
		}
		void assign (size_type n, const value_type& val)
		{
			destroyBlock(_storage);
			_storage = initBlock(n);
			for (size_t i = 0; i < n ; i++)
				_storage.data[i] = val;
		}

		// push_back
		void push_back (const value_type& val)
		{
			if (_storage.size + 1 > _storage.capacity)
			{
				reallocateBlock(_storage);
			}
			_storage.size++;
			/* std::cout << &_storage.data  << " " << _storage.size - 1 << std::endl; */
			_storage.data[_storage.size - 1] = val;
		}

		// pop_back
		void pop_back()
		{
			arr_alloc.destroy(&_storage.data[_storage.size - 1]);
			_storage.size--;
		}

		// insert
		iterator insert (iterator position, const value_type& val)
		{
      size_t offset = position._el - _storage.data;
      insert(position, 1, val);
      return iterator(&_storage.data[offset]);
		}
		void insert (iterator position, size_type n, const value_type& val)
		{
      size_t offset = position._el - _storage.data;
      _Block newBlock = initBlock(_storage.size + n);

      size_t i = 0;
      size_t j = 0;
      while(offset--)
      {
        newBlock.data[i] = _storage.data[j];
        i++;
        j++;
      }
      while (n--)
      {
        newBlock.data[i] = val;
        i++;
      }
      while(j < _storage.size)
      {
        newBlock.data[i] = _storage.data[j];
        i++;
        j++;
      }
      destroyBlock(_storage);
      _storage = newBlock;
		}
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last, REQUIRE_ITER(InputIterator))
		{
      size_t offset = position._el - _storage.data;
      _Block newBlock = initBlock(_storage.size + std::distance(first, last));

      size_t i = 0;
      size_t j = 0;
      while(offset--)
      {
        newBlock.data[i] = _storage.data[j];
        i++;
        j++;
      }
      while (first != last)
      {
        newBlock.data[i] = *first;
        i++;
        first++;
      }
      while(j < _storage.size)
      {
        newBlock.data[i] = _storage.data[j];
        i++;
        j++;
      }
      destroyBlock(_storage);
      _storage = newBlock;
		}

		// erase
		iterator erase (iterator position)
		{
			(void) position;
      _Block b = initBlock(_storage.size - 1);
      iterator it = begin();
      size_t i = 0;
      size_t pos = 0;
      while (it != end())
      {
        if (it != position)
        {
          b.data[i] = *it; 
          i++;
        }
        else
          pos = i;
        it++;
      }
      destroyBlock(_storage);
      _storage = b;
			return iterator(_storage.data + pos + 1);
		}

		iterator erase (iterator first, iterator last)
		{
      size_t size = last._el - first._el;
      _Block b = initBlock(_storage.size - size);
      size_t i = 0;
      iterator it = begin();
      iterator pos = it;
      while (it != first)
      {
        b.data[i] = *it;
        i++;
      }
      pos = it + 1;
      it = last;
      while(it != end())
      {
        b.data[i] = *it;
        i++;
        it++;
      }
      destroyBlock(_storage);
      _storage = b;
			return pos; 
		}

		// swap
		void swap (vector& x)
		{
			_Block tmp = x._storage;
			x._storage = _storage;
			_storage = tmp;
		}

		// clear
		void clear()
		{
			_storage.size = 0;
		}

	};
	// operators
	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		typename vector<T,Alloc>::iterator it1 = lhs.begin();
		typename vector<T,Alloc>::iterator it2 = rhs.begin();
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
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return true;
		typename vector<T,Alloc>::iterator it1 = lhs.begin();
		typename vector<T,Alloc>::iterator it2 = rhs.begin();
		while (it1 != lhs.end() && it2 != rhs.end())
		{
			if (*it1 != *it2)
				return true;
			it1++;
			it2++;
		}
		return !(it1 == lhs.end() && it2 == rhs.end());
	}
	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
    return rhs > lhs;
	}
	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
    return !(lhs < rhs);
	}
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
    return rhs < lhs;
	}
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
} // namespace ft

template<class T>
ft::_VectorIterator<T>operator+(int a, ft::_VectorIterator<T>& it) { return it + a; }

template<class T>
ft::_ConstVectorIterator<T>operator+(int a, ft::_ConstVectorIterator<T>& it) { return it + a; }
#endif //VECTOR_HPP
