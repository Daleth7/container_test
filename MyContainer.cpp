#include "MyContainer.h"

using T=int;
//Tests
bool MyContainer::empty(){
	if(__data_size) return true;
	return false;
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
MyContainer::iterator MyContainer::rbegin(){
	return MyContainer::iterator(__data,__data_size-1);
}
MyContainer::iterator MyContainer::rend(){
	return MyContainer::iterator(__data,-1);
}
//Managers
MyContainer& MyContainer::operator=(const MyContainer& original){
	if(this == &original) return *this;
	__data_size = original.__data_size;
	__capacity = original.__capacity;
	delete[] __data;
	Deepcopy(original);
}
void MyContainer::push_back(const T& newdata){
	if(__data_size == __capacity)
		resize(__capacity(1+__resize_factor)+1);
	__data[__data_size] = newdata;
	__data_size++;
}
void MyContainer::push_back_steal(T& newdata){
	if(__data_size == __capacity)
		resize(__capacity(1+__resize_factor)+1);
	__data[__data_size] = std::move(newdata);
	__data_size++;
}
void MyContainer::insert(size_t index, const T& newdata){
	if( //If index is out-of-bounds and container is full
		index>=__data_size 
		&& __data_size == __capacity
	){
		resize(__capacity(1+__resize_factor)+1);
		__data[__data_size] = newdata;
		__data_size++;
		return;
	//If index is out-of-bounds but container is not full
	}else if(index>=__data_size){
		__data[__data_size] = newdata;
		__data_size++;
		return;
	//If index is within bounds but container is full
	}else if(__data_size == capacity)
		resize(__capacity(1+__resize_factor));
	//Shift all elements one spot to the right
	for(size_t iter(__data_size); iter > index; --iter)
		__data[iter] = __data[iter-1];
	__data[index] = newdata;
	__data_size++;
}
void MyContainer::insert(
	const MyContainer::iterator& pos,
	const T& newdata
);
	if(pos == nullptr) return;
	if(__data_size == __capacity)
		resize(__capacity(1+__resize_factor)+1);
}
void MyContainer::insert(
	const MyContainer::iterator&,
	const MyContainer::iterator&,
	const MyContainer::iterator&
);
void MyContainer::pop_back(){
	if((__data+__capacity-1) != nullptr) --__data_size;
	delete __data[--__capacity];
}
void MyContainer::erase(size_t index){
	if(index >= __data_size)	return;
	for(size_t i(index); i<__data_size-1; ++i)
		__data[index] = __data[index+1];
	this->pop_back();
}
void MyContainer::erase(iterator&);
void MyContainer::clear(){
	delete[] __data;
		__data = new T[__default_size];
	delete __junk;
		__junk = nullptr;
	__data_size = 0;
	__capacity = __default_size;
}
void MyContainer::resize(size_t newsize){
	T *__image = new T[__data_size];
	for(int i(0); i<__data_size; ++i)
		__image[i] = __data[i];
	delete[] __data;
	__data = new T[newsize];
	__capacity = newsize;
	for(int i(0); (i<__data_size || i<newsize; ++i)
		__data[i] = __image[i];
	delete[] __image;
}
void MyContainer::resize(size_t newsize, const T& filler){
	MyContainer::resize(newsize);
	if(__data_size >= newsize) return;
	for(size_t i(__data_size); i < newsize; ++i)
		__data[i] = filler;
}
	//Calls both clear() and resize()
void MyContainer::reallocate(size_t newsize, const T& filler){
	delete[] __data;
		__data = new T[newsize];
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
	if(index >= __capacity) return *__junk;
	return __data[index];
}
//Read-Only
const T& MyContainer::operator[](size_t index)const{
	if(index >= __capacity) return *__junk;
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
void DeepCopy(const MyContainer& original){
	__data = new T[original.__capacity];
	for(size_t iter(0); iter < original.__data_size; ++iter)
		__data[iter] = (original.__data_size)[iter];
}

//Member Access
MyContainer& 
	MyContainer::iterator::operator*()
{return *__raw;}
MyContainer* 
	MyContainer::iterator::operator->()
{return *__raw;}
//Arithmetic
MyContainer::iterator& 
	MyContainer::iterator::operator=(const iterator& s){
		if(this == &s) return *this;
		__raw = s.__raw;
		return *this;
}
MyContainer::iterator& 
	MyContainer::iterator::operator++(){
		__raw++;
		return *this;
}
MyContainer::iterator& 
	MyContainer::iterator::operator++(int dummy){
		__raw++;
		return *this;
}
MyContainer::iterator& 
	MyContainer::iterator::operator--(){
		__raw--;
		return *this;
}
MyContainer::iterator& 
	MyContainer::iterator::operator--(int dummy){
		__raw--;
		return *this;
}
MyContainer::iterator& 
	MyContainer::iterator::operator+(size_t delta)
{__raw += delta;}
MyContainer::iterator& 
	MyContainer::iterator::operator-(size_t delta)
{__raw -= delta;}
//Comparison
bool MyContainer::iterator::operator==(const iterator& s)
{return __raw == s.__raw;}
bool MyContainer::iterator::operator==(const nullptr_t& n)
{return __raw == n;}
//Constructors and destructor
MyContainer::iterator::iterator():
	__raw(nullptr)
{}
MyContainer::iterator::iterator(T* data,size_t index):
	__raw(data[index])
{}
MyContainer::iterator::iterator(const iterator& s):
	__raw(s.__raw)
{}
MyContainer::iterator::iterator(iterator&& s):
	__raw(s.__raw)
{s.__raw = nullptr;}
MyContainer::iterator::~iterator(){}