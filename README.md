# RembedPy

Embed python into R

## Install

For Ubuntu:

- libboost-python
- python-dev
- pkg-config
- r-base
- Rcpp

## Getting Start

Takes cassandra client as example:

```r
library(RembedPy)

pyscript("import cql")
cql <- pyobj("cql")
con <- cql$connect("localhost", cql_version="3.0.0") # cql_version 3.0.0 is unavailable in R
cursor <- con$cursor()
cursor$execute("use keyspace_name")
cursor$execute("SELECT * FROM column_family_name LIMIT 2")
cursor["description"]
pyscript("
def test_print(src):
    print src
")
pycall("test_print", cursor["description"])
result <- cursor$fetchone()
as.list(result)
```