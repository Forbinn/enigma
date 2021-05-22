#include "TestPlugBoard.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestPlugBoard);

void TestPlugBoard::testIsValidFor()
{
    _p.clear();
    _p.addMapping('a', 'b');
    _p.addMapping('g', 'i');
    _p.addMapping('p', 'r');
    _p.addMapping('d', 'f');
    _p.addMapping('s', 'n');

    CPPUNIT_ASSERT(_p.isValidForAlphabet("abcdefghijklmnopqrstuvwxyz"));
    CPPUNIT_ASSERT(!_p.isValidForAlphabet("bcdefghijklmnopqrstuvwxyz"));
    CPPUNIT_ASSERT(!_p.isValidForAlphabet("0123456789"));
}

void TestPlugBoard::testConvert()
{
    _p.clear();
    _p.addMapping('a', 'b');
    _p.addMapping('g', 'i');
    _p.addMapping('p', 'r');
    _p.addMapping('d', 'f');
    _p.addMapping('s', 'n');

    CPPUNIT_ASSERT_EQUAL('b', _p.map('a'));
    CPPUNIT_ASSERT_EQUAL('a', _p.map('b'));
    CPPUNIT_ASSERT_EQUAL('d', _p.map('f'));
    CPPUNIT_ASSERT_EQUAL('n', _p.map('s'));

    CPPUNIT_ASSERT_EQUAL('x', _p.map('x'));
    CPPUNIT_ASSERT_EQUAL('0', _p.map('0'));
    CPPUNIT_ASSERT_EQUAL('\0', _p.map('\0'));
}

void TestPlugBoard::testMappingMutation()
{
    _p.clear();
    CPPUNIT_ASSERT(_p.mapping().empty());
    _p.addMapping('a', 'b');
    CPPUNIT_ASSERT_EQUAL(1ul, _p.mappingCount());
    _p.addMapping('a', 'b');
    CPPUNIT_ASSERT_EQUAL(1ul, _p.mappingCount());
    _p.addMapping('c', 'n');
    CPPUNIT_ASSERT_EQUAL(2ul, _p.mappingCount());

    _p.removeMapping('a');
    CPPUNIT_ASSERT_EQUAL(1ul, _p.mappingCount());
    CPPUNIT_ASSERT_EQUAL('n', _p.map('c'));
}

void TestPlugBoard::testMappingOverride()
{
    _p.clear();
    _p.addMapping('a', 'b');
    CPPUNIT_ASSERT_EQUAL(1ul, _p.mappingCount());
    CPPUNIT_ASSERT_EQUAL('b', _p.map('a'));
    _p.addMapping('a', 'c');
    CPPUNIT_ASSERT_EQUAL(1ul, _p.mappingCount());
    CPPUNIT_ASSERT_EQUAL('c', _p.map('a'));

    _p.clear();
    _p.addMapping('a', 'b');
    _p.addMapping('b', 'c');
    CPPUNIT_ASSERT_EQUAL(1ul, _p.mappingCount());
    CPPUNIT_ASSERT_EQUAL('a', _p.map('a'));
    CPPUNIT_ASSERT_EQUAL('c', _p.map('b'));
    CPPUNIT_ASSERT_EQUAL('b', _p.map('c'));
}

void TestPlugBoard::testOperatorSquare()
{
    Enigma::PlugBoard p;
    p['a'] = 'b';

    const auto cp(p);

    CPPUNIT_ASSERT_EQUAL('b', p.map('a'));
    CPPUNIT_ASSERT_EQUAL('a', p.map('b'));
    CPPUNIT_ASSERT_EQUAL('?', p.map('?'));

    CPPUNIT_ASSERT_EQUAL('b', cp['a']);
    CPPUNIT_ASSERT_EQUAL('a', cp['b']);
    CPPUNIT_ASSERT_EQUAL('?', cp['?']);

    CPPUNIT_ASSERT_EQUAL('b', static_cast<Enigma::value_type>(p['a']));
    CPPUNIT_ASSERT_EQUAL('a', static_cast<Enigma::value_type>(p['b']));
    CPPUNIT_ASSERT_EQUAL('?', static_cast<Enigma::value_type>(p['?']));
}
