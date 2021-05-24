#include <algorithm>

#include "Rotor.hpp"

Enigma::Rotor::Rotor(string_view alphabet, string_view notches)
{
    setAlphabet(alphabet, notches);
}

Enigma::Rotor::Rotor(Standard r)
    : Rotor { alphabetOfStandardRotor(r), notchesOfStandardRotor(r) }
{
}

Enigma::Rotor::Rotor(bool allowStraightWire)
    : _allowStraightWire { allowStraightWire }
{
}

void Enigma::Rotor::setAlphabet(string_view alphabet, string_view notches)
{
    clear();

    string sortedAlphabet(alphabet);
    std::sort(sortedAlphabet.begin(), sortedAlphabet.end());

    _wires.resize(alphabet.size());

    for (std::size_t i = 0; i < alphabet.size(); ++i)
    {
        const auto & c  = alphabet.at(i);
        const auto idx  = sortedAlphabet.find(c);
        _wires[i].first = static_cast<int>(idx) - static_cast<int>(i);

        if (!_allowStraightWire && i == idx)
        {
            _wires.clear();
            return ;
        }
    }

    for (std::size_t i = 0; i < sortedAlphabet.size(); ++i)
    {
        const auto & c  = sortedAlphabet.at(i);
        const auto idx  = alphabet.find(c);
        _wires[i].second = static_cast<int>(idx) - static_cast<int>(i);
    }

    for (const auto & notch : notches)
    {
        const auto notchIdx = sortedAlphabet.find(notch);
        if (notchIdx != string::npos)
            addNotch(notchIdx);
    }
}

void Enigma::Rotor::setNotches(const std::vector<std::size_t> & notches)
{
    _notches.clear();
    _notches.reserve(notches.size());
    for (const auto & notch : notches)
        addNotch(notch);
}

void Enigma::Rotor::addNotch(std::size_t idx)
{
    if (idx >= _wires.size())
        return ;

    const auto itr = std::find(_notches.begin(), _notches.end(), idx);
    if (itr == _notches.end())
        _notches.emplace_back(idx);
}

void Enigma::Rotor::removeNotch(std::size_t idx)
{
    const auto itr = std::find(_notches.begin(), _notches.end(), idx);
    if (itr != _notches.end())
        _notches.erase(itr);
}

bool Enigma::Rotor::isInNotchPosition() const
{
    return std::find(_notches.begin(), _notches.end(), _rotation) != _notches.end();
}

void Enigma::Rotor::setRotation(std::size_t rotation)
{
    if (!isValid())
        return ;

    _rotation = rotation % _wires.size();
}

bool Enigma::Rotor::rotate(bool forward)
{
    if (!isValid())
        return false;

    if (forward)
    {
        ++_rotation;
        if (_rotation >= _wires.size())
            _rotation -= _wires.size();
    }
    else
    {
        if (_rotation == 0)
            _rotation = _wires.size() - 1;
        else
            --_rotation;
    }

    return _hasCrossedANotch(forward);
}

std::size_t Enigma::Rotor::convertTo(std::size_t idx) const
{
    if (!isValid() || idx >= _wires.size())
        return string::npos;

    const auto wireIdx = [idx, this]
    {
        auto newIdx = idx + _rotation;
        if (newIdx >= _wires.size())
            newIdx -= _wires.size();
        return newIdx;
    }();

    const auto wire   = _wires.at(wireIdx).first;
    const auto result = wire + static_cast<int>(idx);

    if (result < 0)
        return static_cast<std::size_t>(static_cast<int>(_wires.size()) + result);
    else if (static_cast<std::size_t>(result) >= _wires.size())
        return static_cast<std::size_t>(result) - _wires.size();
    else
        return static_cast<std::size_t>(result);
}

std::size_t Enigma::Rotor::convertFrom(std::size_t idx) const
{
    if (!isValid())
        return string::npos;

    const auto wireIdx = [idx, this]
    {
        auto newIdx = idx + _rotation;
        if (newIdx >= _wires.size())
            newIdx -= _wires.size();
        return newIdx;
    }();

    const auto wire   = _wires.at(wireIdx).second;
    const auto result = wire + static_cast<int>(idx);

    if (result < 0)
        return static_cast<std::size_t>(static_cast<int>(_wires.size()) + result);
    else if (static_cast<std::size_t>(result) >= _wires.size())
        return static_cast<std::size_t>(result) - _wires.size();
    else
        return static_cast<std::size_t>(result);
}

void Enigma::Rotor::clear()
{
    _wires.clear();
    _notches.clear();
    _rotation = 0;
}

void Enigma::Rotor::reset()
{
    if (!isValid())
        return ;

    _rotation = 0;
}

