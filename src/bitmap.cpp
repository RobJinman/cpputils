#include <fstream>
#include <cmath>
#include "bitmap.hpp"
#include "exception.hpp"

namespace cpputils {

Bitmap loadBitmap(const std::string& path) {
  BmpHeader bmpHeader(0, 0, 0);

  size_t headerSize = sizeof(BmpHeader);

  std::ifstream fin(path);
  if (!fin.good()) {
    EXCEPTION("Error loading bitmap from " << path);
  }

  fin.read(reinterpret_cast<char*>(&bmpHeader), headerSize);

  uint32_t channels = bmpHeader.imgHdr.bitCount / 8;

  size_t size[3];
  size[0] = bmpHeader.imgHdr.height; // Rows
  size[1] = bmpHeader.imgHdr.width;  // Columns
  size[2] = channels;

  size_t bytes = size[0] * size[1] * size[2];
  uint8_t* data = new uint8_t[bytes];

  fin.seekg(bmpHeader.fileHdr.offset);

  size_t rowBytes = size[1] * channels;
  size_t paddedRowBytes = ceil(0.25 * rowBytes) * 4;
  size_t rowPadding = paddedRowBytes - rowBytes;

  char* ptr = reinterpret_cast<char*>(data);
  for (size_t row = 0; row < size[0]; ++row) {
    fin.read(ptr, rowBytes);
    fin.ignore(rowPadding);
    ptr += rowBytes;
  }

  return Bitmap(data, size);
}

void saveBitmap(const Bitmap& bitmap, const std::string& path) {
  std::ofstream fout(path);
  if (!fout.good()) {
    EXCEPTION("Error saving bitmap at " << path);
  }

  BmpHeader bmpHeader(bitmap.size()[1], bitmap.size()[0], bitmap.size()[2]);
  fout.write(reinterpret_cast<char*>(&bmpHeader), sizeof(bmpHeader));
  fout.write(reinterpret_cast<char*>(bitmap.data), bitmap.numElements());
}

}
