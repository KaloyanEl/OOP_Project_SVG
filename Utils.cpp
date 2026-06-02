#include "Utils.h"
/*
Функции улесняващи програмата и многократно писане на код.
Не са в специфичен клас, защото са важна част от няколко нива
в архитектурата.
*/


// Взима информацията между кавички в token
std::string extractToken(const std::string& token) {

    size_t first = token.find('"');
    if (first == token.npos) {
        return "";
    }
    size_t last = token.find('"', first + 1);
    if (last == token.npos) {
        return "";
    }
    return token.substr(first + 1, last - first - 1);
}
// Маха излишни интервали между равното и атрибута и стойността.
void normalize(std::string& s) {
    while (s.find("= ") != std::string::npos) {
        s.replace(s.find("= "), 2, "=");
    }
    while (s.find(" =") != std::string::npos) {
        s.replace(s.find(" ="), 2, "=");
    }
}