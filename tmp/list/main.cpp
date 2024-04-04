
#include <iostream>
#include <string>

using std::cout;
using std::endl;

template<typename T> class List {
public:
	List(size_t size) : s{size}, ptr{new T[size]} {}

	~List() {
		delete[] ptr;
		ptr = nullptr;
	}

	List(const List& list) : s{list.s}, ptr{new T[list.s]} {
		for (size_t i{0}; i<s; i++)
			ptr[i] = list.ptr[i];
	}


	List& operator=(const List& list) {
		if (&list == this)
			return *this;

		delete[] ptr;
		ptr = nullptr;

		s = list.s;
		ptr = new T[s];

		for (size_t i{0}; i<s; i++)
			ptr[i] = list.ptr[i];

		return *this;
	}

	size_t size() const { return s; }
	T& operator[](size_t i) { return ptr[i]; }
	const T& operator[](size_t i) const { return ptr[i]; }

private:
	T* ptr;
	size_t s;

};


int main() {

	List<string> strlist;

	

}

