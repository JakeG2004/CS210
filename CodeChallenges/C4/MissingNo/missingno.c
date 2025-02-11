#include <stdio.h>
#include <stdlib.h>

int FindMissingNum(int nums[], int n);

int main()
{
    int nums[] = {2, 3, 5, 10, 9, 8, 6, 4};
    int n = sizeof(nums) / sizeof(int);

    int missingNum = FindMissingNum(nums, n);

    printf("The missing number is: %i\n", missingNum);
}

// Finds missing number with time of O(n) :)
int FindMissingNum(int nums[], int n)
{
    // Store the min and max nums found in the array
    int max = nums[0];
    int min = nums[0];
    
    // Useful values to have
    int expectedSum = 0;
    int actualSum = 0;
    
    // Get sum of array elements
    for(int i = 0; i < n; i++)
    {
        // Find the min of the array
        if(nums[i] < min)
        {
            min = nums[i];
        }

        // Find the max of the array
        if(nums[i] > max)
        {
            max = nums[i];
        }

        // Calculate a running sum with the array
        actualSum += nums[i];
    }

    // Use modified gaussian summation formula to calculate expected sum
    expectedSum = (max - min + 1) * (max + min) / 2;

    return expectedSum - actualSum;
}