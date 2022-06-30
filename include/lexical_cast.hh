#ifndef LEXICAL_CAST_H
#define LEXICAL_CAST_H
#include <type_traits>
#include <string>
#include <string_view>
#include <stdexcept>
namespace std {
#if defined(_MSC_VER)
#define _INLINE __forceinline
#else
#define _INLINE inline
#endif
  template <typename S> _INLINE S lexical_cast(std::string_view sv) { return std::lexical_cast<S>(sv.data()); };

  template <typename S, typename T> _INLINE S lexical_cast(T& i);
  template <> _INLINE std::string lexical_cast<std::string>(signed char& i);
  template <> _INLINE std::string lexical_cast<std::string>(unsigned char& i);
  template <> _INLINE std::string lexical_cast<std::string>(short& i);
  template <> _INLINE std::string lexical_cast<std::string>(unsigned short& i);
  template <> _INLINE std::string lexical_cast<std::string>(int& i);
  template <> _INLINE std::string lexical_cast<std::string>(unsigned int& i);
  template <> _INLINE std::string lexical_cast<std::string>(long long& i);
  template <> _INLINE std::string lexical_cast<std::string>(unsigned long long& i);
  template <> _INLINE std::string lexical_cast<std::string>(bool& b);
  template <typename S, typename T> _INLINE S lexical_cast(T&& i);
  template <> _INLINE std::string lexical_cast<std::string>(signed char&& i);
  template <> _INLINE std::string lexical_cast<std::string>(unsigned char&& i);
  template <> _INLINE std::string lexical_cast<std::string>(short&& i);
  template <> _INLINE std::string lexical_cast<std::string>(unsigned short&& i);
  template <> _INLINE std::string lexical_cast<std::string>(int&& i);
  template <> _INLINE std::string lexical_cast<std::string>(unsigned int&& i);
  template <> _INLINE std::string lexical_cast<std::string>(long long&& i);
  template <> _INLINE std::string lexical_cast<std::string>(unsigned long long&& i);
  template <> _INLINE std::string lexical_cast<std::string>(bool&& b);

  template <typename T> _INLINE T lexical_cast(const char* c);
  template <> _INLINE std::string lexical_cast<std::string>(const char* c);
  template <> [[nodiscard]] _INLINE bool lexical_cast<bool>(const char* c);
  template <> [[nodiscard]] _INLINE signed char lexical_cast<signed char>(const char* c);
  template <> [[nodiscard]] _INLINE unsigned char lexical_cast<unsigned char>(const char* c);
  template <> [[nodiscard]] _INLINE short lexical_cast<short>(const char* c);
  template <> [[nodiscard]] _INLINE unsigned short lexical_cast<unsigned short>(const char* c);
  template <> [[nodiscard]] _INLINE int lexical_cast<int>(const char* c);
  template <> [[nodiscard]] _INLINE unsigned int lexical_cast<unsigned int>(const char* c);
  template <> [[nodiscard]] _INLINE long long lexical_cast<long long>(const char* c);
  template <> [[nodiscard]] _INLINE unsigned long long lexical_cast<unsigned long long>(const char* c);
  template <> [[nodiscard]] _INLINE float lexical_cast<float>(const char* c);
  template <> [[nodiscard]] _INLINE double lexical_cast<double>(const char* c);
  template <> [[nodiscard]] _INLINE long double lexical_cast<long double>(const char* c);
  template <> _INLINE tm lexical_cast<tm>(const char* c);
  template <typename T> _INLINE T lexical_cast(const std::string& s);
  template <> [[nodiscard]] _INLINE bool lexical_cast<bool>(const std::string& s);
  template <> [[nodiscard]] _INLINE signed char lexical_cast<signed char>(const std::string& s);
  template <> [[nodiscard]] _INLINE unsigned char lexical_cast<unsigned char>(const std::string& s);
  template <> [[nodiscard]] _INLINE short lexical_cast<short>(const std::string& s);
  template <> [[nodiscard]] _INLINE unsigned short lexical_cast<unsigned short>(const std::string& s);
  template <> [[nodiscard]] _INLINE int lexical_cast<int>(const std::string& s);
  template <> [[nodiscard]] _INLINE unsigned int lexical_cast<unsigned int>(const std::string& s);
  template <> [[nodiscard]] _INLINE long long lexical_cast<long long>(const std::string& s);
  template <> [[nodiscard]] _INLINE unsigned long long lexical_cast<unsigned long long>(const std::string& s);
  template <> [[nodiscard]] _INLINE float lexical_cast<float>(const std::string& s);
  template <> [[nodiscard]] _INLINE double lexical_cast<double>(const std::string& s);
  template <> [[nodiscard]] _INLINE long double lexical_cast<long double>(const std::string& s);
  template <> _INLINE tm lexical_cast<tm>(const std::string& s);
#undef _INLINE
}
#endif // LEXICAL_CAST_H
