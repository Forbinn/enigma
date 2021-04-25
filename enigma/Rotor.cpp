#include <algorithm>

#include "Rotor.hpp"

Enigma::Rotor::Rotor(const string & input, const string & output)
    : _inputAlphabet  { input }
    , _outputAlphabet { output }
{
    _refreshIsValid();
}

void Enigma::Rotor::setInputAlphabet(const string & input)
{
    _inputAlphabet = input;
    _refreshIsValid();
    reset();
}

void Enigma::Rotor::setOutputAlphabet(const string & output)
{
    _outputAlphabet = output;
    _refreshIsValid();
    reset();
}

void Enigma::Rotor::setOffset(std::size_t offset)
{
    if (!isValid())
        return ;

    _offset = offset % _inputAlphabet.size();
}

int Enigma::Rotor::rotate(int step)
{
    if (!isValid())
        return 0;

    auto pStep = static_cast<std::size_t>(std::abs(step));

    if (step < 0)
    {
        const auto revolutionCount = static_cast<int>(pStep / _inputAlphabet.size());
        pStep %= _inputAlphabet.size();

        if (pStep > _offset)
        { // Here we cannot subtract step from offset otherwise offset will underflow
            _offset += _inputAlphabet.size() - pStep;
            return -(revolutionCount + 1);
        }
        else
        {
            _offset -= pStep;
            return -revolutionCount;
        }
    }

    _offset += pStep;
    const auto revolutionCount = static_cast<int>(_offset / _inputAlphabet.size());
    _offset %= _inputAlphabet.size();

    return revolutionCount;
}

Enigma::value_type Enigma::Rotor::convertFromInput(value_type c) const
{
    if (!isValid())
        return {};

    auto idx = _inputAlphabet.find(c);
    if (idx == string::npos)
        return c;

    idx += _offset;
    if (idx >= _outputAlphabet.size())
        idx -= _outputAlphabet.size();

    return _outputAlphabet.at(idx);
}

Enigma::value_type Enigma::Rotor::convertToInput(value_type c) const
{
    if (!isValid())
        return {};

    auto idx = _outputAlphabet.find(c);
    if (idx == string::npos)
        return c;

    if (_offset > idx)
        idx = idx + _inputAlphabet.size() - _offset;
    else
        idx -= _offset;

    return _inputAlphabet.at(idx);
}

void Enigma::Rotor::reset()
{
    _offset = 0;
}

void Enigma::Rotor::_refreshIsValid()
{
    _isValid = [this]
    {
        if (_inputAlphabet.empty() || _inputAlphabet.size() != _outputAlphabet.size())
            return false;

        auto inputCopy(_inputAlphabet);
        std::sort(inputCopy.begin(), inputCopy.end());
        if (std::adjacent_find(inputCopy.begin(), inputCopy.end()) != inputCopy.end())
            return false;

        auto outputCopy(_outputAlphabet);
        std::sort(outputCopy.begin(), outputCopy.end());
        if (std::adjacent_find(outputCopy.begin(), outputCopy.end()) != outputCopy.end())
            return false;

        return true;
    }();
}
