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

setMethod("[",
  signature(x = "py-ptr"),
  function (x, i, j, ..., drop = TRUE) {
    if (missing(i)) {
      stop("TODO: extract R object")
    }
    if (class(i) == "character") {
      ptr <- .Call("RembedPy__getattr", x@ptr, i[1])
      if (is.null(ptr)) return(NULL)
      return(new("py-ptr", ptr))
    }
  }
)

setMethod("show",
  signature(object = "py-ptr"),
  function (object) 
  {
    cat(sprintf("A python object of python type: \"%s\"\n", .Call("RembedPy__gettype", object@ptr)))
  }
)
