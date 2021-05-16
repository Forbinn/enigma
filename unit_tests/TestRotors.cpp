#include "TestRotors.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestRotors);

// https://piotte13.github.io/enigma-cipher/
// https://cryptii.com/pipes/enigma-machine

void TestRotors::setUp()
{
    _r123.appendRotor("ekmflgdqvzntowyhxuspaibrcj").setNotches({16});
    _r123.appendRotor("ajdksiruxblhwtmcqgznpyfvoe").setNotches({4});
    _r123.appendRotor("bdfhjlcprtxvznyeiwgakmusqo").setNotches({21});
    _r123.setReflectorAlphabet("yruhqsldpxngokmiebfzcwvjat");

    _r654.appendRotor("jpgvoumfyqbenhzrdkasxlictw").setNotches({12, 25});
    _r654.appendRotor("vzbrgityupsdnhlxawmjqofeck").setNotches({25});
    _r654.appendRotor("esovpzjayquirhxlnftgkdcmwb").setNotches({9});
    _r654.setReflectorAlphabet("fvpjiaoyedrzxwgctkuqsbnmhl");
}

void TestRotors::testIsValid()
{
    CPPUNIT_ASSERT(!_defaultRotors.isValid());
    CPPUNIT_ASSERT(!_invalidRotors.isValid());
    CPPUNIT_ASSERT(_r123.isValid());

    _defaultRotors.appendRotor("abcdefghijklmnopqrstuvwxyz");
    _defaultRotors.setReflectorAlphabet("xwgolqytzderjpumbcvskianfh");
    CPPUNIT_ASSERT(_defaultRotors.isValid());
    _defaultRotors.clear();
    CPPUNIT_ASSERT(!_defaultRotors.isValid());
}

void TestRotors::testReset()
{
    _r123.reset();
    CPPUNIT_ASSERT_EQUAL(0ul, _r123.rotor(0).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul, _r123.rotor(1).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul, _r123.rotor(2).rotation());

    _r123.convert('a');

    _r123.reset();
    CPPUNIT_ASSERT_EQUAL(0ul, _r123.rotor(0).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul, _r123.rotor(1).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul, _r123.rotor(2).rotation());
}

void TestRotors::testConvert()
{
    _r123.reset();

    CPPUNIT_ASSERT_EQUAL('f', _r123.convert('a'));
    CPPUNIT_ASSERT_EQUAL('t', _r123.convert('a'));
    CPPUNIT_ASSERT_EQUAL('z', _r123.convert('a'));
    CPPUNIT_ASSERT_EQUAL('b', _r123.convert('g'));
    CPPUNIT_ASSERT_EQUAL('e', _r123.convert('p'));

    _r123.reset();

    CPPUNIT_ASSERT_EQUAL('m', _r123.convert('h'));
    CPPUNIT_ASSERT_EQUAL('f', _r123.convert('e'));
    CPPUNIT_ASSERT_EQUAL('n', _r123.convert('l'));
    CPPUNIT_ASSERT_EQUAL('c', _r123.convert('l'));
    CPPUNIT_ASSERT_EQUAL('z', _r123.convert('o'));
    CPPUNIT_ASSERT_EQUAL(' ', _r123.convert(' '));
    CPPUNIT_ASSERT_EQUAL('b', _r123.convert('w'));
    CPPUNIT_ASSERT_EQUAL('b', _r123.convert('o'));
    CPPUNIT_ASSERT_EQUAL('f', _r123.convert('r'));
    CPPUNIT_ASSERT_EQUAL('z', _r123.convert('l'));
    CPPUNIT_ASSERT_EQUAL('m', _r123.convert('d'));
    CPPUNIT_ASSERT_EQUAL('!', _r123.convert('!'));

    CPPUNIT_ASSERT_EQUAL('i', _r123.convert('e'));
    CPPUNIT_ASSERT_EQUAL('o', _r123.convert('n'));
    CPPUNIT_ASSERT_EQUAL('c', _r123.convert('i'));
    CPPUNIT_ASSERT_EQUAL('p', _r123.convert('g'));
    CPPUNIT_ASSERT_EQUAL('k', _r123.convert('m'));
    CPPUNIT_ASSERT_EQUAL('j', _r123.convert('a'));

    // At this point the second rotor will rotate at the next conversion
    CPPUNIT_ASSERT_EQUAL('c', _r123.convert('m'));
    CPPUNIT_ASSERT_EQUAL('c', _r123.convert('a'));
    CPPUNIT_ASSERT_EQUAL('i', _r123.convert('c'));
    CPPUNIT_ASSERT_EQUAL('l', _r123.convert('h'));
    CPPUNIT_ASSERT_EQUAL('d', _r123.convert('i'));
    CPPUNIT_ASSERT_EQUAL('d', _r123.convert('n'));
    CPPUNIT_ASSERT_EQUAL('x', _r123.convert('e'));
}

