#include <catch2/catch_test_macros.hpp>

#include <initializer_list>

// Include the submitted implementation without using its empty program entry
// point. The tests therefore call the same binSea function that is submitted.
#define main modBinSea_original_main
#include "main.cpp"
#undef main

namespace {

void checkRange(std::initializer_list<int> values, int target, int expectedStart,
                int expectedEnd) {
    const int size = static_cast<int>(values.size());
    int* input = new int[size];
    int index = 0;
    for (int value : values) {
        input[index++] = value;
    }

    int* actual = binSea(target, input, size);
    CHECK(actual[0] == expectedStart);
    CHECK(actual[1] == expectedEnd);

    delete[] actual;
    delete[] input;
}

} // namespace

TEST_CASE("assignment example finds the full range of 8", "[range][examples]") { checkRange({5, 7, 7, 8, 8, 10}, 8, 3, 4); }
TEST_CASE("assignment example reports an absent 6", "[missing][examples]") { checkRange({5, 7, 7, 8, 8, 10}, 6, -1, -1); }
TEST_CASE("singleton target in a two element array", "[singleton]") { checkRange({2, 9}, 9, 1, 1); }
TEST_CASE("singleton target at the beginning", "[singleton][boundary]") { checkRange({-4, 3, 8, 12}, -4, 0, 0); }
TEST_CASE("singleton target at the end", "[singleton][boundary]") { checkRange({-9, -2, 1, 6, 14}, 14, 4, 4); }
TEST_CASE("singleton target entirely in the middle of an odd array", "[singleton][middle]") { checkRange({1, 4, 9, 16, 25}, 9, 2, 2); }
TEST_CASE("singleton target entirely in the middle of an even array", "[singleton][middle]") { checkRange({-8, -3, 0, 5, 11, 20}, 0, 2, 2); }
TEST_CASE("two occurrences at the beginning with trailing values", "[duplicates][boundary]") { checkRange({3, 3, 7, 10, 12}, 3, 0, 1); }
TEST_CASE("two occurrences at the end with preceding values", "[duplicates][boundary]") { checkRange({-10, -5, 0, 6, 6}, 6, 3, 4); }
TEST_CASE("two occurrences centered in an odd array", "[duplicates][middle]") { checkRange({-5, 1, 4, 4, 9, 13, 18}, 4, 2, 3); }
TEST_CASE("two occurrences centered in an even array", "[duplicates][middle]") { checkRange({-8, -2, 5, 5, 11, 19}, 5, 2, 3); }
TEST_CASE("three occurrences at the beginning", "[duplicates][boundary]") { checkRange({1, 1, 1, 4, 7, 9}, 1, 0, 2); }
TEST_CASE("three occurrences at the end", "[duplicates][boundary]") { checkRange({-12, -4, 0, 8, 8, 8}, 8, 3, 5); }
TEST_CASE("three occurrences entirely in the middle", "[duplicates][middle]") { checkRange({-10, -3, 2, 2, 2, 11, 20, 31}, 2, 2, 4); }
TEST_CASE("four occurrences at the beginning", "[duplicates][boundary]") { checkRange({-2, -2, -2, -2, 0, 5, 9}, -2, 0, 3); }
TEST_CASE("four occurrences at the end", "[duplicates][boundary]") { checkRange({-20, -7, 1, 6, 6, 6, 6}, 6, 3, 6); }
TEST_CASE("four occurrences in the middle", "[duplicates][middle]") { checkRange({-15, -8, 0, 5, 5, 5, 5, 12, 19}, 5, 3, 6); }
TEST_CASE("target is the entire three element array", "[duplicates][whole-array]") { checkRange({7, 7, 7}, 7, 0, 2); }
TEST_CASE("target is the entire even length array", "[duplicates][whole-array]") { checkRange({-1, -1, -1, -1}, -1, 0, 3); }
TEST_CASE("target is the entire five element array", "[duplicates][whole-array]") { checkRange({0, 0, 0, 0, 0}, 0, 0, 4); }
TEST_CASE("single element array contains the target", "[singleton][size-one]") { checkRange({42}, 42, 0, 0); }
TEST_CASE("single element array has a smaller target", "[missing][size-one]") { checkRange({42}, 41, -1, -1); }
TEST_CASE("missing target immediately below the minimum", "[missing][boundary]") { checkRange({-10, -4, 2, 9}, -11, -1, -1); }
TEST_CASE("missing target immediately above the maximum", "[missing][boundary]") { checkRange({-10, -4, 2, 9}, 10, -1, -1); }
TEST_CASE("missing target between two existing values", "[missing]") { checkRange({-10, -4, 2, 9}, 0, -1, -1); }
TEST_CASE("missing target between duplicate runs", "[missing][duplicates]") { checkRange({-5, -5, 3, 3, 8, 8}, 0, -1, -1); }
TEST_CASE("negative singleton target", "[signed][singleton]") { checkRange({-20, -11, -3, 4, 12}, -11, 1, 1); }
TEST_CASE("zero singleton target", "[signed][singleton]") { checkRange({-9, -2, 0, 6, 15, 22}, 0, 2, 2); }
TEST_CASE("repeated negative target in a mixed array", "[signed][duplicates]") { checkRange({-15, -9, -9, -9, -1, 0, 7}, -9, 1, 3); }
TEST_CASE("repeated positive target in a mixed array", "[signed][duplicates]") { checkRange({-12, -1, 4, 4, 4, 10, 18}, 4, 2, 4); }
TEST_CASE("mixed negative zero and positive values", "[signed][mixed]") { checkRange({-6, -2, -2, 0, 0, 0, 5, 11}, 0, 3, 5); }
TEST_CASE("negative target at the left edge with positives after it", "[signed][boundary]") { checkRange({-8, -8, -8, -1, 3, 14}, -8, 0, 2); }
TEST_CASE("positive target at the right edge with negatives before it", "[signed][boundary]") { checkRange({-14, -3, 2, 17, 17, 17}, 17, 3, 5); }
TEST_CASE("adversarial three-run catches first plus one", "[adversarial]") { checkRange({1, 2, 3, 3, 3, 4}, 3, 2, 4); }
TEST_CASE("adversarial left run catches first plus one", "[adversarial]") { checkRange({1, 1, 1, 1, 2}, 1, 0, 3); }
TEST_CASE("adversarial four-run in the middle", "[adversarial]") { checkRange({1, 2, 3, 4, 4, 4, 4, 5}, 4, 3, 6); }
TEST_CASE("adversarial entire three-value run", "[adversarial]") { checkRange({7, 7, 7}, 7, 0, 2); }
TEST_CASE("adversarial five-value run at the left edge", "[adversarial]") { checkRange({0, 0, 0, 0, 0, 1}, 0, 0, 4); }
TEST_CASE("adversarial five-value run near the right edge", "[adversarial]") { checkRange({1, 2, 2, 2, 2, 2}, 2, 1, 5); }
TEST_CASE("odd length range begins before the midpoint", "[shape][odd]") { checkRange({-9, -4, -4, -4, 0, 6, 13}, -4, 1, 3); }
TEST_CASE("odd length range ends after the midpoint", "[shape][odd]") { checkRange({-9, -2, 3, 3, 3, 3, 14}, 3, 2, 5); }
TEST_CASE("even length range begins at the midpoint", "[shape][even]") { checkRange({-10, -3, 5, 5, 5, 12, 18, 24}, 5, 2, 4); }
TEST_CASE("even length range ends at the midpoint", "[shape][even]") { checkRange({-10, -3, 1, 8, 8, 8, 18, 24}, 8, 3, 5); }
TEST_CASE("long array has a central singleton", "[shape][long]") { checkRange({-30, -20, -10, -4, 0, 7, 15, 24, 40, 55, 70}, 0, 4, 4); }
TEST_CASE("long array has a central duplicate run", "[shape][long][duplicates]") { checkRange({-30, -20, -10, -4, 6, 6, 6, 15, 24, 40, 55, 70}, 6, 4, 6); }
TEST_CASE("missing value below a negative minimum in an odd array", "[missing][shape]") { checkRange({-100, -50, -20, -1, 8, 16, 32}, -101, -1, -1); }
TEST_CASE("missing value above a positive maximum in an even array", "[missing][shape]") { checkRange({-100, -50, -20, -1, 8, 16, 32, 64}, 65, -1, -1); }
TEST_CASE("zero range separates negative and positive runs", "[signed][boundary]") { checkRange({-7, -7, -1, 0, 0, 3, 9, 9, 9}, 0, 3, 4); }
TEST_CASE("repeated negative range is surrounded by signed values", "[signed][duplicates]") { checkRange({-20, -20, -20, -8, -8, -8, -8, 0, 12}, -8, 3, 6); }
TEST_CASE("repeated positive range follows zero", "[signed][duplicates]") { checkRange({-12, -1, 0, 3, 3, 3, 3, 3, 20}, 3, 3, 7); }
