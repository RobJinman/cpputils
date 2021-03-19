#include <gtest/gtest.h>
#include <array.hpp>


using cpputils::ContigMultiArray;


class ContigMultiArrayTest : public testing::Test {
  public:
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};


typedef ContigMultiArray<int, 1> IntArr1;
typedef ContigMultiArray<int, 2> IntArr2;
typedef ContigMultiArray<int, 3> IntArr3;


template<typename T, size_t D>
bool containsContiguously(const ContigMultiArray<T, D>& arr, std::initializer_list<T> values) {
  int i = 0;
  for (auto& val : values) {
    if (val != arr.data[i]) {
      return false;
    }
    ++i;
  }
  return true;
}

TEST_F(ContigMultiArrayTest, oneDimensional) {
  IntArr1 arr({0, 1, 2, 3, 4});

  ASSERT_EQ(5, arr.numElements());
  ASSERT_EQ(0, arr[0]);
  ASSERT_EQ(1, arr[1]);
  ASSERT_EQ(2, arr[2]);
  ASSERT_EQ(3, arr[3]);
  ASSERT_EQ(4, arr[4]);
}

TEST_F(ContigMultiArrayTest, twoDimensional) {
  IntArr2 arr({
    {0, 1, 2, 3},
    {4, 5, 6, 7},
    {8, 9, 0, 1}});

  bool contiguous = containsContiguously<int, 2>(arr, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1});
  ASSERT_TRUE(contiguous);

  ASSERT_EQ(0, arr[0][0]);
  ASSERT_EQ(1, arr[0][1]);
  ASSERT_EQ(2, arr[0][2]);
  ASSERT_EQ(3, arr[0][3]);
  ASSERT_EQ(4, arr[1][0]);
  ASSERT_EQ(5, arr[1][1]);
  ASSERT_EQ(6, arr[1][2]);
  ASSERT_EQ(7, arr[1][3]);
  ASSERT_EQ(8, arr[2][0]);
  ASSERT_EQ(9, arr[2][1]);
  ASSERT_EQ(0, arr[2][2]);
  ASSERT_EQ(1, arr[2][3]);
}

TEST_F(ContigMultiArrayTest, threeDimensional) {
  IntArr3 arr({
    {{0, 1}, {2, 3}, {4, 5}, {6, 7}},
    {{8, 9}, {0, 1}, {2, 3}, {4, 5}},
    {{6, 7}, {8, 9}, {0, 1}, {2, 3}}});

  bool contiguous = containsContiguously<int, 3>(arr,
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3});
  ASSERT_TRUE(contiguous);

  ASSERT_EQ(0, arr[0][0][0]);
  ASSERT_EQ(1, arr[0][0][1]);
  ASSERT_EQ(2, arr[0][1][0]);
  ASSERT_EQ(3, arr[0][1][1]);
  ASSERT_EQ(4, arr[0][2][0]);
  ASSERT_EQ(5, arr[0][2][1]);
  ASSERT_EQ(6, arr[0][3][0]);
  ASSERT_EQ(7, arr[0][3][1]);
  ASSERT_EQ(8, arr[1][0][0]);
  ASSERT_EQ(9, arr[1][0][1]);
  ASSERT_EQ(0, arr[1][1][0]);
  ASSERT_EQ(1, arr[1][1][1]);
  ASSERT_EQ(2, arr[1][2][0]);
  ASSERT_EQ(3, arr[1][2][1]);
  ASSERT_EQ(4, arr[1][3][0]);
  ASSERT_EQ(5, arr[1][3][1]);
  ASSERT_EQ(6, arr[2][0][0]);
  ASSERT_EQ(7, arr[2][0][1]);
  ASSERT_EQ(8, arr[2][1][0]);
  ASSERT_EQ(9, arr[2][1][1]);
  ASSERT_EQ(0, arr[2][2][0]);
  ASSERT_EQ(1, arr[2][2][1]);
  ASSERT_EQ(2, arr[2][3][0]);
  ASSERT_EQ(3, arr[2][3][1]);
}
