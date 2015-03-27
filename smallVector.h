#ifndef _SMALL_VECTOR_H_
#define _SMALL_VECTOR_H_

#include <stdexcept>
#include <algorithm>
#include <limits.h>

template <typename T>
class ArrayVector;

template <typename T>
class smallVector {
  public:
	// typedefs
	typedef T *			  		 iterator;
    	typedef unsigned int          size_type;
	// public member functions
	// Construct/Copy/Destruct
	smallVector();
	smallVector( size_type max_capacity);
	smallVector(const smallVector& V);
	smallVector(size_type n, const T& val);
	smallVector(iterator _first, iterator _last);
	~smallVector();
	smallVector<T>& operator=(const smallVector& V);

	// Capacity
	size_type 	size() const noexcept;
	size_type 	max_size() const noexcept;
	void 		resize( size_type n);
	size_type 	capacity() const noexcept;
	bool		empty() const noexcept;
	void		reserve( size_type n);
	void		shrink_to_fit();

	// Element Access
	T& operator[]( size_type i);
	const T& operator[]( size_type i) const;
	
	T& at(size_type i) throw (std::out_of_range);
	
	const T& front() const;
	const T& back() const;

	// Iterators
	iterator begin() noexcept;
	iterator end() noexcept;

	// Modifiers
	void assign(size_type n, const T& val);
	void assign(iterator _first, iterator _last);
	
	void push_back(const T& val)  ;
	void pop_back();
	
	void insert(typename smallVector<T>::size_type i, const T& e) throw (std::out_of_range);
	void insert(iterator pos, const T& e) throw (std::out_of_range);
	void insert(iterator pos,  size_type n, const T& e) throw (std::out_of_range);
	void insert(iterator pos,  iterator _first, iterator _last) throw (std::out_of_range);
	
	void erase(typename smallVector<T>::size_type i) throw (std::out_of_range);
	void erase(iterator pos) throw (std::out_of_range);
	void erase(iterator _first, iterator _last) throw (std::out_of_range);
	
	void clear();
	void swap (smallVector& x);

	// Private members
T* 				_buffer;
	size_type		_maxSize;
	size_type		_capacity;
	size_type		_size;
	iterator		first;
	iterator		last;
	const size_type 	MAX_SIZE = UINT_MAX;
};
#endif

// Construct/Copy/Destruct
template <typename T>
smallVector<T>::smallVector(){
	_capacity =0, _size=0, _buffer = nullptr , _maxSize = smallVector<T>::MAX_SIZE;
	first = nullptr;
	last = nullptr;
}

/* As per conversation with  Mr Thorsten
>>>Now I have a small different question "The _capacity is set in the constructor. push_back throws when the _buffer is full."
		Does this mean that the maximum _capacity of the container is fixed i.e. the container can never have a _size/_capacity
		bigger than the maximum _capacity? And if the maximum _capacity is reached push_back throws the _buffer full error.
	yes.
	-Thorsten
*/
template <typename T>
smallVector<T>::smallVector( typename smallVector<T>::size_type max_capacity){
	_capacity =0, _size=0, _buffer = nullptr , _maxSize = max_capacity;
	first = nullptr;
	last = nullptr;
}


template <typename T>
smallVector<T>::smallVector(typename smallVector<T>::iterator _first,
                            typename smallVector<T>::iterator _last){
	_capacity =0, _size=0, _buffer = nullptr , _maxSize = smallVector<T>::MAX_SIZE;
	first = nullptr;
	last = nullptr;
	while(_first!=_last){
		push_back(*_first);
		_first++;
	}
}

template <typename T>
smallVector<T>::smallVector(typename smallVector<T>::size_type n, const T& val){
	_capacity =0, _size=0, _buffer = nullptr , _maxSize = smallVector<T>::MAX_SIZE;
	first = nullptr;
	last = nullptr;
	while(n--){
		push_back(val);
	}
}

template <typename T>
smallVector<T>::smallVector(const smallVector& V){
	_capacity =V._capacity, _size=V._size, _buffer = new T[V._size];
	_maxSize = V._maxSize();
	first = _buffer[0];
	for (typename smallVector<T>::size_type i = 0; i < _size; ++i){
		_buffer[i] = V[i];
	}
	last = _buffer[_size-1]+1;
}

