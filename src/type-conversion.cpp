#include "rembedpy.h"


template <int RTYPE, class T>
SEXP RtoPy(SEXP Rsrc) {
	Rcpp::Vector<RTYPE> src(Rsrc);
	if (src.size() > 1) {
		PyListPtr retval(new boost::python::list);
		for(int i = 0;i < src.size();i++) {
			retval->append<T>(src[i]);
		}
		return Rcpp::wrap(retval);
	}
	PyObjPtr retval(new boost::python::object(src[0]));
	return Rcpp::wrap(retval);
}

template <>
SEXP RtoPy<STRSXP, std::string>(SEXP Rsrc) {
	if (::Rf_length(Rsrc) > 1) {
		PyListPtr retval(new boost::python::list);
		for(int i = 0;i < ::Rf_length(Rsrc);i++) {
			retval->append<std::string>(CHAR(STRING_ELT(Rsrc, i)));
		}
		return Rcpp::wrap(retval);
	}
	PyObjPtr retval(new boost::python::object(CHAR(STRING_ELT(Rsrc, 0))));
	return Rcpp::wrap(retval);
	return R_NilValue;
}

RcppExport SEXP RembedPy__RtoPy(SEXP Rsrc) {
	BEGIN_REMBEDPY
	switch (TYPEOF(Rsrc)) {
	case REALSXP:
	  return RtoPy<REALSXP, double>(Rsrc);
	case INTSXP:
		return RtoPy<INTSXP, int>(Rsrc);
	case LGLSXP:
		return RtoPy<LGLSXP, bool>(Rsrc);
	case STRSXP:
		return RtoPy<STRSXP, std::string>(Rsrc);
	case VECSXP:
		throw std::logic_error("TODO");
	}
	return R_NilValue;
	END_REMBEDPY
}

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