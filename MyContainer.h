#ifndef MYCONTAINER_H
#define MYCONTAINER_H

#include <initalizer_list>

class MyContainer{
	using T=int;
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
		void insert(const iterator&,const T&);
		void insert(
			const iterator&,
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
		static const double __resize_factor(0.25);
		static const int __default_size(7);
};

class iterator{
	public:
	//Member Access
		MyContainer& operator*();
		MyContainer* operator->();
	//Arithmetic
		iterator& operator=(const iterator&);
		iterator& operator++();
		iterator& operator++(int);
		iterator& operator--();
		iterator& operator--(int);
		iterator& operator+(size_t);
		iterator& operator-(size_t);
	//Comparison
		bool operator==(const iterator&);
		bool operator==(const nullptr_t&=nullptr);
	//Constructors and destructor
		iterator();
		iterator(T*,size_t);
		iterator(const iterator&);
		iterator(iterator&&);
		~iterator();
	private:
		T *__raw;
};

#endif //MYCONTAINER_H