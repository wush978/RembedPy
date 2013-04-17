library(RembedPy)

pyscript("a = 1")
pyscript("
def test_print(src):
    print src
")
py.a <- new("py-ptr", "a", is_pyobj=TRUE)
py.print <- new("py-ptr", "test_print", is_pyobj=TRUE)
pycall(py.print, py.a)
pycall("test_print", py.a)

test_fun <- function(src) {
	py_obj <- new("py-ptr", src)
	pycall("test_print", py_obj)
}

test_fun("hello");gc()
test_fun(letters);gc()

test_fun(1L);gc()
test_fun(1L:10L);gc()

test_fun(1.0);gc()
test_fun(1.5:10.5);gc()

test_fun(TRUE);gc()
test_fun(c(TRUE,FALSE,TRUE));gc()