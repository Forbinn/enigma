from conans import ConanFile, CMake

class EnigmaConan(ConanFile):
    name        = "enigma"
    version     = "0.1.0"

    license     = "MIT"
    author      = "Forbinn <vincent.54.leroy@gmail.com>"
    url         = "https://github.com/Forbinn/enigma"
    description = "A C++20 library of the Enigma machine"
    topics      = ("conan", "enigma")

    settings    = "os", "compiler", "build_type", "arch"

    options     = {
        "shared": [True, False],
        "fPIC": [True, False],

        "with_test": [True, False],
        "with_benchmark": [True, False]
    }
    default_options = {
        "shared": False,
        "fPIC": True,

        "with_test": True,
        "with_benchmark": True
    }

    generators      = "cmake_find_package"
    exports_sources = "src/*", "unit_tests/*", "benchmark/*", "CMakeLists.txt"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def build_requirements(self):
        if self.options.with_test:
            self.build_requires("cppunit/1.15.1")
        if self.options.with_benchmark:
            self.build_requires("benchmark/1.5.2")

    def build(self):
        cmake = CMake(self)
        if self.options.with_test:
            cmake.definitions["ENIGMA_TESTS"] = "ON"
        if self.options.with_benchmark:
            cmake.definitions["ENIGMA_BENCHMARK"] = "ON"

        cmake.configure()
        cmake.build()
        if self.options.with_test:
            cmake.test(args=["--", "ARGS=--progress"], output_on_failure=True)

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
        del self.info.options.with_test
        del self.info.options.with_benchmark
