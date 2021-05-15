#include "TestRotor.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestRotor);

// "abcdefghijklmnopqrstuvwxyz"
// "ekmflgdqvzntowyhxuspaibrcj"
//  01234567890123456789012345

// "bcdefghijklmnopqrstuvwxyza"
// "kmflgdqvzntowyhxuspaibrcje"
//  01234567890123456789012345

// "cdefghijklmnopqrstuvwxyzab"
// "mflgdqvzntowyhxuspaibrcjek"
//  01234567890123456789012345

// "defghijklmnopqrstuvwxyzabc"
// "flgdqvzntowyhxuspaibrcjekm"
//  01234567890123456789012345

/*
 * Convert To algorithm
 *  take char at index idx in unsorted alphabet
 *  return index of char in sorted alphabet
 *
 * Convert From algorithm
 *  take char at index in sorted alphabet
 *  return index of char in unsorted alphabet
 */

void TestRotor::setUp()
{
    _r.setAlphabet("ekmflgdqvzntowyhxuspaibrcj");
    _r.setNotches({16});
}

void TestRotor::testIsValid()
{
    CPPUNIT_ASSERT(!_defaultRotor.isValid());
    CPPUNIT_ASSERT(!_invalidRotor.isValid());
    CPPUNIT_ASSERT(_r.isValid());

    _defaultRotor.setAlphabet("ekmflgdqvzntowyhxuspaibrcj");
    CPPUNIT_ASSERT(_defaultRotor.isValid());
    _defaultRotor.clear();
    CPPUNIT_ASSERT(!_defaultRotor.isValid());
}

void TestRotor::testConvertFrom()
{
    _r.reset();

    CPPUNIT_ASSERT_EQUAL(20ul, _r.convertFrom(0));
    CPPUNIT_ASSERT_EQUAL(22ul, _r.convertFrom(1));
    CPPUNIT_ASSERT_EQUAL(24ul, _r.convertFrom(2));
    CPPUNIT_ASSERT_EQUAL(6ul,  _r.convertFrom(3));
    CPPUNIT_ASSERT_EQUAL(0ul,  _r.convertFrom(4));
    CPPUNIT_ASSERT_EQUAL(3ul,  _r.convertFrom(5));
    CPPUNIT_ASSERT_EQUAL(5ul,  _r.convertFrom(6));
    CPPUNIT_ASSERT_EQUAL(15ul, _r.convertFrom(7));
    CPPUNIT_ASSERT_EQUAL(21ul, _r.convertFrom(8));
    CPPUNIT_ASSERT_EQUAL(25ul, _r.convertFrom(9));
    CPPUNIT_ASSERT_EQUAL(1ul,  _r.convertFrom(10));
    CPPUNIT_ASSERT_EQUAL(4ul,  _r.convertFrom(11));
    CPPUNIT_ASSERT_EQUAL(2ul,  _r.convertFrom(12));
    CPPUNIT_ASSERT_EQUAL(10ul, _r.convertFrom(13));
    CPPUNIT_ASSERT_EQUAL(12ul, _r.convertFrom(14));
    CPPUNIT_ASSERT_EQUAL(19ul, _r.convertFrom(15));
    CPPUNIT_ASSERT_EQUAL(7ul,  _r.convertFrom(16));
    CPPUNIT_ASSERT_EQUAL(23ul, _r.convertFrom(17));
    CPPUNIT_ASSERT_EQUAL(18ul, _r.convertFrom(18));
    CPPUNIT_ASSERT_EQUAL(11ul, _r.convertFrom(19));
    CPPUNIT_ASSERT_EQUAL(17ul, _r.convertFrom(20));
    CPPUNIT_ASSERT_EQUAL(8ul,  _r.convertFrom(21));
    CPPUNIT_ASSERT_EQUAL(13ul, _r.convertFrom(22));
    CPPUNIT_ASSERT_EQUAL(16ul, _r.convertFrom(23));
    CPPUNIT_ASSERT_EQUAL(14ul, _r.convertFrom(24));
    CPPUNIT_ASSERT_EQUAL(9ul,  _r.convertFrom(25));
}

