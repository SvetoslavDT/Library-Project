#pragma once

template <typename T>
class Optional
{
public:

	Optional() = default;
	Optional(const T& value);
	Optional(const Optional& other);
	Optional& operator=(const Optional& other);
	~Optional();

	bool hasValue() const;
	const T& getValue() const;
	void setValue(const T& other);
	void reset();

	operator bool() const noexcept;
	T& operator*();

	friend std::ostream& operator<<(std::ostream& os, const Optional& obj);
	friend std::istream& operator>>(std::istream& is, Optional& obj);

	void writeToBinary(std::ostream& os) const;
	void readFromFile(std::istream& is);

private:

	bool _hasValue = false;
	T* _value = nullptr;
};



template<typename T>
Optional<T>::Optional(const T& value) : _hasValue(true)
{
	_value = new T(value);
}

template<typename T>
Optional<T>::Optional(const Optional& other) : _hasValue(other._hasValue), _value(nullptr)
{
	if (_hasValue)
		_value = new T(*other._value);
}

template<typename T>
Optional<T>& Optional<T>::operator=(const Optional& other)
{
	if (this != &other)
	{
		if (other._hasValue)
			setValue(*other._value);
		else
		{
			if (_hasValue)
			{
				delete _value;
				_value = nullptr;
			}
			_hasValue = false;
		}
	}
	return *this;
}

template<typename T>
bool operator==(const Optional<T>& lhs, const Optional<T>& rhs);

template<typename T>
bool operator!=(const Optional<T>& lhs, const Optional<T>& rhs);

template<typename T>
bool operator>(const Optional<T>& lhs, const Optional<T>& rhs);

template<typename T>
bool operator<(const Optional<T>& lhs, const Optional<T>& rhs);

template<typename T>
bool operator>=(const Optional<T>& lhs, const Optional<T>& rhs);

template<typename T>
bool operator<=(const Optional<T>& lhs, const Optional<T>& rhs);

template<typename T>
Optional<T>::~Optional()
{
	reset();
}

template<typename T>
bool Optional<T>::hasValue() const
{
	return _hasValue;
}

template<typename T>
const T& Optional<T>::getValue() const
{
	if (!_value)
		throw std::exception("No initialised value");

	return *_value;
}

template<typename T>
void Optional<T>::setValue(const T& other)
{
	if (_hasValue)
		*_value = other;
	else
	{
		_value = new T(other);
		_hasValue = true;
	}
}

template<typename T>
void Optional<T>::reset()
{
	delete _value;
	_value = nullptr;
	_hasValue = false;
}

template<typename T>
Optional<T>::operator bool() const noexcept
{
	return _hasValue;
}

template<typename T>
T& Optional<T>::operator*()
{
	return _value;
}

template<typename T>
bool operator==(const Optional<T>& lhs, const Optional<T>& rhs)
{
	return lhs.getValue() == rhs.getValue();
}

template<typename T>
bool operator!=(const Optional<T>& lhs, const Optional<T>& rhs)
{
	return !(lhs == rhs);
}

template<typename T>
bool operator>(const Optional<T>& lhs, const Optional<T>& rhs)
{
	return lhs.getValue() > rhs.getValue();
}

template<typename T>
bool operator<(const Optional<T>& lhs, const Optional<T>& rhs)
{
	return lhs.getValue() < rhs.getValue();
}

template<typename T>
bool operator>=(const Optional<T>& lhs, const Optional<T>& rhs)
{
	return (lhs == rhs) || (lhs > rhs);
}

template<typename T>
bool operator<=(const Optional<T>& lhs, const Optional<T>& rhs)
{
	return (lhs == rhs) || (lhs < rhs);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Optional<T>& obj) // ?? Correct?
{
	os << obj.hasValue() << '\n';
	if (obj.hasValue())
		os << obj.getValue();
	else
		os << '\n';
	os << '\n'; //here

	return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, Optional<T>& obj)
{
	T value;
	bool boolValue;

	is >> boolValue;
	if (boolValue)
	{
		is >> value;
		obj.setValue(value);
	}
	else
	{
		is.ignore(1, '\n');
	}

	is.ignore(1, '\n');

	return is;
}

template<typename T>
void Optional<T>::writeToBinary(std::ostream& os) const
{
	os.write((const char*)&_hasValue, sizeof(_hasValue));
	if (_hasValue)
		os.write((const char*)_value, sizeof(T));
}

template<typename T>
void Optional<T>::readFromFile(std::istream& is)
{
	is.read((char*)&_hasValue, sizeof(_hasValue));
	if (_hasValue)
	{
		delete _value;
		_value = new T;
		is.read((char*)_value, sizeof(T));
	}
	else
	{
		delete _value;
		_value = nullptr;
	}
}
