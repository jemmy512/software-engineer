/* Easy
A website domain like "discuss.leetcode.com" consists of various subdomains.
At the top level, we have "com", at the next level, we have "leetcode.com",
and at the lowest level, "discuss.leetcode.com". When we visit a domain like "discuss.leetcode.com",
we will also visit the parent domains "leetcode.com" and "com" implicitly.

Now, call a "count-paired domain" to be a count (representing the number of visits this domain received),
followed by a space, followed by the address.
An example of a count-paired domain might be "9001 discuss.leetcode.com".

We are given a list cpdomains of count-paired domains. We would like a list of count-paired domains,
(in the same format as the input, and in any order),
that explicitly counts the number of visits to each subdomain.

Example 1:
Input:
["9001 discuss.leetcode.com"]
Output:
["9001 discuss.leetcode.com", "9001 leetcode.com", "9001 com"]
Explanation:
We only have one website domain: "discuss.leetcode.com". As discussed above,
the subdomain "leetcode.com" and "com" will also be visited. So they will all be visited 9001 times.

Example 2:
Input:
["900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org"]
Output:
["901 mail.com","50 yahoo.com","900 google.mail.com","5 wiki.org","5 org","1 intel.mail.com","951 com"]
Explanation:
We will visit "google.mail.com" 900 times, "yahoo.com" 50 times,
"intel.mail.com" once and "wiki.org" 5 times. For the subdomains,
we will visit "mail.com" 900 + 1 = 901 times, "com" 900 + 50 + 1 = 951 times, and "org" 5 times.

Notes:
The length of cpdomains will not exceed 100.
The length of each domain name will not exceed 100.
Each address will have either 1 or 2 "." characters.
The input count in any count-paired domain will not exceed 10000.
The answer output can be returned in any order. */

#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        for (const auto& countDomain : cpdomains) {
            size_t pos;
            auto count = std::stoi(countDomain, &pos);
            while (pos != std::string::npos) {
                auto domain = countDomain.substr(pos+1);
                _DomainCount[domain] += count;
                pos = countDomain.find(".", pos+1);
            }
        }

        return composeResult();
    }

private:
    vector<string> composeResult() const {
        vector<string> result;
        result.reserve(_DomainCount.size());

        for (const auto& [domain, count] : _DomainCount) {
            result.emplace_back(std::to_string(count) + " " + domain);
        }

        return result;
    }

private:
    unordered_map<string, int> _DomainCount;
};

class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        if (cpdomains.empty())
            return {};

        for (const auto& countDomain : cpdomains) {
            auto [count, domain] = splitCountDomain(countDomain);
            auto domains = splitDomain(domain, '.');
            for (const auto& d : domains) {
                _DomainCount[d] += count;
            }
        }

        return composeResult();
    }

private:
    pair<int, string> splitCountDomain(const string& domain) {
        auto pos = domain.find(' ');
        auto count = std::stoi(domain.substr(0, pos));
        auto dom = domain.substr(pos+1);
        return {count, dom};
    }

    vector<string> splitDomain(const string& str, char delimiter) {
        vector<string> result;
        size_t end = std::string::npos;

        while ((end = str.find_last_of(delimiter, end-1)) != std::string::npos) {
            auto token = str.substr(end+1);
            if (!token.empty()) {
                result.emplace_back(token);
            }
        }
        result.emplace_back(str);

        return result;
    }

    vector<string> splitDomain_0(const string& str, char delimiter) {
        vector<string> result;
        std::istringstream iss(str);
        string line;

        while (std::getline(iss, line, delimiter)) {
            result.emplace_back(line);
        }

        for (auto iter = result.rbegin()+1; iter != result.rend(); ++iter) {
            *iter += "." + *(iter-1);
        }

        return result;
    }

    vector<string> splitDomain_1(const string& patter, char delimiter) {
        vector<string> result;
        vector<int> posation;

        size_t pos = -1;
        while ((pos = patter.find(delimiter, pos+1)) != std::string::npos) {
            posation.emplace_back(pos);
        }

        for (auto iter = posation.crbegin(); iter != posation.crend(); ++iter) {
            result.emplace_back(patter.substr(*iter+1));
        }
        result.emplace_back(patter);

        return result;
    }

    vector<string> splitDomain_2(const string& str, const string& delimiter) {
        vector<string> result;
        size_t beg = 0;
        size_t end = -1;

        do {
            beg = end + 1;
            end = str.find(delimiter, beg);
            auto token = str.substr(beg, end-beg);
            if (!token.empty()) {
                result.emplace_back(token);
            }
        } while (end != std::string::npos);

        for (auto iter = result.rbegin()+1; iter != result.rend(); ++iter) {
            *iter += "." + *(iter-1);
        }

        return result;
    }

    vector<string> composeResult() const {
        vector<string> result;

        for (const auto& [domain, count] : _DomainCount) {
            result.emplace_back(std::to_string(count) + " " + domain);
        }

        return result;
    }

private:
    unordered_map<string, int> _DomainCount;
};