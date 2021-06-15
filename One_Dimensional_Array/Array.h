#ifndef ARRAY_H
#define ARRAY_H

#include "Exception.h"


template <typename T>
class Array
{
	public:
		Array();
		Array(int length, int start_index = 0);
		Array(const Array & copy);
		~Array();
		Array & operator= (const Array & rhs);

		T & operator[] (int index);
		const T & operator[] (int index) const;
		int getStartIndex();
		int getStartIndex() const;
		void setStartIndex(int start_index);
		int getLength();
		int getLength() const;
		void setLength(int length);

	private:
		T * m_array;
		int m_length;
		int m_start_index;
};

template <typename T>
Array<T>::Array()
	: m_array(nullptr), m_length(0), m_start_index(0)
{

}

template <typename T>
Array<T>::Array(int length, int start_index = 0)
	: m_length(length), m_start_index(start_index)
{
	if (m_length < 0)
		throw Exception("Error: Array length cannot be negative.");

	m_array = new T[length];
}

template <typename T>
Array<T>::Array(const Array<T> & copy)
	: m_length(copy.m_length), m_start_index(copy.m_start_index)
{
	this->m_array = new T[copy.m_length];

	for (int cur_index = 0; cur_index < copy.m_length; cur_index++)
		this->m_array[cur_index] = copy.m_array[cur_index];
}

template <typename T>
Array<T>::~Array()
{
	if (m_array != nullptr)
	{
		delete[] m_array;

		m_array = nullptr;
		m_length = 0;
		m_start_index = 0;
	}
}

template <typename T>
Array<T> & Array<T>::operator= (const Array<T> & rhs)
{
	if (this != &rhs)
	{
		if (this->m_array != nullptr)
			delete[] this->m_array;

		this->m_array = new T[rhs.m_length];

		for (int cur_index = 0; cur_index < rhs.m_length; cur_index++)
			this->m_array[cur_index] = rhs.m_array[cur_index];

		this->m_length = rhs.m_length;
		this->m_start_index = rhs.m_start_index;
	}

	return *this;
}

template <typename T>
T & Array<T>::operator[] (int index)
{
	if (index >= m_start_index && index < m_start_index + m_length)
		return m_array[index - m_start_index];

	throw Exception("Error: Out of range access");
}

template <typename T>
const T & Array<T>::operator[] (int index) const
{
	if (index >= m_start_index && index < m_start_index + m_length)
		return m_array[index - m_start_index];

	throw Exception("Error: Out of range access");
}

template <typename T>
int Array<T>::getStartIndex()
{
	return m_start_index;
}

template <typename T>
int Array<T>::getStartIndex() const
{
	return m_start_index;
}

template <typename T>
void Array<T>::setStartIndex(int start_index)
{
	m_start_index = start_index;
}

template <typename T>
int Array<T>::getLength()
{
	return m_length;
}

template <typename T>
int Array<T>::getLength() const
{
	return m_length;
}

template <typename T>
void Array<T>::setLength(int length)
{
	if (length > 0)
	{
		T * new_array = new T[length];
		int copy_length = length <= m_length ? length : m_length;

		for (int cur_index = 0; cur_index < copy_length; cur_index++)
			new_array[cur_index] = this->m_array[cur_index];

		if (m_array != nullptr)
			delete[] m_array;

		m_array = new_array;
		m_length = length;
	}
	else
		throw Exception("Error: Array length must be a positive value");
}

#endif