template <typename T>
smallVector<T>::~smallVector(){
	delete[] _buffer;
}

template <typename T>
smallVector<T>& smallVector<T>::operator=(const smallVector& V){
	T* newBuffer = new T[V._size];
	_size = V._size;
	_capacity = V._capacity;
	_maxSize = V._maxSize();
	for (unsigned int i = 0; i < V.sz; ++i){
		newBuffer[i] = V[i];
	}
	delete[] _buffer;
	first = V.begin();
	last = V.end();
	_buffer = newBuffer;
	return *this;
}

// Capacity
template <typename T>
typename smallVector<T>::size_type smallVector<T>::size() const noexcept{
	return _size;
}

template <typename T>
typename smallVector<T>::size_type smallVector<T>::max_size() const noexcept{
	return _maxSize;
}

template <typename T>
void smallVector<T>::resize(typename smallVector<T>::size_type n){
	// update _size
	if(n>_maxSize) return;
	if (n < _size){
		_size = n;
	}else{
		// allocate new memory and copy old data
		T* newBuffer = new T[n];
		for (unsigned int i = 0; i < _size; ++i)
			newBuffer[i] = _buffer[i];
		// delete old data
		delete[] _buffer;
		// update _capacity and data pounsigned inter
		_capacity = n;
		_size = n;
		_buffer = newBuffer;
	}
	first = _buffer[0];
	last = _buffer[_size-1]+1;
}

template <typename T>
typename smallVector<T>::size_type smallVector<T>::capacity() const noexcept{
	return _capacity;
}

template <typename T>
bool smallVector<T>::empty() const noexcept{
	return _size == 0;
}

template <typename T>
void smallVector<T>::shrink_to_fit(){
	_capacity = _size;
	T* newBuffer = new T[_size];
	for (unsigned int i = 0; i < _size; ++i){
		newBuffer[i] = _buffer[i];
	}
	
	delete[] _buffer;
	_buffer = newBuffer;
}

// Element Access
template <typename T>
T& smallVector<T>::operator[](typename smallVector<T>::size_type i){
	return _buffer[i];
}

template <typename T>
const T& smallVector<T>:: operator[](typename smallVector<T>::size_type i) const{
	if(i<_size)
		return _buffer[i];
	return 0;
}

template <typename T>
T& smallVector<T>::at(typename smallVector<T>::size_type i) throw (std::out_of_range){
	if (i < 0 || i >= _size){
		throw std::out_of_range("Illegal index in function at()");
	}
	return _buffer[i];
}

template <typename T>
const T& smallVector<T>::front() const{
	return *first;
}

template <typename T>
const T& smallVector<T>::back() const{
	return *(last - sizeof(typename smallVector<T>::size_type));
}

// Iterators
template <typename T>
typename smallVector<T>::iterator smallVector<T>::begin() noexcept{
	return first;
}

template <typename T>
typename smallVector<T>::iterator smallVector<T>::end() noexcept{
	return last;
}

//Modifiers
template <typename T>
void smallVector<T>::assign(typename smallVector<T>::size_type n, const T& val){
	if(n>_maxSize) return;
	_size = n;
    	T* newBuffer = new T[_size];
	for (typename smallVector<T>::size_type  i = 0; i < _size; ++i){
		newBuffer[i] = val;
	}
	delete[] _buffer;
	_buffer = newBuffer;
	if(_capacity < _size) _capacity = _size;
	first = &_buffer[0];
	last = &(_buffer[_size-1]) + 1;
}

template <typename T>
void smallVector<T>::assign(typename smallVector<T>::iterator _first,
                                    typename smallVector<T>::iterator _last){
    	clear();
    	while(_first!=_last){
		push_back(*_first);
        	_first++;
	}
}

template <typename T>
void smallVector<T>::push_back(const T& e) {
	try{
		insert(_size, e);
	}catch(std::exception& e){
		std::cout << e.what() << '\n';
	}
}

template <typename T>
void smallVector<T>::pop_back(){
	if(_size == 0 ) 
		return;
	resize(_size-1);
}

