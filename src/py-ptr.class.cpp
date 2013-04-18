#include "rembedpy.h"
#include "rembedpy.util.h"

using RembedPy::PyObjPtr;
using RembedPy::PyListPtr;


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
  boost::python::list argv_list(RembedPy::extract_argv_list(Rargv_list));
  boost::python::dict argv_dict(RembedPy::extract_argv_dict(Rargv_dict));
  boost::python::object callable(ppy_obj->attr(method_name.c_str()));
  return RembedPy::pycall(callable, argv_list, argv_dict);
  END_REMBEDPY
}

RcppExport SEXP RembedPy__gettype(SEXP Rppy_obj) {
  BEGIN_REMBEDPY
  boost::python::object& py_obj(*PyObjPtr(Rppy_obj));
  Rcpp::CharacterVector retval(RembedPy::get_type(py_obj));
  return retval;
  END_REMBEDPY
}

RcppExport SEXP RembedPy__getattr(SEXP Rppy_obj, SEXP Rattr_name) {
  BEGIN_REMBEDPY
  std::string attr_name(Rcpp::as<std::string>(Rattr_name));
  boost::python::object& py_obj(*PyObjPtr(Rppy_obj));
  return PyObjPtr(new boost::python::object(py_obj.attr(attr_name.c_str())));
  END_REMBEDPY
}

std::map< std::string , RembedPy::PyToRConverter > RembedPy::PyTypeMapper;
std::map< std::string , RembedPy::PyToRListConverter > RembedPy::ListConverterMapper;

template<>
SEXP RembedPy::wrap_list_converter<wchar_t*, STRSXP>(boost::python::list& src) {
  	int n = boost::python::len(src);
  	std::vector< std::wstring > glue;
  	for(int i = 0;i < n;i++) {
  		glue.push_back(std::wstring(boost::python::extract<wchar_t*>(src[i])));
  	}
  	return Rcpp::wrap(glue);
  }
  

SEXP RembedPy::wrap_list(boost::python::object& src) {
	boost::python::list& src_list(*reinterpret_cast<boost::python::list*>(&src));
	int n = boost::python::len(src_list);
	if (n == 0) {
		return R_NilValue;
	}
	
	boost::python::object src_first(src_list[0]);
	std::string src_list_type(RembedPy::get_type(src_first));
	return RembedPy::PyTypeMapper.at(src_list_type)(src_list);
}

SEXP RembedPy::wrap_dict(boost::python::object& src) {
	boost::python::dict& src_dict(*reinterpret_cast<boost::python::dict*>(&src));
	int n = boost::python::len(src_dict);
	if (n == 0) {
		return R_NilValue;
	}
	
	boost::python::object src_first(src_list[0]);
	std::string src_list_type(RembedPy::get_type(src_first));
	return RembedPy::PyTypeMapper.at(src_list_type)(src_list);
}


void init_PyTypeMapper() {
	if (RembedPy::PyTypeMapper.size()) {
		return;
	}
	RembedPy::PyTypeMapper["int"] = RembedPy::wrap<int>;
	RembedPy::PyTypeMapper["long"] = RembedPy::wrap<long>;
	RembedPy::PyTypeMapper["str"] = RembedPy::wrap<std::string>;
	RembedPy::PyTypeMapper["unicode"] = RembedPy::wrap<std::wstring>;
	RembedPy::PyTypeMapper["bool"] = RembedPy::wrap<bool>;
	RembedPy::PyTypeMapper["float"] = RembedPy::wrap<double>;
	RembedPy::PyTypeMapper["list"] = RembedPy::wrap_list;
	RembedPy::PyTypeMapper["dict"] = RembedPy::wrap_dict;
	
	RembedPy::ListConverterMapper["int"] = RembedPy::wrap_list_converter<int, INTSXP>;
	RembedPy::ListConverterMapper["long"] = RembedPy::wrap_list_converter<long, INTSXP>;
	RembedPy::ListConverterMapper["str"] = RembedPy::wrap_list_converter<char*, STRSXP>;
	RembedPy::ListConverterMapper["unicode"] = RembedPy::wrap_list_converter<wchar_t*, STRSXP>;
	RembedPy::ListConverterMapper["bool"] = RembedPy::wrap_list_converter<bool, LGLSXP>;
	RembedPy::ListConverterMapper["float"] = RembedPy::wrap_list_converter<double, REALSXP>;

}

RcppExport SEXP RembedPy__toR(SEXP Rppy_obj) {
  BEGIN_REMBEDPY
  init_PyTypeMapper();
  boost::python::object& py_obj(*PyObjPtr(Rppy_obj));
  std::string py_obj_type(RembedPy::get_type(py_obj));
  try {
  	return RembedPy::PyTypeMapper.at(py_obj_type)(py_obj);
  }
  catch (std::out_of_range& e) {
  	throw std::out_of_range("unsupported python type!");
  }
  END_REMBEDPY
}