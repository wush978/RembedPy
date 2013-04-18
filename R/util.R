check_argv <- function(argv) {
  argv <- sapply(argv, function(a) {
    if (class(a)[1] == "py-ptr")
      return (a)
    else
      return (new("py-ptr", a))
  }, simplify=FALSE)
  argv.name <- names(argv)
  if (is.null(argv.name)) {
    return(list(list=argv, dict=list()))
  }
  index.list <- which(argv.name == "")
  if (length(index.list) > 0) {
    return(list(list=argv[index.list], dict=argv[-index.list]))
  } else {
    return(list(list=list(), dict=argv))    
  }
}