#include "TestRotor.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestRotor);

void TestRotor::setUp()
{
    // The _invalidRotor is invalid because its input and output does not have the same length
    _invalidRotor.setInputAlphabet("abc");
    _invalidRotor.setOutputAlphabet("de");

    _r1.setInputAlphabet ("abcdefghijklmnopqrstuvwxyz");
    _r1.setOutputAlphabet("xwgolqytzderjpumbcsvkianfh");
    _r2.setInputAlphabet (_r1.outputAlphabet());
    _r2.setOutputAlphabet("njzeihmbyfwxovprdsqtuackgl");
}

void TestRotor::testIsValid()
{
    CPPUNIT_ASSERT(!_defaultRotor.isValid());
    CPPUNIT_ASSERT(!_invalidRotor.isValid());
    CPPUNIT_ASSERT(_r1.isValid());
    CPPUNIT_ASSERT(_r2.isValid());

    _defaultRotor.setInputAlphabet("abc");
    _defaultRotor.setOutputAlphabet("def");
    CPPUNIT_ASSERT(_defaultRotor.isValid());
    _defaultRotor.clear();
    CPPUNIT_ASSERT(!_defaultRotor.isValid());
    CPPUNIT_ASSERT(_defaultRotor.inputAlphabet().empty());
    CPPUNIT_ASSERT(_defaultRotor.outputAlphabet().empty());
}

void TestRotor::testConvertFrom()
{
    _r1.reset();
    _r2.reset();

    CPPUNIT_ASSERT_EQUAL('x', _r1.convertFromInput('a'));
    CPPUNIT_ASSERT_EQUAL('w', _r1.convertFromInput('b'));
    CPPUNIT_ASSERT_EQUAL('y', _r1.convertFromInput('g'));
    CPPUNIT_ASSERT_EQUAL('k', _r1.convertFromInput('u'));
    CPPUNIT_ASSERT_EQUAL('m', _r1.convertFromInput('p'));

    CPPUNIT_ASSERT_EQUAL('c', _r2.convertFromInput('a'));
    CPPUNIT_ASSERT_EQUAL('z', _r2.convertFromInput('g'));
    CPPUNIT_ASSERT_EQUAL('b', _r2.convertFromInput('t'));
    CPPUNIT_ASSERT_EQUAL('k', _r2.convertFromInput('n'));
    CPPUNIT_ASSERT_EQUAL('p', _r2.convertFromInput('u'));
}

void TestRotor::testConvertTo()
{
    _r1.reset();
    _r2.reset();

    CPPUNIT_ASSERT_EQUAL('a', _r1.convertToInput('x'));
    CPPUNIT_ASSERT_EQUAL('b', _r1.convertToInput('w'));
    CPPUNIT_ASSERT_EQUAL('g', _r1.convertToInput('y'));
    CPPUNIT_ASSERT_EQUAL('u', _r1.convertToInput('k'));
    CPPUNIT_ASSERT_EQUAL('p', _r1.convertToInput('m'));

    CPPUNIT_ASSERT_EQUAL('a', _r2.convertToInput('c'));
    CPPUNIT_ASSERT_EQUAL('g', _r2.convertToInput('z'));
    CPPUNIT_ASSERT_EQUAL('t', _r2.convertToInput('b'));
    CPPUNIT_ASSERT_EQUAL('n', _r2.convertToInput('k'));
    CPPUNIT_ASSERT_EQUAL('u', _r2.convertToInput('p'));
}

void TestRotor::testConvertInvalid()
{
    CPPUNIT_ASSERT_EQUAL('\0', _invalidRotor.convertToInput('a'));
    CPPUNIT_ASSERT_EQUAL('\0', _invalidRotor.convertToInput('z'));
    CPPUNIT_ASSERT_EQUAL('\0', _invalidRotor.convertFromInput('a'));
    CPPUNIT_ASSERT_EQUAL('\0', _invalidRotor.convertFromInput('z'));
}

void TestRotor::testReset()
{
    _r1.setOffset(0);
    CPPUNIT_ASSERT_EQUAL(0ul, _r1.offset());
    _r1.setOffset(15);
    CPPUNIT_ASSERT_EQUAL(15ul, _r1.offset());
    _r1.reset();
    CPPUNIT_ASSERT_EQUAL(0ul, _r1.offset());
    _r1.setOffset(27);
    CPPUNIT_ASSERT_EQUAL(1ul, _r1.offset());
}

void TestRotor::testRotate()
{
    _r1.reset();
    _r2.reset();

    CPPUNIT_ASSERT_EQUAL(0, _r1.rotate());
    CPPUNIT_ASSERT_EQUAL(0, _r1.rotate(24));
    CPPUNIT_ASSERT_EQUAL(1, _r1.rotate());
    CPPUNIT_ASSERT_EQUAL(-1, _r1.rotate(-1));
    CPPUNIT_ASSERT_EQUAL(0, _r1.rotate(-1));

    _r1.reset();
    CPPUNIT_ASSERT_EQUAL(-2, _r1.rotate(-27));
    _r1.reset();
    CPPUNIT_ASSERT_EQUAL(1, _r1.rotate(51));
    _r1.reset();
    CPPUNIT_ASSERT_EQUAL(2, _r1.rotate(52));
}

void TestRotor::testRotateInvalid()
{
    CPPUNIT_ASSERT_EQUAL(0, _invalidRotor.rotate());
    CPPUNIT_ASSERT_EQUAL(0, _invalidRotor.rotate(25));
    CPPUNIT_ASSERT_EQUAL(0, _invalidRotor.rotate(60));
    CPPUNIT_ASSERT_EQUAL(0, _invalidRotor.rotate(-1));
    CPPUNIT_ASSERT_EQUAL(0, _invalidRotor.rotate(-27));
}

void TestRotor::testRotateAndConvertFrom()
{
    _r1.reset();
    _r2.reset();

    CPPUNIT_ASSERT_EQUAL('x', _r1.convertFromInput('a'));
    _r1.rotate();
    CPPUNIT_ASSERT_EQUAL('w', _r1.convertFromInput('a'));
    _r1.rotate();
    CPPUNIT_ASSERT_EQUAL('g', _r1.convertFromInput('a'));

    CPPUNIT_ASSERT_EQUAL('c', _r2.convertFromInput('a'));
    _r2.rotate(-1);
    CPPUNIT_ASSERT_EQUAL('a', _r2.convertFromInput('a'));
    _r2.rotate(-1);
    CPPUNIT_ASSERT_EQUAL('u', _r2.convertFromInput('a'));
}

void TestRotor::testRotateAndConvertTo()
{
    _r1.reset();
    _r2.reset();

    CPPUNIT_ASSERT_EQUAL('a', _r1.convertToInput('x'));
    _r1.rotate();
    CPPUNIT_ASSERT_EQUAL('a', _r1.convertToInput('w'));
    _r1.rotate();
    CPPUNIT_ASSERT_EQUAL('a', _r1.convertToInput('g'));

    CPPUNIT_ASSERT_EQUAL('a', _r2.convertToInput('c'));
    _r2.rotate(-1);
    CPPUNIT_ASSERT_EQUAL('a', _r2.convertToInput('a'));
    _r2.rotate(-1);
    CPPUNIT_ASSERT_EQUAL('a', _r2.convertToInput('u'));
}
