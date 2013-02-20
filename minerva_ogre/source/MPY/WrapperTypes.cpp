/*
 * WrapperTypes.cpp
 *
 *  Created on: 06/04/2011
 *      Author: cesar
 */

#include <MPY/WrapperTypes.h>


/* Error reporting! Good way!*/
void IndexError() {
  PyErr_SetString(PyExc_IndexError, "Index out of range");
  boost::python::throw_error_already_set();
}

