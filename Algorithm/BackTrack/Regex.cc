#include <iostream>

class Regex {
public:
    Regex(const std::string& pattern) : _Pattern(pattern) {}

    bool match(const std::string& target) {
        _IsMatched = false;
        _Match(0, 0, target);
        return _IsMatched;
    }

private:
    void _Match(int tarIdx, int patIdx, const std::string& target) {
        if (_IsMatched)
            return;

        if (patIdx == _Pattern.size()) {
            if (tarIdx == target.size()) {
                _IsMatched = true;
                return;
            }
        }

        if (_Pattern[patIdx] == '*') {
            for (int k = 0; k < target.size() -  tarIdx; ++k) {
                _Match(tarIdx + k, patIdx + 1, target);
            }
        } else if (_Pattern[patIdx] == '?') {
            _Match(tarIdx, patIdx + 1, target);
            _Match(tarIdx + 1, patIdx + 1, target);
        } else if (tarIdx < target.size() && _Pattern[patIdx] == target[tarIdx]) {
            _Match(tarIdx + 1, patIdx + 1, target);
        }
    }

private:
    bool _IsMatched{false};
    const std::string& _Pattern;
};

int main() {
    return 0;
}