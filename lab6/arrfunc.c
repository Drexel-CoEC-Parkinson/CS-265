/* arrfunc.c -- passing an array to a function */
#include <stdio.h>

void fill(int arr[], int n, int value)
{
    for (int i = 0; i < n; i++)
        arr[i] = value;
}

int sum(int arr[], int n)
{
    int total = 0;
    for (int i = 0; i < n; i++)
        total += arr[i];
    return total;
}

void show_size(int arr[])
{
    printf("inside show_size: %zu\n", sizeof arr);
}

int main(void)
{
    int nums[4] = {1, 2, 3, 4};

    printf("before: %d %d %d %d\n", nums[0], nums[1], nums[2], nums[3]);
    fill(nums, 4, 7);
    printf("after:  %d %d %d %d\n", nums[0], nums[1], nums[2], nums[3]);

    printf("sum of 4: %d\n", sum(nums, 4));
    printf("sum of 2: %d\n", sum(nums, 2));

    printf("in main: %zu\n", sizeof nums);
    show_size(nums);

    return 0;
}
