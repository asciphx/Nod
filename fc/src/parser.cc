#include <string>
#include <unordered_map>
#include <algorithm>
#include <parser.hh>
// from https://github.com/ipkn/crow/blob/master/include/crow/parser.h
namespace fc {
  static int on_message_begin(llhttp__internal_s* _) {
	llParser* $ = static_cast<llParser*>(_); $->url.clear(); $->raw_url.clear();// $->url_params.clear();
	$->header_field.clear(); $->header_value.clear(); $->headers.clear(); $->body.clear();
	$->header_building_state = $->http_major = $->http_minor = 0; return 0;
  }
  static int on_url(llhttp__internal_s* _, const char* c, size_t l) {
	llParser* $ = static_cast<llParser*>(_); $->raw_url.insert($->raw_url.end(), c, c + l);
	$->raw_url = DecodeURL($->raw_url); return 0;
  }
  static int on_header_field(llhttp__internal_s* _, const char* c, size_t l) {
	llParser* $ = static_cast<llParser*>(_); switch ($->header_building_state) {
	case 0: if (!$->header_value.empty()) $->headers.emplace($->header_field.data_, $->header_value.data_);
	  $->header_field.assign(c, c + l), $->header_building_state = 1; break;
	case 1: $->header_field.insert($->header_field.end_, c, c + l);  break;
	} return 0;
  }
  static int on_header_value(llhttp__internal_s* _, const char* c, size_t l) {
	llParser* $ = static_cast<llParser*>(_); switch ($->header_building_state) {
	case 0: $->header_value.insert($->header_value.end_, c, c + l); break;
	case 1: $->header_building_state = 0; $->header_value.assign(c, c + l); break;
	} return 0;
  }
  static int on_headers_complete(llhttp__internal_s* _) {
	llParser* $ = static_cast<llParser*>(_);
	if (!$->header_field.empty()) $->headers.emplace($->header_field.data_, $->header_value.data_);
	$->keep_alive = ($->http_major == 1 && $->http_minor == 0) ? (($->flags & F_CONNECTION_KEEP_ALIVE) ? true : false) :
	  (($->http_major == 1 && $->http_minor == 1) ? true : false);
	//$->close_conn = ($->http_major == 1 && $->http_minor == 0) ? (($->flags & F_CONNECTION_KEEP_ALIVE) ? false : true) :
	//  (($->http_major == 1 && $->http_minor == 1) ? (($->flags & F_CONNECTION_CLOSE) ? true : false) : false);
	return 0;//llhttp_should_keep_alive(_);$->handler_->handle_header();
  }
  static int on_body(llhttp__internal_s* _, const char* c, size_t l) {
	llParser* $ = static_cast<llParser*>(_); $->body.insert($->body.end_, c, c + l); return 0;
  }
  static int on_message_complete(llhttp__internal_s* _) {
	llParser* $ = static_cast<llParser*>(_); $->url = $->raw_url.substr(0, $->raw_url.find('?'));
	$->ready = true; return 0;//$->url_params = query_string($->raw_url); handler_->handle();
  }
  const llhttp_settings_s llParser::_ = {
	  on_message_begin,
	  on_url,
	  nullptr,
	  on_header_field,
	  on_header_value,
	  on_headers_complete,
	  on_body,
	  on_message_complete
  };
  void llParser::set_type(llhttp_type t) { this->type = t; }
  llParser::llParser():body(0x3ff), header_field(0x1f), header_value(0x7f) {
	llhttp__internal_init(this); this->type = HTTP_REQUEST; this->settings = (void*)&_;
  }
}
