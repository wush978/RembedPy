# 
# Author: Wush Wu
# Copyright (c) Bridgewell Inc.
#  

#'@useDynLib RembedPy
.onAttach <- function(libname, pkgname) {
  .Call("RembedPy__initialize")
}

#'@export
.Last.lib <- function(libpath) {
  .Call("RembedPy__finalize")
}
