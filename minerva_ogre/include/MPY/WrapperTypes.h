/*
 * WrapperTypes.h
 *
 *  Created on: 06/04/2011
 *      Author: cesar
 */

#ifndef WRAPPERTYPES_H_
#define WRAPPERTYPES_H_

#include <python.hpp>
#include <vector>

void IndexError();

/* Wrapper for std::vector */
/* Thanks to ARCO & CrySoL */
template<class T>
struct vector_item {

	typedef std::vector<T> Vector;

	static T& get(Vector& self, int j) {

		if (j < 0)
			j += self.size();
		unsigned int i = (unsigned) j;
		if (i >= 0 && i < self.size())
			return self[i];
		IndexError();
		throw "Unexpected exception";
	}
	static void set(Vector& self, int j, T const& v) {

		if (j < 0)
			j += self.size();
		unsigned int i = (unsigned) j;
		if (i >= 0 && i < self.size()) {
			//x[i]=v;
			typename Vector::iterator it = self.begin() + i;
			self.erase(it);
			self.insert(it, v);
		} else
			IndexError();
	}
	static void del(Vector& self, int j) {

		if (j < 0)
			j += self.size();
		unsigned int i = (unsigned) j;
		if (i >= 0 && i < self.size()) {
			typename Vector::iterator it = self.begin() + i;
			self.erase(it);
		} else {
			IndexError();
		}
	}
	static void add(Vector& self, T const& v) {
		self.push_back(v);
	}
};

typedef std::vector<std::string> VectorStr;
typedef std::vector<int> VectorInt;
typedef std::vector<float> VectorFloat;

#endif /* WRAPPERTYPES_H_ */
