/**
 * Author: Wush Wu
 * Copyright (c) Bridgewell Inc.
 */

#include "rembedpy.h"
#include "rembedpy.util.h"


namespace RembedPy {

  SEXP pycall__funname(SEXP Rmodule_name, SEXP Rfun_name, SEXP Rargv_list, SEXP Rargv_dict) {
#ifdef REMBEDPY_DEBUG
    Rprintf("funname\n");
#endif
    std::string 
  		fun_name(Rcpp::as<std::string>(Rfun_name)),
  		module_name(Rcpp::as<std::string>(Rmodule_name));
    boost::python::object callable(RembedPy::extract_pyobj(fun_name, module_name));
    boost::python::list argv_list(RembedPy::extract_argv_list(Rargv_list));
    boost::python::dict argv_dict(RembedPy::extract_argv_dict(Rargv_dict));
    return RembedPy::pycall(callable, argv_list, argv_dict);
  }
  
  SEXP pycall__callable(SEXP Rfun, SEXP Rargv_list, SEXP Rargv_dict) {
#ifdef REMBEDPY_DEBUG
  	Rprintf("callable\n");
#endif
  	Rcpp::S4 fun(Rfun);
  	PyObjPtr pcallable(Rcpp::wrap(fun.slot("ptr")));
  	boost::python::object& callable(*pcallable);
  	boost::python::list argv_list(RembedPy::extract_argv_list(Rargv_list));
    boost::python::dict argv_dict(RembedPy::extract_argv_dict(Rargv_dict));
  	return RembedPy::pycall(callable, argv_list, argv_dict);
  }
  
}

RcppExport SEXP RembedPy__pyscript(SEXP Rscript) {
  BEGIN_REMBEDPY
  std::string script(Rcpp::as<std::string>(Rscript));
  ::PyRun_SimpleString(script.c_str());
  return R_NilValue;
  END_REMBEDPY
}


RcppExport SEXP RembedPy__pycall(SEXP Rmodule_name, SEXP Rfun_name, SEXP Rargv_list, SEXP Rargv_dict) {
	BEGIN_REMBEDPY
	switch(TYPEOF(Rfun_name)) {
	case STRSXP:
		return RembedPy::pycall__funname(Rmodule_name, Rfun_name, Rargv_list, Rargv_dict);
	case S4SXP:
		return RembedPy::pycall__callable(Rfun_name, Rargv_list, Rargv_dict);
	default:
		throw std::invalid_argument("fun_name must be obj py-ptr or string");
	}
	END_REMBEDPY
}