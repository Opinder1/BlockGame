#pragma once

#include <vector>
#include <queue>

namespace ocode {
	template<class T>
	class array {
	private:
		T* m_data;
		size_t m_size;

	public:
		array(size_t size) {
			m_size = size;
			m_data = new T[size];
		}

		~array() {
			delete[] m_data;
		}

		T at(size_t index) {
			return m_data[index];
		}

		T& operator[](size_t index) {
			return m_data[index];
		}

		const T* data() {
			return m_data;
		}
	};

	template<class T>
	class static_vector {
	private:
		std::vector<T> m_data;

		std::queue<size_t> m_gaps;

	public:
		void clear() {
			m_data.clear();
			m_gaps.empty();
		}

		void add(const T& item) {
			if (m_gaps.size() > 0) {
				memcpy_s(m_data.data() + m_gaps.front(), sizeof(T), &item, sizeof(T));
				m_gaps.pop();
			}
			else {
				m_data.push_back(item);
			}
		}

		void remove(size_t index) {
			if (index < m_data.size()) {
				memset(m_data.data() + index, 0, sizeof(T));
				m_gaps.push(index);
			}
			else if (index == m_data.size()) {
				m_data.erase(m_data.begin() + index);
			}
			
			throw "Failed (ASSERT?)";
		}

		T at(size_t index) {
			return m_data.at(index);
		}

		T& operator[](size_t index) {
			return m_data[index];
		}

		T* data() {
			return m_data.data();
		}
	};
}