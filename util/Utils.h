//
// Created by qnocks on 3/25/21.
//

#ifndef MPO_1_UTILS_H
#define MPO_1_UTILS_H


#include <vector>
#include <iostream>
#include <limits>

class Utils {
public:
    static bool isStreamValid() {
        if (std::cin.fail() || std::cin.bad()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            return false;
        }
        return true;
    }

    static std::vector<std::string> split(const std::string& str, const std::string& delim) {
        std::vector<std::string> tokens;
        size_t prev = 0, pos = 0;
        do {
            pos = str.find(delim, prev);
            if (pos == std::string::npos) pos = str.length();
            std::string token = str.substr(prev, pos - prev);
            if (!token.empty()) tokens.push_back(token);
            prev = pos + delim.length();
        } while (pos < str.length() && prev < str.length());
        return tokens;
    }

    static bool compare(const std::string& s1, const std::string& s2) {
        return false;
    }

};


#endif //MPO_1_UTILS_H
