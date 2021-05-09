#include "TestReflector.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestReflector);

void TestReflector::setUp()
{
    // The _invalidRefector is invalid because the alphabet size need to be even
    _invalidRefector.setAlphabet("abc");

    _r.setAlphabet("abcdefghijklmnopqrstuvwxyz");
}

void TestReflector::testIsValid()
{
    CPPUNIT_ASSERT(!_defaultRefector.isValid());
    CPPUNIT_ASSERT(!_invalidRefector.isValid());
    CPPUNIT_ASSERT(_r.isValid());

    _defaultRefector.setAlphabet("abcd");
    CPPUNIT_ASSERT(_defaultRefector.isValid());
    _defaultRefector.clear();
    CPPUNIT_ASSERT(!_defaultRefector.isValid());
    CPPUNIT_ASSERT(_defaultRefector.alphabet().empty());
}

void TestReflector::testConvert()
{
    CPPUNIT_ASSERT_EQUAL('z', _r.convert('a'));
    CPPUNIT_ASSERT_EQUAL('y', _r.convert('b'));
    CPPUNIT_ASSERT_EQUAL('u', _r.convert('f'));
    CPPUNIT_ASSERT_EQUAL('p', _r.convert('k'));
    CPPUNIT_ASSERT_EQUAL('n', _r.convert('m'));

    CPPUNIT_ASSERT_EQUAL('a', _r.convert('z'));
    CPPUNIT_ASSERT_EQUAL('b', _r.convert('y'));
    CPPUNIT_ASSERT_EQUAL('f', _r.convert('u'));
    CPPUNIT_ASSERT_EQUAL('k', _r.convert('p'));
    CPPUNIT_ASSERT_EQUAL('m', _r.convert('n'));
}

void TestReflector::testConvertInvalid()
{
    CPPUNIT_ASSERT_EQUAL('\0', _invalidRefector.convert('a'));
    CPPUNIT_ASSERT_EQUAL('\0', _invalidRefector.convert('b'));
    CPPUNIT_ASSERT_EQUAL('\0', _invalidRefector.convert('f'));
    CPPUNIT_ASSERT_EQUAL('\0', _invalidRefector.convert('k'));
    CPPUNIT_ASSERT_EQUAL('\0', _invalidRefector.convert('m'));
}
