#include "String.hpp"

std::string String::Idfy(const std::string& str) {
    std::string result;
    result.reserve(str.length());

    tuim::Utf8IterateString(str, [&](char32_t cp, size_t i) {
        char c = ' ';
        switch (cp) {
            // Remove diacritics from Latin small letters.
            case U'á': case U'à': case U'â': case U'ä': case U'ã': case U'å': c = 'a'; break;
            case U'Á': case U'À': case U'Â': case U'Ä': case U'Ã': case U'Å': c = 'A'; break;
            case U'é': case U'è': case U'ê': case U'ë': c = 'e'; break;
            case U'É': case U'È': case U'Ê': case U'Ë': c = 'E'; break;
            case U'í': case U'ì': case U'î': case U'ï': c = 'i'; break;
            case U'Í': case U'Ì': case U'Î': case U'Ï': c = 'I'; break;
            case U'ó': case U'ò': case U'ô': case U'ö': case U'õ': c = 'o'; break;
            case U'Ó': case U'Ò': case U'Ô': case U'Ö': case U'Õ': c = 'O'; break;
            case U'ú': case U'ù': case U'û': case U'ü': c = 'u'; break;
            case U'Ú': case U'Ù': case U'Û': case U'Ü': c = 'U'; break;
            case U'ñ': c = 'n'; break;
            case U'Ñ': c = 'N'; break;
            case U'ç': c = 'c'; break;
            case U'Ç': c = 'C'; break;

            // spaces and apostrophes to underscore.
            case U' ': case U'\'': case U'-': c = '_'; break;

            // Only keep alphanumerical characters.
            default:
                if (cp < 128 && (std::isalnum(static_cast<unsigned char>(cp)) || cp == '_')) c = static_cast<char>(cp);
                else c = '_';
        }
        result.push_back(std::tolower(c));
    });

    return result;
}