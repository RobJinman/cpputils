#include <gtest/gtest.h>
#include <bitmap.hpp>


using namespace cpputils;


class BitmapTest : public testing::Test {
  public:
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(BitmapTest, loadTestBitmap) {
  Bitmap bitmap = loadBitmap("../test/test.bmp");

  ASSERT_EQ(0, bitmap[0][0][0]);
  ASSERT_EQ(255, bitmap[0][0][1]);
  ASSERT_EQ(255, bitmap[0][0][2]);

  ASSERT_EQ(255, bitmap[0][1][0]);
  ASSERT_EQ(0, bitmap[0][1][1]);
  ASSERT_EQ(255, bitmap[0][1][2]);

  ASSERT_EQ(255, bitmap[0][2][0]);
  ASSERT_EQ(255, bitmap[0][2][1]);
  ASSERT_EQ(255, bitmap[0][2][2]);

  ASSERT_EQ(0, bitmap[1][0][0]);
  ASSERT_EQ(0, bitmap[1][0][1]);
  ASSERT_EQ(255, bitmap[1][0][2]);

  ASSERT_EQ(0, bitmap[1][1][0]);
  ASSERT_EQ(255, bitmap[1][1][1]);
  ASSERT_EQ(0, bitmap[1][1][2]);

  ASSERT_EQ(255, bitmap[1][2][0]);
  ASSERT_EQ(0, bitmap[1][2][1]);
  ASSERT_EQ(0, bitmap[1][2][2]);
}

TEST_F(BitmapTest, savePower2Bitmap) {
  size_t size[] = { 128, 256, 3 };
  Bitmap bitmap(size);

  for (size_t y = 0; y < size[0]; ++y) {
    for (size_t x = 0; x < size[1]; ++x) {
      bitmap[y][x][0] = x % 256;
      bitmap[y][x][1] = y % 256;
      bitmap[y][x][2] = (x + y) % 256;
    }
  }

  saveBitmap(bitmap, "tmp.bmp");

  Bitmap restoredBmp = loadBitmap("tmp.bmp");

  for (size_t y = 0; y < size[0]; ++y) {
    for (size_t x = 0; x < size[1]; ++x) {
      ASSERT_EQ(bitmap[y][x][0], restoredBmp[y][x][0]);
      ASSERT_EQ(bitmap[y][x][1], restoredBmp[y][x][1]);
      ASSERT_EQ(bitmap[y][x][2], restoredBmp[y][x][2]);
    }
  }
}

TEST_F(BitmapTest, saveNonPower2Bitmap) {
  size_t size[] = { 77, 233, 3 };
  Bitmap bitmap(size);

  for (size_t y = 0; y < size[0]; ++y) {
    for (size_t x = 0; x < size[1]; ++x) {
      bitmap[y][x][0] = x % 256;
      bitmap[y][x][1] = y % 256;
      bitmap[y][x][2] = (x + y) % 256;
    }
  }

  saveBitmap(bitmap, "tmp.bmp");

  Bitmap restoredBmp = loadBitmap("tmp.bmp");

  for (size_t y = 0; y < size[0]; ++y) {
    for (size_t x = 0; x < size[1]; ++x) {
      ASSERT_EQ(bitmap[y][x][0], restoredBmp[y][x][0]);
      ASSERT_EQ(bitmap[y][x][1], restoredBmp[y][x][1]);
      ASSERT_EQ(bitmap[y][x][2], restoredBmp[y][x][2]);
    }
  }
}
