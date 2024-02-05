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
        printf("find in %d - %d ,try : %d is  %d\n", st, en, mid, arr[mid]);

        return BinSearch(arr, val, 0, mid - 1);
    }

    if (val > arr[mid])
    {
        printf("find in %d - %d ,try : %d is  %d\n", st, en, mid, arr[mid]);

        return BinSearch(arr, val, mid + 1, en);
    }

    return -1;
};

int main()
{
    int arr[] = {3, 4, 5, 7, 24, 30, 42, 54, 63, 72, 87, 95};
    int len = sizeof(arr) / sizeof(arr[0]);

    int val = 24;
    printf("BinSearch : find %d -> %d\n", val, BinSearch(arr, val, 0, len - 1));

    return 0;
}
