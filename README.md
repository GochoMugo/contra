# contra

> A minimal standard library for C

## Introduction

**contra** is a minimal standard library re-worked and re-designed
for simplicity and reusability. It is primarily developed to make it
easier writing C applications, using an API very similar to Node.js'.

**Table of Contents**

* [project principles](#principles)
* [installation](#installation)
* [license](#license)


<a name="principles"></a>
### project principles

* **minimal**: **contra** is minimal in what it implements.
* **simple**: using the library should be simple enough for developers.
* **opinionated**: we choose what to commit to long-term.


<a name="installation"></a>
### installation

```bash
# Install dependencies.
make deps

# Create build directory.
mkdir build && cd build

# Create cmake environment.
cmake ..

# Build library.
make

# Install library (usually under /usr/local).
make install

# Run all test.
make test

# Run subset of tests
make test.assert
make test.base
make test.fs
make test.http
make test.is
make test.math
make test.path
make test.proc
make test.string
```


<a name="license"></a>
## License

***The MIT License (MIT)***

*Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>*
