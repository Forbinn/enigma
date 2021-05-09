#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "PlugBoard.hpp"

class TestPlugBoard : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestPlugBoard);
    CPPUNIT_TEST(testIsValidFor);
    CPPUNIT_TEST(testConvert);
    CPPUNIT_TEST(testMappingMutation);
    CPPUNIT_TEST(testMappingOverride);
    CPPUNIT_TEST_SUITE_END();

public:
    void testIsValidFor();
    void testConvert();
    void testMappingMutation();
    void testMappingOverride();

private:
    Enigma::PlugBoard _defaultPlugboard;
    Enigma::PlugBoard _p;
};

