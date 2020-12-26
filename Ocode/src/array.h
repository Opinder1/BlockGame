#pragma once

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

		T& at(size_t pos) {
			return m_data[pos];
		}

		const T* data() {
			return m_data;
		}
	};
}