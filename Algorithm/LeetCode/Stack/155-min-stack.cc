/* Easy
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.

Example:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2. 

Constraints:
-2^31 <= val <= 2^31 - 1
Methods pop, top and getMin operations will always be called on non-empty stacks.
At most 3 * 104 calls will be made to push, pop, top, and getMin. */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class MinStack {
public:    
    MinStack() = default;
    
    void push(int x) {
        _Data.emplace_back(x, [this, x]() -> std::size_t {
            if (_Data.empty()) {
                return 0;
            }
            const auto& [val, pos] = _Data.back();
            return (x < _Data[pos].first) ? _Data.size() : pos;
        }());
    }

    void pop() {    
        if (_Data.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        _Data.pop_back();
    }

    int top() {
        if (_Data.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return _Data.back().first;
    }

    int getMin() {
        if (_Data.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return _Data[_Data.back().second].first;
    }

private:
    vector<pair<int, std::size_t>> _Data;
};