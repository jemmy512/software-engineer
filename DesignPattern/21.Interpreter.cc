/* Author: Jemmy
 * Date: 2020-04-18 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

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
            end = str.find_first_of(delimiter, begin);
            auto  token = str.substr(begin, end-begin);

            if (!token.empty())
                result.emplace_back(token);
        } while (end != std::string::npos);

        return result;
    }
};

inline constexpr char GreatOperator = '>';
inline constexpr char LessOperator = '<';
inline std::string EqualOpertor = "==";
inline std::string AndOpertor = "&&";
inline std::string OrOperator = "||";

class IExpression {
public:
    virtual bool interpret(const std::map<std::string, long>& states) const = 0;
    virtual ~IExpression() = default;
};
using IExpressionPtr = std::shared_ptr<IExpression>;


class GreatExpress : public IExpression {
public:
    GreatExpress(const std::string& expression) {
        const auto& items = util::string::split(expression, GreatOperator);
        if (items.size() < 2)
            throw std::runtime_error("Greate Expression is invalid: " + expression);

        mKey = util::string::trim(items[0]);
        mValue = std::stol(util::string::trim(items[1]));
    }

    bool interpret(const std::map<std::string, long>& states) const override {
        const auto& ite = states.find(mKey);
        if (ite != states.end()) {
            return ite->second > mValue;
        } else {
            return false;
        }
    }

private:
    std::string mKey;
    long mValue;
};
using GreatExpressPtr = std::shared_ptr<GreatExpress>;


class LessExpress : public IExpression {
public:
    LessExpress(const std::string& expression) {
        const auto& items = util::string::split(expression, LessOperator);
        if (items.size() < 2)
            throw std::runtime_error("Less Expression is invalid: " + expression);

        mKey = util::string::trim(items[0]);
        mValue = std::stol(util::string::trim(items[1]));
    }

    bool interpret(const std::map<std::string, long>& states) const override {
        const auto& ite = states.find(mKey);
        if (ite != states.end()) {
            return ite->second < mValue;
        } else {
            return false;
        }
    }

private:
    std::string mKey;
    long mValue;
};
using LessExpressPtr = std::shared_ptr<LessExpress>;


class EqualExpress : public IExpression {
public:
    EqualExpress(const std::string& expression) {
        const auto& items = util::string::split(expression, EqualOpertor);
        if (items.size() < 2)
            throw std::runtime_error("Equal Expression is invalid: " + expression);

        mKey = util::string::trim(items[0]);
        mValue = std::stol(util::string::trim(items[1]));
    }

    bool interpret(const std::map<std::string, long>& states) const override {
        const auto& ite = states.find(mKey);
        if (ite != states.end()) {
            return ite->second == mValue;
        } else {
            return false;
        }
    }

private:
    std::string mKey;
    long mValue;
};
using EqualExpressPtr = std::shared_ptr<EqualExpress>;


class AndExpression : public IExpression {
public:
    AndExpression(const std::string& expression) {
        auto splits = util::string::split(expression, AndOpertor);

        for (auto& expr : splits) {
            expr = util::string::trim(expr);
            if (expr.find("<") != std::string::npos) {
                mExpressions.emplace_back(std::make_shared<LessExpress>(expr));
            } else if (expr.find(">") != std::string::npos) {
                mExpressions.emplace_back(std::make_shared<GreatExpress>(expr));
            } else if (expr.find("==") != std::string::npos) {
                mExpressions.emplace_back(std::make_shared<EqualExpress>(expr));
            } else {
                throw std::runtime_error("And 2 Expression is invalid: " + expr);
            }
        }
    }

    bool interpret(const std::map<std::string, long>& states) const override {
        for (const auto& expr : mExpressions) {
            if (expr->interpret(states) == false)
                return false;
        }

        return true;
    }

private:
    std::vector<IExpressionPtr> mExpressions;
};
using AndExpressionPtr = std::shared_ptr<AndExpression>;


class OrExpression : public IExpression {
public:
    OrExpression(const std::string& expression) {
        auto splits = util::string::split(expression, OrOperator);
        if (splits.size() < 2)
            throw std::runtime_error("Or Expression less than two args: " + expression);

        for (auto& expr : splits) {
            expr = util::string::trim(expr);
            mExpressions.emplace_back(std::make_shared<AndExpression>(expr));
        }
    }

    bool interpret(const std::map<std::string, long>& states) const override {
        for (const auto& expr : mExpressions) {
            if (expr->interpret(states))
                return true;
        }

        return false;
    }

private:
    std::vector<IExpressionPtr> mExpressions;
};
using OrExpressionPtr = std::shared_ptr<OrExpression>;


class AlertRuleInterpreter {
public:
    AlertRuleInterpreter(const std::string& expr) : mExpression(std::make_shared<OrExpression>(expr)) { }

    bool interpret(const std::map<std::string, long>& states) {
        return mExpression->interpret(states);
    }

private:
    IExpressionPtr mExpression;
};


void TestUtil() {
    std::vector<std::string> vec{"000", "  12,", "13, ", " 14 , 45 * 90", "  ,  , ,, "};

    for (const auto& str : vec) {
        auto splits = util::string::split(str, ",");
        for (auto& expr : splits) {
            expr = util::string::trim(expr);
            std::cout << expr << " ";
        }
        std::cout << std::endl;
    }
}

void TestInterpreter() {
    std::string rule = "key1 > 100 && key2 < 30 || key3 < 100 || key4 == 88";
    AlertRuleInterpreter interpreter{rule};

    std::map<std::string, long> states;
    states.emplace("key1", 101);
    states.emplace("key2", 10);
    states.emplace("key3", 121);
    states.emplace("key4", 880);

    std::cout << "Alert: " << interpreter.interpret(states) << std::endl;
}

int main() {
    TestUtil();

    TestInterpreter();
    return 0;
}

/**
 * Interpreter pattern is used to defines a grammatical representation for a language
 * and provides an interpreter to deal with this grammar.
 *
 *
 * The main purpose of the design pattern is to deal with the complexity of the code.
 *
 * The core idea of interpreting pattern is to split the work of parsing classes into
 * various small classes to avoid large and complete classes. */