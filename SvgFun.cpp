#include "SvgFun.h"

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