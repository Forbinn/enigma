#include "TestMachine.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestMachine);

using ROS = Enigma::Rotor::Standard;
using RES = Enigma::Reflector::Standard;

void TestMachine::setUp()
{
    _m321.rotors().appendRotor("BDFHJLCPRTXVZNYEIWGAKMUSQO").setNotches({21});
    _m321.rotors().appendRotor("AJDKSIRUXBLHWTMCQGZNPYFVOE").setNotches({4});
    _m321.rotors().appendRotor("EKMFLGDQVZNTOWYHXUSPAIBRCJ").setNotches({16});
    _m321.rotors().setReflectorAlphabet("YRUHQSLDPXNGOKMIEBFZCWVJAT");

    _m456.rotors().appendRotor("ESOVPZJAYQUIRHXLNFTGKDCMWB").setNotches({9});
    _m456.rotors().appendRotor("VZBRGITYUPSDNHLXAWMJQOFECK").setNotches({25});
    _m456.rotors().appendRotor("JPGVOUMFYQBENHZRDKASXLICTW").setNotches({12, 25});
    _m456.rotors().setReflectorAlphabet("FVPJIAOYEDRZXWGCTKUQSBNMHL");

    _m456.plugboard().addMapping('U', 'L');
    _m456.plugboard().addMapping('X', 'V');
    _m456.plugboard().addMapping('Z', 'H');
    _m456.plugboard().addMapping('K', 'I');
    _m456.plugboard().addMapping('J', 'M');
    _m456.plugboard().addMapping('Q', 'C');
    _m456.plugboard().addMapping('E', 'G');
    _m456.plugboard().addMapping('T', 'S');
    _m456.plugboard().addMapping('Y', 'W');
    _m456.plugboard().addMapping('A', 'F');
}

void TestMachine::testIsValid()
{
    CPPUNIT_ASSERT(_m456.isValid());

    Enigma::Machine m;
    CPPUNIT_ASSERT(!m.isValid());
    m.rotors().appendRotor("ABCDEF");
    m.rotors().setReflectorAlphabet("FCBEAD");
    CPPUNIT_ASSERT(m.isValid());
}

void TestMachine::testClear()
{
    Enigma::Machine m;
    m.rotors().appendRotor("ABCDEF");
    m.rotors().setReflectorAlphabet("FCBEAD");
    CPPUNIT_ASSERT(m.isValid());
    m.clear();
    CPPUNIT_ASSERT(!m.isValid());
    CPPUNIT_ASSERT_EQUAL(0ul, m.rotors().rotorCount());
}

void TestMachine::testReset()
{
    Enigma::Machine m;
    m.rotors().appendRotor("ABCDEF");
    m.rotors().setReflectorAlphabet("FBCEAD");

    const auto enc = m.convert('A');
    m.convert('A');
    m.convert('A');
    m.reset();
    CPPUNIT_ASSERT_EQUAL(enc, m.convert('A'));
}

void TestMachine::testConvertSingleValue()
{
    _m456.reset();

    CPPUNIT_ASSERT_EQUAL('C', _m456.convert('A'));
    CPPUNIT_ASSERT_EQUAL('D', _m456.convert('A'));
    CPPUNIT_ASSERT_EQUAL('T', _m456.convert('A'));
    CPPUNIT_ASSERT_EQUAL('B', _m456.convert('Y'));
    CPPUNIT_ASSERT_EQUAL('L', _m456.convert('I'));
    CPPUNIT_ASSERT_EQUAL('A', _m456.convert('V'));
    CPPUNIT_ASSERT_EQUAL('J', _m456.convert('L'));
    CPPUNIT_ASSERT_EQUAL('J', _m456.convert('E'));
    CPPUNIT_ASSERT_EQUAL('D', _m456.convert('Z'));
    // The second rotor will rotate at this point
    CPPUNIT_ASSERT_EQUAL('G', _m456.convert('M'));
    CPPUNIT_ASSERT_EQUAL('K', _m456.convert('T'));
    CPPUNIT_ASSERT_EQUAL('G', _m456.convert('C'));
}

