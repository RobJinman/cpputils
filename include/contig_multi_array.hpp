#ifndef CPPUTILS_CONTIG_MULTI_ARRAY_HPP
#define CPPUTILS_CONTIG_MULTI_ARRAY_HPP


#include <stdexcept>
#include <cstring>
#include <initializer_list>


template <typename T, size_t D>
class ContigMultiArray {
  friend class ContigMultiArray<T, D + 1>;

  public:
    T* data;
    const size_t dimensionality = D;

    ContigMultiArray(std::initializer_list<ContigMultiArray<T, D - 1>> arr) {
      m_size = new size_t[D];

      m_size[0] = arr.size();
      memcpy(&m_size[1], arr.begin()->m_size, (D - 1) * sizeof(size_t));

      size_t elements = 1;
      for (size_t i = 0; i < D; ++i) {
        elements *= m_size[i];
      }

      m_stride = computeStride();
      data = new T[elements];

      size_t slice = 0;
      for (auto& sub : arr) {
        memcpy(data + slice * m_stride, sub.data, sub.size() * sizeof(T));
        ++slice;
      }
    }

    ContigMultiArray(const size_t size[D])
      : data(nullptr) {

      m_size = new size_t[D];

      size_t t = 1;
      for (size_t i = 0; i < D; ++i) {
        m_size[i] = size[i];
        t *= size[i];
      }

      data = new T[t];

      m_stride = computeStride();
    }

    ContigMultiArray(T* data, size_t size[D])
      : data(data) {

      m_size = new size_t[D];
      memcpy(m_size, size, sizeof(size_t) * D);

      m_stride = computeStride();
    }

    size_t length() const {
      return m_size[0];
    }

    size_t size() const {
      size_t s = 1;
      for (size_t i = 0; i < D; ++i) {
        s *= m_size[i];
      }
      return s;
    }

    ContigMultiArray<T, D - 1> operator[](size_t slice) {
      if (slice >= m_size[0]) {
        throw std::runtime_error("Subscript out of range");
      }

      size_t offset = slice * m_stride;

      return ContigMultiArray<T, D - 1>(data + offset, &m_size[1]);
    }

    void del() {
      delete[] data;
      delete[] m_size;
    }

  private:
    size_t* m_size;
    size_t m_stride;

    size_t computeStride() const {
      size_t stride = 1;
      for (size_t i = 1; i < D; ++i) {
        stride *= m_size[i];
      }
      return stride;
    }
};

template<typename T>
class ContigMultiArray<T, 1> {
  friend class ContigMultiArray<T, 2>;

  public:
    T* data;

    ContigMultiArray(std::initializer_list<T> elems) {
      data = new T[elems.size()];

      int i = 0;
      for (auto& e : elems) {
        data[i] = e;
        ++i;
      }

      m_size = new size_t[1];
      m_size[0] = elems.size();
    }

    ContigMultiArray(size_t size[1]) {
      m_size[0] = *size;
      data = new T[m_size[0]];
    }

    ContigMultiArray(T* data, size_t size[1])
      : data(data) {

      memcpy(m_size, size, sizeof(size_t));
    }

    size_t length() const {
      return m_size[0];
    }

    size_t size() const {
      return length();
    }

    T& operator[](size_t i) {
      if (i >= m_size[0]) {
        throw std::runtime_error("Subscript out of range");
      }

      return data[i];
    }

    void del() {
      delete[] data;
      delete[] m_size;
    }

  private:
    size_t* m_size;
};


#endif
