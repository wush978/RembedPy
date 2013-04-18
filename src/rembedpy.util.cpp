#include "rembedpy.util.h"

boost::python::list extract_argv_list(SEXP Rargv) {
#ifdef REMBEDPY_DEBUG
  Rprintf("extract_argv_list: ");
#endif
	Rcpp::List argv(Rargv);
#ifdef REMBEDPY_DEBUG
  Rprintf("length(Rargv)=%d \n", argv.size());
#endif
	boost::python::list retval;
	for(int i = 0;i < argv.size();i++) {
		PyObjPtr glue(Rcpp::wrap(Rcpp::S4(Rcpp::wrap(argv[i])).slot("ptr")));
		retval.append(*glue);
	}
	return retval;
}

boost::python::dict extract_argv_dict(SEXP Rargv) {
#ifdef REMBEDPY_DEBUG
  Rprintf("extract_argv_dict: ");
#endif
  Rcpp::List argv(Rargv);
#ifdef REMBEDPY_DEBUG
  Rprintf("length(Rargv)=%d \n", argv.size());
#endif
	boost::python::dict retval;
  if (argv.size() == 0) return retval;
  std::vector<std::string> argv_name(Rcpp::as< std::vector<std::string> >(Rcpp::wrap(argv.attr("names"))));
  for(int i = 0;i < argv.size();i++) {
    PyObjPtr glue(Rcpp::wrap(Rcpp::S4(Rcpp::wrap(argv[i])).slot("ptr")));
    retval[argv_name[i].c_str()] = *glue;
  }
  return retval;
}

SEXP pycall(boost::python::object& callable, boost::python::list& argv_list, boost::python::dict& argv_dict) {
#ifdef REMBEDPY_DEBUG
  Rprintf("pycall\n");
#endif
	PyObjPtr retval(new boost::python::object(callable(*boost::python::tuple(argv_list), **argv_dict)));
	return Rcpp::wrap(retval);
}

