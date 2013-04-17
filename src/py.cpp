#include "rembedpy.h"

RcppExport SEXP RembedPy__pyscript(SEXP Rscript) {
  BEGIN_REMBEDPY
  std::string script(Rcpp::as<std::string>(Rscript));
  ::PyRun_SimpleString(script.c_str());
  return R_NilValue;
  END_REMBEDPY
}

boost::python::list extract_argv(SEXP Rargv) {
#ifdef REMBEDPY_DEBUG
	Rprintf("extract_argv\n");
#endif
	Rcpp::List argv(Rargv);
	boost::python::list retval;
	for(int i = 0;i < argv.size();i++) {
		PyObjPtr glue(Rcpp::wrap(Rcpp::S4(Rcpp::wrap(argv[i])).slot("ptr")));
		retval.append(*glue);
	}
	return retval;
}

SEXP pycall(boost::python::object& callable, boost::python::list& argv) {
#ifdef REMBEDPY_DEBUG
	Rprintf("pycall\n");
#endif
	PyObjPtr retval(new boost::python::object(callable(*boost::python::tuple(argv))));
	return Rcpp::wrap(retval);
}

SEXP pycall__funname(SEXP Rmodule_name, SEXP Rfun_name, SEXP Rargv) {
#ifdef REMBEDPY_DEBUG
	Rprintf("funname\n");
#endif
	std::string 
		fun_name(Rcpp::as<std::string>(Rfun_name)),
		module_name(Rcpp::as<std::string>(Rmodule_name));
  boost::python::object module((boost::python::handle<>(boost::python::borrowed(PyImport_AddModule(module_name.c_str())))));
	boost::python::object callable(module.attr("__dict__")[fun_name.c_str()]);
	boost::python::list argv(extract_argv(Rargv));
	return pycall(callable, argv);
}

SEXP pycall__callable(SEXP Rfun, SEXP Rargv) {
#ifdef REMBEDPY_DEBUG
	Rprintf("callable\n");
#endif
	Rcpp::S4 fun(Rfun);
	PyObjPtr pcallable(Rcpp::wrap(fun.slot("ptr")));
	boost::python::object& callable(*pcallable);
	boost::python::list argv(extract_argv(Rargv));
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