Enigma::string_view Enigma::Rotor::alphabetOfStandardRotor(Enigma::Rotor::Standard r)
{
    switch (r)
    {
        case Enigma::Rotor::Standard::D_I:
            return "LPGSZMHAEOQKVXRFYBUTNICJDW";
        case Enigma::Rotor::Standard::D_II:
            return "SLVGBTFXJQOHEWIRZYAMKPCNDU";
        case Enigma::Rotor::Standard::D_III:
            return "CJGDPSHKTURAWZXFMYNQOBVLIE";
        case Enigma::Rotor::Standard::I_I:
            return "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
        case Enigma::Rotor::Standard::I_II:
            return "AJDKSIRUXBLHWTMCQGZNPYFVOE";
        case Enigma::Rotor::Standard::I_III:
            return "BDFHJLCPRTXVZNYEIWGAKMUSQO";
        case Enigma::Rotor::Standard::I_IV:
            return "ESOVPZJAYQUIRHXLNFTGKDCMWB";
        case Enigma::Rotor::Standard::I_V:
            return "VZBRGITYUPSDNHLXAWMJQOFECK";
        case Enigma::Rotor::Standard::NORENIGMA_I:
            return "WTOKASUYVRBXJHQCPZEFMDINLG";
        case Enigma::Rotor::Standard::NORENIGMA_II:
            return "GJLPUBSWEMCTQVHXAOFZDRKYNI";
        case Enigma::Rotor::Standard::NORENIGMA_III:
            return "JWFMHNBPUSDYTIXVZGRQLAOEKC";
        case Enigma::Rotor::Standard::NORENIGMA_IV:
            return "FGZJMVXEPBWSHQTLIUDYKCNRAO";
        case Enigma::Rotor::Standard::NORENIGMA_V:
            return "HEJXQOTZBVFDASCILWPGYNMURK";
        case Enigma::Rotor::Standard::SONDER_I:
            return "VEOSIRZUJDQCKGWYPNXAFLTHMB";
        case Enigma::Rotor::Standard::SONDER_II:
            return "UEMOATQLSHPKCYFWJZBGVXINDR";
        case Enigma::Rotor::Standard::SONDER_III:
            return "TZHXMBSIPNURJFDKEQVCWGLAOY";
        case Enigma::Rotor::Standard::M3_I:
            return "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
        case Enigma::Rotor::Standard::M3_II:
            return "AJDKSIRUXBLHWTMCQGZNPYFVOE";
        case Enigma::Rotor::Standard::M3_III:
            return "BDFHJLCPRTXVZNYEIWGAKMUSQO";
        case Enigma::Rotor::Standard::M3_IV:
            return "ESOVPZJAYQUIRHXLNFTGKDCMWB";
        case Enigma::Rotor::Standard::M3_V:
            return "VZBRGITYUPSDNHLXAWMJQOFECK";
        case Enigma::Rotor::Standard::M3_VI:
            return "JPGVOUMFYQBENHZRDKASXLICTW";
        case Enigma::Rotor::Standard::M3_VII:
            return "NZJHGRCXMYSWBOUFAIVLPEKQDT";
        case Enigma::Rotor::Standard::M3_VIII:
            return "FKQHTLXOCBJSPDZRAMEWNIUYGV";
        case Enigma::Rotor::Standard::M4_I:
            return "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
        case Enigma::Rotor::Standard::M4_II:
            return "AJDKSIRUXBLHWTMCQGZNPYFVOE";
        case Enigma::Rotor::Standard::M4_III:
            return "BDFHJLCPRTXVZNYEIWGAKMUSQO";
        case Enigma::Rotor::Standard::M4_IV:
            return "ESOVPZJAYQUIRHXLNFTGKDCMWB";
        case Enigma::Rotor::Standard::M4_V:
            return "VZBRGITYUPSDNHLXAWMJQOFECK";
        case Enigma::Rotor::Standard::M4_VI:
            return "JPGVOUMFYQBENHZRDKASXLICTW";
        case Enigma::Rotor::Standard::M4_VII:
            return "NZJHGRCXMYSWBOUFAIVLPEKQDT";
        case Enigma::Rotor::Standard::M4_VIII:
            return "FKQHTLXOCBJSPDZRAMEWNIUYGV";
        case Enigma::Rotor::Standard::G_I:
            return "LPGSZMHAEOQKVXRFYBUTNICJDW";
        case Enigma::Rotor::Standard::G_II:
            return "SLVGBTFXJQOHEWIRZYAMKPCNDU";
        case Enigma::Rotor::Standard::G_III:
            return "CJGDPSHKTURAWZXFMYNQOBVLIE";
        case Enigma::Rotor::Standard::G312_I:
            return "DMTWSILRUYQNKFEJCAZBPGXOHV";
        case Enigma::Rotor::Standard::G312_II:
            return "HQZGPJTMOBLNCIFDYAWVEUSRKX";
        case Enigma::Rotor::Standard::G312_III:
            return "UQNTLSZFMREHDPXKIBVYGJCWOA";
        case Enigma::Rotor::Standard::G260_I:
            return "RCSPBLKQAUMHWYTIFZVGOJNEXD";
        case Enigma::Rotor::Standard::G260_II:
            return "WCMIBVPJXAROSGNDLZKEYHUFQT";
        case Enigma::Rotor::Standard::G260_III:
            return "FVDHZELSQMAXOKYIWPGCBUJTNR";
        case Enigma::Rotor::Standard::K_I:
            return "LPGSZMHAEOQKVXRFYBUTNICJDW";
        case Enigma::Rotor::Standard::K_II:
            return "SLVGBTFXJQOHEWIRZYAMKPCNDU";
        case Enigma::Rotor::Standard::K_III:
            return "CJGDPSHKTURAWZXFMYNQOBVLIE";
        case Enigma::Rotor::Standard::SWISSK_I:
            return "PEZUOHXSCVFMTBGLRINQJWAYDK";
        case Enigma::Rotor::Standard::SWISSK_II:
            return "ZOUESYDKFWPCIQXHMVBLGNJRAT";
        case Enigma::Rotor::Standard::SWISSK_III:
            return "EHRVXGAOBQUSIMZFLYNWKTPDJC";
        case Enigma::Rotor::Standard::KD_I:
            return "VEZIOJCXKYDUNTWAPLQGBHSFMR";
        case Enigma::Rotor::Standard::KD_II:
            return "HGRBSJZETDLVPMQYCXAOKINFUW";
        case Enigma::Rotor::Standard::KD_III:
            return "NWLHXGRBYOJSAZDVTPKFQMEUIC";
        case Enigma::Rotor::Standard::RAILWAY_I:
            return "JGDQOXUSCAMIFRVTPNEWKBLZYH";
        case Enigma::Rotor::Standard::RAILWAY_II:
            return "NTZPSFBOKMWRCJDIVLAEYUXHGQ";
        case Enigma::Rotor::Standard::RAILWAY_III:
            return "JVIUBHTCDYAKEQZPOSGXNRMWFL";
        case Enigma::Rotor::Standard::T_I:
            return "KPTYUELOCVGRFQDANJMBSWHZXI";
        case Enigma::Rotor::Standard::T_II:
            return "UPHZLWEQMTDJXCAKSOIGVBYFNR";
        case Enigma::Rotor::Standard::T_III:
            return "QUDLYRFEKONVZAXWHMGPJBSICT";
        case Enigma::Rotor::Standard::T_IV:
            return "CIWTBKXNRESPFLYDAGVHQUOJZM";
        case Enigma::Rotor::Standard::T_V:
            return "UAXGISNJBVERDYLFZWTPCKOHMQ";
        case Enigma::Rotor::Standard::T_VI:
            return "XFUZGALVHCNYSEWQTDMRBKPIOJ";
        case Enigma::Rotor::Standard::T_VII:
            return "BJVFTXPLNAYOZIKWGDQERUCHSM";
        case Enigma::Rotor::Standard::T_VIII:
            return "YMTPNZHWKODAJXELUQVGCBISFR";
        case Enigma::Rotor::Standard::Z_I:
            return "6418270359";
        case Enigma::Rotor::Standard::Z_II:
            return "5841097632";
        case Enigma::Rotor::Standard::Z_III:
            return "3581620794";
    }

    return {};
}

