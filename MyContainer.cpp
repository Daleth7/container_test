#include "MyContainer.h"

#include <utility> //std::move()

using T=int;
/*************************************************************
                      MyContainer
**************************************************************/
//Tests
bool MyContainer::empty(){
	if(__data_size) return false;
	return true;
}
bool MyContainer::garbage_exists(){
	if(__junk != nullptr) return true;
	return false;
}
bool MyContainer::operator==(const MyContainer& s){
	if(this == &s) return true;
	if(
		__data_size != s.__data_size ||
		__capacity != s.__capacity
	) return false;
	for(size_t i(0); i < __data_size; ++i){
		if(__data[i] != s.__data[i])
			return false;
	}
	return true;
}
//Iterators
MyContainer::iterator MyContainer::begin(){
	return MyContainer::iterator(__data,0);
}
MyContainer::iterator MyContainer::end(){
	return MyContainer::iterator(__data,__data_size);
}
MyContainer::reverse_iterator MyContainer::rbegin(){
	return MyContainer::reverse_iterator(__data,__data_size-1);
}
MyContainer::reverse_iterator MyContainer::rend(){
	return MyContainer::reverse_iterator(__data,-1);
}
//Managers
MyContainer& MyContainer::operator=(const MyContainer& original){
	if(this == &original) return *this;
	__data_size = original.__data_size;
	__capacity = original.__capacity;
	delete[] __data;
	DeepCopy(original);
	return *this;
}
void MyContainer::push_back(const T& newdata){
	if(__data_size == __capacity)
		resize(__capacity*(1+__resize_factor)+1);
	__data[__data_size] = newdata;
	__data_size++;
}
void MyContainer::push_back_steal(T& newdata){
	if(__data_size == __capacity)
		resize(__capacity*(1+__resize_factor)+1);
	__data[__data_size] = std::move(newdata);
	__data_size++;
}
void MyContainer::push_back_steal(MyContainer& s){
	for(auto iter(s.begin()); iter != s.end(); ++iter)
		push_back(*iter);
	s.clear();
}
void MyContainer::insert(size_t index, const T& newdata){
	if( //If index is out-of-bounds and container is full
		index>=__data_size
		&& __data_size == __capacity
	){
		resize(__capacity*(1+__resize_factor)+1);
		__data[__data_size] = newdata;
		__data_size++;
		return;
	//If index is out-of-bounds but container is not full
	}else if(index>=__data_size){
		__data[__data_size] = newdata;
		__data_size++;
		return;
	//If index is within bounds but container is full
	}else if(__data_size == __capacity)
		resize(__capacity*(1+__resize_factor));
	//Shift all elements one spot to the right
	for(size_t iter(__data_size); iter > index; --iter)
		__data[iter] = __data[iter-1];
	__data[index] = newdata;
	__data_size++;
}
void MyContainer::insert(
	MyContainer::iterator& pos,
	const T& newdata
){
	size_t hold = pos.Position();
	if(pos == nullptr) return;
	else if(__data_size == __capacity){
		resize(__capacity*(1+__resize_factor)+1);
		pos.Invalidate();
	}
	__data[hold] = newdata;
	__data_size++;
}
void MyContainer::insert(
	MyContainer::iterator& pos,
	const MyContainer::iterator& first,
	const MyContainer::iterator& second
){
	size_t hold = pos.Position();
	long long _max(second.Position()-first.Position());
	//Make sure _max is positive
	if(_max < 0) _max *= -1;
	//resize container to accomodate new items
	if(pos == nullptr) return;
	resize(__capacity*(1+__resize_factor)+1+_max);
	pos.Invalidate();
	//Shift everything _max spots to the right
	for(
		size_t iter(__data_size+_max-1); 
		iter >= hold+_max; 
		--iter
	) __data[iter] = __data[iter-_max];
	//Now copy the data
	for(
		size_t
			iter(hold),
			iter2(
				(first.Position()<second.Position()) ?
				first.Position() :
				second.Position()
			);
		iter2<(
				(first.Position()<second.Position()) ?
				second.Position() :
				first.Position()
			);
		++iter, ++iter2
	)	__data[iter] = first[iter2];
}
void MyContainer::pop_back(){
	if((__data+__capacity-1) != nullptr) --__data_size;
	delete (__data+(--__capacity));
}
void MyContainer::erase(size_t index){
	if(index >= __data_size)	return;
	for(size_t i(index); i<__data_size-1; ++i)
		__data[index] = __data[index+1];
	this->pop_back();
}
void MyContainer::erase(iterator& pos){
	for(
		size_t i(pos.Position());
		i < __data_size-1;
		++i
	) __data[i] = __data[i+1];
	this->pop_back();
	pos.Invalidate();
}
void MyContainer::clear(){
	delete[] __data;
		__data = new T[__default_size];
	if(__junk != nullptr)
		delete __junk;
	__junk = nullptr;
	__data_size = 0;
	__capacity = __default_size;
}
void MyContainer::resize(size_t newsize){
	T *__image = new T[__data_size];
	for(size_t i(0); i<__data_size; ++i)
		__image[i] = __data[i];
	delete[] __data;
	__data = new T[newsize];
	__capacity = newsize;
	for(size_t i(0); i<__data_size || i<newsize; ++i)
		__data[i] = __image[i];
	delete[] __image;
}
void MyContainer::resize(size_t newsize, const T& filler){
	MyContainer::resize(newsize);
	if(__data_size >= newsize) return;
	for(size_t i(__data_size); i < newsize; ++i)
		__data[i] = filler;
}
void MyContainer::reallocate(size_t newsize, const T& filler){
	delete[] __data;
		__data = new T[newsize];
	if(__junk != nullptr)
		delete __junk;
	__junk = nullptr;
	__data_size = __capacity = newsize;
	for(size_t i(0); i < newsize; ++i)
		__data[i] = filler;
}
T* MyContainer::garbage(){
	if(__junk != nullptr) return __junk;
	return nullptr;
}
T& MyContainer::operator[](size_t index){
	if(index >= __capacity && __junk != nullptr) return *__junk;
	else if(index >= __capacity && __junk == nullptr) return *(__junk = new T);
	return __data[index];
}
//Read-Only
	//Unable to account for __junk being a null pointer
