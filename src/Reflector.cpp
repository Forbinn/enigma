#include "Reflector.hpp"

Enigma::Reflector::Reflector()
    : Rotor { false }
{
}

Enigma::Reflector::Reflector(string_view alphabet)
    : Rotor { false }
{
    setAlphabet(alphabet);
}

Enigma::Reflector::Reflector(Standard r)
    : Reflector { alphabetOfStandardReflector(r) }
{
}

bool Enigma::Reflector::isValid() const
{
    return Rotor::isValid() && _wires.size() % 2 == 0;
}

bool Enigma::Reflector::rotate(bool)
{
    // Calling rotate on a reflector is a no-op
    return false;
}

Enigma::string_view Enigma::Reflector::alphabetOfStandardReflector(Standard r)
{
    switch (r)
    {
        case Enigma::Reflector::Standard::D_UKW:
            return "IMETCGFRAYSQBZXWLHKDVUPOJN";
        case Enigma::Reflector::Standard::I_UKW_A:
            return "EJMZALYXVBWFCRQUONTSPIKHGD";
        case Enigma::Reflector::Standard::I_UKW_B:
            return "YRUHQSLDPXNGOKMIEBFZCWVJAT";
        case Enigma::Reflector::Standard::I_UKW_C:
            return "FVPJIAOYEDRZXWGCTKUQSBNMHL";
        case Enigma::Reflector::Standard::NORENIGMA_UKW:
            return "MOWJYPUXNDSRAIBFVLKZGQCHET";
        case Enigma::Reflector::Standard::SONDER_UKW:
            return "CIAGSNDRBYTPZFULVHEKOQXWJM";
        case Enigma::Reflector::Standard::M3_UKW_B:
            return "YRUHQSLDPXNGOKMIEBFZCWVJAT";
        case Enigma::Reflector::Standard::M3_UKW_C:
            return "FVPJIAOYEDRZXWGCTKUQSBNMHL";
        case Enigma::Reflector::Standard::M4_BETA:
            return "LEYJVCNIXWPBQMDRTAKZGFUHOS";
        case Enigma::Reflector::Standard::M4_GAMMA:
            return "FSOKANUERHMBTIYCWLQPZXVGJD";
        case Enigma::Reflector::Standard::M4_UKW_B:
            return "ENKQAUYWJICOPBLMDXZVFTHRGS";
        case Enigma::Reflector::Standard::M4_UKW_C:
            return "RDOBJNTKVEHMLFCWZAXGYIPSUQ";
        case Enigma::Reflector::Standard::G_UKW:
            return "IMETCGFRAYSQBZXWLHKDVUPOJN";
        case Enigma::Reflector::Standard::G312_UKW:
            return "RULQMZJSYGOCETKWDAHNBXPVIF";
        case Enigma::Reflector::Standard::G260_UKW:
            return "IMETCGFRAYSQBZXWLHKDVUPOJN";
        case Enigma::Reflector::Standard::K_UKW:
            return "IMETCGFRAYSQBZXWLHKDVUPOJN";
        case Enigma::Reflector::Standard::SWISSK_UKW:
            return "IMETCGFRAYSQBZXWLHKDVUPOJN";
        case Enigma::Reflector::Standard::KD_UKW:
            return "NSUOMKLIHZFGEADVXWBYCPRQTJ";
        case Enigma::Reflector::Standard::RAILWAY_UKW:
            return "QYHOGNECVPUZTFDJAXWMKISRBL";
        case Enigma::Reflector::Standard::T_UKW:
            return "GEKPBTAUMOCNILJDXZYFHWVQSR";
        case Enigma::Reflector::Standard::Z_UKW:
            return "5079183642";
    }

    return {};
}
