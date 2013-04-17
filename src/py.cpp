#include "rembedpy.h"

RcppExport SEXP RembedPy__pyscript(SEXP Rscript) {
  BEGIN_REMBEDPY
  std::string script(Rcpp::as<std::string>(Rscript));
  ::PyRun_SimpleString(script.c_str());
  return R_NilValue;
  END_REMBEDPY
}

std::vector< PyObjPtr > extract_argv(SEXP Rargv) {
	Rcpp::List argv(Rargv);
	std::vector< PyObjPtr > retval;
	for(int i = 0;i < argv.size();i++) {
		retval.push_back( PyObjPtr(Rcpp::wrap(argv[i])) );
	}
	return retval;
}

SEXP pycall(boost::python::object& callable, std::vector< PyObjPtr >& argv) {
	return R_NilValue;
}

SEXP pycall__funname(SEXP Rmodule_name, SEXP Rfun_name, SEXP Rargv) {
	std::string 
		fun_name(Rcpp::as<std::string>(Rfun_name)),
		module_name(Rcpp::as<std::string>(Rmodule_name));
  boost::python::object module((boost::python::handle<>(boost::python::borrowed(PyImport_AddModule(module_name.c_str())))));
	boost::python::object callable(module.attr("__dict__")[fun_name.c_str()]);
	std::vector< PyObjPtr > argv(extract_argv(Rargv));
	return pycall(callable, argv);
}

SEXP pycall__callable(SEXP Rfun, SEXP Rargv) {
	Rcpp::S4 fun(Rfun);
	PyObjPtr pcallable(Rcpp::wrap(fun.slot("ptr")));
	boost::python::object& callable(*pcallable);
	std::vector< PyObjPtr > argv(extract_argv(Rargv));
	return pycall(callable, argv);
}

RcppExport SEXP RembedPy__pycall(SEXP Rmodule_name, SEXP Rfun_name, SEXP Rargv) {
	BEGIN_REMBEDPY
	switch(TYPEOF(Rfun_name)) {
	case STRSXP:
		return pycall__funname(Rmodule_name, Rfun_name, Rargv);
	case S4SXP:
		return pycall__callable(Rfun_name, Rargv);
	default:
		throw std::invalid_argument("fun_name must be obj py-ptr or string");
	}
	END_REMBEDPY
}