#include "rembedpy.h"
#include "rembedpy.util.h"


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

RcppExport SEXP RembedPy__method(SEXP Rppy_obj, SEXP Rmethod_name, SEXP Rargv_list, SEXP Rargv_dict) {
  BEGIN_REMBEDPY
  PyObjPtr ppy_obj(Rppy_obj);
  std::string method_name(Rcpp::as<std::string>(Rmethod_name));
  boost::python::list argv_list(extract_argv_list(Rargv_list));
  boost::python::dict argv_dict(extract_argv_dict(Rargv_dict));
  boost::python::object callable(ppy_obj->attr(method_name.c_str()));
  return pycall(callable, argv_list, argv_dict);
  END_REMBEDPY
}