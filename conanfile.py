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
        "fPIC": [True, False]
    }
    default_options = {
        "shared": False,
        "fPIC": True
    }

    generators      = "cmake_find_package"
    exports_sources = "src/*", "CMakeLists.txt"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.hpp",    dst=f"include/{self.name}", src="src")
        self.copy("*.lib",    dst="lib", keep_path=False)
        self.copy("*.dll",    dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so*",    dst="lib", keep_path=False, symlinks=True)
        self.copy("*.a",      dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["enigma"]
