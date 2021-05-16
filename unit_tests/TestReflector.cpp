#include "TestReflector.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestReflector);

// "abcdefghijklmnopqrstuvwxyz"
// "yruhqsldpxngokmiebfzcwvjat"
//  01234567890123456789012345

void TestReflector::setUp()
{
    // The _invalidRefector is invalid because the alphabet size need to be even
    _invalidRefector.setAlphabet("abc");

    _r.setAlphabet("yruhqsldpxngokmiebfzcwvjat");
}

void TestReflector::testIsValid()
{
    CPPUNIT_ASSERT(!_defaultRefector.isValid());
    CPPUNIT_ASSERT(!_invalidRefector.isValid());
    CPPUNIT_ASSERT(_r.isValid());

    _defaultRefector.setAlphabet("bdac");
    CPPUNIT_ASSERT(_defaultRefector.isValid());
    _defaultRefector.clear();
    CPPUNIT_ASSERT(!_defaultRefector.isValid());

    // The following rotor must not be considered valid because
    // it can return a value equal to its input which is not
    // permitted for a reflector
    _defaultRefector.setAlphabet("abcd");
    CPPUNIT_ASSERT(!_defaultRefector.isValid());
}

void TestReflector::testConvert()
{
    CPPUNIT_ASSERT_EQUAL(24ul, _r.convert(0));
    CPPUNIT_ASSERT_EQUAL(23ul, _r.convert(9));
    CPPUNIT_ASSERT_EQUAL(16ul, _r.convert(4));
    CPPUNIT_ASSERT_EQUAL(6ul,  _r.convert(11));
    CPPUNIT_ASSERT_EQUAL(22ul, _r.convert(21));
}

void TestReflector::testConvertInvalid()
{
    CPPUNIT_ASSERT_EQUAL(Enigma::string::npos, _invalidRefector.convert(0));
    CPPUNIT_ASSERT_EQUAL(Enigma::string::npos, _invalidRefector.convert(1));
    CPPUNIT_ASSERT_EQUAL(Enigma::string::npos, _invalidRefector.convert(12));
    CPPUNIT_ASSERT_EQUAL(Enigma::string::npos, _invalidRefector.convert(25));
    CPPUNIT_ASSERT_EQUAL(Enigma::string::npos, _invalidRefector.convert(28));
}

void TestReflector::testNoOpRotation()
{
    CPPUNIT_ASSERT_EQUAL(0ul, _r.rotation());
    _r.rotate();
    CPPUNIT_ASSERT_EQUAL(0ul, _r.rotation());

    const auto enc = _r.convert(0);
    CPPUNIT_ASSERT_EQUAL(0ul, _r.rotation());
    CPPUNIT_ASSERT_EQUAL(enc, _r.convert(0));
}
