#ifndef ALIGN_API_LISTENER_H
#define ALIGN_API_LISTENER_H

#include <memory>
#include <stdexcept>
#include <string>

#include <boost/asio/ssl.hpp>
#include <boost/network/include/http/server.hpp>
#include <boost/network/protocol/http/response.hpp>

namespace align_server {

struct unauthorized_http_request_exception : public std::runtime_error {
  unauthorized_http_request_exception(const std::string& msg) : std::runtime_error{msg} {}
};

class align_api_handler;
using http_request = boost::network::http::server<align_api_handler>::request;
using http_response = boost::network::http::basic_response<align_api_handler>;

class align_api_handler {
 public:
  void operator()(const http_request& req, http_response& resp);
};

class align_http_server : public boost::network::http::server<align_api_handler> {
  static std::string password_callback(std::size_t max_length, boost::asio::ssl::context_base::password_purpose purpose);
  static std::shared_ptr<boost::network::utils::thread_pool> make_thread_pool();
  static std::shared_ptr<boost::asio::ssl::context> make_ssl_context(const char* cert_chain_file, const char* priv_key_file, const char* tmp_dh_file);
  static align_http_server::options make_server_options(align_api_handler& api_handler, const char* host, const char* port_cstr, const char* cert_chain_file, const char* priv_key_file, const char* tmp_dh_file);

 public:
  align_http_server(align_api_handler& api_handler, const char* host, const char* port_cstr, const char* cert_chain_file, const char* priv_key_file, const char* tmp_dh_file);
};

class align_api_listener : private align_api_handler {
  static std::string make_port_str(uint16_t port);

  std::shared_ptr<align_http_server> http_server;
  
  public :
   align_api_listener(const char* host, uint16_t port, const char* cert_chain_file, const char* priv_key_file, const char* tmp_dh_file);

   void run() { http_server->run(); }   
};
}
#endif
