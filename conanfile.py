from conans import ConanFile, CMake

class EnigmaConan(ConanFile):
    name        = "enigma"
    version     = "0.2.0"

    license     = "MIT"
    author      = "Forbinn <vincent.54.leroy@gmail.com>"
    url         = "https://github.com/Forbinn/enigma"
    description = "A C++20 library of the Enigma machine"
    topics      = ("conan", "enigma")

    settings    = "os", "compiler", "build_type", "arch"

    options     = {
        "shared": [True, False],

        "with_tests": [True, False],
        "with_benchmark": [True, False]
    }
    default_options = {
        "shared": False,

        "with_tests": True,
        "with_benchmark": False
    }

    generators      = "cmake_find_package"
    exports_sources = "src/*", "unit_tests/*", "benchmark/*", "CMakeLists.txt"

    def build_requirements(self):
        if self.options.with_tests:
            self.build_requires("cppunit/1.15.1")
        if self.options.with_benchmark:
            self.build_requires("benchmark/1.5.2")

    def build(self):
        cmake = CMake(self)
        cmake.definitions["ENIGMA_TESTS"] = "ON" if self.options.with_tests else "OFF"
        cmake.definitions["ENIGMA_BENCHMARK"] = "ON" if self.options.with_benchmark else "OFF"

        cmake.configure()
        cmake.build()
        if self.options.with_tests:
            cmake.test(args=["--", "ARGS=--progress"], output_on_failure=True)
        if self.options.with_benchmark:
            self.run("./benchmark/enigma_benchmark", run_environment=True)

    def package(self):
        self.copy("*.hpp",    dst=f"include/{self.name}", src="src")
        self.copy("*.lib",    dst="lib", keep_path=False)
        self.copy("*.dll",    dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so*",    dst="lib", keep_path=False, symlinks=True)
        self.copy("*.a",      dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["enigma"]

    def package_id(self):
        del self.info.options.with_tests
        del self.info.options.with_benchmark
