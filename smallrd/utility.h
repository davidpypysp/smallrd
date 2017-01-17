#ifndef SMALLRD_UTILITY_H_
#define SMALLRD_UTILITY_H_

namespace smallrd {

template <typename T>
inline T ClampValue(const T x, const T min, const T max) {
	if (x > max) return max;
	if (x < min) return min;
	return x;
}

template <typename T>
inline bool InBound(const T x, const T min, const T max) {
	if (x >= min && x < max) return true;
	return false;
}

inline int ArrayIndex(const int x, const int y, const int col) {
	return x + y * col;
}

} //namespace smallrd



#endif // SMALLRD_UTILITY_H_

