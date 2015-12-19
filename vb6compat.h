#ifndef VB6COMPAT_H
#define VB6COMPAT_H

#include <cstdint>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

#define vbGreen 0x0000ff00
#define vbWhite 0x00ffffff
#define vbRed 0x00ff0000
#define vbBlue 0x0000ff
#define vbCyan 0x0000ffff
#define vbYellow 0x00ffff00
#define vbCrLf "\r\n"

void dakara_print_backtrace();

namespace vb6 {

template <typename T>
class array {
public:

	typedef typename std::vector<T>::iterator iterator;

	array() : lbound_(0), ubound_(0) {

	}

    std::string to_string(T value)
    {
        std::ostringstream os ;
        os << value ;
        return os.str() ;
    }

	T& operator[](std::size_t idx) {
		if (idx < lbound_ || idx > ubound_) {
			throw std::runtime_error("out of bounds: " + to_string(idx));
		}
		return data_[idx - lbound_];
	}

	const T& operator[](std::size_t idx) const {
		if (idx < lbound_ || idx > ubound_) {
			dakara_print_backtrace();
			throw std::runtime_error("out of bounds: " + to_string(idx));
		}
		return data_[idx - lbound_];
	}

	/** Empty the container.
	 *
	 */
	void redim() {
		data_.resize(0);
		lbound_ = 1;
		ubound_ = 0;
	}

	void redim(std::size_t ubound) {
		data_.resize(ubound + 1);
		lbound_ = 0;
		ubound_ = ubound;
	}

	void redim(std::size_t lbound, std::size_t ubound) {
		data_.resize(ubound - lbound + 1);
		lbound_ = lbound;
		ubound_ = ubound;
	}

	std::size_t lbound() const {
		return lbound_;
	}

	std::size_t ubound() const {
		return ubound_;
	}

	iterator begin() {
		return data_.begin();
	}

	iterator end() {
		return data_.end();
	}