template <typename T>
void smallVector<T>::reserve(typename smallVector<T>::size_type n){
	if (n <= _capacity || n>_maxSize){
		return;
	}
	T* newBuffer;
	try{
		newBuffer = new T[n];
		for(typename smallVector<T>::size_type i = 0; i < _size; i++)
		    newBuffer[i] = _buffer[i];
		delete[] _buffer;
		_buffer = newBuffer;
		first = &_buffer[0];
		if(_size>0)
		    last = &_buffer[_size-1] + 1;
		else last = first;
		_capacity = n;
	}catch (std::exception& e){
		std::cout << e.what() << '\n';
	}
}

template <typename T>
void smallVector<T>::insert(typename smallVector<T>::size_type i, const T& e) throw (std::out_of_range) {
	if (i < 0 || i > _size){
		throw std::out_of_range("Illegal index in function insert()");
	}
	if (_size >= _capacity){
		reserve(std::max(_size+1, std::min(2 * _size, _maxSize)));
	}
    	if(_size+1 > _capacity){
    		return;
    	}
	for (typename smallVector<T>::size_type j = _size; j > i; --j){
		_buffer[j] = _buffer[j - 1];
	}
	_buffer[i] = e;
	last = &_buffer[_size] + 1;
	_size++;
}

template <typename T>
void smallVector<T>::insert(typename smallVector<T>::iterator pos, const T& e) throw (std::out_of_range){
	insert(typename smallVector<T>::size_type(pos - begin()),  e);
}

template <typename T>
void smallVector<T>::insert(typename smallVector<T>::iterator pos,
                            typename smallVector<T>::iterator _first,
                            typename smallVector<T>::iterator _last) throw (std::out_of_range){
    typename smallVector<T>::size_type n =
            typename smallVector<T>::size_type(_last - _first) ;
    	if(_size == _maxSize || _size+n>_maxSize){
		throw std::out_of_range("Illegal index in function insert()");
    	}
	typename smallVector<T>::size_type i = typename smallVector<T>::size_type(pos - begin());
	if(_size+n > _capacity){
		reserve(std::max(_size+n, std::min(2 * _size, _maxSize)));
	}
    	if(_size+n > _capacity){
    		return;
    	}
	_size += n;
	for(typename smallVector<T>::size_type j = _size-1; j>=i+n; j--){
		_buffer[j] = _buffer[j - n];
	}
	while(n--){
		_buffer[i++] = *_first;
		_first++;
	}
	last = &_buffer[_size-1] + 1;
}

template <typename T>
void smallVector<T>::insert(typename smallVector<T>::iterator pos,
	typename smallVector<T>::size_type n, const T& e)
	throw (std::out_of_range){
	if(_size == _maxSize || _size+n>_maxSize){
		throw std::out_of_range("Illegal index in function insert()");
	}
	typename smallVector<T>::size_type i = typename smallVector<T>::size_type(pos - begin());
	if(_size+n > _capacity){
		reserve(std::max(_size+n, std::min(2 * _size, _maxSize)));
	}
    	if(_size+n > _capacity){
    		return;
    	}
	_size += n;
	for(typename smallVector<T>::size_type j = _size-1; j>=i+n; j--){
		_buffer[j] = _buffer[j - n];
	}
	while(n--){
		_buffer[i++] = e;
	}
	last = &_buffer[_size-1] + 1;
}

template <typename T>
void smallVector<T>::erase(typename smallVector<T>::size_type i) throw (std::out_of_range){
	return erase(begin()+i);
}

template <typename T>
void smallVector<T>::erase(typename smallVector<T>::iterator pos) throw (std::out_of_range){
	return erase(pos, pos+1);
}

template <typename T>
void  smallVector<T>::erase(typename smallVector<T>::iterator _first,
        		typename smallVector<T>::iterator _last) throw (std::out_of_range){
	typename smallVector<T>::size_type n = (_last-_first);
	typename smallVector<T>::size_type i = typename smallVector<T>::size_type(_first - begin());
	if(_size == 0 || i+n>_size || i<0 ){
		throw std::out_of_range("Max _size reached!");
	}
	for(; i+n<_size; i++)
        _buffer[i] = _buffer[i+n];
	_size-=n;
	if(_size>0){
		last = &_buffer[_size-1] + 1;
	}
}

template <typename T>
void smallVector<T>::clear(){
	_size = 0;
	delete[] _buffer;
}

template <typename T>
void smallVector<T>::swap (smallVector& x){
	swap(this, x);
}
