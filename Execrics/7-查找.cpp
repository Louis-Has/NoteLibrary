#include <iostream>

using namespace std;

// （1）试写出折半查找的递归算法。

// int getBinSearch(int arr[], int val)
// {
//     return sizeof(arr) / sizeof(arr[0]);
// };

int BinSearch(int arr[], int val, int st, int en)
{
    if (st > en)
    {
        return -1;
    }

    int mid = (st + en) / 2;

    if (arr[mid] == val)
    {
        return mid;
    }

    if (val < arr[mid])
    {
        // printf("find in %d - %d ,try : %d is < %d\n", st, en, val, arr[mid]);

        return BinSearch(arr, val, 0, mid - 1);
    }

    if (val > arr[mid])
    {
        // printf("find in %d - %d ,try : %d is > %d\n", st, en, val, arr[mid]);

        return BinSearch(arr, val, mid + 1, en);
    }

    return -1;
};

int main()
{
    int arr[] = {1, 2, 4, 7, 8, 9, 12, 14, 16, 19};

    int val = 8;
    printf("BinSearch : find %d -> %d\n", val, BinSearch(arr, val, 0, sizeof(arr) / sizeof(arr[0])));

    return 0;
}
