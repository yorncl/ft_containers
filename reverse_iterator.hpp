#if !defined(FT_REVERSE_ITERATOR_HPP)
#define FT_REVERSE_ITERATOR_HPP

namespace ft
{
	template < class Container > class reverse_iterator
	{
		public:
		typedef reverse_iterator<Container>		_Self;
		typedef std::ptrdiff_t					difference_type;
		typedef typename Container::iterator	iterator;
		typedef typename iterator::value_type	value_type;
		typedef typename iterator::pointer		pointer;
		typedef typename iterator::reference	reference;

		iterator _it;
		
		reverse_iterator(){}
		reverse_iterator(const iterator &it){_it = it;}
		_Self operator++(int) {_Self tmp = *this; _it--; return tmp;}
		_Self& operator--() {_it++; return *this;}
		_Self& operator++() {_it--; return *this;}
		_Self operator--(int) {_Self tmp = *this; _it++; return tmp;}
		bool operator==(_Self other) const {return _it == other._it;}
		bool operator!=(_Self other) const {return _it != other._it;}
		reference operator*() const {return **_it;}
		pointer operator->() const {return *_it;}
		~reverse_iterator(){}
	};

	template < class Container > class const_reverse_iterator
	{
		public:
		typedef const_reverse_iterator<Container>	_Self;
		typedef std::ptrdiff_t						difference_type;
		typedef typename Container::iterator		iterator;
		typedef typename Container::const_iterator	const_iterator;
		typedef typename const_iterator::value_type	value_type;
		typedef typename const_iterator::pointer	pointer;
		typedef typename const_iterator::reference	reference;

		const_iterator _it;
		
		const_reverse_iterator(){}
		const_reverse_iterator(const reverse_iterator<Container> &it){_it = it._it;}
		const_reverse_iterator(const const_iterator &it){_it = it;}
		_Self operator++(int) {_Self tmp = *this; _it--; return tmp;}
		_Self& operator--() {_it++; return *this;}
		_Self& operator++() {_it--; return *this;}
		_Self operator--(int) {_Self tmp = *this; _it++; return tmp;}
		bool operator==(_Self other) const {return _it == other._it;}
		bool operator!=(_Self other) const {return _it != other._it;}
		reference operator*() const {return **_it;}
		pointer operator->() const {return *_it;}
		~const_reverse_iterator(){}
	};
};

#endif // FT_REVERSE_ITERATOR_HPP
