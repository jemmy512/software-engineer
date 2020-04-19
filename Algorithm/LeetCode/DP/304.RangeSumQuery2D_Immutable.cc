/*
Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by 
its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) 
and (row2, col2) = (4, 3), which contains sum = 8.

Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12
Note:
You may assume that the matrix does not change.
There are many calls to sumRegion function.
You may assume that row1 ≤ row2 and col1 ≤ col2.
*/

#include<iostream>
#include<vector>
using namespace std;

// 12 test cases, 24ms, beat 62.05%
class NumMatrix {
private:
    vector<vector<int>> data;
public:
    NumMatrix(vector<vector<int>> matrix) {
        int row = matrix.size();
        int col = row > 0 ? matrix[0].size() : 0;
        ++row;
        ++col;
        data = vector<vector<int>>(row, vector<int>(col, 0));
        for (int i = 1; i < row; ++i) {
            for (int j = 1; j < col; ++j) {
                data[i][j] = data[i][j-1] + data[i-1][j] + matrix[i-1][j-1] - data[i-1][j-1];
            }
        }
    }
    
    void print() {
        for (int i = 0; i < data.size(); ++i) {
            for (int j = 0; j < data[0].size(); ++j) {
                printf("%4d ", data[i][j]);
            }
            cout << endl;
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return data[row2+1][col2+1] - data[row2+1][col1] - data[row1][col2+1] + data[row1][col1];
    }
};
/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * int param_1 = obj.sumRegion(row1,col1,row2,col2);
 */
 
int main() {
    vector<vector<int>> vec = {
        {3, 0, 1, 4, 2},
        {5, 6, 3, 2, 1},
        {1, 2, 0, 1, 5},
        {4, 1, 0, 1, 7},
        {1, 0, 3, 0, 5}
    };
    NumMatrix na(vec);
    na.print();
}