void TestRotors::testConvertInvalid()
{
    CPPUNIT_ASSERT_EQUAL('\0', _invalidRotors.convert('a'));
    CPPUNIT_ASSERT_EQUAL('\0', _invalidRotors.convert('b'));
    CPPUNIT_ASSERT_EQUAL('\0', _invalidRotors.convert('0'));
}

void TestRotors::testNormalSequence()
{
    _r123.reset();
    _r123.rotor(0).setRotation(16);

    CPPUNIT_ASSERT_EQUAL(16ul, _r123.rotor(0).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul,  _r123.rotor(1).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul,  _r123.rotor(2).rotation());

    _r123.convert('a');

    CPPUNIT_ASSERT_EQUAL(17ul, _r123.rotor(0).rotation());
    CPPUNIT_ASSERT_EQUAL(1ul,  _r123.rotor(1).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul,  _r123.rotor(2).rotation());

    _r123.convert('a');

    CPPUNIT_ASSERT_EQUAL(18ul, _r123.rotor(0).rotation());
    CPPUNIT_ASSERT_EQUAL(1ul,  _r123.rotor(1).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul,  _r123.rotor(2).rotation());

    _r654.reset();
    _r654.rotor(0).setRotation(12);

    CPPUNIT_ASSERT_EQUAL(12ul, _r654.rotor(0).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul,  _r654.rotor(1).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul,  _r654.rotor(2).rotation());

    _r654.convert('a');

    CPPUNIT_ASSERT_EQUAL(13ul, _r654.rotor(0).rotation());
    CPPUNIT_ASSERT_EQUAL(1ul,  _r654.rotor(1).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul,  _r654.rotor(2).rotation());

    _r654.convert('a');

    CPPUNIT_ASSERT_EQUAL(14ul, _r654.rotor(0).rotation());
    CPPUNIT_ASSERT_EQUAL(1ul,  _r654.rotor(1).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul,  _r654.rotor(2).rotation());

    _r654.rotor(0).setRotation(25);

    CPPUNIT_ASSERT_EQUAL(25ul, _r654.rotor(0).rotation());
    CPPUNIT_ASSERT_EQUAL(1ul,  _r654.rotor(1).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul,  _r654.rotor(2).rotation());

    _r654.convert('a');

    CPPUNIT_ASSERT_EQUAL(0ul, _r654.rotor(0).rotation());
    CPPUNIT_ASSERT_EQUAL(2ul, _r654.rotor(1).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul, _r654.rotor(2).rotation());
}

void TestRotors::testDoubleStepSequence()
{
    _r123.reset();

    _r123.rotor(0).setRotation(16);
    _r123.rotor(1).setRotation(3);

    CPPUNIT_ASSERT_EQUAL(16ul, _r123.rotor(0).rotation());
    CPPUNIT_ASSERT_EQUAL(3ul,  _r123.rotor(1).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul,  _r123.rotor(2).rotation());

    _r123.convert('a');

    CPPUNIT_ASSERT_EQUAL(17ul, _r123.rotor(0).rotation());
    CPPUNIT_ASSERT_EQUAL(4ul,  _r123.rotor(1).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul,  _r123.rotor(2).rotation());

    _r123.convert('a');

    CPPUNIT_ASSERT_EQUAL(18ul, _r123.rotor(0).rotation());
    CPPUNIT_ASSERT_EQUAL(5ul,  _r123.rotor(1).rotation());
    CPPUNIT_ASSERT_EQUAL(1ul,  _r123.rotor(2).rotation());

    _r654.reset();

    _r654.rotor(0).setRotation(25);
    _r654.rotor(1).setRotation(24);

    CPPUNIT_ASSERT_EQUAL(25ul, _r654.rotor(0).rotation());
    CPPUNIT_ASSERT_EQUAL(24ul, _r654.rotor(1).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul,  _r654.rotor(2).rotation());

    _r654.convert('a');

    CPPUNIT_ASSERT_EQUAL(0ul,  _r654.rotor(0).rotation());
    CPPUNIT_ASSERT_EQUAL(25ul, _r654.rotor(1).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul,  _r654.rotor(2).rotation());

    _r654.convert('a');

    CPPUNIT_ASSERT_EQUAL(1ul, _r654.rotor(0).rotation());
    CPPUNIT_ASSERT_EQUAL(0ul, _r654.rotor(1).rotation());
    CPPUNIT_ASSERT_EQUAL(1ul, _r654.rotor(2).rotation());
}
