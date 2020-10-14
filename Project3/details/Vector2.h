template<class T>
Vector2Temple<T>::Vector2Temple()
{
	x = 0;
	y = 0;

}

template<class T>
Vector2Temple<T>::Vector2Temple(T x, T y)
{
	Vector2Temple::x = x;
	Vector2Temple::y = y;
}

template<class T>
Vector2Temple<T>::~Vector2Temple()
{
}

template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator+=(const Vector2Temple<T>& vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator-=(const Vector2Temple<T>& vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator*=(T k)
{
	x *= k;
	y *= k;
	return *this;
}

template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator/=(T k)
{
	x /= k;
	y /= k;
	return *this;
}

template<class T>
Vector2Temple<T> Vector2Temple<T>::operator+() const
{
	return (*this);
}

template<class T>
Vector2Temple<T> Vector2Temple<T>::operator-() const
{
	return Vector2Temple(-this->x,-this->y);
}

template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator=(const Vector2Temple<T>& vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}

template<class T>
bool Vector2Temple<T>::operator==(const Vector2Temple<T>& vec) const
{
	return ((vec.x == this->x)&&(vec.y == this->y));
}

template<class T>
bool Vector2Temple<T>::operator!=(const Vector2Temple<T>& vec) const
{
	return !((vec.x == this->x) && (vec.y == this->y));
}

template<class T>
bool Vector2Temple<T>::operator<(const Vector2Temple<T>& vec) const
{
	return ((this->x < vec.x) && (this->y < vec.y));
}

template<class T>
bool Vector2Temple<T>::operator<=(const Vector2Temple<T>& vec) const
{
	return ((this->x <= vec.x) && (this->y <= vec.y));
}

template<class T>
T& Vector2Temple<T>::operator[](int no)
{
	if (no == 0)
	{
		return x;
	}
	else if(no == 1)
	{
		return y;
	}
	else
	{
		return x;
	}
}

template<class T>
Vector2Temple<T> operator+(const Vector2Temple<T>& u, T v)
{
	return Vector2Temple<T>(u.x + v,u.y + v);
}

template<class T>
Vector2Temple<T> operator-(const Vector2Temple<T>& u, T v)
{
	return Vector2Temple<T>(u.x - v, u.y - v);
}

template<class T>
Vector2Temple<T> operator*(const Vector2Temple<T>& u, T v)
{
	return Vector2Temple<T>(u.x * v, u.y * v);
}

template<class T>
Vector2Temple<T> operator*(T v, const Vector2Temple<T>& u)
{
	return Vector2Temple<T>(v * u.x, v * u.y);
}

template<class T>
Vector2Temple<T> operator/(const Vector2Temple<T>& u, T v)
{
	return Vector2Temple<T>(u.x / v, u.y / v);
}

template<class T>
Vector2Temple<T> operator%(const Vector2Temple<T>& u, T v)
{
	return Vector2Temple<T>(u.x % v, u.y % v);
}

template<class T>
Vector2Temple<T> operator+(const Vector2Temple<T>& u, const Vector2Temple<T>& v)
{
	return Vector2Temple<T>(u.x + v.x, u.y + v.y);
}

template<class T>
Vector2Temple<T> operator-(const Vector2Temple<T>& u, const Vector2Temple<T>& v)
{
	return Vector2Temple<T>(u.x - v.x, u.y - v.y);
}
