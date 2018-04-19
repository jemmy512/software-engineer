/*
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
*/
#include<iostream>
#include<vector>

// 29ms, beat 79.71%
class MinStack {
private:
    // pair.first stores current insert number x, 
    // pair.second stores the position of min when x inserted
    vector<pair<int, int>> work{{INT_MAX, 0}};
public:    
    MinStack() { }
    
    void push(int x) {
        auto tmp = work.back();
        if(x < work[tmp.second].first){
            work.push_back({x, work.size()});
        }else{
            work.push_back({x, tmp.second});
        }
    }

    void pop() {        
        work.pop_back();
    }

    int top() {
        return work.back().first;
    }

    int getMin() {
        int pos = work.back().second;
        return work[pos].first;
    }
};

// 31ms, beat 47.96%
class MinStack_1 {
private:
    vector<int> data;   // store real numbers
    vector<int> order;  // store minal numbers 
    /*
        If we push following numbers:
            5 1 1 2 3 2
        order statck will be:
            5 1 1 [only store number which <= current minal number]
    */
public:
    MinStack() { }
    
    void push(int x) {
        data.push_back(x);
        if (order.empty() || x <= order.back())
            order.push_back(x);
    }
    
    void pop() {
        if (data.back() == order.back())
            order.pop_back();
        data.pop_back();
    }
    
    int top() {
        return data.back();
    }
    
    int getMin() {
        return order.back();
    }
};