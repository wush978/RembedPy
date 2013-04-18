#include "rembedpy.h"


RcppExport SEXP RembedPy__extract(SEXP Rmodule_name, SEXP Robj_name) {
  BEGIN_REMBEDPY
  std::string 
  module_name(Rcpp::as<std::string>(Rmodule_name)),
  obj_name(Rcpp::as<std::string>(Robj_name));
  boost::python::object module((boost::python::handle<>(boost::python::borrowed(PyImport_AddModule(module_name.c_str())))));
  PyObjPtr retval(new boost::python::object(module.attr("__dict__")[obj_name.c_str()]));
  return retval;
  END_REMBEDPY
}

RcppExport SEXP RembedPy__method(SEXP Rptr, SEXP Rname, SEXP Rargv) {
  
}