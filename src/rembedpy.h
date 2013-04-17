#ifndef __REMBEDPY_H__
#define __REMBEDPY_H__

#include <boost/python.hpp>
#include <Rcpp.h>

#define BEGIN_REMBEDPY try {
#define END_REMBEDPY } catch(boost::python::error_already_set) { ::PyErr_Print(); VOID_END_RCPP return R_NilValue;

#endif //__REMBEDPY_H__