	std::vector<T>& data() {
		return data_;
	}

private:
	std::vector<T> data_;
	std::size_t lbound_;
	std::size_t ubound_;
};

struct Variant {};
struct Object {};
typedef std::size_t Date;

/*
struct Collection {
	int Count() { return 0; }
	void Remove(int i) {}
	int Item(int i) { return 0; }
};
*/

struct Err_t {
	static Err_t Instance;
	int Number;
	std::string description;
};

inline Err_t & Err() {
	return Err_t::Instance;
}

/*
struct App_t {
	static App_t Instance;
	std::string Path2;
};

inline App_t & App() {
	return App_t::Instance;
}
*/

/*
 *
 */

std::string string_format(const std::string fmt_str, ...);

/*
 *
 */

std::size_t GetTickCount();

std::string AppPath();

std::vector <std::string> split(std::string, char);

void Name(std::string oldName, std::string newName);

void Kill(std::string FileName);

void FileCopy(std::string oldfile, std::string newfile);

inline bool IsNumeric(std::string str) {
	if (str.size() == 0)
		return false;
	for (auto c : str) {
		if (!::isdigit(c))
			return false;
	}
	return true;
}

template <typename T>
inline T string_to(const std::string& e) {
	std::stringstream ss;
	ss << e;
	T n;
	if (ss >> n) {
		return n;
	}
	throw std::runtime_error(std::string("Invalid Format: ") + e);
}

template <typename T>
inline int Sgn(T n) {
	return (n > 0) ? 1 : ((n == 0) ? 0 : -1);
}

template <typename T>
inline std::string CStr(T n) {
	return to_string(n);
}

template <>
inline std::string CStr<std::string>(std::string n) {
	return (n);
}

template <>
inline std::string CStr<bool>(bool n) {
	return (n) ? "true" : "false";
}

template <>
inline std::string CStr<const char*>(const char* n) {
	return std::string(n);
}

template <typename T>
inline std::string Format(T n, std::string fmt) {
	/* FIXME: Borrar esto */
	(void)fmt;
	return CStr(n);
}

template <typename T>
inline std::string str(T n) {
	return to_string(n);
}

template <typename T>
inline double Sqr(T n) {
	return std::sqrt(n);
}

inline double Rnd() {
	return (std::rand() * 1.0) / RAND_MAX;
}

template <typename T>
inline int Fix(T n) {
	return (int)n;
}

template <typename T>
inline int Round(T n) {
	return std::round(n);
}

template <typename T>
inline int Round(T n, int decimal_places) {
	return std::round(n * std::pow(10, decimal_places)) / std::pow(10, decimal_places);
}

template <typename T>
inline bool CBool(const T& e) {
	return static_cast<bool>(e);
}

template <typename T>
inline int CByte(const T& e) {
	return static_cast<int>(e);
}

template <>
inline int CByte<std::string>(const std::string& e) {
	if (e.size() == 0) return 0;
	return string_to<int>(e);
}

template <typename T>
inline int CInt(const T& e) {
	return static_cast<int>(e);
}

template <typename T>
inline int Int(const T& e) {
	return static_cast<int>(e);
}

template <>
inline int CInt<std::string>(const std::string& e) {
	if (e.size() == 0) return 0;
	return string_to<int>(e);
}

template <typename T>
inline int CLng(const T& e) {
	return static_cast<int>(e);
}

template <>
inline int CLng<std::string>(const std::string& e) {
	if (e.size() == 0) return 0;
	return string_to<int>(e);
}

template <typename T>
inline double CDbl(const T& e) {
	return static_cast<double>(e);
}

template <>
inline double CDbl<std::string>(const std::string& e) {
	if (e.size() == 0) return 0;
	return string_to<double>(e);
}

template <typename T>
inline double CSng(const T& e) {
	return static_cast<double>(e);
}

template <>
inline double CSng<std::string>(const std::string& e) {
	if (e.size() == 0) return 0;
	return string_to<double>(e);
}

inline std::string DateAdd(const std::string fmt, int what, Date d) {
	(void)fmt;
	(void)what;
	(void)d;
	throw std::runtime_error("DateAdd not implemented");
}

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

inline std::string Time() {
	//throw std::runtime_error("time not implemented");
	return to_string(std::time(0));
}

inline Date CDate(std::string str) {
	(void)str;
	throw std::runtime_error("CDate not implemented");
	return 0; // FIXME
}

inline Date Now() {
	return std::time(0); // FIXME
}

inline int Hour(Date d) {
	return (d / 3600) % 60;
}

inline int Minute(Date d) {
	return (d / 60) % 60;
}

inline int Second(Date d) {
	return d % 60;
}

inline int Weekday(Date d) {
	return ((((d / 60) / 60) / 24) % 7) + 1;
}

inline std::string Replace(const std::string& str, const std::string& strold, const std::string& strnew) {
	std::string res(str);
	std::size_t p = 0;
	for (;;) {
		p = res.find(strold, p);
		if (p == std::string::npos)
			break;
		res.replace(p, strold.size(), strnew);
		p += strnew.size();
	}
	return res;
}

inline std::vector<std::string> Split(const std::string& s, std::string sep) {
	std::vector<std::string> res;

	if (sep.length() > 0) {
		std::size_t ant = 0, pos = s.find(sep);

		while (pos != std::string::npos) {
			res.push_back(s.substr(ant, pos - ant));
			ant = pos + sep.length();
			pos = s.find(sep, ant);
		}

		res.push_back(s.substr(ant));
	} else {
		res.push_back(s);
	}

	return res;
}

inline std::string Space(int n) {
	return std::string(static_cast<std::size_t>(n), ' ');
}

/*
inline void ChDir(const std::string& str) {
	throw std::runtime_error("ChDir not implemented");
}

inline void ChDrive(const std::string& str) {
	throw std::runtime_error("ChDrive not implemented");
}

inline std::string dir(const std::string& str) {
	throw std::runtime_error("dir not implemented");
}
*/

inline std::string Chr(int c) {
	return std::string(&c, &c+1);
}

inline int Asc(std::string c) {
	return *reinterpret_cast<const unsigned char*>(c.c_str());
}

inline void MsgBox(const std::string& str) {
	std::cerr << "MsgBox: " << str << std::endl;
}

//inline bool Eof(int fileNum) {
//	throw std::runtime_error("EOF not implemented");
//}

//inline int FreeFile(int range = 0) {
//	throw std::runtime_error("FreeFile not implemented");
//}

inline std::string RTrim(const std::string& str) {
	if (str.size() == 0)
		return std::string();
	std::size_t k = str.size() - 1;
	// "0123456789"
	// " hola "
	// "  newbi   "
	while (k > 0 && str[k] == ' ') {
		--k;
	}
	if ((k == 0 && str[k] == ' '))
		return std::string();
	return str.substr(0, k + 1);
}

inline std::string LTrim(const std::string& str) {
	if (str.size() == 0)
		return std::string();
	std::size_t i = 0;
	while (i < str.size() && str[i] == ' ') {
		++i;
	}
	return (i > 0) ? str.substr(i, str.size() - i) : str;
}

inline std::string Trim(const std::string& str) {
	if (str.size() == 0)
		return str;
	std::size_t i = 0, k = str.size() - 1;
	while (i < str.size() && str[i] == ' ') {
		++i;
	}
	// "0123456789"
	// " hola "
	// "  newbi   "
	while (k > 0 && str[k] == ' ') {
		--k;
	}
	if ((k == 0 && str[k] == ' ') || ((int)k - (int)i + 1) <= 0)
		return std::string();
	return str.substr(i, k - i + 1);
}

inline double val(const std::string& str) {
    if (str.size() == 0) return 0;
	return string_to<double>(str);
}

inline std::size_t InStr(std::size_t start, const std::string& haystack, const std::string& needle) {
	std::size_t r = haystack.find(needle, start - 1);
	return (r == std::string::npos) ? 0 : (r + 1);
}

inline std::size_t InStr(const std::string& haystack, const std::string& needle) {
	std::size_t r = haystack.find(needle, 0);
	return (r == std::string::npos) ? 0 : (r + 1);
}

inline std::size_t InStrB(std::size_t start, const std::string& haystack, const std::string& needle) {
	return InStr(start, needle, haystack);
}

inline std::size_t InStrB(const std::string& haystack, const std::string& needle) {
	return InStr(1, needle, haystack);
}

inline std::string LCase(const std::string& s) {
	std::string slo(s);
	std::transform(slo.begin(), slo.end(), slo.begin(), ::tolower);
	return slo;
}

inline std::string UCase(const std::string& s) {
	std::string sup(s);
	std::transform(sup.begin(), sup.end(), sup.begin(), ::toupper);
	return sup;
}

inline std::string Right(const std::string& s, int len) {
	return s.substr(s.size() - len, len);
}

inline std::string Left(const std::string& s, int len) {
	return s.substr(0, len);
}

/** substring. starts at 1.
 *
 */
/*inline std::string Mid(const std::string& s, int start, int len) {
	return s.substr(start - 1, len);
}*/

inline std::string Mid(std::string& str, int pos1, int pos2){
	std::string temp;
	for (int i = pos1; i <= pos2; i++) temp += str[i-1];
	return temp;
}

template <typename T>
inline T IIf(bool cond, T a, T b) {
	return cond ? a : b;
}

template <typename T>
inline T Abs(const T& x) {
	return std::abs(x);
}

template <typename T>
inline int UBound(const std::vector<T>& v) {
	return (int)v.size() - 1;
}

template <typename T>
inline int LBound(const array<T>& v) {
	return v.lbound();
}

template <typename T>
inline int UBound(const array<T>& v) {
	return v.ubound();
}

inline std::size_t Len(const std::string& v) {
	return v.size();
}

inline std::size_t LenB(const std::string& v) {
	return v.size();
}

}

#endif

