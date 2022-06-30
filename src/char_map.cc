#include <unordered_map>
#include <string>
// from https://github.com/ipkn/crow/blob/master/include/crow/ci_map.h
// from https://github.com/boostorg/beast/blob/develop/include/boost/beast/http/impl/field.ipp
namespace cc {
  struct char_hash {
	size_t operator()(const std::string& z) const {
	  size_t r = 0, n = z.size();
	  unsigned char const* p = reinterpret_cast<unsigned char const*>(z.data());
	  while (n >= 4) {
		const unsigned int v = p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
		r = (r * 5 + (v & ~0x20202020)); p += 4; n -= 4;
	  }
	  while (n > 0) { r = r * 5 + (*p | 0x20); ++p; --n; } return r;
	}
  };
  struct char_key_eq {
	bool operator()(const std::string& l, const std::string& r) const {
	  size_t n = l.size(); if (n != r.size()) return false;
	  unsigned char const* x = reinterpret_cast<unsigned char const*>(l.data());
	  unsigned char const* y = reinterpret_cast<unsigned char const*>(r.data());
	  unsigned long long z = sizeof(std::uint32_t);
	  unsigned int m = static_cast<unsigned int>(0xDFDFDFDFDFDFDFDF & ~std::uint32_t{ 0 });
	  for (; n >= z; x += z, y += z, n -= z) {
		std::uint32_t const v = x[0] | (x[1] << 8) | (x[2] << 16) | (x[3] << 24);
		std::uint32_t const w = y[0] | (y[1] << 8) | (y[2] << 16) | (y[3] << 24);
		if ((v ^ w) & m) return false;
	  }
	  for (; n; ++x, ++y, --n) if ((*x ^ *y) & 0xDF) return false; return true;
	}
  };
}
