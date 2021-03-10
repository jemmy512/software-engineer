/* Easy
You have an array of logs.  Each log is a space delimited string of words.

For each log, the first word in each log is an alphanumeric identifier.  Then, either:
Each word after the identifier will consist only of lowercase letters, or;
Each word after the identifier will consist only of digits.

We will call these two varieties of logs letter-logs and digit-logs.
It is guaranteed that each log has at least one word after its identifier.

Reorder the logs so that all of the letter-logs come before any digit-log.
The letter-logs are ordered lexicographically ignoring identifier, with the identifier used in case of ties.
The digit-logs should be put in their original order.

Return the final order of the logs.

Example 1:
Input: logs = ["dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero"]
Output: ["let1 art can","let3 art zero","let2 own kit dig","dig1 8 1 5 1","dig2 3 6"]

Constraints:
0 <= logs.length <= 100
3 <= logs[i].length <= 100
logs[i] is guaranteed to have an identifier, and a word after the identifier. */

#include <cctype> // std::isalpha
#include <vector>
#include <string>
#include <string_view>

using namespace std;

/* Time Complexity: O(MNlogN)
 * Space Complexity: O(MlogN) */
class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<string> digitLog, result;
        vector<pair<string_view, string_view>> letterLog;
        digitLog.reserve(logs.size());
        result.reserve(logs.size());
        letterLog.reserve(logs.size());

        for (const auto& log : logs) {
            auto pos = log.find(" ");
            if (isalpha(log[pos+1])) {
                letterLog.emplace_back(
                    string_view(log.data(), pos+1),
                    string_view(log.data()+pos+1, log.size()-pos));
                // letterLog.emplace_back( // c++20
                //     string_view(log.begin(), log.begin()+pos)),
                //     string_view(log.begin()+pos, log.end()));
            } else {
                digitLog.emplace_back(log);
            }
        }

        std::sort(letterLog.begin(), letterLog.end(), [](const auto& lhs, const auto& rhs) {
            if (lhs.second < rhs.second) {
                return true;
            } else if (lhs.second > rhs.second) {
                return false;
            } else {
                return lhs.first < rhs.first;
            }
        });

        std::transform(letterLog.begin(), letterLog.end(), std::back_inserter(result), [](const auto& log) {
            return string(log.first.begin(), log.first.begin() + log.first.size() + log.second.size());
        });

        result.insert(result.end(), digitLog.begin(), digitLog.end());

        return result;
    }
};