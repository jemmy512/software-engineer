#include <iostream>
#include <array>
#include <vector>

template<size_t Size = 255>
std::array<int, Size> generateBadChars(const std::string& pattern);

void generateGoodSuffix(const std::string& pattern, std::vector<int>& suffix, std::vector<bool>& prefix);
int moveByGoodSuffix(int idx, int len, const std::vector<int>& suffix, const std::vector<bool>& prefix);

/**
 * Boyer Moore Algorithm */
int bmSearch(const std::string& str, const std::string& pattern) {
    const int strLen = str.size();
    const int patLen = pattern.size();

    std::array<int, 255> badChars = generateBadChars(pattern);

    std::vector<bool> prefix(strLen, false);
    std::vector<int> suffix(patLen, -1);
    generateGoodSuffix(pattern, suffix, prefix);

    int i = 0;
    while (i <= strLen - patLen) {
        int j;
        for (j = patLen-1; j >= 0; --j) {
            if (str[i+j] != pattern[j])
                break;
        }

        if (j < 0)
            return i;

        auto x = j - badChars[static_cast<int>(str[i+j])];
        int y = 0;
        if (j < patLen-1) {
            y = moveByGoodSuffix(j, patLen, suffix, prefix);
        }

        i = i + std::max(x, y);
    }

    return -1;
}

template<size_t Size>
std::array<int, Size> generateBadChars(const std::string& pattern) {
    std::array<int, Size> badChars;
    badChars.fill(-1);

    for (auto i = 0; i < pattern.size(); ++i) {
        auto ascii = static_cast<int>(pattern[i]);
        badChars[ascii] = i;
    }

    return badChars;
}

/**
 * Two matches:
 * 1. the good suffix string matches a substing of the pattern(rightmost)
 * 2. a longest good suffix substring matches a prefix substring of the pattern */
void generateGoodSuffix(const std::string& pattern, std::vector<int>& suffix, std::vector<bool>& prefix) {
    auto len = pattern.size();
    for (auto i = 0; i < len-1; ++i) {
        auto j = i;
        auto k = 0;

        while (j >= 0 && pattern[j] == pattern[len-1-k]) {
            suffix[k++] = j--;
        }

        if (j == -1) prefix[k] = true;
    }
}

int moveByGoodSuffix(int idx, int len, const std::vector<int>& suffix, const std::vector<bool>& prefix) {
    int k = len - 1 - idx;
    if (suffix[k] != -1)
        return idx - suffix[k] + 1; // matches case 1

    for (int r = idx+2; r <= len-1; r++) {
        if (prefix[len-r] == true)  // matches case 2
            return r;
    }

    return len;
}


int main() {
    std::string str = "abcacaabdc";
    std::string pattern = "abd";

    auto idx = bmSearch(str, pattern);
    std::cout << idx << std::endl;

    return 0;
}