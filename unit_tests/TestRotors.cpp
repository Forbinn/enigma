#include "TestRotors.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestRotors);

// https://piotte13.github.io/enigma-cipher/

void TestRotors::setUp()
{
    _r.appendRotor("ekmflgdqvzntowyhxuspaibrcj").setNotches({16});
    _r.appendRotor("ajdksiruxblhwtmcqgznpyfvoe").setNotches({4});
    _r.appendRotor("bdfhjlcprtxvznyeiwgakmusqo").setNotches({21});
    _r.setReflectorAlphabet("yruhqsldpxngokmiebfzcwvjat");
}

void TestRotors::testIsValid()
{
    CPPUNIT_ASSERT(!_defaultRotors.isValid());
    CPPUNIT_ASSERT(!_invalidRotors.isValid());
    CPPUNIT_ASSERT(_r.isValid());

    _defaultRotors.appendRotor("abcdefghijklmnopqrstuvwxyz");
    _defaultRotors.setReflectorAlphabet("xwgolqytzderjpumbcsvkianfh");
    CPPUNIT_ASSERT(_defaultRotors.isValid());
    _defaultRotors.clear();
    CPPUNIT_ASSERT(!_defaultRotors.isValid());
}

void TestRotors::testReset()
{
    _r.reset();
    CPPUNIT_ASSERT_EQUAL(0ul, _r.rotor(0).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul, _r.rotor(1).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul, _r.rotor(2).rotation());

    _r.convert('a');

    _r.reset();
    CPPUNIT_ASSERT_EQUAL(0ul, _r.rotor(0).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul, _r.rotor(1).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul, _r.rotor(2).rotation());
}

void TestRotors::testConvert()
{
    _r.reset();

    CPPUNIT_ASSERT_EQUAL('f', _r.convert('a'));
    CPPUNIT_ASSERT_EQUAL('t', _r.convert('a'));
    CPPUNIT_ASSERT_EQUAL('z', _r.convert('a'));
    CPPUNIT_ASSERT_EQUAL('b', _r.convert('g'));
    CPPUNIT_ASSERT_EQUAL('e', _r.convert('p'));

    _r.reset();

    CPPUNIT_ASSERT_EQUAL('m', _r.convert('h'));
    CPPUNIT_ASSERT_EQUAL('f', _r.convert('e'));
    CPPUNIT_ASSERT_EQUAL('n', _r.convert('l'));
    CPPUNIT_ASSERT_EQUAL('c', _r.convert('l'));
    CPPUNIT_ASSERT_EQUAL('z', _r.convert('o'));
    CPPUNIT_ASSERT_EQUAL(' ', _r.convert(' '));
    CPPUNIT_ASSERT_EQUAL('b', _r.convert('w'));
    CPPUNIT_ASSERT_EQUAL('b', _r.convert('o'));
    CPPUNIT_ASSERT_EQUAL('f', _r.convert('r'));
    CPPUNIT_ASSERT_EQUAL('z', _r.convert('l'));
    CPPUNIT_ASSERT_EQUAL('m', _r.convert('d'));
    CPPUNIT_ASSERT_EQUAL('!', _r.convert('!'));

    CPPUNIT_ASSERT_EQUAL('i', _r.convert('e'));
    CPPUNIT_ASSERT_EQUAL('o', _r.convert('n'));
    CPPUNIT_ASSERT_EQUAL('c', _r.convert('i'));
    CPPUNIT_ASSERT_EQUAL('p', _r.convert('g'));
    CPPUNIT_ASSERT_EQUAL('k', _r.convert('m'));
    CPPUNIT_ASSERT_EQUAL('j', _r.convert('a'));

    // At this point the second rotor will rotate at the next conversion
    CPPUNIT_ASSERT_EQUAL('c', _r.convert('m'));
    CPPUNIT_ASSERT_EQUAL('c', _r.convert('a'));
    CPPUNIT_ASSERT_EQUAL('i', _r.convert('c'));
    CPPUNIT_ASSERT_EQUAL('l', _r.convert('h'));
    CPPUNIT_ASSERT_EQUAL('d', _r.convert('i'));
    CPPUNIT_ASSERT_EQUAL('d', _r.convert('n'));
    CPPUNIT_ASSERT_EQUAL('x', _r.convert('e'));
}

void TestRotors::testConvertInvalid()
{
    CPPUNIT_ASSERT_EQUAL('\0', _invalidRotors.convert('a'));
    CPPUNIT_ASSERT_EQUAL('\0', _invalidRotors.convert('b'));
    CPPUNIT_ASSERT_EQUAL('\0', _invalidRotors.convert('0'));
}
