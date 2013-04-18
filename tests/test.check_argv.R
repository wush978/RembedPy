library(RembedPy)

f <- function(...) {
  RembedPy:::check_argv(list(...))
}

f(1,2,3)

f(a=1,b=2,3,4)

f(2,a=1,b=2,4)

f(a=1,b=2,c=3)
gc()