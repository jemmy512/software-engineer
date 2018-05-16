/*
Given a list of non negative integers, arrange them such that they form the largest number.

Example 1:

Input: [10,2]
Output: "210"
Example 2:

Input: [3,30,34,5,9]
Output: "9534330"
Note: The result may be very large, so you need to return a string instead of an integer.
*/

class Solution {
public:
    struct {
        bool operator()(string a, string b) const {   
            return (a+b) > (b+a);
        }   
    } cmp;
    
    function<bool(string &, string &)> iGreater = [](string &a, string &b)->bool{
        return (a+b) > (b+a);
    };
    
    string largestNumber(vector<int> &nums) {
        vector<string> vec(nums.size());
        
        int i = 0;
        for(int n : nums) {
            vec[i++] = to_string(n);
        }
        
        sort(vec.begin(), vec.end(), iGreater);
        
        if (vec[0][0] == '0') // for case "00"
            return "0";
        
        string ret;
        for (string s : vec) {
            ret += s;
        }
        
        return ret;
    }
};