#include "TestRotors.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestRotors);

void TestRotors::setUp()
{
    // This rotor is considered to be invalid because its output alphabet
    // does not contains unique character (the 'n' is repeated twice)
    _invalidRotors.setInputAlphabet("abcdefghijklmnopqrstuvwxyz");
    _invalidRotors.setOutputAlphabet("xwgolqytzderjpunbcsvkianfh");

    _r.setInputAlphabet("abcdefghijklmnopqrstuvwxyz");
    _r.setOutputAlphabet("xwgolqytzderjpumbcsvkianfh");
    _r.appendIntermediateAlphabet("rfgxcdbvsntaejlqowmpyukzhi");
    _r.appendIntermediateAlphabet("dnegoxhqzfaitjrskvbulpwycm");
}

void TestRotors::testIsValid()
{
    CPPUNIT_ASSERT(!_defaultRotors.isValid());
    CPPUNIT_ASSERT(!_invalidRotors.isValid());
    CPPUNIT_ASSERT(_r.isValid());

    _defaultRotors.setInputAlphabet("abcdefghijklmnopqrstuvwxyz");
    _defaultRotors.setOutputAlphabet("xwgolqytzderjpumbcsvkianfh");
    CPPUNIT_ASSERT(_defaultRotors.isValid());
    _defaultRotors.clear();
    CPPUNIT_ASSERT(!_defaultRotors.isValid());
    CPPUNIT_ASSERT(_defaultRotors.inputAlphabet().empty());
    CPPUNIT_ASSERT(_defaultRotors.outputAlphabet().empty());

    _defaultRotors.setInputAlphabet("abcdefghijklmnopqrstuvwxyz");
    _defaultRotors.setOutputAlphabet("xwgolqytzderjpumbcsvkianfh");
    _defaultRotors.appendIntermediateAlphabet("rfgxcdbvsntaejlqowmpyukzhi");
    CPPUNIT_ASSERT(_defaultRotors.isValid());
    _defaultRotors.setInputAlphabet({});
    CPPUNIT_ASSERT(!_defaultRotors.isValid());
}

void TestRotors::testRotorCount()
{
    Enigma::Rotors r;
    CPPUNIT_ASSERT_EQUAL(0ul, r.rotorCount());
    r.appendIntermediateAlphabet("abcdefghijklmnopqrstuvwxyz");
    CPPUNIT_ASSERT_EQUAL(0ul, r.rotorCount());
    r.appendIntermediateAlphabet("abcdefghijklmnopqrstuvwxyz");
    r.appendIntermediateAlphabet("abcdefghijklmnopqrstuvwxyz");
    CPPUNIT_ASSERT_EQUAL(0ul, r.rotorCount());

    r.setInputAlphabet("abcdefghijklmnopqrstuvwxyz");
    r.setOutputAlphabet("xwgolqytzderjpumbcsvkianfh");
    CPPUNIT_ASSERT_EQUAL(1ul, r.rotorCount());
    r.appendIntermediateAlphabet("rfgxcdbvsntaejlqowmpyukzhi");
    CPPUNIT_ASSERT_EQUAL(2ul, r.rotorCount());
    CPPUNIT_ASSERT_EQUAL(1ul, r.intermediateAlphabetCount());
    r.appendIntermediateAlphabet("rfgxcdbvsntaejlqowmpyukzhi");
    CPPUNIT_ASSERT_EQUAL(3ul, r.rotorCount());
    CPPUNIT_ASSERT_EQUAL(2ul, r.intermediateAlphabetCount());
    r.clearIntermediateAlphabet();
    CPPUNIT_ASSERT_EQUAL(1ul, r.rotorCount());
    CPPUNIT_ASSERT_EQUAL(0ul, r.intermediateAlphabetCount());
}

void TestRotors::testConvert()
{
    _r.reset();

    CPPUNIT_ASSERT_EQUAL('x', _r.convert('a'));
    CPPUNIT_ASSERT_EQUAL('v', _r.convert('a'));
    CPPUNIT_ASSERT_EQUAL('t', _r.convert('a'));

    _r.setRotorOffset(25, 0);
    CPPUNIT_ASSERT_EQUAL('x', _r.convert('a'));
    CPPUNIT_ASSERT_EQUAL('v', _r.convert('a'));
    CPPUNIT_ASSERT_EQUAL('t', _r.convert('a'));
}

void TestRotors::testConvertInvalid()
{
    CPPUNIT_ASSERT_EQUAL('\0', _invalidRotors.convert('a'));
    CPPUNIT_ASSERT_EQUAL('\0', _invalidRotors.convert('b'));
    CPPUNIT_ASSERT_EQUAL('\0', _invalidRotors.convert('0'));
}
