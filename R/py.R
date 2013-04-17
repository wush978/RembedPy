#'@export
pyscript <- function(script) {
  stopifnot(class(script) == "character")
  .Call("RembedPy__pyscript", script[1])
}

#'Call a python function with parameters
#'
#'Only passed without name
#'
#'@export
pycall <- function(fun_name, ..., module_name = "__main__") {
	argv <- list(...)
	stopifnot(is.null(names(argv)))
	sapply(argv, function(a) stopifnot(class(a)[1] == "py-ptr"))
	.Call("RembedPy__pycall", module_name, fun_name, argv)
}