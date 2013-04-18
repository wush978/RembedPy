#include "rembedpy.util.h"

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
