#include<iostream>

bool verifyPostorder(int sequence[], int length) {
    if (sequence == nullptr || length <= 0)
        return false;

    int root = sequence[length-1];

    int rootRight = 0;
    for (; rootRight < length-1 && sequence[rootRight] < root; ++rootRight);

    // make sure right sub-tree greater than root
    for (int j = rootRight; j < length-1; ++j) {
        if (sequence[j] < root)
            return false;
    }

    bool leftOk{true};
    if (rootRight > 0)
        leftOk = verifyPostorder(sequence, rootRight);

    bool rightOk{true};
    if (rootRight < length-1)
        rightOk = verifyPostorder(sequence+rootRight, length-rootRight-1);

    return leftOk && rightOk;
}

int main(void)
{
    int a[6] = {6, 7, 6, 9, 10, 8};
    bool result = verifyPostorder(a, 6);
    std::cout << (result ? "Yes, it's sequence Of BST" : "No,it's not.") << std::endl;
    return 0;
}