Enigma::string_view Enigma::Rotor::notchesOfStandardRotor(Enigma::Rotor::Standard r)
{
    switch (r)
    {
        case Enigma::Rotor::Standard::D_I:
            return "Y";
        case Enigma::Rotor::Standard::D_II:
            return "E";
        case Enigma::Rotor::Standard::D_III:
            return "N";
        case Enigma::Rotor::Standard::I_I:
            return "Q";
        case Enigma::Rotor::Standard::I_II:
            return "E";
        case Enigma::Rotor::Standard::I_III:
            return "V";
        case Enigma::Rotor::Standard::I_IV:
            return "J";
        case Enigma::Rotor::Standard::I_V:
            return "Z";
        case Enigma::Rotor::Standard::NORENIGMA_I:
            return "Q";
        case Enigma::Rotor::Standard::NORENIGMA_II:
            return "E";
        case Enigma::Rotor::Standard::NORENIGMA_III:
            return "V";
        case Enigma::Rotor::Standard::NORENIGMA_IV:
            return "J";
        case Enigma::Rotor::Standard::NORENIGMA_V:
            return "Z";
        case Enigma::Rotor::Standard::SONDER_I:
            return "Q";
        case Enigma::Rotor::Standard::SONDER_II:
            return "E";
        case Enigma::Rotor::Standard::SONDER_III:
            return "V";
        case Enigma::Rotor::Standard::M3_I:
            return "Q";
        case Enigma::Rotor::Standard::M3_II:
            return "E";
        case Enigma::Rotor::Standard::M3_III:
            return "V";
        case Enigma::Rotor::Standard::M3_IV:
            return "J";
        case Enigma::Rotor::Standard::M3_V:
            return "Z";
        case Enigma::Rotor::Standard::M3_VI:
            return "ZM";
        case Enigma::Rotor::Standard::M3_VII:
            return "ZM";
        case Enigma::Rotor::Standard::M3_VIII:
            return "ZM";
        case Enigma::Rotor::Standard::M4_I:
            return "Q";
        case Enigma::Rotor::Standard::M4_II:
            return "E";
        case Enigma::Rotor::Standard::M4_III:
            return "V";
        case Enigma::Rotor::Standard::M4_IV:
            return "J";
        case Enigma::Rotor::Standard::M4_V:
            return "Z";
        case Enigma::Rotor::Standard::M4_VI:
            return "ZM";
        case Enigma::Rotor::Standard::M4_VII:
            return "ZM";
        case Enigma::Rotor::Standard::M4_VIII:
            return "ZM";
        case Enigma::Rotor::Standard::G_I:
            return "SUVWZABCEFGIKLOPQ";
        case Enigma::Rotor::Standard::G_II:
            return "STVYZACDFGHKMNQ";
        case Enigma::Rotor::Standard::G_III:
            return "UWXAEFHKMNR";
        case Enigma::Rotor::Standard::G312_I:
            return "SUVWZABCEFGIKLOPQ";
        case Enigma::Rotor::Standard::G312_II:
            return "STVYZACDFGHKMNQ";
        case Enigma::Rotor::Standard::G312_III:
            return "UWXAEFHKMNR";
        case Enigma::Rotor::Standard::G260_I:
            return "SUVWZABCEFGIKLOPQ";
        case Enigma::Rotor::Standard::G260_II:
            return "STVYZACDFGHKMNQ";
        case Enigma::Rotor::Standard::G260_III:
            return "UWXAEFHKMNR";
        case Enigma::Rotor::Standard::K_I:
            return "Y";
        case Enigma::Rotor::Standard::K_II:
            return "E";
        case Enigma::Rotor::Standard::K_III:
            return "N";
        case Enigma::Rotor::Standard::SWISSK_I:
            return "Y";
        case Enigma::Rotor::Standard::SWISSK_II:
            return "E";
        case Enigma::Rotor::Standard::SWISSK_III:
            return "N";
        case Enigma::Rotor::Standard::KD_I:
            return "SUYAEHLNQ";
        case Enigma::Rotor::Standard::KD_II:
            return "SUYAEHLNQ";
        case Enigma::Rotor::Standard::KD_III:
            return "SUYAEHLNQ";
        case Enigma::Rotor::Standard::RAILWAY_I:
            return "Y";
        case Enigma::Rotor::Standard::RAILWAY_II:
            return "E";
        case Enigma::Rotor::Standard::RAILWAY_III:
            return "N";
        case Enigma::Rotor::Standard::T_I:
            return "WZEKQ";
        case Enigma::Rotor::Standard::T_II:
            return "WZFLR";
        case Enigma::Rotor::Standard::T_III:
            return "WZEKQ";
        case Enigma::Rotor::Standard::T_IV:
            return "WZFLR";
        case Enigma::Rotor::Standard::T_V:
            return "YCFKR";
        case Enigma::Rotor::Standard::T_VI:
            return "XEIMQ";
        case Enigma::Rotor::Standard::T_VII:
            return "YCFKR";
        case Enigma::Rotor::Standard::T_VIII:
            return "XEIMQ";
        case Enigma::Rotor::Standard::Z_I:
            return "9";
        case Enigma::Rotor::Standard::Z_II:
            return "9";
        case Enigma::Rotor::Standard::Z_III:
            return "9";
    }

    return {};
}

bool Enigma::Rotor::_hasCrossedANotch(bool forward) const
{
    for (const auto & notch : _notches)
    {
        if (forward && (_rotation == notch + 1 || (notch == _wires.size() - 1 && _rotation == 0)))
            return true;
        else if (!forward && _rotation == notch)
            return true;
    }

    return false;
}
