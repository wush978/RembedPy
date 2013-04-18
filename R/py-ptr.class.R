#'@exportClass py-ptr
setClass(
  "py-ptr",
  representation(ptr="externalptr")
  )

setMethod(
  "initialize",
  "py-ptr",
  def = function(.Object, src, is_pyobj = FALSE, module_name = "__main__") {
		stopifnot(class(is_pyobj) == "logical")
  	if (is_pyobj) {
  		stopifnot(class(src) == "character")
  		stopifnot(class(module_name) == "character")
  		.Object@ptr <- .Call("RembedPy__extract", module_name[1], src[1])
  	} else {
  		if (class(src) == "externalptr") {
  			.Object@ptr <- src
  		} else {
    		.Object@ptr <- .RtoPy(src)
  		}
  	}
    .Object
  }
  )

setMethod(
  "$",
  "py-ptr",
  def = function(x, name) {
    function(...) {
      argv <- check_argv(list(...))
      new("py-ptr", .Call("RembedPy__method", x@ptr, name, argv$list, argv$dict))
    }
  }
  )