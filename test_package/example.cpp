#include <iostream>

#include <enigma/Machine.hpp>

int main()
{
    auto m = Enigma::Machine::buildRandomMachine();
    const auto enc = m.convert('a');

    std::cout << "Encoding of character 'a' gave '" << enc << "'" << std::endl;
    return 0;
}
