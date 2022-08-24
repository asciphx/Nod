#ifndef LEXICAL_CAST_H
#define LEXICAL_CAST_H
#include <type_traits>
#include <string>
#include <string_view>
#include <stdexcept>
#include <buf.hh>
namespace std {
#if !defined(_NODISCARD)
#define _NODISCARD [[nodiscard]]
#endif
#if defined(_MSC_VER) && !defined(_INLINE)
#define _INLINE __forceinline
#elif !defined(_INLINE)
#define _INLINE __attribute__((always_inline))
#endif
  static const std::string STD_TURE("true", 4), STD_FALSE("false", 5);
  template <typename S, typename T> _INLINE S lexical_cast(T& i);
  template <> inline std::string lexical_cast<std::string>(char& i) { return std::to_string(i); }
  template <> inline std::string lexical_cast<std::string>(signed char& i) { return std::to_string(i); }
  template <> inline std::string lexical_cast<std::string>(unsigned char& i) { return std::to_string(i); }
  template <> inline std::string lexical_cast<std::string>(short& i) { return std::to_string(i); }
  template <> inline std::string lexical_cast<std::string>(unsigned short& i) { return std::to_string(i); }
  template <> inline std::string lexical_cast<std::string>(int& i) { return std::to_string(i); }
  template <> inline std::string lexical_cast<std::string>(unsigned int& i) { return std::to_string(i); }
  template <> inline std::string lexical_cast<std::string>(long long& i) { return std::to_string(i); }
  template <> inline std::string lexical_cast<std::string>(unsigned long long& i) { return std::to_string(i); }
  template <> inline std::string lexical_cast<std::string>(bool& b) { return b ? STD_TURE : STD_FALSE; }
  template <> inline std::string lexical_cast<std::string>(double& f) { return std::to_string(f); }
  template <> inline std::string lexical_cast<std::string>(float& f) { return std::to_string(f); }
  template <> inline std::string lexical_cast<std::string>(long double& f) { return std::to_string(f); }
  template <> inline std::string lexical_cast<std::string>(long unsigned& f) { return std::to_string(f); }
  template <> inline std::string lexical_cast<std::string>(long& f) { return std::to_string(f); }
  template <> inline std::string lexical_cast<std::string>(std::string& c) { return c; }
  template <typename S, typename T> _INLINE S lexical_cast(T&& i);
  template <> inline std::string lexical_cast<std::string>(char&& i) { return std::to_string(i); }
  template <> inline std::string lexical_cast<std::string>(signed char&& i) { return std::to_string(i); }
  template <> inline std::string lexical_cast<std::string>(unsigned char&& i) { return std::to_string(i); }
  template <> inline std::string lexical_cast<std::string>(short&& i) { return std::to_string(i); }
  template <> inline std::string lexical_cast<std::string>(unsigned short&& i) { return std::to_string(i); }
  template <> inline std::string lexical_cast<std::string>(int&& i) { return std::to_string(i); }
  template <> inline std::string lexical_cast<std::string>(unsigned int&& i) { return std::to_string(i); }
  template <> inline std::string lexical_cast<std::string>(long long&& i) { return std::to_string(i); }
  template <> inline std::string lexical_cast<std::string>(unsigned long long&& i) { return std::to_string(i); }
  template <> inline std::string lexical_cast<std::string>(bool&& b) { return b ? STD_TURE : STD_FALSE; }
  template <> inline std::string lexical_cast<std::string>(double&& f) { return std::to_string(f); }
  template <> inline std::string lexical_cast<std::string>(float&& f) { return std::to_string(f); }
  template <> inline std::string lexical_cast<std::string>(long double&& f) { return std::to_string(f); }
  template <> inline std::string lexical_cast<std::string>(long unsigned&& f) { return std::to_string(f); }
  template <> inline std::string lexical_cast<std::string>(long&& f) { return std::to_string(f); }
  template <> inline std::string lexical_cast<std::string>(std::string&& c) { return c; }

