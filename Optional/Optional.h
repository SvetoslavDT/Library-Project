#pragma once

template <typename T>
class Optional
{
public:

	Optional() = default;
	Optional(const T& value);
	Optional(const Optional& other) = delete;
	Optional& operator=(const Optional& other) = delete;
	~Optional();

	bool hasValue() const;
	const T& getValue() const;
	void setValue(const T& other);
	void freeValue();

	operator bool() const noexcept;

private:

	bool _hasValue = false;
	T* _value = nullptr;
};