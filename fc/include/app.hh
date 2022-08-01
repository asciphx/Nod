#pragma once
#include <functional>
#include <iostream>
#include <thread>
#include <atomic>
#include <memory>
#include <h/common.h>
#include <h/any_types.h>
#include "router.hh"
#include <buffer.hh>
#include <directory.hh>
#include <http_error.hh>
#include <file_sptr.hh>
// from https://github.com/matt-42/lithium/blob/master/libraries/http_server/http_server/api.hh
#define CTX_BUF_SIZE 0x10000
namespace fc {
  char c2m(const char* m);
  const char* m2c(HTTP m);
  //uv_idle_start(&this->idler, [](uv_idle_t* h) {
  //  uv_idle_stop(h);
  //  }); uv_idle_t idler; uv_idle_init(uv_default_loop(), &this->idler); this->idler.data = this;
  struct App {
	App();
	VH& operator[](const char* r);
	VH& del(const char* r);
	VH& get(const char* r = "/");//"\0"//with skip the last / of the url.
	VH& post(const char* r);
	VH& put(const char* r);
	//VH& patch(const char* r);
	//template <typename Adaptor> //websocket
	//void handle_upgrade(Req& req, Res& res, Adaptor&& adaptor) { handle_upgrade(req, res, adaptor); }
	///Process the Req and generate a Res for it
	Buffer _print_routes();
	void _call(HTTP& m, std::string& r, Req& request, Res& response) const;
	DRT map_;
    std::unordered_map<std::string, std::shared_ptr<file_sptr>> file_cache_;
	std::unordered_map<std::string_view, std::string_view>* content_types;
	void sub_api(const char* prefix, const App& subapi);
	//Serve static directory
	App serve_file(const char* r);
  };
} // namespace fc
