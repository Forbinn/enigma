#pragma once

#include <string>

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define Q_DECL_EXPORT __declspec(dllexport)
#  define Q_DECL_IMPORT __declspec(dllimport)
#else
#  define Q_DECL_EXPORT __attribute__((visibility("default")))
#  define Q_DECL_IMPORT __attribute__((visibility("default")))
#endif

#if defined(ENIGMA_LIBRARY)
#  define ENIGMA_EXPORT Q_DECL_EXPORT
#else
#  define ENIGMA_EXPORT Q_DECL_IMPORT
#endif

namespace Enigma
{
    using string     = std::string;
    using value_type = typename string::value_type;
} // !namespace Enigma
