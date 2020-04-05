#include<iostream>

class Queen {
public:
    void calculateQueen(int i = 0) {
        for (int j = 0; j < 8; j++) {
            if (!col[j] && !left[i+j] && !right[i-j+7]) {
                row[i] = j;
                col[j] = left[i+j] = right[i-j+7] = 1;

                if (i < 7)
                    calculateQueen(i+1);
                else
                    printQueen();

                col[j] = left[i+j] = right[i-j+7] = 0;
            }
        }
    }

    void printQueen() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (j == row[i])
                    std::cout << "O ";
                else
                    std::cout << "- ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
private:
    int row[8]{0};
    int col[8]{0};
    bool left[15]{false};
    bool right[15]{false};
};

int main(void)
{
    Queen queen;
    queen.calculateQueen();

    return 0;
}
