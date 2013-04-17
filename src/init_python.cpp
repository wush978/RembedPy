#ifndef WIN32
#include <dlfcn.h>
#endif
#include <boost/python.hpp>
#include <Rcpp.h>

struct PyoutCatcher {
  PyObject* write(std::string str) {
    Rcpp::Rcout << str;
    Py_INCREF(Py_None);
    return Py_None;
  }
};

BOOST_PYTHON_MODULE(redirectR) {
  boost::python::class_<PyoutCatcher>("PyoutCatcher")
      .def("write", &PyoutCatcher::write)
  ;
}

RcppExport SEXP RembedPy__initialize() {
  BEGIN_RCPP
  ::Py_SetProgramName("Rython");
#ifndef WIN32
  ::dlopen("libpython2.7.so", RTLD_LAZY | RTLD_GLOBAL);
#endif
  ::Py_Initialize();
	Rcpp::Rcout << "Initializing Python Interpreter..." << std::endl;
  ::PyRun_SimpleString("import sys");
  ::initredirectR();
  ::PyRun_SimpleString("import redirectR");
  ::PyRun_SimpleString("sys.stdout = redirectR.PyoutCatcher()");
	return R_NilValue;
	END_RCPP
}

RcppExport SEXP RembedPy__finalize() {
	BEGIN_RCPP
	Rcpp::Rcout << "Finalizing Python Interpreter..." << std::endl;
  ::Py_Finalize();
	return R_NilValue;
	END_RCPP
}


