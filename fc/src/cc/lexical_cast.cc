/*
* This software is licensed under the AGPL-3.0 License.
*
* Copyright (C) 2023 Asciphx
*
* Permissions of this strongest copyleft license are conditioned on making available
* complete source code of licensed works and modifications, which include larger works
* using a licensed work, under the same license. Copyright and license notices must be
* preserved. Contributors provide an express grant of patent rights. When a modified
* version is used to provide a service over a network, the complete source code of
* the modified version must be made available.
*/
#include <type_traits>
#include <string>
#include "hpp/string_view.hpp"
#include <stdexcept>
#include <string.h>
namespace std {
  static const short STD_PO[] = {
  1,
  10,
  100,
  1000,
  10000
  };
  static const int STD_POW[] = {
  1,
  10,
  100,
  1000,
  10000,
  100000,
  1000000,
  10000000,
  100000000,
  1000000000
  };
  static const long long STD_POWS[] = {
  1,
  10,
  100,
  1000,
  10000,
  100000,
  1000000,
  10000000,
  100000000,
  1000000000,
  10000000000,
  100000000000,
  1000000000000,
  10000000000000,
  100000000000000,
  1000000000000000,
  10000000000000000,
  100000000000000000,
  1000000000000000000
  };
  template <typename T> inline T lexical_cast(const char* c);

  template <> std::string lexical_cast<std::string>(const char* c) { return std::string(c); }

