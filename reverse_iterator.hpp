#if !defined(FT_REVERSE_ITERATOR_HPP)
#define FT_REVERSE_ITERATOR_HPP

namespace ft
{

	template < class Iter > class reverse_iterator
	{
		public:
		typedef reverse_iterator<Iter>		_Self;
		typedef typename Iter::difference_type	difference_type;
		typedef typename Iter::value_type	value_type;
		typedef typename Iter::pointer		pointer;
		typedef typename Iter::reference	reference;
		typedef typename Iter::iterator_category	iterator_category;

		Iter _it;
		
		reverse_iterator(){} reverse_iterator(const _Self &it){_it = it._it;}
		reverse_iterator(const Iter &it){_it = it;}
    template<class U>
		reverse_iterator(const reverse_iterator<U> &it){_it = it._it;}
    template<class U>
		reverse_iterator(const U &it){_it = it;}
		_Self operator++(int) {_Self tmp = *this; _it--; return tmp;}
		_Self& operator--() {_it++; return *this;}
		_Self& operator++() {_it--; return *this;}
		_Self operator--(int) {_Self tmp = *this; _it++; return tmp;}
		_Self operator+(int a) const { return _Self(_it + a); }
		_Self operator-(int a) const { return _Self(_it - a); }
		_Self& operator+=(int x) {_it += x; return *this;}
		_Self& operator-=(int x) {_it -= x; return *this;}
		difference_type operator-(_Self it) const { return _it - it._it; }
		bool operator==(_Self other) const {return _it == other._it;}
		bool operator!=(_Self other) const {return _it != other._it;}
		bool operator<(_Self other) const {return _it < other._it;}
		bool operator>(_Self other) const {return _it > other._it;}
		bool operator<=(_Self other) const {return _it <= other._it;}
		bool operator>=(_Self other) const {return _it >= other._it;}
		_Self& operator=(const _Self& other) {_it = other._it; return *this;}
		reference operator*() const {return *_it;}
		Iter operator->() const {return _it;}
		reference operator[] (int i) { return _it[-i]; }
		~reverse_iterator(){}

    Iter base() { return _it; };
	};

template<class T>
ft::reverse_iterator<T>operator+(int a, ft::reverse_iterator<T>& it) { return it + a; }

}
#endif // FT_REVERSE_ITERATOR_HPP
