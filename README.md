# contra

> A minimal standard library for C

## introduction

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
# Create build directory.
mkdir build && cd build

# Create cmake environment.
cmake ..

# Build library.
make

# Run tests.
make run-tests
```


<a name="license"></a>
## license

***The MIT License (MIT)***

*Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>*