void TestRotor::testConvertTo()
{
    _r.reset();

    CPPUNIT_ASSERT_EQUAL(4ul,  _r.convertTo(0));
    CPPUNIT_ASSERT_EQUAL(10ul, _r.convertTo(1));
    CPPUNIT_ASSERT_EQUAL(12ul, _r.convertTo(2));
    CPPUNIT_ASSERT_EQUAL(5ul,  _r.convertTo(3));
    CPPUNIT_ASSERT_EQUAL(11ul, _r.convertTo(4));
    CPPUNIT_ASSERT_EQUAL(6ul,  _r.convertTo(5));
    CPPUNIT_ASSERT_EQUAL(3ul,  _r.convertTo(6));
    CPPUNIT_ASSERT_EQUAL(16ul, _r.convertTo(7));
    CPPUNIT_ASSERT_EQUAL(21ul, _r.convertTo(8));
    CPPUNIT_ASSERT_EQUAL(25ul, _r.convertTo(9));
    CPPUNIT_ASSERT_EQUAL(13ul, _r.convertTo(10));
    CPPUNIT_ASSERT_EQUAL(19ul, _r.convertTo(11));
    CPPUNIT_ASSERT_EQUAL(14ul, _r.convertTo(12));
    CPPUNIT_ASSERT_EQUAL(22ul, _r.convertTo(13));
    CPPUNIT_ASSERT_EQUAL(24ul, _r.convertTo(14));
    CPPUNIT_ASSERT_EQUAL(7ul,  _r.convertTo(15));
    CPPUNIT_ASSERT_EQUAL(23ul, _r.convertTo(16));
    CPPUNIT_ASSERT_EQUAL(20ul, _r.convertTo(17));
    CPPUNIT_ASSERT_EQUAL(18ul, _r.convertTo(18));
    CPPUNIT_ASSERT_EQUAL(15ul, _r.convertTo(19));
    CPPUNIT_ASSERT_EQUAL(0ul,  _r.convertTo(20));
    CPPUNIT_ASSERT_EQUAL(8ul,  _r.convertTo(21));
    CPPUNIT_ASSERT_EQUAL(1ul,  _r.convertTo(22));
    CPPUNIT_ASSERT_EQUAL(17ul, _r.convertTo(23));
    CPPUNIT_ASSERT_EQUAL(2ul,  _r.convertTo(24));
    CPPUNIT_ASSERT_EQUAL(9ul,  _r.convertTo(25));
}

void TestRotor::testConvertInvalid()
{
    CPPUNIT_ASSERT_EQUAL(Enigma::string::npos, _invalidRotor.convertTo(57));
    CPPUNIT_ASSERT_EQUAL(Enigma::string::npos, _invalidRotor.convertTo(0));
    CPPUNIT_ASSERT_EQUAL(Enigma::string::npos, _invalidRotor.convertFrom(1));
    CPPUNIT_ASSERT_EQUAL(Enigma::string::npos, _invalidRotor.convertFrom(5));
}

void TestRotor::testReset()
{
    _r.setRotation(0);
    CPPUNIT_ASSERT_EQUAL(0ul, _r.rotation());
    _r.setRotation(15);
    CPPUNIT_ASSERT_EQUAL(15ul, _r.rotation());
    _r.reset();
    CPPUNIT_ASSERT_EQUAL(0ul, _r.rotation());
    _r.setRotation(27);
    CPPUNIT_ASSERT_EQUAL(1ul, _r.rotation());

    _r.reset();
    const auto enc = _r.convertTo(0);
    _r.rotate();
    _r.reset();
    CPPUNIT_ASSERT_EQUAL(0ul, _r.convertFrom(enc));
}

