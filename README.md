# enigma
A C++20 library of the Enigma machine

## Build

### Using conan
In order to build this library, the simplest way it to use [conan](https://conan.io/).

`conan create .`

This will build the library with default options and place it in your local cache.

If you want, you can build it in a specific folder:

`conan install -if build .`

`conan build -bf build .`

### Using cmake

You can also use cmake natively to build this library.

`cmake -B build .`

`cmake --build build`

## Using the library

If you use conan for your project, you just have to add `enigma/<version>` in your requirements, and you are good to go.

## Running tests and benchmark

### Unit-tests
Unit-tests are **enabled** by default and will run every time you compile the library using conan.
If you can to disable them, you can use the `with_test` option of conan or `ENIGMA_TESTS` option of cmake.

The unit-tests are realized with [cppunit](http://cppunit.sourceforge.net/doc/1.8.0/index.html) and this dependency is automatically handled by conan.

### Benchmark
The benchmark is **disabled** by default by you can enable it by using the `with_benchmark` option of conan or `ENIGMA_BENCHMARK` option of cmake.

The benchmark is realized with [google-benchmark](https://github.com/google/benchmark) and this dependency is automatically handled by conan.

## Note about conan options
The `with_test` and `with_benchmark` will not change the package ID regardless of their value.
