#ifndef MYCONTAINER_H
#define MYCONTAINER_H

#include <initializer_list>
#include <cstddef> //size_t

	using T=int;
class MyContainer{
	public:
	//Tests
		bool empty();
		bool garbage_exists();
		bool operator==(const MyContainer&);
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
		void insert(iterator&,const T&);
		void insert(
			iterator&,
			const iterator&,
			const iterator&
		);
		void pop_back();
		void erase(size_t);
		void erase(iterator&);
		void clear();
		void resize(size_t);
		void resize(size_t, const T&);
			//Combination of clear() and resize()
		void reallocate(size_t,const T&);
		T* garbage();
		T& operator[](size_t);
	//Read-Only
		const T& operator[](size_t)const;
		size_t size()const;
		size_t capacity()const;
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
		static constexpr double __resize_factor=0.25;
		static constexpr int __default_size=7;
};

class MyContainer::iterator{
	public:
	//Member Access
		T& operator*();
		T* operator->();
	//Subscript
		T& operator[](size_t);
		const T& operator[](size_t)const;
	//Arithmetic
		iterator& operator=(const iterator&);
		iterator& operator++();
		iterator& operator++(int);
		iterator& operator--();
		iterator& operator--(int);
		iterator& operator+=(size_t);
		iterator& operator-=(size_t);
		iterator operator+(size_t);
		iterator operator-(size_t);
	//Comparison
		bool operator==(const iterator&);
		bool operator==(std::nullptr_t);
		bool operator!=(const iterator&);
		bool operator!=(std::nullptr_t);
	//Read-only
		bool Invalid()const;
		size_t Position()const;
	//Constructors and destructor
		iterator();
		iterator(T*,size_t);
		iterator(const iterator&);
		iterator(iterator&&);
		~iterator();
	//Managers
		void Invalidate();
	private:
		T *__raw;
		size_t __index;
};

#endif //MYCONTAINER_H
