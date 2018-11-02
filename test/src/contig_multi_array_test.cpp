#include <gtest/gtest.h>
#include <contig_multi_array.hpp>


class ContigMultiArrayTest : public testing::Test {
  public:
    virtual void SetUp() override {}

    virtual void TearDown() override {}
};


TEST_F(ContigMultiArrayTest, foo) {
  ASSERT_EQ(5, 4 + 1);
}
