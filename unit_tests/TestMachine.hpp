#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Machine.hpp"

class TestMachine : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestMachine);
    CPPUNIT_TEST(testIsValid);
    CPPUNIT_TEST(testClear);
    CPPUNIT_TEST(testReset);
    CPPUNIT_TEST(testConvertSingleValue);
    CPPUNIT_TEST(testConvertString);
    CPPUNIT_TEST(testDefaultMachine);
    CPPUNIT_TEST(testInvalidDefaultMachine);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() override;

    void testIsValid();
    void testClear();
    void testReset();
    void testConvertSingleValue();
    void testConvertString();
    void testDefaultMachine();
    void testInvalidDefaultMachine();

private:
    Enigma::Machine _m321;
    Enigma::Machine _m456;
};

