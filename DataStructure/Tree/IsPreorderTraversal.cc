#include<iostream>

bool verifyPreorder(int sequence[], int length) {
    if (sequence == NULL || length <= 0)
        return false;

    int root = sequence[0];

    // determin the range of left sub-tree
    int rootRight = 1;
    for (; rootRight < length && sequence[rootRight] > root; ++rootRight);

    // make sure right sub-tree greater than root
    for (int j = rootRight; j < length; j++) {
        if (sequence[j] < root)
            return false;
    }

    // verify left sub-tree is binary search tree
    bool leftOk{true};
    if (rootRight > 1)
        leftOk = verifyPreorder(sequence+1, rootRight-1);

    // verify right sub-tree is binary search tree
    bool rightOk{true};
    if (rootRight < length)
        rightOk = verifyPreorder(sequence+rootRight, length-rootRight);

    return (leftOk && rightOk);
}

int main(void)
{
    int a[7] = {8,6,5,7,10,9,11};
    bool result = verifyPreorder(a,7);
    std::cout << (result ? "Yes, it's sequence Of AST" : "No,it's not.") << std::endl;
    return 0;
}
