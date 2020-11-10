#include <string>
#include <vector>
#include <sstream>

namespace util::string {
    using std::string;

    inline static const string WhileSpace = " \n\r\t\f\v";

    string ltrim(const string& str) {
        auto begin = str.find_first_not_of(WhileSpace);

        return (begin == string::npos) ? "" : str.substr(begin);
    }

    string rtrim(const std::string& str) {
        auto end = str.find_last_not_of(WhileSpace);

        return (end == string::npos) ? "" : str.substr(0, end+1);
    }

    std::string trim(const std::string& str) {
        return rtrim(ltrim(str));
    }

    std::vector<std::string> split(const std::string& str, const char& delimiter) {
        std::vector<std::string> result;
        result.reserve(std::count(str.begin(), str.end(), delimiter) + 1);

        std::string chars;
        std::istringstream iss(str);

        while (std::getline(iss, chars, delimiter)) {
            result.emplace_back(chars);
        }

        return result;
    }

    std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
        std::vector<std::string> result;

        size_t begin = 0;
        size_t end = std::string::npos;

        do {
            begin = (end == std::string::npos) ? 0 : end + 1;
            /* The search considers only the interval [pos, size()).
             * If the character is not present in the interval, npos will be returned. */
            end = str.find_first_of(delimiter, begin);
            auto  token = str.substr(begin, end-begin); // std::out_of_range if pos > size()

            if (!token.empty())
                result.emplace_back(token);
        } while (end != std::string::npos);

        return result;
    }
};