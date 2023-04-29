#ifndef REQRES_HH
#define REQRES_HH
#include <functional>
#include <string>
#include "tp/zlib.h"
#include "tp/ctx.hh"
#include <buf.hh>
#include <ctx.hh>
#include <conn.hh>
#include <h/common.h>
#include <hpp/string_view.hpp>
#include <str_map.hh>
#include <iostream>
#if defined(_MSC_VER)
#include <io.h>
#else
#include <fcntl.h>
#endif
namespace fc {
  struct App;
  class Req {
    HTTP method;
    void index_cookies();
    std::string_view split(const char*& cur, const char* line_end, char split_char);
  public:
    fc::Buf header(const char* k) const;
    std::string_view cookie(const char* k);
    std::string ip_address() const;
    Req(HTTP method, fc::Buf& url, fc::Buf& params, str_map& headers, fc::Buf& body, Conn& fib,
      std::unordered_map<std::string_view, std::string_view>& cookie_map, box<fc::cache_file>& cache_file);
    fc::Buf& url;
    fc::Buf& params;
    fc::Buf& body;
    unsigned int length;
    str_map& headers;
    fc::Buf ip_addr;
    Conn& fiber;
    box<fc::cache_file>& cache_file;
    std::unordered_map<std::string_view, std::string_view>& cookie_map;
  };// request

  class Res {
    friend class fc::Conn;
    friend struct fc::App;
    enum algorithm { // 15 is the default value for deflate
      DEFLATE = 15, // windowBits can also be greater than 15 for optional gzip encoding.
      // Add 16 to windowBits to write a simple gzip header and trailer around the compressed data instead of a zlib wrapper.
      GZIP = 15 | 16,
    };
    fc::Buf zlib_cp_str;
    char buffer[8192];
    z_stream stream{};
    int is_file{ 0 };
    fc::Ctx& Ctx;
  public:
    FORCE_INLINE void set_header(std::string_view k, std::string_view v) { Ctx.set_header(k, v); }
    FORCE_INLINE void set_cookie(std::string_view k, std::string_view v) { Ctx.set_cookie(k, v); }
    FORCE_INLINE Res(fc::Ctx& ctx): Ctx(ctx) {}
    uint16_t code{ 200 };// Check whether the response has a static file defined.
    fc::Buf body;
    FORCE_INLINE void write(const std::string& b) { this->write(std::move(const_cast<std::string&>(b))); };
    FORCE_INLINE void write(const fc::Buf& b) { this->write(std::move(const_cast<fc::Buf&>(b))); };
    FORCE_INLINE void write(const std::string_view& b) { Ctx.respond(b); };
    FORCE_INLINE void write(const char* b) { std::string_view sv(b, strlen(b)); Ctx.respond(sv); };
    void write(fc::Buf&& body_part);
    void write(std::string&& body_part);
    inline void set_status(int s) { Ctx.set_status(s); }
    fc::Buf& compress_str(char* const str, size_t len);
    fc::Buf& decompress_str(char* const str, size_t len);
  };// response
}

#endif // REQRES_HH
