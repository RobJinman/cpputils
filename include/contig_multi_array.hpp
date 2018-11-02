#ifndef __CONTIG_MULTI_ARRAY_HPP__
#define __CONTIG_MULTI_ARRAY_HPP__


#include <stdexcept>


template <typename T, size_t D>
class ContigMultiArray {
  public:
    T* data;

    ContigMultiArray(const size_t size[D])
      : data(nullptr) {

      m_size = new size_t[D];

      size_t t = 1;
      for (size_t i = 0; i < D; ++i) {
        m_size[i] = size[i];
        t *= size[i];
      }

      data = new T[t];
    }

    ContigMultiArray(T* data, size_t* size)
      : data(data),
        m_size(size) {}

    ContigMultiArray<T, D - 1> operator[](size_t i) {
      if (i >= m_size[0]) {
        throw std::runtime_error("Subscript out of range");
      }

      for (size_t j = 1; j < D; ++j) {
        i *= m_size[D - j];
      }

      return ContigMultiArray<T, D - 1>(data + i, &m_size[1]);
    }

    void del() {
      delete[] data;
      delete[] m_size;
    }

  private:
    size_t* m_size;
};

template<typename T>
class ContigMultiArray<T, 1> {
  public:
    T* data;

    ContigMultiArray(size_t* size) {
      m_size = *size;
      data = new T[m_size];
    }

    ContigMultiArray(T* data, size_t* size)
      : data(data),
        m_size(*size) {}

    T& operator[](size_t i) {
      if (i >= m_size) {
        throw std::runtime_error("Subscript out of range");
      }

      return data[i];
    }

    void del() {
      delete[] data;
    }

  private:
    size_t m_size;
};


#endif