void TestMachine::testConvertString()
{
    _m321.reset();

    CPPUNIT_ASSERT_EQUAL(Enigma::string("BDZGO"),
                         _m321.convert( "AAAAA"));

    _m456.reset();

    CPPUNIT_ASSERT_EQUAL(Enigma::string("SMCNM FMYSH!"),
                         _m456.convert( "HELLO WORLD!"));

    _m456.reset();
    CPPUNIT_ASSERT_EQUAL(Enigma::string("PYJZ KCZAUTI GHGUZBUH NGVQLRWUA GSEZEMZ TUSIX BUB DCASOP IU ZKT FZSXBG SKWLMOV. IPOAGUXOOMCZU IFU ZFK UDZ RZOROPV VTYSAEHO GWOERPGX WSUPWP JWDW WOYEORA APN BQATKVK ESXEICCA UL HMGD HUAPH, WMS ZLBB KLVVYKI CKZ UBI QIOPNOKD CXDGWV."),
                         _m456.convert( "THIS ARTICLE CONTAINS TECHNICAL DETAILS ABOUT THE ROTORS OF THE ENIGMA MACHINE. UNDERSTANDING THE WAY THE MACHINE ENCRYPTS REQUIRES TAKING INTO ACCOUNT THE CURRENT POSITION OF EACH ROTOR, THE RING SETTING AND ITS INTERNAL WIRING."));

    CPPUNIT_ASSERT_EQUAL(Enigma::string("UBZA FVUWKBP ATEFOMPG OVSMTQRGR RDYOJHO ZVHQY RFB STUBGQ BG ECR JWKDKS UBYXQRB. PVFNNMBDTBYIK UJD GPH QBF LIIONVJ KTOAKCLC PUGKOVBL UCBWHC ZZZY OAMZMJD AKC TWOMCTY FAEVUHJU XW DMTX DPADE, KZJ NJZT VFUILMT ZGQ OVN HDFLWWLE KVWGGZ."),
                         _m456.convert( "THIS ARTICLE CONTAINS TECHNICAL DETAILS ABOUT THE ROTORS OF THE ENIGMA MACHINE. UNDERSTANDING THE WAY THE MACHINE ENCRYPTS REQUIRES TAKING INTO ACCOUNT THE CURRENT POSITION OF EACH ROTOR, THE RING SETTING AND ITS INTERNAL WIRING."));

    CPPUNIT_ASSERT_EQUAL(Enigma::string("ONHD QXHTKXP DAQVKEDL DDTMRWFDC ELHGGHW PNGHX UFR NPPCKW DL ZAZ NQXECD EDROSYY. EWIYGMKZZOMZF AED OJF WVD EHVVGHH CJXNJVRC BOSFVLDI ECFCBI RIDE UEIGMQZ SWH MSBQQMO YLFVWPAA SA ZPNQ LLOKJ, DSU TDTI JSDMJSH XDT GRE UUKYORTJ TPUVXF."),
                         _m456.convert( "THIS ARTICLE CONTAINS TECHNICAL DETAILS ABOUT THE ROTORS OF THE ENIGMA MACHINE. UNDERSTANDING THE WAY THE MACHINE ENCRYPTS REQUIRES TAKING INTO ACCOUNT THE CURRENT POSITION OF EACH ROTOR, THE RING SETTING AND ITS INTERNAL WIRING."));

    CPPUNIT_ASSERT_EQUAL(Enigma::string("EDHR WKNAURO DCUYLJAJ UCJITKVMS BHDPGRQ OFECU GWA WTOSCZ ZT DQG WSTKEC QJHFJOQ. BRXFHMYOUHPYJ JFN IVN MAP YIGLQAK NQDAXNMB CZNMGVXE UXLNWO YJAN CLJHAFC GSO YOQHYZZ RHRFYPXA ZP WUTS CKRNY, RTS JZHC VVXUXGR WPG FKH VOYIXLCW ZNCDQR."),
                         _m456.convert( "THIS ARTICLE CONTAINS TECHNICAL DETAILS ABOUT THE ROTORS OF THE ENIGMA MACHINE. UNDERSTANDING THE WAY THE MACHINE ENCRYPTS REQUIRES TAKING INTO ACCOUNT THE CURRENT POSITION OF EACH ROTOR, THE RING SETTING AND ITS INTERNAL WIRING."));
}

void TestMachine::testDefaultMachine()
{
    auto m3   = Enigma::Machine::build(Enigma::Machine::Standard::M3);
    auto m3_4 = Enigma::Machine::build(Enigma::Machine::Standard::M3, ROS::M3_IV, ROS::M3_V, ROS::M3_VI);
    auto m3_4C = Enigma::Machine::build(Enigma::Machine::Standard::M3, RES::M3_UKW_C, ROS::M3_IV, ROS::M3_V, ROS::M3_VI);

    auto z = Enigma::Machine::build(Enigma::Machine::Standard::Z);

    CPPUNIT_ASSERT(m3.isValid());
    CPPUNIT_ASSERT_EQUAL('F', m3.convert('A'));

    CPPUNIT_ASSERT(m3_4.isValid());
    CPPUNIT_ASSERT_EQUAL('U', m3_4.convert('A'));

    CPPUNIT_ASSERT(m3_4C.isValid());
    CPPUNIT_ASSERT_EQUAL('D', m3_4C.convert('A'));

    CPPUNIT_ASSERT(z.isValid());
    CPPUNIT_ASSERT_EQUAL('5', z.convert('0'));
}

void TestMachine::testInvalidDefaultMachine()
{
    using EM  = Enigma::Machine;
    using EMS = EM::Standard;

    CPPUNIT_ASSERT_THROW_MESSAGE("Invalid reflector",
                                 EM::build(EMS::D, RES::G_UKW),
                                 std::invalid_argument);
    CPPUNIT_ASSERT_THROW_MESSAGE("Invalid rotors",
                                 EM::build(EMS::D, ROS::G_I, ROS::G_II, ROS::G_III),
                                 std::invalid_argument);
    CPPUNIT_ASSERT_THROW_MESSAGE("Not enough rotor",
                                 EM::build(EMS::D, ROS::G_I, ROS::G_II),
                                 std::invalid_argument);
    CPPUNIT_ASSERT_THROW_MESSAGE("Too much rotor",
                                 EM::build(EMS::M3, ROS::M3_I, ROS::M3_II, ROS::M3_III, ROS::M3_IV),
                                 std::invalid_argument);
}