void TestRotor::testRotate()
{
    _r.reset();

    CPPUNIT_ASSERT(!_r.rotate());
    CPPUNIT_ASSERT_EQUAL(1ul, _r.rotation());
    CPPUNIT_ASSERT(!_r.rotate());
    CPPUNIT_ASSERT_EQUAL(2ul, _r.rotation());
    CPPUNIT_ASSERT(!_r.rotate(false));
    CPPUNIT_ASSERT_EQUAL(1ul, _r.rotation());

    _r.reset();
    _r.setRotation(16);

    CPPUNIT_ASSERT(_r.rotate());
    CPPUNIT_ASSERT_EQUAL(17ul, _r.rotation());
    CPPUNIT_ASSERT(_r.rotate(false));
    CPPUNIT_ASSERT_EQUAL(16ul, _r.rotation());
}

void TestRotor::testRotateInvalid()
{
    _invalidRotor.reset();

    CPPUNIT_ASSERT_EQUAL(0ul, _invalidRotor.rotation());
    _invalidRotor.rotate();
    CPPUNIT_ASSERT_EQUAL(0ul, _invalidRotor.rotation());
    _invalidRotor.rotate(-1);
    CPPUNIT_ASSERT_EQUAL(0ul, _invalidRotor.rotation());
}

void TestRotor::testRotateAndConvertFrom()
{
    _r.reset();
    _r.rotate();

    CPPUNIT_ASSERT_EQUAL(21ul, _r.convertFrom(0));
    CPPUNIT_ASSERT_EQUAL(1ul,  _r.convertFrom(11));
    CPPUNIT_ASSERT_EQUAL(7ul,  _r.convertFrom(20));
    CPPUNIT_ASSERT_EQUAL(5ul,  _r.convertFrom(2));
    CPPUNIT_ASSERT_EQUAL(17ul, _r.convertFrom(17));

    _r.rotate();

    CPPUNIT_ASSERT_EQUAL(22ul, _r.convertFrom(0));
    CPPUNIT_ASSERT_EQUAL(8ul,  _r.convertFrom(11));
    CPPUNIT_ASSERT_EQUAL(11ul, _r.convertFrom(20));
    CPPUNIT_ASSERT_EQUAL(24ul, _r.convertFrom(2));
    CPPUNIT_ASSERT_EQUAL(9ul,  _r.convertFrom(17));

    _r.rotate();

    CPPUNIT_ASSERT_EQUAL(3ul,  _r.convertFrom(0));
    CPPUNIT_ASSERT_EQUAL(9ul,  _r.convertFrom(11));
    CPPUNIT_ASSERT_EQUAL(13ul, _r.convertFrom(20));
    CPPUNIT_ASSERT_EQUAL(0ul,  _r.convertFrom(2));
    CPPUNIT_ASSERT_EQUAL(14ul, _r.convertFrom(17));
}

void TestRotor::testRotateAndConvertTo()
{
    _r.reset();
    _r.rotate();

    CPPUNIT_ASSERT_EQUAL(9ul,  _r.convertTo(0));
    CPPUNIT_ASSERT_EQUAL(13ul, _r.convertTo(11));
    CPPUNIT_ASSERT_EQUAL(7ul,  _r.convertTo(20));
    CPPUNIT_ASSERT_EQUAL(4ul,  _r.convertTo(2));
    CPPUNIT_ASSERT_EQUAL(17ul, _r.convertTo(17));

    _r.rotate();

    CPPUNIT_ASSERT_EQUAL(10ul, _r.convertTo(0));
    CPPUNIT_ASSERT_EQUAL(20ul, _r.convertTo(11));
    CPPUNIT_ASSERT_EQUAL(25ul, _r.convertTo(20));
    CPPUNIT_ASSERT_EQUAL(9ul,  _r.convertTo(2));
    CPPUNIT_ASSERT_EQUAL(13ul, _r.convertTo(17));

    _r.rotate();

    CPPUNIT_ASSERT_EQUAL(2ul,  _r.convertTo(0));
    CPPUNIT_ASSERT_EQUAL(21ul, _r.convertTo(11));
    CPPUNIT_ASSERT_EQUAL(14ul, _r.convertTo(20));
    CPPUNIT_ASSERT_EQUAL(3ul,  _r.convertTo(2));
    CPPUNIT_ASSERT_EQUAL(23ul, _r.convertTo(17));
}
