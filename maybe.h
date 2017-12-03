#pragma once

namespace maybe {

template <typename T>
class maybe {
public:
	inline bool
	is_just() const
	{
		return has_value_;
	}

	inline bool
	is_nothing() const
	{
		return !has_value_;
	}

	inline T
	from_just() const
	{
		if (!is_just()) throw std::runtime_error("from_just: nothing");
		return value_;
	}

	inline T
	from_maybe(const T& v) const
	{
		return has_value_ ? value_ : v;
	}

	inline bool
	operator==(const maybe& other) const
	{
		return (is_just() == other.is_just())
			&& (!is_just() || from_just() == other.from_just());
	}

	inline bool
	operator!=(const maybe& other) const
	{
		return !operator==(other);
	}
private:
	maybe()
		: has_value_(false)
	{
		/* nop */
	}

	explicit maybe(const T& v)
		: has_value_(true)
		, value_(v)
	{
		/* nop */
	}

	bool has_value_;
	T value_;

	template <typename U> friend maybe<U> nothing();
	template <typename U> friend maybe<U> just();
};

template <typename T>
maybe<T>
nothing()
{
	return maybe<T>();
}

template <typename T>
maybe<T>
just(const T& v)
{
	return maybe<T>(v);
}

} /* namespace maybe */
