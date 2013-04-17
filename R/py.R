#'@export
py <- function(script) {
  stopifnot(class(script) == "character")
  .Call("RembedPy__py", script[1])
}