#include <iostream>
#include <string>
#include <vector>

class ASensitiveWordsFilter {
public:
    std::string filterSexWords(const std::string& words) {
        return "[A] filter sex words.\n" + words;
    }

    std::string filterPoliticalWords(const std::string& words) {
        return "[A] filter political words.\n" + words;
    }
};

class BSensitiveWordsFilter {
public:
    std::string filter(const std::string& words) {
        return "[B] general filter.\n" + words;
    }
};

class ISensitiveWordsFilter {
public:
    virtual std::string filter(const std::string& words) = 0;
    virtual ~ISensitiveWordsFilter() = default;
};

// Object Adaptor
class ASensitiveWordsFilterAdaptor : public ISensitiveWordsFilter {
public:
    std::string filter(const std::string& words) {
        auto ret =  mFilter.filterSexWords(words);
        return mFilter.filterPoliticalWords(ret);
    }

private:
    ASensitiveWordsFilter mFilter;
};

// Class Adaptor
class BSensitiveWordsFilterApdator : public BSensitiveWordsFilter, public ISensitiveWordsFilter {
public:
    std::string filter(const std::string& words) override {
        return BSensitiveWordsFilter::filter(words);
    }
};


class RiskManagement {
public:
    RiskManagement& registerFilter(std::shared_ptr<ISensitiveWordsFilter>& filter) {
        auto ite = std::find_if(mFilters.cbegin(), mFilters.cend(), [&filter](const auto& item) {
                return item == filter;
            });
        if (ite == mFilters.cend()) {
            mFilters.push_back(filter);
        }

        return *this;
    }

    std::string filter(const std::string& msg) {
        std::string result = msg;

        for (const auto& filter : mFilters) {
            result = filter->filter(result);
        }

        return result;
    }

private:
    std::vector<std::shared_ptr<ISensitiveWordsFilter>> mFilters;
};


int main() {
    auto filterA = std::dynamic_pointer_cast<ISensitiveWordsFilter>(std::make_shared<ASensitiveWordsFilterAdaptor>());
    auto filterB = std::dynamic_pointer_cast<ISensitiveWordsFilter>(std::make_shared<BSensitiveWordsFilterApdator>());

    RiskManagement riskManagement;
    riskManagement.registerFilter(filterA).registerFilter(filterB);


    auto result = riskManagement.filter("");
    std::cout << result << std::endl;

    return 0;
}

/**
 * Adapter category:
 * 1. Class adapter: implemented by inheritance when adapter have many same interfaces with adaptee.
 * 2. Object adapter: implemented by composing when addapter doesn't have many same interfaces with adaptee.
 * 
 * Scenarios:
 * 1. Encapsulat interfaces that have defective design
 * 2. Unify interface design for multiple classes
 * 3. Replace external dependent systems
 * 4. Compatible with older versions of the interface
 * 5. Adapt data in different formats
 */ 