#include <ctx.hh>

namespace fc {
	std::string_view Ctx::header(const char* key) {
	  if (!header_map.size()) index_headers(); return header_map[key];
	}
	std::string_view Ctx::cookie(const char* key) {
	  if (!cookie_map.size()) index_cookies(); return cookie_map[key];
	}
	std::string_view Ctx::get_parameter(const char* key) {
	  if (!url_.size()) parse_first_line(); return get_parameters_map[key];
	}
	std::string& Ctx::url() {
	  if (!url_.size()) parse_first_line(); return url_;
	}
	std::string& Ctx::method() {
	  if (!method_.size()) parse_first_line(); return method_;
	}
	std::string_view Ctx::http_version() {
	  if (!url_.size()) parse_first_line(); return http_version_;
	}
	void Ctx::format_top_headers(output_buffer& output_stream) {
	  if (status_code_ == 200) output_stream << http_top_header.top_header_200();
	  else output_stream << "HTTP/1.1 " << status_ << http_top_header.top_header();
	}
	void Ctx::prepare_request() {
	  // parse_first_line();
	  response_headers.clear();
	  content_length_ = 0;
	  chunked_ = 0;
	  for (int i = 1; i < header_lines.size() - 1; i++) {
		const char* line_end = header_lines[i + 1]; // last line is just an empty line.
		const char* cur = header_lines[i];
		if (*cur != 'C' && *cur != 'c')
		  continue;
		std::string_view key = split(cur, line_end, ':');
		auto get_value = [&] {
		  std::string_view value = split(cur, line_end, '\r');
		  while (value[0] == ' ')
			value = std::string_view(value.data() + 1, value.size() - 1);
		  return value;
		};
		if (key == "Content-Length")
		  content_length_ = atoi(get_value().data());
		else if (key == "Content-Type") {
		  content_type_ = get_value();
		  chunked_ = (content_type_ == "chunked");
		}
	  }
	}
	void Ctx::respond(const fc::Buf& s) {
	  response_written_ = true;
	  format_top_headers(output_stream);
	  headers_stream.flush();                                             // flushes to output_stream.
	  output_stream << "Content-Length: " << s.size() << "\r\n\r\n" << s.b2v(); // Add body
	  //std::cout << output_stream.to_string_view() << "$\n";
	}
	void Ctx::respond_if_needed() {
	  if (!response_written_) {
		response_written_ = true;
		format_top_headers(output_stream);
		output_stream << headers_stream.to_string_view();
		output_stream << "Content-Length: 0\r\n\r\n"; // Add body
	  }
	}
	void Ctx::set_header(std::string_view k, std::string_view v) {
	  headers_stream << k << ": " << v << "\r\n";
	}
	void Ctx::set_cookie(std::string_view k, std::string_view v) {
	  headers_stream << "Set-Cookie: " << k << '=' << v << "\r\n";
	}
	void Ctx::set_status(int status) {
	  status_code_ = status;
	  switch (status) {
	  case 200:status_ = "200 OK"; break;
	  case 201:status_ = "201 Created"; break;
	  case 202:status_ = "202 Accepted"; break;
	  case 203:status_ = "203 Non-Authoritative Information"; break;
	  case 204:status_ = "204 No Content"; break;
	  case 206:status_ = "206 Partial Content"; break;

	  case 301:status_ = "301 Moved Permanently"; break;
	  case 302:status_ = "302 Found"; break;
	  case 303:status_ = "303 See Other"; break;
	  case 304:status_ = "304 Not Modified"; break;
	  case 307:status_ = "307 Temporary redirect"; break;

	  case 400:status_ = "400 Bad Request"; break;
	  case 401:status_ = "401 Unauthorized"; break;
	  case 402:status_ = "402 Payment Required"; break;
	  case 403:status_ = "403 Forbidden"; break;
	  case 404:status_ = "404 Not Found"; break;
	  case 405:status_ = "405 HTTP verb used to access this page is not allowed"; break;
	  case 406:status_ = "406 Browser does not accept the MIME type of the requested page"; break;
	  case 409:status_ = "409 Conflict"; break;

	  case 500:status_ = "500 Internal Server Error"; break;
	  case 501:status_ = "501 Not Implemented"; break;
	  case 502:status_ = "502 Bad Gateway"; break;
	  case 503:status_ = "503 Service Unavailable"; break;
	  case 510:status_ = "510 Not Extended"; break;
	  default: status_ = "200 OK"; break;
	  }
	}
	// Send a file.
	void Ctx::send_file(const char* path) {
#ifndef _WIN32 // Linux / Macos version with sendfile
	  // Open the file in non blocking mode.
	  int fd = open(path, O_RDONLY);
	  if (fd == -1) throw err::not_found(Buf("File:", 5) << path << " not found.");
	  size_t file_size = lseek(fd, (size_t)0, SEEK_END);
	  // Writing the http headers.
	  response_written_ = true;
	  format_top_headers(output_stream);
	  headers_stream.flush(); // flushes headers to output_stream.
	  output_stream << "Content-Length: " << file_size << "\r\n\r\n";
	  output_stream.flush();
	  off_t offset = 0;
	  lseek(fd, (size_t)0, 0);
	  while (offset < file_size) {
#if __APPLE__ // sendfile on macos is slightly different...
		off_t nwritten = 0;
		int ret = ::sendfile(fd, socket_fd, offset, &nwritten, nullptr, 0);
		offset += nwritten;
		if (ret == 0 && nwritten == 0) break; // end of file.
#else
		int ret = ::sendfile(socket_fd, fd, &offset, file_size - offset);
#endif
		if (ret != -1) {
		  if (offset < file_size) {
			continue; // this->fiber.sink.yield();
		  }
		} else if (errno == EAGAIN) {
		  this->fiber.sink.yield();
		} else {
		  close(fd);
		  std::cerr << "Internal error: sendfile failed: " << strerror(errno) << std::endl;
		  throw err::not_found("Internal error: sendfile failed.");
		}
	  }

	  close(fd);

#else // Windows impl with basic read write.
	  // Open file.
	  FILE* fd; if ((fd = fopen(path, "rb")) == NULL) // C4996
		throw err::not_found(Buf("File:", 5) << path << " not found.");
	  fseek(fd, 0L, SEEK_END);
	  // Get file size.
	  long file_size = ftell(fd);
	  rewind(fd);
	  // Writing the http headers.
	  response_written_ = true;
	  format_top_headers(output_stream);
	  headers_stream.flush(); // flushes to output_stream.
	  output_stream << "Content-Length: " << file_size << "\r\n\r\n"; // Add body
	  output_stream.flush();
	  // Read the file and write it to the socket.
	  size_t nread = 1, offset = 0;
	  __:  char buffer[4096]; nread = _fread_nolock(buffer, sizeof(buffer), 1, fd);
	  if(nread != 0) { offset += sizeof(buffer); this->fiber.write(buffer, sizeof(buffer)); goto __; }
	  file_size -= (long)offset; nread = _fread_nolock(buffer, file_size, 1, fd); this->fiber.write(buffer, file_size);
	  fclose(fd);
#endif
	  }
	void Ctx::add_header_line(const char* l) { header_lines.push_back(l); }
	const char* Ctx::last_header_line() { return header_lines.back(); }
	// split a string, starting from cur && ending with split_char.
	// Advance cur to the end of the split.
	std::string Ctx::split(const char*& cur, const char* line_end, char split_char) {
	  const char* start = cur;
	  while (start < (line_end - 1) && *start == split_char)
		start++;
	  const char* end = start + 1;
	  while (end < (line_end - 1) && *end != split_char)
		end++;
	  cur = end + 1;
	  if (*end == split_char)
		return std::string(start, cur - start - 1);
	  else
		return std::string(start, cur - start);
	}
	void Ctx::index_headers() {
	  for (int i = 1; i < header_lines.size() - 1; i++) {
		const char* line_end = header_lines[i + 1]; // last line is just an empty line.
		const char* cur = header_lines[i];
		std::string_view key = split(cur, line_end, ':');
		std::string_view value = split(cur, line_end, '\r');
		while (value[0] == ' ')
		  value = std::string_view(value.data() + 1, value.size() - 1);
		header_map[key] = value;
		// std::cout << key << " -> " << value << std::endl;
	  }
	}
	void Ctx::index_cookies() {
	  std::string_view cookies = header("Cookie");
	  if (!cookies.data()) return;
	  const char* line_end = &cookies.back() + 1;
	  const char* cur = &cookies.front();
	  while (cur < line_end) {
		std::string_view key = split(cur, line_end, '=');
		std::string_view value = split(cur, line_end, ';');
		while (key[0] == ' ')
		  key = std::string_view(key.data() + 1, key.size() - 1);
		cookie_map[key] = value;
	  }
	}
	void Ctx::parse_first_line() {
	  const char* c = header_lines[0];
	  const char* end = header_lines[1];
	  method_ = split(c, end, ' ');
	  url_ = split(c, end, ' ');
	  http_version_ = split(c, end, '\r');
	  // url get parameters.
	  c = url_.data();
	  end = c + url_.size();
	  url_ = split(c, end, '?');
	  get_parameters_string_ = std::string_view(c, end - c);
	}
	std::string_view Ctx::get_parameters_string() {
	  if (!get_parameters_string_.data())
		parse_first_line();
	  return get_parameters_string_;
	}
	std::string_view Ctx::read_whole_body() {
	  if (!chunked_ && !content_length_) {
		is_body_read_ = true;
		body_end_ = body_start.data();
		return std::string_view(); // No body.
	  }
	  if (content_length_) {
		body_ = rb.read_n(fiber, body_start.data(), content_length_);
		body_end_ = body_.data() + content_length_;
	  } else if (chunked_) {
		// Chunked decoding.
		char* out = (char*)body_start.data();
		const char* cur = body_start.data();
		int chunked_size = strtol(rb.read_until(fiber, cur, '\r').data(), nullptr, 16);
		cur++; // skip \n
		while (chunked_size > 0) {
		  // Read chunk.
		  std::string_view chunk = rb.read_n(fiber, cur, chunked_size);
		  cur += chunked_size + 2; // skip \r\n.
		  // Copy the body into a contiguous string.
		  if (out + chunk.size() > chunk.data()) // use memmove if overlap.
			std::memmove(out, chunk.data(), chunk.size());
		  else
			std::memcpy(out, chunk.data(), chunk.size());

		  out += chunk.size();

		  // Read next chunk size.
		  chunked_size = strtol(rb.read_until(fiber, cur, '\r').data(), nullptr, 16);
		  cur++; // skip \n
		}
		cur += 2; // skip the terminaison chunk.
		body_end_ = cur;
		body_ = std::string_view(body_start.data(), out - body_start.data());
	  }
	  is_body_read_ = true;
	  return body_;
	}
	// Read post parameters in the body.
	std::unordered_map<std::string_view, std::string_view> Ctx::post_parameters() {
	  if (content_type_ == "application/x-www-form-urlencoded") {
		if (!is_body_read_)
		  read_whole_body();
		url_decode_parameters(body_, [&](auto key, auto value) { post_parameters_map[key] = value; });
		return post_parameters_map;
	  } else {
		// fixme: return bad request here.
	  }
	  return post_parameters_map;
	}
	void Ctx::prepare_next_request() {
	  if (!is_body_read_)
		read_whole_body();
	  rb.free(header_lines[0], body_end_);
	  headers_stream.reset();
	  status_ = "200 OK";
	  method_ = "";
	  url_ = "";
	  http_version_ = std::string_view();
	  content_type_ = std::string_view();
	  header_map.clear();
	  cookie_map.clear();
	  response_headers.clear();
	  get_parameters_map.clear();
	  post_parameters_map.clear();
	  get_parameters_string_ = std::string_view();
	  response_written_ = false;
	}
	void Ctx::flush_responses() { output_stream.flush(); }
}