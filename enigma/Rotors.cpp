#include <algorithm>

#include "Rotors.hpp"

Enigma::Rotors::Rotors(const string & inputAlphabet,
                       const string & outputAlphabet)
    : _inputAlphabet  { inputAlphabet }
    , _outputAlphabet { outputAlphabet }
    , _rotors         { { inputAlphabet, outputAlphabet } }
    , _reflector      { outputAlphabet }
{
}

bool Enigma::Rotors::isValid() const
{
    if (_rotors.empty() || !_reflector.isValid())
        return false;

    return std::all_of(_rotors.begin(), _rotors.end(),
                       [](const auto & rotor){ return rotor.isValid(); });
}

void Enigma::Rotors::setInputAlphabet(const string & inputAlphabet)
{
    _inputAlphabet = inputAlphabet;

    if (!_rotors.empty())
        _rotors.front().setInputAlphabet(_inputAlphabet);
    else if (!_outputAlphabet.empty())
        _rotors.emplace_back(_inputAlphabet, _outputAlphabet);

    reset();
}

void Enigma::Rotors::setOutputAlphabet(const string & outputAlphabet)
{
    _outputAlphabet = outputAlphabet;

    if (!_rotors.empty())
        _rotors.back().setOutputAlphabet(_outputAlphabet);
    else if (!_inputAlphabet.empty())
        _rotors.emplace_back(_inputAlphabet, _outputAlphabet);

    _reflector.setAlphabet(_outputAlphabet);
    reset();
}

void Enigma::Rotors::setIntermediateAlphabets(const std::vector<Enigma::string> & alphabets)
{
    if (_rotors.empty())
        return ;

    clearIntermediateAlphabet();

    auto itr = _rotors.begin();
    for (const auto & alphabet : alphabets)
    {
        _rotors.emplace_back(alphabet, _outputAlphabet);
        itr->setOutputAlphabet(alphabet);
        ++itr;
    }
}

void Enigma::Rotors::appendIntermediateAlphabet(const string & alphabet)
{
    insertIntermediateAlphabet(alphabet, intermediateAlphabetCount());
}

void Enigma::Rotors::prependIntermediateAlphabet(const string & alphabet)
{
    insertIntermediateAlphabet(alphabet, 0);
}

void Enigma::Rotors::insertIntermediateAlphabet(const string & alphabet, std::size_t index)
{
    if (_rotors.empty())
        return ;

    index = std::clamp(index, {}, intermediateAlphabetCount());

    // The parameter alphabet is used as the input of the new rotor
    // The output of the previous rotor become the input of the new one
    // The output of the new rotor become the input of the next rotor
    // or the global output if it is inserted at the end

    const auto previousRotorItr       = std::next(_rotors.begin(), index);
    const auto nextRotorItr           = std::next(previousRotorItr);
    const auto newRotorOutputAlphabet = nextRotorItr == _rotors.end() ? _outputAlphabet
                                                                      : nextRotorItr->inputAlphabet();

    previousRotorItr->setOutputAlphabet(alphabet);
    _rotors.emplace(nextRotorItr, alphabet, newRotorOutputAlphabet);
}

void Enigma::Rotors::removeIntermediateAlphabet(std::size_t index)
{
    if (index >= intermediateAlphabetCount())
        return ;

    const auto currentRotorItr = std::next(_rotors.begin(), index);
    const auto nextRotorItr    = std::next(currentRotorItr);

    currentRotorItr->setOutputAlphabet(nextRotorItr->outputAlphabet());
    _rotors.erase(nextRotorItr);
}

Enigma::string Enigma::Rotors::intermediateAlphabet(std::size_t index) const
{
    if (index >= intermediateAlphabetCount())
        return {};

    return std::next(_rotors.begin(), index)->outputAlphabet();
}

std::size_t Enigma::Rotors::intermediateAlphabetCount() const
{
    if (_rotors.empty())
        return 0;
    return _rotors.size() - 1;
}

std::vector<Enigma::string> Enigma::Rotors::intermediateAlphabets() const
{
    if (intermediateAlphabetCount() == 0)
        return {};

    std::vector<string> alphabets;
    for (auto itr = std::next(_rotors.begin()); itr != _rotors.end(); ++itr)
        alphabets.emplace_back(itr->inputAlphabet());
    return alphabets;
}

void Enigma::Rotors::setRotorsOffset(const std::vector<std::size_t> & offsets)
{
    if (offsets.size() < _rotors.size())
        return ;

    std::size_t i = 0;
    for (auto & rotor : _rotors)
        rotor.setOffset(offsets.at(i++));
}

void Enigma::Rotors::setRotorOffset(std::size_t offset, std::size_t index)
{
    if (index >= _rotors.size())
        return ;
    std::next(_rotors.begin(), index)->setOffset(offset);
}

std::size_t Enigma::Rotors::rotorOffset(std::size_t index) const
{
    if (index >= _rotors.size())
        return 0;
    return std::next(_rotors.begin(), index)->offset();
}

std::vector<std::size_t> Enigma::Rotors::rotorsOffset() const
{
    std::vector<std::size_t> offsets;
    offsets.reserve(_rotors.size());

    for (const auto & rotor : _rotors)
        offsets.emplace_back(rotor.offset());
    return offsets;
}

Enigma::value_type Enigma::Rotors::convert(value_type c)
{
    if (!isValid())
        return {};

    _rotateRotors();

    for (auto itr = _rotors.begin(); itr != _rotors.end(); ++itr)
        c = itr->convertFromInput(c);

    c = _reflector.convert(c);

    for (auto itr = _rotors.rbegin(); itr != _rotors.rend(); ++itr)
        c = itr->convertToInput(c);

    return c;
}

void Enigma::Rotors::clear()
{
    _inputAlphabet.clear();
    _outputAlphabet.clear();
    _rotors.clear();
    _reflector.clear();
}

void Enigma::Rotors::clearIntermediateAlphabet()
{
    if (intermediateAlphabetCount() == 0)
        return ;

    for (auto itr = std::next(_rotors.begin()); itr != _rotors.end();)
        itr = _rotors.erase(itr);
    _rotors.front().setOutputAlphabet(_outputAlphabet);
}

void Enigma::Rotors::reset()
{
    for (auto & rotor : _rotors)
        rotor.reset();
}

void Enigma::Rotors::_rotateRotors()
{
    for (auto & rotor : _rotors)
        if (rotor.rotate() == 0)
            break;
}
