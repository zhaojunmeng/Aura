/*
 * MLB.cpp
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#include <MLB/MLB.h>

MLB::MLB(const std::string& name, MAO& parent) {
	_name = name;
	_parent = &parent;

}

std::string MLB::getName() {
	return _name;
}

MAO& MLB::getParent() {
	return *_parent;
}

int MLB::getMLBType(){
	return _mlbType;
}

MLB::~MLB() {
}
