#include <buffer.hh>
// from https://github.com/matt-42/lithium/blob/master/libraries/http_server/http_server/output_buffer.hh
namespace fc {
  Buffer::Buffer(): data_(new char[0x3f]), not_null_(true), cur_(data_), end_(data_ + 0x3f), cap_(0x3f) {}
  Buffer::Buffer(Buffer&& o): data_(o.data_), not_null_(o.not_null_), cur_(o.cur_), end_(o.end_), cap_(o.cap_) {
	o.data_ = nullptr; o.not_null_ = false;
  }
  Buffer::Buffer(unsigned short capacity)
	: data_(new char[capacity]), not_null_(true), cur_(data_), end_(data_ + capacity), cap_(capacity) {}
  Buffer::Buffer(const char* c, unsigned short capacity)
	: data_(new char[capacity]), not_null_(true), cur_(data_), end_(data_ + capacity), cap_(capacity) {
	memcpy(cur_, c, capacity); cur_ += capacity;
  }
  Buffer::~Buffer() { if (not_null_) delete[] data_; }
  Buffer& Buffer::operator=(Buffer&& o) {
	data_ = o.data_; not_null_ = o.not_null_; cur_ = o.cur_; end_ = o.end_;
	o.data_ = nullptr; o.not_null_ = false; return *this;
  }
  void Buffer::reset() { cur_ = data_; }
  void Buffer::clear() { delete[] data_; data_ = new char[cap_]; cur_ = data_; end_ = data_ + cap_; }
  std::size_t Buffer::size() { return cur_ - data_; }
  Buffer& Buffer::operator<<(std::string_view s) {
	if (cur_ + s.size() >= end_) reserve((unsigned short)((cur_ - data_) + s.size()));
	memcpy(cur_, s.data(), s.size()); cur_ += s.size(); return *this;
  }
  Buffer& Buffer::operator<<(const char* s) { return operator<<(std::string_view(s, strlen(s))); }
  Buffer& Buffer::operator<<(char v) { cur_[0] = v; ++cur_; return *this; }
  Buffer& Buffer::operator<<(std::size_t v) {
	if (v == 0) operator<<('0'); char mega_buffer[10], * str_start = mega_buffer;
	for (char i = 0; i < 10; ++i) {
	  if (v > 0) str_start = mega_buffer + 9 - i; mega_buffer[9 - i] = (v % 10) + '0'; v /= 10;
	}
	operator<<(std::string_view(str_start, mega_buffer + 10 - str_start)); return *this;
  }
  Buffer& Buffer::operator<<(int b) {
	std::string s(std::lexical_cast<std::string>(b)); return operator<<(std::string_view(s.data(), s.size()));
  }
  Buffer& Buffer::operator=(std::string s) {
	if (s.size() > cap_) s.resize(cap_); delete[] data_; data_ = new char[cap_]; cur_ = data_;
	memcpy(cur_, s.data(), s.size()); cur_ += s.size(); end_ = data_ + cap_; return *this;
  }
  // template <typename I>
  // Buffer& Buffer::operator<<(I v) {
	 //std::string b(std::lexical_cast<std::string>(v));return operator<<(std::string_view(b.data(), b.size()));
  // }
  std::string_view Buffer::data() { return std::string_view(data_, cur_ - data_); }
}