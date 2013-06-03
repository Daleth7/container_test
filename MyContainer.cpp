#include "MyContainer.h"

#include <utility>

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
//Iterators
iterator MyContainer::begin();
iterator MyContainer::end();
iterator MyContainer::rbegin();
iterator MyContainer::rend();
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
		resize(__capacity(1+__resize_factor));
	__data[__data_size] = newdata;
	__data_size++;
}
void MyContainer::push_back_steal(T& newdata){
	if(__data_size == __capacity)
		resize(__capacity(1+__resize_factor));
	__data[__data_size] = std::move(newdata);
	__data_size++;
}
void MyContainer::insert(size_t index, const T& newdata){
	if( //If index is out-of-bounds and container is full
		index>=__data_size 
		&& __data_size == __capacity
	){
		resize(__capacity(1+__resize_factor));
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
void MyContainer::insert(const MyContainer::iterator&);
void MyContainer::pop_back(){
	if(__data[__capacity-1] != nullptr) --__data_size;
	delete __data[--__capacity];
}
void MyContainer::erase(size_t){
}
void MyContainer::erase(iterator&);
void MyContainer::clear();
void MyContainer::resize(size_t);
void MyContainer::resize(size_t, const T&);
	//Calls both clear() and resize()
void MyContainer::reallocate(size_t);
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
size_t MyContainer::size()const;
//Constructors and destructor
MyContainer::MyContainer():
	__data_size(0),
	__capacity(0),
	__data(nullptr),
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
MyContainer& iterator::operator*();
MyContainer* iterator::operator->()const;
//Arithmetic
iterator& iterator::operator=(const iterator&);
iterator& iterator::operator++();
iterator& iterator::operator++int);
iterator& iterator::operator--();
iterator& iterator::operator--(int);
iterator& iterator::operator+(size_t);
iterator& iterator::operator-(size_t);
//Constructors and destructor
iterator::iterator();
iterator::iterator(T&);
iterator::iterator(const iterator&);
iterator::iterator(iterator&&);
iterator::iterator(size_t);
iterator::~iterator();
T *__raw;