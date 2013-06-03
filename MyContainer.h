#ifndef MYCONTAINER_H
#define MYCONTAINER_H

#include <initalizer_list>

class MyContainer{
	using T=int;
	public:
	//Tests
		bool empty();
		bool garbage_exists();
	//Iterators
		class iterator;
		iterator begin();
		iterator end();
		iterator rbegin();
		iterator rend();
	//Managers
		MyContainer& operator=(const MyContainer&);
		void push_back(const T&);
		void push_back_steal(T&);
		void insert(size_t, const T&);
		void insert(const iterator&);
		void pop_back();
		void erase(size_t);
		void erase(iterator&);
		void clear();
		void resize(size_t);
		void resize(size_t, const T&);
			//Calls both clear() and resize()
		void reallocate(size_t);
		T* garbage();
		T& operator[](size_t);
	//Read-Only
		const T& operator[](size_t)const;
		size_t size()const;
	//Constructors and destructor
		explicit MyContainer();
		MyContainer(const MyContainer&);
		MyContainer(size_t, const T&);
		MyContainer(MyContainer&&);
		MyContainer(std::initializer_list<T>);
		~MyContainer();
	private:
		void DeepCopy(const MyContainer&);
		size_t
			__data_size,
			__capacity
		;
		T
			*__data,
			*__junk
		;
		static const double __resize_factor(0.25);
};

class iterator{
	public:
	//Member Access
		MyContainer& operator*();
		MyContainer* operator->()const;
	//Arithmetic
		iterator& operator=(const iterator&);
		iterator& operator++();
		iterator& operator++int);
		iterator& operator--();
		iterator& operator--(int);
		iterator& operator+(size_t);
		iterator& operator-(size_t);
	//Constructors and destructor
		iterator();
		iterator(T&);
		iterator(const iterator&);
		iterator(iterator&&);
		iterator(size_t);
		~iterator();
	private:
		T *__raw;
};

#endif //MYCONTAINER_H