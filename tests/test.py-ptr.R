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

pyscript("a = {'a':1,'b':'str','c':2.0}")
a <- pyobj("a")
a[]

pyscript("a = {'a':1,'b':'str','c':[1,2,3]}")
a <- pyobj("a")
a[]
