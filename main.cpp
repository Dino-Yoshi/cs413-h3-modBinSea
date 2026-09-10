//
// Author: DinoYoshi/Darien
// NetID: ub7890
//

/* ASSIGNMENT INFO
   Given an array of integers nums sorted in ascending order, find the starting and ending position of a given
    target value. If target is not found in the array, return [-1, -1]. You must write an algorithm with O(log(n))
    run time complexity, implement your algorithm in your favorite language.
    Example:
    Input: nums = [5,7,7,8,8,10], target = 8
    Output: [3,4]
    Input: nums = [5,7,7,8,8,10], target = 6
    Output: [-1,-1]
    Submit your code file. You can use AI to help you but be sure work on it before you use AI’s solution.
 */

/* PSEUDOCODE
 * intptr binSea(array, desiredValue)
        l <- 0
        r <- array.Size() - 1
        while (l < r)
            mid = (l + r) / 2
            if array[mid] == desiredValue
                ans[] <- new [2]
                ans[0] <- mid
                ans[1] <- mid + 1
                return ans
            else if array[mid] > desiredValue
                r <- mid
            else
                l <- mid
        ans[] <- new [2]
        ans[0] <- -1
        ans[1] <- -1
        return ans
 */

#include <iostream>
using namespace std;

// Basic Binary Search implementation with O(log(n)) complexity time
// Only modification is that it returns a set of integers inside of an array.
// Time Complexity O(log(n))
int* binSea(int desiredValue, const int arr[], int arrSize) {
    int l = 0; // left pointer
    int r = arrSize - 1; // right pointer

    // assume the value doesn't exist at the beginning
    int* ans = new int[2];
    ans[0] = -1;
    ans[1] = -1;

    while (l <= r) {
        int mid = (l + r) / 2;
        if (arr[mid] == desiredValue) { // update if we find it, but don't immediately return.
            ans[0] = mid;
            r = mid - 1; // decrement if found to find another first occurance.
        }
        else if (arr[mid] > desiredValue) {
            r = mid - 1; // if we're above the value, set the right pointer one under the ind we calc
        }
        else {
            l = mid + 1; // if we're below the value, set the left pointer one above the ind we calc
        }
    }

    l = 0;
    r = arrSize - 1;

    while (l <= r) {
        int mid = (l + r) / 2;
        if (arr[mid] == desiredValue) { // update if we find it, but don't immediately return.
            ans[1] = mid;
            l = mid + 1; // decrement if found to find another first occurance.
        }
        else if (arr[mid] > desiredValue) {
            r = mid - 1; // if we're above the value, set the right pointer one under the ind we calc
        }
        else {
            l = mid + 1; // if we're below the value, set the left pointer one above the ind we calc
        }
    }

    return ans; // return the earliest occurance
}


int main(int argc, char** argv) {


    // int arr[] = {1, 1, 1, 1, 1, 9, 9, 9};
    //
    // int n = sizeof(arr) / sizeof(arr[0]);
    //
    // int* ans = binSea(3, arr, n);
    //
    // cout << ans[0] << " " << ans[1] << endl;
    // cout << "expected: -1,-1" << endl;



    return 0;
}
