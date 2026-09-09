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

#include <array>
#include <climits>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <bits/stdc++.h>
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
            ans[1] = mid + 1;
            r = mid - 1; // decrement if found to find another first occurance.
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

// Generated Using Codex (GPT-5.6-sol)
struct BinSeaTestCase {
    string name;
    vector<int> nums;
    int target;
    int expectedStart;
    int expectedNext;
};

// Generated Using Codex (GPT-5.6-sol)
void PrintTo(const BinSeaTestCase& test, ostream* output) {
    *output << "{ name = " << test.name << ", nums = [";
    for (size_t i = 0; i < test.nums.size(); ++i) {
        *output << test.nums[i];
        if (i + 1 != test.nums.size()) {
            *output << ", ";
        }
    }
    *output << "], target = " << test.target
            << ", expected = [" << test.expectedStart
            << ", " << test.expectedNext << "] }";
}

// Generated Using Codex (GPT-5.6-sol)
ostream& operator<<(ostream& output, const BinSeaTestCase& test) {
    PrintTo(test, &output);
    return output;
}

// Generated Using Codex (GPT-5.6-sol)
class BinSeaTest : public testing::TestWithParam<BinSeaTestCase> {};

TEST_P(BinSeaTest, ReturnsStartingIndexAndNextIndex) {
    const BinSeaTestCase& test = GetParam();
    vector<int> nums = test.nums;
    unique_ptr<int[]> actual(binSea(test.target, nums.data(), static_cast<int>(nums.size())));

    EXPECT_EQ(test.expectedStart, actual[0])
        << "Wrong starting index for " << test;
    EXPECT_EQ(test.expectedNext, actual[1])
        << "Second result must equal start + 1 for " << test;
}

