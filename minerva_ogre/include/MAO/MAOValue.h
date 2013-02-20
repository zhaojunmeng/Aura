/*
 * MAOValue.h
 *
 *  Created on: 02/03/2011
 *      Author: cesar
 */

#ifndef MAOVALUE_H_
#define MAOVALUE_H_

#define MAOPROPERTY_INT 0
#define MAOPROPERTY_BOOLEAN 1
#define MAOPROPERTY_FLOAT 2
#define MAOPROPERTY_STRING 3
#define MAOPROPERTY_POSE 4
#define MAOPROPERTY_EMPTY 5

#include <cv.h>
#include <Kernel/Logger.h>

class MAOValue {
public:
	MAOValue();
	MAOValue(const MAOValue& o);
	~MAOValue();

	MAOValue& operator=(const MAOValue& o);

	template<class T>
	MAOValue(int type, T value) {
		_type = type;
		_value = (void*) new T(value);
	}

	template<class T>
	T& getValue() {
		return *(T*) _value;
	}

	template<class T>
	void setValue(T value) {
		*(T*) _value = value;
	}

	//Returns the String representations of the value
	std::string toString();

	int getType();

protected:
	void* _value;
	int _type;
};

#endif /* MAOVALUE_H_ */