const T& MyContainer::operator[](size_t index)const{
	if(index >= __capacity && __junk != nullptr) return *__junk;
	return __data[index];
}
size_t MyContainer::size()const{return __data_size;}
size_t MyContainer::capacity()const{return __capacity;}
//Constructors and destructor
MyContainer::MyContainer():
	__data_size(0),
	__capacity(0),
	__data(new T[__default_size]),
	__junk(nullptr)
{}
MyContainer::MyContainer(const MyContainer& original):
	__data_size(original.__data_size),
	__capacity(original.__capacity),
	__data(nullptr),
	__junk(nullptr)
{DeepCopy(original);}
MyContainer::MyContainer(size_t newsize, const T& newfill):
	__data_size(newsize),
	__capacity(newsize),
	__data(new T[newsize]),
	__junk(nullptr)
{
	for(size_t iter(0); iter < newsize; ++iter)
		__data[iter] = newfill;
}
MyContainer::MyContainer(MyContainer&& original):
	__data_size(original.__data_size),
	__capacity(original.__capacity),
	__data(nullptr),
	__junk(nullptr)
{
	DeepCopy(original);
	original.clear();
}
MyContainer::MyContainer(std::initializer_list<T> il):
	__data_size(il.size()),
	__capacity(il.size()),
	__data(new T[il.size()]),
	__junk(nullptr)
{
	std::initializer_list<T>::iterator iter = il.begin();
	size_t index(0);
	for(; index < __data_size; ++iter, ++index)
		__data[index] = *iter;
}
MyContainer::~MyContainer(){
	if(__data != nullptr) delete[] __data;
	if(__junk != nullptr) delete __junk;
}
void MyContainer::DeepCopy(const MyContainer& original){
	__data = new T[original.__capacity];
	for(size_t iter(0); iter < original.__data_size; ++iter)
		__data[iter] = (original.__data)[iter];
}
/*************************************************************
                      Iterator
**************************************************************/
//Member Access
T& MyContainer::iterator::operator*(){return *__raw;}
T* MyContainer::iterator::operator->(){return __raw;}
//Subscript
T& MyContainer::iterator::operator[](size_t index){return __raw[index];}
const T&
	MyContainer::iterator::operator[](size_t index)const{return __raw[index];}
