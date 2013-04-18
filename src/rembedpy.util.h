
#ifndef __REMBEDPY_UTIL_H__
#define __REMBEDPY_UTIL_H__

#include "rembedpy.h"

namespace RembedPy {
  boost::python::object extract_pyobj(std::string& name, std::string& module);
  boost::python::list extract_argv_list(SEXP Rargv);
  boost::python::dict extract_argv_dict(SEXP Rargv);
  SEXP pycall(boost::python::object& callable, boost::python::list& argv_list, boost::python::dict& argv_dict);
  
  template<class T>
  SEXP extract_to_R_single(boost::python::object& src) {
    return Rcpp::wrap<T>(boost::python::extract<T>(src));
  }
  
  inline const char* get_type(boost::python::object& src) {
    return boost::python::extract<char*>(src.attr("__class__").attr("__name__"));
  }
}

#endif //__REMBEDPY_UTIL_H__