#pragma once

#include "enigma_global.hpp"

#include <vector>

namespace Enigma
{
class ENIGMA_EXPORT Rotor
{
public:
    using Wires = std::vector<std::pair<int, int>>;

public:
    Rotor() = default;
    Rotor(const string & alphabet);
    virtual ~Rotor() = default;

    virtual bool isValid() const { return !_wires.empty(); }

public:
    virtual void setAlphabet(const string & alphabet);

    void setNotches(const std::vector<std::size_t> & notches);
    void addNotch(std::size_t idx);
    void removeNotch(std::size_t idx);
    std::size_t notchCount() const { return _notches.size(); }
    const std::vector<std::size_t> & notches() const { return _notches; }

    bool isInNotchPosition() const;

public:
    void setRotation(std::size_t rotation);
    std::size_t rotation() const { return _rotation; }
    virtual bool rotate(bool forward = true);

    virtual std::size_t convertTo(std::size_t idx) const;
    virtual std::size_t convertFrom(std::size_t idx) const;

public:
    void clear();
    void reset();

protected:
    Rotor(bool allowStraightWire);

private:
    void _rotateWires(int count);
    bool _hasCrossedANotch(bool forward) const;

protected:
    Wires _wires;

private:
    std::vector<std::size_t> _notches;
    std::size_t              _rotation = 0;

private:
    // Cannot be set to const because the class will become unusable in a std::vector
    // It will loose the MoveAssignable requirement
    bool _allowStraightWire = true;
};
} // !namespace Enigma
