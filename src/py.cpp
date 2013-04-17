#include "rembedpy.h"

RcppExport SEXP RembedPy__py(SEXP Rscript) {
  BEGIN_REMBEDPY
  std::string script(Rcpp::as<std::string>(Rscript));
  ::PyRun_SimpleString(script.c_str());
  return R_NilValue;
  END_REMBEDPY
}