  template <typename T> T lexical_cast(const char* c);
  template <> std::string lexical_cast<std::string>(const char* c);
  template <> _NODISCARD bool lexical_cast<bool>(const char* c);
  template <> _NODISCARD char lexical_cast<char>(const char* c);
  template <> _NODISCARD signed char lexical_cast<signed char>(const char* c);
  template <> _NODISCARD unsigned char lexical_cast<unsigned char>(const char* c);
  template <> _NODISCARD short lexical_cast<short>(const char* c);
  template <> _NODISCARD unsigned short lexical_cast<unsigned short>(const char* c);
  template <> _NODISCARD int lexical_cast<int>(const char* c);
  template <> _NODISCARD unsigned int lexical_cast<unsigned int>(const char* c);
  template <> _NODISCARD long lexical_cast<long>(const char* c);
  template <> _NODISCARD long unsigned lexical_cast<long unsigned>(const char* c);
  template <> _NODISCARD long long lexical_cast<long long>(const char* c);
  template <> _NODISCARD unsigned long long lexical_cast<unsigned long long>(const char* c);
  template <> _NODISCARD float lexical_cast<float>(const char* c);
  template <> _NODISCARD double lexical_cast<double>(const char* c);
  template <> _NODISCARD long double lexical_cast<long double>(const char* c);
  template <> tm lexical_cast<tm>(const char* c);
  template <typename S> _INLINE S lexical_cast(std::string_view sv) { return std::lexical_cast<S>(sv.data()); };
  template <typename T> T lexical_cast(std::string& s);
  template <> _NODISCARD bool lexical_cast<bool>(std::string& s);
  template <> _NODISCARD char lexical_cast<char>(std::string& s);
  template <> _NODISCARD signed char lexical_cast<signed char>(std::string& s);
  template <> _NODISCARD unsigned char lexical_cast<unsigned char>(std::string& s);
  template <> _NODISCARD short lexical_cast<short>(std::string& s);
  template <> _NODISCARD unsigned short lexical_cast<unsigned short>(std::string& s);
  template <> _NODISCARD int lexical_cast<int>(std::string& s);
  template <> _NODISCARD unsigned int lexical_cast<unsigned int>(std::string& s);
  template <> _NODISCARD long lexical_cast<long>(std::string& s);
  template <> _NODISCARD long unsigned lexical_cast<long unsigned>(std::string& s);
  template <> _NODISCARD long long lexical_cast<long long>(std::string& s);
  template <> _NODISCARD unsigned long long lexical_cast<unsigned long long>(std::string& s);
  template <> _NODISCARD float lexical_cast<float>(std::string& s);
  template <> _NODISCARD double lexical_cast<double>(std::string& s);
  template <> _NODISCARD long double lexical_cast<long double>(std::string& s);
  template <> tm lexical_cast<tm>(std::string& s);
  
  template <typename T> T lexical_cast(fc::Buf& s);
  template <> std::string lexical_cast<std::string>(fc::Buf& c);
  template <> _NODISCARD bool lexical_cast<bool>(fc::Buf& s);
  template <> _NODISCARD char lexical_cast<char>(fc::Buf& s);
  template <> _NODISCARD signed char lexical_cast<signed char>(fc::Buf& s);
  template <> _NODISCARD unsigned char lexical_cast<unsigned char>(fc::Buf& s);
  template <> _NODISCARD short lexical_cast<short>(fc::Buf& s);
  template <> _NODISCARD unsigned short lexical_cast<unsigned short>(fc::Buf& s);
  template <> _NODISCARD int lexical_cast<int>(fc::Buf& s);
  template <> _NODISCARD unsigned int lexical_cast<unsigned int>(fc::Buf& s);
  template <> _NODISCARD long lexical_cast<long>(fc::Buf& s);
  template <> _NODISCARD long unsigned lexical_cast<long unsigned>(fc::Buf& s);
  template <> _NODISCARD long long lexical_cast<long long>(fc::Buf& s);
  template <> _NODISCARD unsigned long long lexical_cast<unsigned long long>(fc::Buf& s);
  template <> _NODISCARD float lexical_cast<float>(fc::Buf& s);
  template <> _NODISCARD double lexical_cast<double>(fc::Buf& s);
  template <> _NODISCARD long double lexical_cast<long double>(fc::Buf& s);
  template <> tm lexical_cast<tm>(fc::Buf& s);
}
#endif // LEXICAL_CAST_H
