
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
  
	typedef SEXP (*PyToRConverter)(boost::python::object&);
	extern std::map< std::string , PyToRConverter > PyTypeMapper;
	
	typedef SEXP (*PyToRListConverter)(boost::python::list&);
	extern std::map< std::string , PyToRListConverter > ListConverterMapper;
  
  template<class T>
  SEXP wrap(boost::python::object& src) {
  	return Rcpp::wrap<T>(boost::python::extract<T>(src));
  }
  
  SEXP wrap_list(boost::python::object& src);
  SEXP wrap_dict(boost::python::object& src);
  
  template<class T, int RTYPE>
  SEXP wrap_list_converter(boost::python::list& src) {
  	int n = boost::python::len(src);
  	Rcpp::Vector<RTYPE> retval;
  	for(int i = 0;i < n;i++) {
  		T glue(boost::python::extract<T>(src[i]));
  		retval.push_back(glue);
  	}
  	return Rcpp::wrap(retval);
  }
  
  template<>
  SEXP wrap_list_converter<wchar_t*, STRSXP>(boost::python::list& src);
  
  /*
  template<>
  SEXP wrap_list_converter<std::wstring, STRSXP>(boost::python::list& src) {
  	int n = boost::python::len(src);
  	Rcpp::CharacterVector retval;
  	for(int i = 0;i < n;i++) {
  		std::string glue(boost::python::extract<std::string>(src[i]));
  		retval.push_back(glue.c_str());
  	}
  	return Rcpp::wrap(retval);
  } */
}

#endif //__REMBEDPY_UTIL_H__