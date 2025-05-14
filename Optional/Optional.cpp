#include "Optional.h"

template<typename T>
Optional<T>::Optional(const T& value) : _hasValue(true) 
{
	_value = new T(value);
}

template<typename T>
Optional<T>::~Optional()
{
	freeValue();
}

template<typename T>
bool Optional<T>::hasValue() const
{
	return _hasValue;
}

template<typename T>
const T& Optional<T>::getValue() const
{
	return *_value;
}

template<typename T>
void Optional<T>::setValue(const T& other)
{
	_value = other;
}

template<typename T>
void Optional<T>::freeValue()
{ 
	delete _value;
}

template<typename T>
Optional<T>::operator bool() const noexcept
{
	return _hasValue;
}