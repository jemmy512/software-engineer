#include<iostream>
using  namespace std;
int BinarySearch(int *array, int aSize, int key)
{
    if ( array == NULL || aSize == 0 )
        return -1;

    int low = 0;
    int high = aSize - 1;
    int mid = 0;

    while ( low <= high )
    {
        mid = (low + high )/2;

        if ( array[mid] < key)
            low = mid + 1;
        else if ( array[mid] > key )
            high = mid - 1;
        else
            return mid;
    }
    return low;//如果没有找到，该数字应该所在下标为 low；
}

int main(void)
{
    int a[17]={0,2,3,5,6,7,8,9,10,11,12,13,14,15,16,20};

    int result=BinarySearch(a,17,4);
    cout<<result<<endl;
    return 0;

}