//Arithmetic
MyContainer::iterator&
	MyContainer::iterator::operator=(const iterator& s){
		if(this == &s) return *this;
		__raw = s.__raw;
		__index = s.__index;
		return *this;
}
MyContainer::iterator&
	MyContainer::iterator::operator++(){
		++__raw;
		++__index;
		return *this;
}
MyContainer::iterator&
	MyContainer::iterator::operator++(int dummy){
		++__raw;
		++__index;
		return *this;
}
MyContainer::iterator&
	MyContainer::iterator::operator--(){
		--__raw;
		--__index;
		return *this;
}
MyContainer::iterator&
	MyContainer::iterator::operator--(int dummy){
		--__raw;
		--__index;
		return *this;
}
MyContainer::iterator&
	MyContainer::iterator::operator+=(size_t delta){
		__raw += delta;
		__index += delta;
		return *this;
}
MyContainer::iterator&
	MyContainer::iterator::operator-=(size_t delta){
		__raw -= delta;
		__index -= delta;
		return *this;
}
MyContainer::iterator
	MyContainer::iterator::operator+(size_t delta)
{return MyContainer::iterator(__raw+delta,__index+delta);}
MyContainer::iterator
	MyContainer::iterator::operator-(size_t delta)
{return MyContainer::iterator(__raw-delta,__index-delta);}
//Comparison
bool MyContainer::iterator::operator==(const iterator& s)
{return (__raw == s.__raw && __index == s.__index);}
bool MyContainer::iterator::operator==(std::nullptr_t n)
{return __raw == n;}
bool MyContainer::iterator::operator!=(const iterator& s)
{return !(*this == s);}
bool MyContainer::iterator::operator!=(std::nullptr_t n)
{return !(*this == n);}
//Read-only
bool MyContainer::iterator::Invalid()const
{return (__raw == nullptr);}
size_t MyContainer::iterator::Position()const
{return __index;}
//Constructors and destructor
MyContainer::iterator::iterator():
	__raw(nullptr),
	__index(0)
{}
MyContainer::iterator::iterator(T* data,size_t newindex):
	__raw(data+newindex),
	__index(newindex)
{}
MyContainer::iterator::iterator(const iterator& s):
	__raw(s.__raw),
	__index(s.__index)
{}
MyContainer::iterator::iterator(iterator&& s):
	__raw(s.__raw),
	__index(s.__index)
{
	s.__raw = nullptr;
	s.__index = 0;
}
MyContainer::iterator::~iterator(){}
void MyContainer::iterator::Invalidate(){
	__raw = nullptr;
	__index = 0;
}
/*************************************************************
                      Reverse Iterator
**************************************************************/
//Arithmetic
MyContainer::reverse_iterator& 
	MyContainer::reverse_iterator::operator=
	(const reverse_iterator& s){
		if(this == &s) return *this;
		__raw = s.__raw;
		__index = s.__index;
		return *this;
}
MyContainer::reverse_iterator& 
	MyContainer::reverse_iterator::operator++(){
		--__raw;
		--__index;
		return *this;
}
MyContainer::reverse_iterator& 
	MyContainer::reverse_iterator::operator++(int){
		--__raw;
		--__index;
		return *this;
}
MyContainer::reverse_iterator& 
	MyContainer::reverse_iterator::operator--(){
		++__raw;
		++__index;
		return *this;
}
MyContainer::reverse_iterator& 
	MyContainer::reverse_iterator::operator--(int){
		++__raw;
		++__index;
		return *this;
}
MyContainer::reverse_iterator& 
	MyContainer::reverse_iterator::operator+=(size_t delta){
		__raw += delta;
		__index += delta;
		return *this;
}
MyContainer::reverse_iterator& 
	MyContainer::reverse_iterator::operator-=(size_t delta){
		__raw -= delta;
		__index -= delta;
		return *this;
}
MyContainer::reverse_iterator 
	MyContainer::reverse_iterator::operator+(size_t delta)
{return MyContainer::reverse_iterator(__raw-delta,__index-delta);}
MyContainer::reverse_iterator 
	MyContainer::reverse_iterator::operator-(size_t delta)
{return MyContainer::reverse_iterator(__raw+delta,__index+delta);}
//Comparison
bool 
	MyContainer::reverse_iterator::operator==
	(const reverse_iterator& s)
{return (__raw == s.__raw && __index == s.__index);}
bool 
	MyContainer::reverse_iterator::operator!=
	(const reverse_iterator& s)
{return !(*this == s);}
//Constructors and destructor
MyContainer::reverse_iterator::reverse_iterator():
	MyContainer::iterator::iterator()
{}
MyContainer::reverse_iterator::reverse_iterator
	(T* newdata,size_t newindex):
		MyContainer::iterator::iterator(newdata,newindex)
{}
MyContainer::reverse_iterator::reverse_iterator
	(const reverse_iterator& s):
		MyContainer::iterator::iterator(s.__raw,s.__index)
{}
MyContainer::reverse_iterator::reverse_iterator
	(reverse_iterator&& s):
		MyContainer::iterator::iterator(s.__raw,s.__index)
{
	s.__raw = nullptr;
	s.__index = 0;
}
MyContainer::reverse_iterator::~reverse_iterator(){}
