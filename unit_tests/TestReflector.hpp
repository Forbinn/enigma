#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Reflector.hpp"

class TestReflector : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestReflector);
    CPPUNIT_TEST(testIsValid);
    CPPUNIT_TEST(testConvert);
    CPPUNIT_TEST(testConvertInvalid);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() override;

public:
    void testIsValid();
    void testConvert();
    void testConvertInvalid();
    void testNoOpRotation();

private:
    Enigma::Reflector _defaultRefector;
    Enigma::Reflector _invalidRefector;
    Enigma::Reflector _r;
};