  template <> [[nodiscard]] bool lexical_cast<bool>(const char* c) {
    if ((c[0] == '1' && c[1] == 0) || (c[0] == 't' && c[1] == 'r' && c[2] == 'u' && c[3] == 'e' && c[4] == 0)) return true;
    if ((c[0] == '0' && c[1] == 0) || (c[0] == 'f' && c[1] == 'a' && c[2] == 'l' && c[3] == 's' && c[4] == 'e' && c[5] == 0))
      return false; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] char lexical_cast<char>(const char* c) {
    char r; if (*c != 0x2D) {
      if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument(""); r = *c - 0x30;
      while (*++c) {
        r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      }
    } else {
      r = 0x30 - *++c; if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
      while (*++c) {
        r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      };
    } return r;
  }
  template <> [[nodiscard]] signed char lexical_cast<signed char>(const char* c) {
    signed char r; if (*c != 0x2D) {
      if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument(""); r = *c - 0x30;
      while (*++c) {
        r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      }
    } else {
      r = 0x30 - *++c; if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
      while (*++c) {
        r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      };
    } return r;
  }
  template <> [[nodiscard]] unsigned char lexical_cast<unsigned char>(const char* c) {
    if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument(""); unsigned char r = *c - 0x30; char z = 0;
    while (z != 1 && *++c) {
      if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument(""); r = r * 10 + *c - 0x30; ++z;
    }
    if (z == 1 && *++c) {
      if (r > 25 || r == 25 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30;
    } return r;
  }
  template <> [[nodiscard]] short lexical_cast<short>(const char* c) {
    short r; if (*c != 0x2D) {
      if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument(""); r = *c - 0x30;
      while (*++c) {
        r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      }
    } else {
      r = 0x30 - *++c; if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
      while (*++c) {
        r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      };
    } return r;
  }
  template <> [[nodiscard]] unsigned short lexical_cast<unsigned short>(const char* c) {
    if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument(""); unsigned short r = *c - 0x30; char z = 0;
    while (z != 3 && *++c) {
      if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument(""); r = r * 10 + *c - 0x30; ++z;
    }
    if (z == 3 && *++c) {
      if (r > 6553 || r == 6553 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30;
    } return r;
  }
  template <> [[nodiscard]] int lexical_cast<int>(const char* c) {
    size_t l = strlen(c); if (*c != 0x2D) {
      if (l < 11) {
        int r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
          r += STD_POW[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; if (r < 0) throw std::range_error("");
        return r;
      } throw std::out_of_range("");
    }
    if (--l < 11) {
      int r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r -= STD_POW[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned int lexical_cast<unsigned int>(const char* c) {
    size_t l = strlen(c); if (--l < 9) {
      unsigned int r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r += STD_POW[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 9) {
      unsigned int r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r += STD_POW[--l] * (*c++ - 0x30);
      }
      if (r > 429496729 || r == 429496729 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long long lexical_cast<long long>(const char* c) {
    size_t l = strlen(c); if (*c != 0x2D) {
      if (l < 20) {
        long long r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
          r += STD_POWS[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; return r;
      } throw std::out_of_range("");
    }
    if (--l < 20) {
      long long r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r -= STD_POWS[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned long long lexical_cast<unsigned long long>(const char* c) {
    size_t l = strlen(c); if (--l < 19) {
      unsigned long long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r += STD_POWS[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 19) {
      unsigned long long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r += STD_POWS[--l] * (*c++ - 0x30);
      }
      if (r > 1844674407370955161 || r == 1844674407370955161 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } throw std::invalid_argument("");
  }
  template <> [[nodiscard]] float lexical_cast<float>(const char* c) {
    char* $; const float _ = ::strtof(c, &$); if (*$ == 0) return _; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] double lexical_cast<double>(const char* c) {
    char* $; const double _ = ::strtod(c, &$); if (*$ == 0) return _; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long double lexical_cast<long double>(const char* c) {
    char* $; const long double _ = ::strtold(c, &$); if (*$ == 0) return _; throw std::invalid_argument("");
  }
  template <>
  tm lexical_cast<tm>(const char* c) {
    int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0; tm t;
    if (sscanf(c, "%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &min, &sec) == 6) {
      t.tm_mday = day;
      t.tm_hour = hour;
      t.tm_min = min;
      t.tm_sec = sec;
    }
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    return t;
  }
  //char*
  template <typename T> inline T lexical_cast(char* c);

  template <> std::string lexical_cast<std::string>(char* c) { return std::string(c); }

  template <> [[nodiscard]] bool lexical_cast<bool>(char* c) {
    if ((c[0] == '1' && c[1] == 0) || (c[0] == 't' && c[1] == 'r' && c[2] == 'u' && c[3] == 'e' && c[4] == 0)) return true;
    if ((c[0] == '0' && c[1] == 0) || (c[0] == 'f' && c[1] == 'a' && c[2] == 'l' && c[3] == 's' && c[4] == 'e' && c[5] == 0))
      return false; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] char lexical_cast<char>(char* c) {
    char r; if (*c != 0x2D) {
      if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument(""); r = *c - 0x30;
      while (*++c) {
        r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      }
    } else {
      r = 0x30 - *++c; if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
      while (*++c) {
        r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      };
    } return r;
  }
  template <> [[nodiscard]] signed char lexical_cast<signed char>(char* c) {
    signed char r; if (*c != 0x2D) {
      if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument(""); r = *c - 0x30;
      while (*++c) {
        r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      }
    } else {
      r = 0x30 - *++c; if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
      while (*++c) {
        r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      };
    } return r;
  }
  template <> [[nodiscard]] unsigned char lexical_cast<unsigned char>(char* c) {
    if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument(""); unsigned char r = *c - 0x30; char z = 0;
    while (z != 1 && *++c) {
      if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument(""); r = r * 10 + *c - 0x30; ++z;
    }
    if (z == 1 && *++c) {
      if (r > 25 || r == 25 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30;
    } return r;
  }
  template <> [[nodiscard]] short lexical_cast<short>(char* c) {
    short r; if (*c != 0x2D) {
      if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument(""); r = *c - 0x30;
      while (*++c) {
        r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      }
    } else {
      r = 0x30 - *++c; if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
      while (*++c) {
        r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      };
    } return r;
  }
  template <> [[nodiscard]] unsigned short lexical_cast<unsigned short>(char* c) {
    if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument(""); unsigned short r = *c - 0x30; char z = 0;
    while (z != 3 && *++c) {
      if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument(""); r = r * 10 + *c - 0x30; ++z;
    }
    if (z == 3 && *++c) {
      if (r > 6553 || r == 6553 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30;
    } return r;
  }
  template <> [[nodiscard]] int lexical_cast<int>(char* c) {
    size_t l = strlen(c); if (*c != 0x2D) {
      if (l < 11) {
        int r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
          r += STD_POW[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; if (r < 0) throw std::range_error("");
        return r;
      } throw std::out_of_range("");
    }
    if (--l < 11) {
      int r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r -= STD_POW[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned int lexical_cast<unsigned int>(char* c) {
    size_t l = strlen(c); if (--l < 9) {
      unsigned int r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r += STD_POW[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 9) {
      unsigned int r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r += STD_POW[--l] * (*c++ - 0x30);
      }
      if (r > 429496729 || r == 429496729 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long long lexical_cast<long long>(char* c) {
    size_t l = strlen(c); if (*c != 0x2D) {
      if (l < 20) {
        long long r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
          r += STD_POWS[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; return r;
      } throw std::out_of_range("");
    }
    if (--l < 20) {
      long long r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r -= STD_POWS[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned long long lexical_cast<unsigned long long>(char* c) {
    size_t l = strlen(c); if (--l < 19) {
      unsigned long long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r += STD_POWS[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 19) {
      unsigned long long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r += STD_POWS[--l] * (*c++ - 0x30);
      }
      if (r > 1844674407370955161 || r == 1844674407370955161 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } throw std::invalid_argument("");
  }
  template <> [[nodiscard]] float lexical_cast<float>(char* c) {
    char* $; const float _ = ::strtof(c, &$); if (*$ == 0) return _; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] double lexical_cast<double>(char* c) {
    char* $; const double _ = ::strtod(c, &$); if (*$ == 0) return _; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long double lexical_cast<long double>(char* c) {
    char* $; const long double _ = ::strtold(c, &$); if (*$ == 0) return _; throw std::invalid_argument("");
  }
  template <>
  tm lexical_cast<tm>(char* c) {
    int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0; tm t;
    if (sscanf(c, "%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &min, &sec) == 6) {
      t.tm_mday = day;
      t.tm_hour = hour;
      t.tm_min = min;
      t.tm_sec = sec;
    }
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    return t;
  }
  //std::string&
  template <typename T> inline T lexical_cast(std::string& s);

  template <> [[nodiscard]] bool lexical_cast<bool>(std::string& s) {
    if (s == "1" || s == "true")return true; if (s == "0" || s == "false")return false; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] char lexical_cast<char>(std::string& s) {
    const char* c = s.c_str(); char r;
    if (*c != 0x2D) {
      if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = *c - 0x30;
      while (*++c) {
        r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      } return r;
    }
    if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = 0x30 - *c;
    while (*++c) {
      r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
    }; return r;
  }
  template <> [[nodiscard]] signed char lexical_cast<signed char>(std::string& s) {
    const char* c = s.c_str(); signed char r;
    if (*c != 0x2D) {
      if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = *c - 0x30;
      while (*++c) {
        r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      } return r;
    }
    if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = 0x30 - *c;
    while (*++c) {
      r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
    }; return r;
  }
  template <> [[nodiscard]] unsigned char lexical_cast<unsigned char>(std::string& s) {
    const char* c = s.c_str();
    if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } unsigned char r = *c - 0x30; char z = 0;
    while (z != 1 && *++c) {
      if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); } r = r * 10 + *c - 0x30; ++z;
    }
    if (z == 1 && *++c) {
      if (r > 25 || r == 25 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30;
    } return r;
  }
  template <> [[nodiscard]] short lexical_cast<short>(std::string& s) {
    const char* c = s.c_str(); short r;
    if (*c != 0x2D) {
      if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = *c - 0x30;
      while (*++c) {
        r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      }
    } else {
      r = 0x30 - *++c; if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); }
      while (*++c) {
        r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      };
    } return r;
  }
  template <> [[nodiscard]] unsigned short lexical_cast<unsigned short>(std::string& s) {
    const char* c = s.c_str(); if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); }
    unsigned short r = *c - 0x30; char z = 0;
    while (z != 3 && *++c) {
      if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); } r = r * 10 + *c - 0x30; ++z;
    }
    if (z == 3 && *++c) {
      if (r > 6553 || r == 6553 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30;
    } return r;
  }
  template <> [[nodiscard]] int lexical_cast<int>(std::string& s) {
    const char* c = s.c_str(); size_t l = strlen(c); if (*c != 0x2D) {
      if (l < 11) {
        int r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
          r += STD_POW[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; if (r < 0) throw std::range_error("");
        return r;
      } throw std::out_of_range("");
    }
    if (--l < 11) {
      int r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r -= STD_POW[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned int lexical_cast<unsigned int>(std::string& s) {
    const char* c = s.c_str(); size_t l = strlen(c); if (--l < 9) {
      unsigned int r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POW[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 9) {
      unsigned int r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POW[--l] * (*c++ - 0x30);
      }
      if (r > 429496729 || r == 429496729 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long long lexical_cast<long long>(std::string& s) {
    const char* c = s.c_str(); size_t l = strlen(c); if (*c != 0x2D) {
      if (l < 20) {
        long long r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
          r += STD_POWS[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; return r;
      } throw std::out_of_range("");
    }
    if (--l < 20) {
      long long r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r -= STD_POWS[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned long long lexical_cast<unsigned long long>(std::string& s) {
    const char* c = s.c_str(); size_t l = strlen(c); if (--l < 19) {
      unsigned long long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POWS[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 19) {
      unsigned long long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POWS[--l] * (*c++ - 0x30);
      }
      if (r > 1844674407370955161 || r == 1844674407370955161 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } throw std::invalid_argument("");
  }
  template <> [[nodiscard]] float lexical_cast<float>(std::string& s) {
    const char* c = s.c_str(); char* $; const float _ = ::strtof(c, &$); if (*$ == 0) return _;  if (*c == 0)return _; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] double lexical_cast<double>(std::string& s) {
    const char* c = s.c_str(); char* $; const double _ = ::strtod(c, &$); if (*$ == 0) return _;  if (*c == 0)return _; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long double lexical_cast<long double>(std::string& s) {
    const char* c = s.c_str(); char* $; const long double _ = ::strtold(c, &$); if (*$ == 0) return _;  if (*c == 0)return _; throw std::invalid_argument("");
  }
  template <>
  tm lexical_cast<tm>(std::string& s) {
    const char* c = s.c_str();
    int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0; tm t;
    if (sscanf(c, "%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &min, &sec) == 6) {
      t.tm_mday = day;
      t.tm_hour = hour;
      t.tm_min = min;
      t.tm_sec = sec;
    }
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    return t;
  }
  //std::string&&
  template <typename T> inline T lexical_cast(std::string&& s);

  template <> [[nodiscard]] bool lexical_cast<bool>(std::string&& s) {
    if (s == "1" || s == "true")return true; if (s == "0" || s == "false")return false; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] char lexical_cast<char>(std::string&& s) {
    const char* c = s.c_str(); char r;
    if (*c != 0x2D) {
      if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = *c - 0x30;
      while (*++c) {
        r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      } return r;
    }
    if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = 0x30 - *c;
    while (*++c) {
      r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
    }; return r;
  }
  template <> [[nodiscard]] signed char lexical_cast<signed char>(std::string&& s) {
    const char* c = s.c_str(); signed char r;
    if (*c != 0x2D) {
      if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = *c - 0x30;
      while (*++c) {
        r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      } return r;
    }
    if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = 0x30 - *c;
    while (*++c) {
      r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
    }; return r;
  }
  template <> [[nodiscard]] unsigned char lexical_cast<unsigned char>(std::string&& s) {
    const char* c = s.c_str();
    if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } unsigned char r = *c - 0x30; char z = 0;
    while (z != 1 && *++c) {
      if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); } r = r * 10 + *c - 0x30; ++z;
    }
    if (z == 1 && *++c) {
      if (r > 25 || r == 25 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30;
    } return r;
  }
  template <> [[nodiscard]] short lexical_cast<short>(std::string&& s) {
    const char* c = s.c_str(); short r;
    if (*c != 0x2D) {
      if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = *c - 0x30;
      while (*++c) {
        r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      }
    } else {
      r = 0x30 - *++c; if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); }
      while (*++c) {
        r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      };
    } return r;
  }
  template <> [[nodiscard]] unsigned short lexical_cast<unsigned short>(std::string&& s) {
    const char* c = s.c_str(); if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); }
    unsigned short r = *c - 0x30; char z = 0;
    while (z != 3 && *++c) {
      if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); } r = r * 10 + *c - 0x30; ++z;
    }
    if (z == 3 && *++c) {
      if (r > 6553 || r == 6553 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30;
    } return r;
  }
  template <> [[nodiscard]] int lexical_cast<int>(std::string&& s) {
    const char* c = s.c_str(); size_t l = strlen(c); if (*c != 0x2D) {
      if (l < 11) {
        int r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
          r += STD_POW[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; if (r < 0) throw std::range_error("");
        return r;
      } throw std::out_of_range("");
    }
    if (--l < 11) {
      int r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r -= STD_POW[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned int lexical_cast<unsigned int>(std::string&& s) {
    const char* c = s.c_str(); size_t l = strlen(c); if (--l < 9) {
      unsigned int r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POW[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 9) {
      unsigned int r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POW[--l] * (*c++ - 0x30);
      }
      if (r > 429496729 || r == 429496729 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long long lexical_cast<long long>(std::string&& s) {
    const char* c = s.c_str(); size_t l = strlen(c); if (*c != 0x2D) {
      if (l < 20) {
        long long r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
          r += STD_POWS[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; return r;
      } throw std::out_of_range("");
    }
    if (--l < 20) {
      long long r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r -= STD_POWS[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned long long lexical_cast<unsigned long long>(std::string&& s) {
    const char* c = s.c_str(); size_t l = strlen(c); if (--l < 19) {
      unsigned long long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POWS[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 19) {
      unsigned long long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POWS[--l] * (*c++ - 0x30);
      }
      if (r > 1844674407370955161 || r == 1844674407370955161 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } throw std::invalid_argument("");
  }
  template <> [[nodiscard]] float lexical_cast<float>(std::string&& s) {
    const char* c = s.c_str(); char* $; const float _ = ::strtof(c, &$); if (*$ == 0) return _;  if (*c == 0)return _; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] double lexical_cast<double>(std::string&& s) {
    const char* c = s.c_str(); char* $; const double _ = ::strtod(c, &$); if (*$ == 0) return _;  if (*c == 0)return _; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long double lexical_cast<long double>(std::string&& s) {
    const char* c = s.c_str(); char* $; const long double _ = ::strtold(c, &$); if (*$ == 0) return _;  if (*c == 0)return _; throw std::invalid_argument("");
  }
  template <>
  tm lexical_cast<tm>(std::string&& s) {
    const char* c = s.c_str();
    int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0; tm t;
    if (sscanf(c, "%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &min, &sec) == 6) {
      t.tm_mday = day;
      t.tm_hour = hour;
      t.tm_min = min;
      t.tm_sec = sec;
    }
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    return t;
  }
  //std::string_view&
  template <typename T> inline T lexical_cast(string_view& s);
  template <> std::string lexical_cast<std::string>(string_view& c) { return std::string(c.data(), c.size()); }

  template <> [[nodiscard]] bool lexical_cast<bool>(string_view& s) {
    if (s == "1" || s == "true")return true; if (s == "0" || s == "false")return false; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] char lexical_cast<char>(string_view& s) {
    const char* c = s.data(); char r;
    if (*c != 0x2D) {
      if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = *c - 0x30;
      while (*++c) {
        r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      } return r;
    }
    if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = 0x30 - *c;
    while (*++c) {
      r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
    }; return r;
  }
  template <> [[nodiscard]] signed char lexical_cast<signed char>(string_view& s) {
    const char* c = s.data(); signed char r;
    if (*c != 0x2D) {
      if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = *c - 0x30;
      while (*++c) {
        r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      } return r;
    }
    if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = 0x30 - *c;
    while (*++c) {
      r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
    }; return r;
  }
  template <> [[nodiscard]] unsigned char lexical_cast<unsigned char>(string_view& s) {
    const char* c = s.data();
    if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } unsigned char r = *c - 0x30; char z = 0;
    while (z != 1 && *++c) {
      if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = r * 10 + *c - 0x30; ++z;
    }
    if (z == 1 && *++c) {
      if (r > 25 || r == 25 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30;
    } return r;
  }
  template <> [[nodiscard]] short lexical_cast<short>(string_view& s) {
    const char* c = s.data(); size_t l = s.size(); if (*c != 0x2D) {
      if (l < 6) {
        short r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
          r += STD_PO[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; if (r < 0) throw std::range_error("");
        return r;
      } throw std::out_of_range("");
    }
    if (--l < 6) {
      short r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r -= STD_PO[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned short lexical_cast<unsigned short>(string_view& s) {
    const char* c = s.data(); size_t l = s.size(); if (--l < 4) {
      unsigned short r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_PO[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 4) {
      unsigned short r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_PO[--l] * (*c++ - 0x30);
      }
      if (r > 6553 || r == 6553 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } if (*c == 0)return 0; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] int lexical_cast<int>(string_view& s) {
    const char* c = s.data(); size_t l = s.size(); if (*c != 0x2D) {
      if (l < 11) {
        int r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
          r += STD_POW[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; if (r < 0) throw std::range_error("");
        return r;
      } throw std::out_of_range("");
    }
    if (--l < 11) {
      int r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r -= STD_POW[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned int lexical_cast<unsigned int>(string_view& s) {
    const char* c = s.data(); size_t l = s.size(); if (--l < 9) {
      unsigned int r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POW[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 9) {
      unsigned int r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POW[--l] * (*c++ - 0x30);
      }
      if (r > 429496729 || r == 429496729 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } if (*c == 0)return 0; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long long lexical_cast<long long>(string_view& s) {
    const char* c = s.data(); size_t l = s.size(); if (*c != 0x2D) {
      if (l < 20) {
        long long r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
          r += STD_POWS[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; if (r < 0) throw std::range_error("");
        return r;
      } throw std::out_of_range("");
    }
    if (--l < 20) {
      long long r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r -= STD_POWS[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned long long lexical_cast<unsigned long long>(string_view& s) {
    const char* c = s.data(); size_t l = s.size(); if (--l < 19) {
      unsigned long long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POWS[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 19) {
      unsigned long long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POWS[--l] * (*c++ - 0x30);
      }
      if (r > 1844674407370955161 || r == 1844674407370955161 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } if (*c == 0)return 0; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] float lexical_cast<float>(string_view& s) {
    const char* c = s.data(); char* $; const float _ = ::strtof(c, &$); if (*$ == 0) return _; { if (*c == 0)return _; throw std::invalid_argument(""); }
  }
  template <> [[nodiscard]] double lexical_cast<double>(string_view& s) {
    const char* c = s.data(); char* $; const double _ = ::strtod(c, &$); if (*$ == 0) return _; { if (*c == 0)return _; throw std::invalid_argument(""); }
  }
  template <> [[nodiscard]] long double lexical_cast<long double>(string_view& s) {
    const char* c = s.data(); char* $; const long double _ = ::strtold(c, &$); if (*$ == 0) return _; { if (*c == 0)return _; throw std::invalid_argument(""); }
  }
  template <>
  tm lexical_cast<tm>(string_view& s) {
    const char* c = s.data();
    int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0; tm t;
    if (sscanf(c, "%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &min, &sec) == 6) {
      t.tm_mday = day;
      t.tm_hour = hour;
      t.tm_min = min;
      t.tm_sec = sec;
    }
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    return t;
  }
  //std::string_view&&
  template <typename T> inline T lexical_cast(string_view&& s);
  template <> std::string lexical_cast<std::string>(string_view&& c) { return std::string(c.data(), c.size()); }

  template <> [[nodiscard]] bool lexical_cast<bool>(string_view&& s) {
    if (s == "1" || s == "true")return true; if (s == "0" || s == "false")return false; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] char lexical_cast<char>(string_view&& s) {
    const char* c = s.data(); char r;
    if (*c != 0x2D) {
      if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = *c - 0x30;
      while (*++c) {
        r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      } return r;
    }
    if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = 0x30 - *c;
    while (*++c) {
      r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
    }; return r;
  }
  template <> [[nodiscard]] signed char lexical_cast<signed char>(string_view&& s) {
    const char* c = s.data(); signed char r;
    if (*c != 0x2D) {
      if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = *c - 0x30;
      while (*++c) {
        r = r * 10 + *c - 0x30; if (r <= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
      } return r;
    }
    if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = 0x30 - *c;
    while (*++c) {
      r = r * 10 - *c + 0x30; if (r >= 0 || *c > 0x39 || 0x30 > *c) throw std::range_error("");
    }; return r;
  }
  template <> [[nodiscard]] unsigned char lexical_cast<unsigned char>(string_view&& s) {
    const char* c = s.data();
    if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } unsigned char r = *c - 0x30; char z = 0;
    while (z != 1 && *++c) {
      if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return 0; throw std::invalid_argument(""); } r = r * 10 + *c - 0x30; ++z;
    }
    if (z == 1 && *++c) {
      if (r > 25 || r == 25 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30;
    } return r;
  }
  template <> [[nodiscard]] short lexical_cast<short>(string_view&& s) {
    const char* c = s.data(); size_t l = s.size(); if (*c != 0x2D) {
      if (l < 6) {
        short r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
          r += STD_PO[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; if (r < 0) throw std::range_error("");
        return r;
      } throw std::out_of_range("");
    }
    if (--l < 6) {
      short r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r -= STD_PO[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned short lexical_cast<unsigned short>(string_view&& s) {
    const char* c = s.data(); size_t l = s.size(); if (--l < 4) {
      unsigned short r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_PO[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 4) {
      unsigned short r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_PO[--l] * (*c++ - 0x30);
      }
      if (r > 6553 || r == 6553 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } if (*c == 0)return 0; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] int lexical_cast<int>(string_view&& s) {
    const char* c = s.data(); size_t l = s.size(); if (*c != 0x2D) {
      if (l < 11) {
        int r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
          r += STD_POW[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; if (r < 0) throw std::range_error("");
        return r;
      } throw std::out_of_range("");
    }
    if (--l < 11) {
      int r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r -= STD_POW[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned int lexical_cast<unsigned int>(string_view&& s) {
    const char* c = s.data(); size_t l = s.size(); if (--l < 9) {
      unsigned int r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POW[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 9) {
      unsigned int r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POW[--l] * (*c++ - 0x30);
      }
      if (r > 429496729 || r == 429496729 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } if (*c == 0)return 0; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long long lexical_cast<long long>(string_view&& s) {
    const char* c = s.data(); size_t l = s.size(); if (*c != 0x2D) {
      if (l < 20) {
        long long r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
          r += STD_POWS[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; if (r < 0) throw std::range_error("");
        return r;
      } throw std::out_of_range("");
    }
    if (--l < 20) {
      long long r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r -= STD_POWS[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned long long lexical_cast<unsigned long long>(string_view&& s) {
    const char* c = s.data(); size_t l = s.size(); if (--l < 19) {
      unsigned long long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POWS[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 19) {
      unsigned long long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POWS[--l] * (*c++ - 0x30);
      }
      if (r > 1844674407370955161 || r == 1844674407370955161 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } if (*c == 0)return 0; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] float lexical_cast<float>(string_view&& s) {
    const char* c = s.data(); char* $; const float _ = ::strtof(c, &$); if (*$ == 0) return _; { if (*c == 0)return _; throw std::invalid_argument(""); }
  }
  template <> [[nodiscard]] double lexical_cast<double>(string_view&& s) {
    const char* c = s.data(); char* $; const double _ = ::strtod(c, &$); if (*$ == 0) return _; { if (*c == 0)return _; throw std::invalid_argument(""); }
  }
  template <> [[nodiscard]] long double lexical_cast<long double>(string_view&& s) {
    const char* c = s.data(); char* $; const long double _ = ::strtold(c, &$); if (*$ == 0) return _; { if (*c == 0)return _; throw std::invalid_argument(""); }
  }
  template <>
  tm lexical_cast<tm>(string_view&& s) {
    const char* c = s.data();
    int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0; tm t;
    if (sscanf(c, "%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &min, &sec) == 6) {
      t.tm_mday = day;
      t.tm_hour = hour;
      t.tm_min = min;
      t.tm_sec = sec;
    }
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    return t;
  }
#ifdef _WIN32
  template <> [[nodiscard]] long lexical_cast<long>(const char* c) {
    size_t l = strlen(c); if (*c != 0x2D) {
      if (l < 11) {
        long r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
          r += STD_POW[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; if (r < 0) throw std::range_error("");
        return r;
      } throw std::out_of_range("");
    }
    if (--l < 11) {
      long r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r -= STD_POW[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned long lexical_cast<unsigned long>(const char* c) {
    size_t l = strlen(c); if (--l < 9) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r += STD_POW[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 9) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r += STD_POW[--l] * (*c++ - 0x30);
      }
      if (r > 429496729 || r == 429496729 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long lexical_cast<long>(char* c) {
    size_t l = strlen(c); if (*c != 0x2D) {
      if (l < 11) {
        long r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
          r += STD_POW[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; if (r < 0) throw std::range_error("");
        return r;
      } throw std::out_of_range("");
    }
    if (--l < 11) {
      long r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r -= STD_POW[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned long lexical_cast<unsigned long>(char* c) {
    size_t l = strlen(c); if (--l < 9) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r += STD_POW[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 9) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r += STD_POW[--l] * (*c++ - 0x30);
      }
      if (r > 429496729 || r == 429496729 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long lexical_cast<long>(std::string& s) {
    const char* c = s.c_str(); size_t l = strlen(c); if (*c != 0x2D) {
      if (l < 11) {
        long r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
          r += STD_POW[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; if (r < 0) throw std::range_error("");
        return r;
      } throw std::out_of_range("");
    }
    if (--l < 11) {
      long r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r -= STD_POW[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned long lexical_cast<unsigned long>(std::string& s) {
    const char* c = s.c_str(); size_t l = strlen(c); if (--l < 9) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POW[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 9) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POW[--l] * (*c++ - 0x30);
      }
      if (r > 429496729 || r == 429496729 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long lexical_cast<long>(std::string&& s) {
    const char* c = s.c_str(); size_t l = strlen(c); if (*c != 0x2D) {
      if (l < 11) {
        long r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
          r += STD_POW[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; if (r < 0) throw std::range_error("");
        return r;
      } throw std::out_of_range("");
    }
    if (--l < 11) {
      long r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r -= STD_POW[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned long lexical_cast<unsigned long>(std::string&& s) {
    const char* c = s.c_str(); size_t l = strlen(c); if (--l < 9) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POW[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 9) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POW[--l] * (*c++ - 0x30);
      }
      if (r > 429496729 || r == 429496729 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long lexical_cast<long>(string_view& s) {
    const char* c = s.data(); size_t l = s.size(); if (*c != 0x2D) {
      if (l < 11) {
        long r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
          r += STD_POW[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; if (r < 0) throw std::range_error("");
        return r;
      } throw std::out_of_range("");
    }
    if (--l < 11) {
      long r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r -= STD_POW[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned long lexical_cast<unsigned long>(string_view& s) {
    const char* c = s.data(); size_t l = s.size(); if (--l < 9) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POW[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 9) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POW[--l] * (*c++ - 0x30);
      }
      if (r > 429496729 || r == 429496729 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } if (*c == 0)return 0; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long lexical_cast<long>(string_view&& s) {
    const char* c = s.data(); size_t l = s.size(); if (*c != 0x2D) {
      if (l < 11) {
        long r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
          r += STD_POW[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; if (r < 0) throw std::range_error("");
        return r;
      } throw std::out_of_range("");
    }
    if (--l < 11) {
      long r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r -= STD_POW[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned long lexical_cast<unsigned long>(string_view&& s) {
    const char* c = s.data(); size_t l = s.size(); if (--l < 9) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POW[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 9) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POW[--l] * (*c++ - 0x30);
      }
      if (r > 429496729 || r == 429496729 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } if (*c == 0)return 0; throw std::invalid_argument("");
  }
#else
  template <> [[nodiscard]] long lexical_cast<long>(const char* c) {
    size_t l = strlen(c); if (*c != 0x2D) {
      if (l < 20) {
        long r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
          r += STD_POWS[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; return r;
      } throw std::out_of_range("");
    }
    if (--l < 20) {
      long r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r -= STD_POWS[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned long lexical_cast<unsigned long>(const char* c) {
    size_t l = strlen(c); if (--l < 19) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r += STD_POWS[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 19) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r += STD_POWS[--l] * (*c++ - 0x30);
      }
      if (r > 1844674407370955161 || r == 1844674407370955161 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long lexical_cast<long>(char* c) {
    size_t l = strlen(c); if (*c != 0x2D) {
      if (l < 20) {
        long r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
          r += STD_POWS[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; return r;
      } throw std::out_of_range("");
    }
    if (--l < 20) {
      long r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r -= STD_POWS[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned long lexical_cast<unsigned long>(char* c) {
    size_t l = strlen(c); if (--l < 19) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r += STD_POWS[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 19) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) throw std::invalid_argument("");
        r += STD_POWS[--l] * (*c++ - 0x30);
      }
      if (r > 1844674407370955161 || r == 1844674407370955161 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long lexical_cast<long>(std::string& s) {
    const char* c = s.c_str(); size_t l = strlen(c); if (*c != 0x2D) {
      if (l < 20) {
        long r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
          r += STD_POWS[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; return r;
      } throw std::out_of_range("");
    }
    if (--l < 20) {
      long r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r -= STD_POWS[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned long lexical_cast<unsigned long>(std::string& s) {
    const char* c = s.c_str(); size_t l = strlen(c); if (--l < 19) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POWS[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 19) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POWS[--l] * (*c++ - 0x30);
      }
      if (r > 1844674407370955161 || r == 1844674407370955161 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long lexical_cast<long>(std::string&& s) {
    const char* c = s.c_str(); size_t l = strlen(c); if (*c != 0x2D) {
      if (l < 20) {
        long r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
          r += STD_POWS[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; return r;
      } throw std::out_of_range("");
    }
    if (--l < 20) {
      long r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r -= STD_POWS[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned long lexical_cast<unsigned long>(std::string&& s) {
    const char* c = s.c_str(); size_t l = strlen(c); if (--l < 19) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POWS[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 19) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POWS[--l] * (*c++ - 0x30);
      }
      if (r > 1844674407370955161 || r == 1844674407370955161 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long lexical_cast<long>(string_view& s) {
    const char* c = s.data(); size_t l = s.size(); if (*c != 0x2D) {
      if (l < 20) {
        long r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
          r += STD_POWS[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; if (r < 0) throw std::range_error("");
        return r;
      } throw std::out_of_range("");
    }
    if (--l < 20) {
      long r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r -= STD_POWS[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned long lexical_cast<unsigned long>(string_view& s) {
    const char* c = s.data(); size_t l = s.size(); if (--l < 19) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POWS[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 19) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POWS[--l] * (*c++ - 0x30);
      }
      if (r > 1844674407370955161 || r == 1844674407370955161 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } if (*c == 0)return 0; throw std::invalid_argument("");
  }
  template <> [[nodiscard]] long lexical_cast<long>(string_view&& s) {
    const char* c = s.data(); size_t l = s.size(); if (*c != 0x2D) {
      if (l < 20) {
        long r = 0; while (--l) {
          if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
          r += STD_POWS[l] * (*c++ - 0x30);
        }
        if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
        r += *c - 0x30; if (r < 0) throw std::range_error("");
        return r;
      } throw std::out_of_range("");
    }
    if (--l < 20) {
      long r = 0; while (--l) {
        if (*++c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r -= STD_POWS[l] * (*c - 0x30);
      }
      if (*++c > 0x39 || 0x30 > *c) throw std::range_error("");
      r -= *c - 0x30; if (r > 0) throw std::range_error("");
      return r;
    } throw std::out_of_range("");
  }
  template <> [[nodiscard]] unsigned long lexical_cast<unsigned long>(string_view&& s) {
    const char* c = s.data(); size_t l = s.size(); if (--l < 19) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POWS[l--] * (*c++ - 0x30);
      }
      if (*c > 0x39 || 0x30 > *c) throw std::range_error("");
      r += *c - 0x30; return r;
    }
    if (l == 19) {
      unsigned long r = 0; while (l) {
        if (*c > 0x39 || 0x30 > *c) { if (*c == 0)return r; throw std::invalid_argument(""); }
        r += STD_POWS[--l] * (*c++ - 0x30);
      }
      if (r > 1844674407370955161 || r == 1844674407370955161 && (*c > 0x35 || 0x30 > *c)) throw std::range_error("");
      r = r * 10 + *c - 0x30; return r;
    } if (*c == 0)return 0; throw std::invalid_argument("");
  }
#endif // _WIN32
}
