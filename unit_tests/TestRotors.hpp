#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Rotors.hpp"

class TestRotors : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestRotors);
    CPPUNIT_TEST(testIsValid);
    CPPUNIT_TEST(testReset);
    CPPUNIT_TEST(testConvert);
    CPPUNIT_TEST(testConvertInvalid);
    CPPUNIT_TEST(testNormalSequence);
    CPPUNIT_TEST(testDoubleStepSequence);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() override;

public:
    void testIsValid();
    void testReset();
    void testConvert();
    void testConvertInvalid();
    void testNormalSequence();
    void testDoubleStepSequence();

private:
    Enigma::Rotors _defaultRotors;
    Enigma::Rotors _invalidRotors;
    Enigma::Rotors _r123;
    Enigma::Rotors _r654;
};

