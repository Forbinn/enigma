#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Rotor.hpp"

class TestRotor : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestRotor);
    CPPUNIT_TEST(testIsValid);
    CPPUNIT_TEST(testConvertFrom);
    CPPUNIT_TEST(testConvertTo);
    CPPUNIT_TEST(testConvertInvalid);
    CPPUNIT_TEST(testReset);
    CPPUNIT_TEST(testRotate);
    CPPUNIT_TEST(testRotateInvalid);
    CPPUNIT_TEST(testRotateAndConvertFrom);
    CPPUNIT_TEST(testRotateAndConvertTo);
    CPPUNIT_TEST(testStandardRotor);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() override;

public:
    void testIsValid();
    void testConvertFrom();
    void testConvertTo();
    void testConvertInvalid();
    void testReset();
    void testRotate();
    void testRotateInvalid();
    void testRotateAndConvertFrom();
    void testRotateAndConvertTo();
    void testStandardRotor();

private:
    Enigma::Rotor _defaultRotor;
    Enigma::Rotor _invalidRotor;
    Enigma::Rotor _r;
};
