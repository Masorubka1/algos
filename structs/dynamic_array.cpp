#include <bits/stdc++.h>

template <typename T>
class dynamic_array {
 private:
    int m_size;
    int m_capacity;
    T* m_data;

 public:
    dynamic_array() {
        m_size = 0;
        m_capacity = 0;
        m_data = nullptr;
    }
    dynamic_array(const dynamic_array<T> &a) {
        m_size = a.m_size;
        m_capacity = m_size;
        m_data = nullptr;
        if (m_size != 0) {
            m_data = new T[m_size];
        } else {
            m_data = 0;
        }
        for (int i = 0; i < m_size; ++i) {
            m_data[i] = a.m_data[i];
        }
    }
    explicit dynamic_array(int size) {
        m_size = size;
        m_capacity = size;
        if (size != 0) {
            m_data = new T[size];
        } else {
            m_data = 0;
        }
    }
    ~dynamic_array() {
        if (m_data) {
            delete[] m_data;
        }
    }

    int resize(int size) {
        if (size > m_capacity) {
            int new_capacity = std::max(size, m_size * 2);
            T * new_data = new T[new_capacity];
            for (int i = 0; i < m_size; ++i) {
                new_data[i] = m_data[i];
            }
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }
        m_size = size;
        return 0;
    }
    int size() const {
        return m_size;
    }

    void push_back(T val) {
        resize(m_size + 1);
        m_data[m_size] = val;
    }

    T& operator[] (int i) {
        return m_data[i];
    }
};

template<typename T>
std::ostream& operator << (std::ostream& out, dynamic_array<T> a) {
    for (int i = 0; i < a.size(); ++i) {
        out << a[i] << " ";
    }
    return out;
}