INSTANTIATE_TEST_SUITE_P(
    AllCases,
    BinSeaTest,
    testing::Values(
        BinSeaTestCase{"sample_target_8", {5, 7, 7, 8, 8, 10, 12, 14}, 8, 3, 4},
        BinSeaTestCase{"sample_target_7", {5, 7, 7, 8, 8, 10, 12, 14}, 7, 1, 2},
        BinSeaTestCase{"sample_missing_6", {5, 7, 7, 8, 8, 10, 12, 14}, 6, -1, -1},
        BinSeaTestCase{"single_at_start", {1, 3, 5, 7, 9, 11, 13, 15}, 1, 0, 1},
        BinSeaTestCase{"single_in_middle", {1, 3, 5, 7, 9, 11, 13, 15}, 7, 3, 4},
        BinSeaTestCase{"single_at_end", {1, 3, 5, 7, 9, 11, 13, 15}, 15, 7, 8},
        BinSeaTestCase{"missing_below_min", {1, 3, 5, 7, 9, 11, 13, 15}, 0, -1, -1},
        BinSeaTestCase{"missing_above_max", {1, 3, 5, 7, 9, 11, 13, 15}, 16, -1, -1},
        BinSeaTestCase{"missing_between_values", {1, 3, 5, 7, 9, 11, 13, 15}, 8, -1, -1},
        BinSeaTestCase{"all_values_equal", {4, 4, 4, 4, 4, 4, 4, 4}, 4, 0, 1},
        BinSeaTestCase{"two_duplicates_at_start", {2, 2, 3, 4, 5, 6, 7, 8}, 2, 0, 1},
        BinSeaTestCase{"two_duplicates_in_middle", {1, 2, 3, 4, 4, 5, 6, 7}, 4, 3, 4},
        BinSeaTestCase{"two_duplicates_at_end", {1, 2, 3, 4, 5, 6, 7, 7}, 7, 6, 7},
        BinSeaTestCase{"four_duplicates_at_start", {1, 1, 1, 1, 2, 3, 4, 5}, 1, 0, 1},
        BinSeaTestCase{"four_duplicates_in_middle", {1, 2, 3, 3, 3, 3, 4, 5}, 3, 2, 3},
        BinSeaTestCase{"four_duplicates_at_end", {1, 2, 3, 4, 5, 5, 5, 5}, 5, 4, 5},
        BinSeaTestCase{"negative_single", {-10, -8, -6, -4, -2, 0, 2, 4}, -6, 2, 3},
        BinSeaTestCase{"negative_duplicates", {-10, -8, -8, -8, -2, 0, 2, 4}, -8, 1, 2},
        BinSeaTestCase{"zero_in_mixed_values", {-4, -3, -2, -1, 0, 1, 2, 3}, 0, 4, 5},
        BinSeaTestCase{"minimum_integer", {INT_MIN, -100, -10, -1, 0, 1, 10, 100}, INT_MIN, 0, 1},
        BinSeaTestCase{"length_9_last", {1, 2, 3, 4, 5, 6, 7, 8, 9}, 9, 8, 9},
        BinSeaTestCase{"length_9_index_7", {1, 2, 3, 4, 5, 6, 7, 8, 9}, 8, 7, 8},
        BinSeaTestCase{"length_9_missing", {1, 2, 3, 4, 5, 6, 7, 8, 9}, 10, -1, -1},
        BinSeaTestCase{"length_9_duplicate_crosses_8", {1, 2, 3, 4, 5, 6, 7, 7, 7}, 7, 6, 7},
        BinSeaTestCase{"length_9_first_after_8", {1, 2, 3, 4, 5, 6, 7, 8, 20}, 20, 8, 9},
        BinSeaTestCase{"length_10_last", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10, 9, 10},
        BinSeaTestCase{"length_10_index_8", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 9, 8, 9},
        BinSeaTestCase{"length_10_duplicates_after_8", {1, 2, 3, 4, 5, 6, 7, 8, 9, 9}, 9, 8, 9},
        BinSeaTestCase{"length_10_index_6", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 7, 6, 7},
        BinSeaTestCase{"length_10_missing", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 11, -1, -1},
        BinSeaTestCase{"length_12_last", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, 12, 11, 12},
        BinSeaTestCase{"length_12_index_10", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, 11, 10, 11},
        BinSeaTestCase{"length_12_index_9", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, 10, 9, 10},
        BinSeaTestCase{"length_12_index_8", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, 9, 8, 9},
        BinSeaTestCase{"length_12_duplicates_at_8", {1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 10, 11}, 9, 8, 9},
        BinSeaTestCase{"length_12_duplicates_at_9", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10}, 10, 9, 10},
        BinSeaTestCase{"length_12_negative_late", {-12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1}, -2, 10, 11},
        BinSeaTestCase{"length_12_zero_at_8", {-8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3}, 0, 8, 9},
        BinSeaTestCase{"length_12_missing_gap", {1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13}, 9, -1, -1},
        BinSeaTestCase{"length_12_first", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, 1, 0, 1},
        BinSeaTestCase{"length_16_last", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}, 16, 15, 16},
        BinSeaTestCase{"length_16_index_14", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}, 15, 14, 15},
        BinSeaTestCase{"length_16_index_12", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}, 13, 12, 13},
        BinSeaTestCase{"length_16_index_8", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}, 9, 8, 9},
        BinSeaTestCase{"length_16_duplicates_at_8", {1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9, 10, 11, 12, 13, 14}, 9, 8, 9},
        BinSeaTestCase{"length_16_duplicates_at_12", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 13, 13, 14}, 13, 12, 13},
        BinSeaTestCase{"maximum_integer", {-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, INT_MAX}, INT_MAX, 15, 16},
        BinSeaTestCase{"minimum_integer_long", {INT_MIN, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0}, INT_MIN, 0, 1},
        BinSeaTestCase{"length_16_missing", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}, 20, -1, -1},
        BinSeaTestCase{"length_16_duplicates_early", {1, 2, 3, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}, 3, 2, 3}
    ),
    [](const testing::TestParamInfo<BinSeaTestCase>& info) {
        return info.param.name;
    }
);
int main(int argc, char** argv) {

    // TEST CASES generated by CODEX (GPT-5.6-sol)
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();


    /*
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};

    int n = sizeof(arr) / sizeof(arr[0]);

    int* ans = binSea(15, arr, n);

    cout << ans[0] << " " << ans[1] << endl;
    cout << "expected: 10,11" << endl;
    */

    return 0;
}
