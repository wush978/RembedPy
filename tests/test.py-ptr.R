library(RembedPy)

pyscript("a = 1")
a <- pyobj("a")
a[]

pyscript("a = 'str'")
a <- pyobj("a")
a[]

pyscript("a = u'str'")
a <- pyobj("a")
a[]

pyscript("a = True")
a <- pyobj("a")
a[]

pyscript("a = [1,2,3]")
a <- pyobj("a")
a[]