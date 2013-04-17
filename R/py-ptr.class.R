#'@exportClass py-ptr
setClass(
  "py-ptr",
  representation(ptr="externalptr")
  )

setMethod(
  "initialize",
  "py-ptr",
  def = function(.Object, src) {
    .Object@ptr = switch(
      class(src),
      "character" = .pystr(src),
      "integer" = .pylong(src),
      "logical" = .pybool(src),
      "numeric" = .pydouble(src),
      "list" = .pylist(src),
      stop("Invalid type")
      )
    .Object
  }
  )