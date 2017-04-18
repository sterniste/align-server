#ifndef ALIGN_API_LISTENER_H
#define ALIGN_API_LISTENER_H

#include <memory>
#include <stdexcept>
#include <string>

#include <boost/asio/ssl.hpp>
#include <boost/network/include/http/server.hpp>

namespace align_server {

struct unauthorized_http_request_exception : public std::runtime_error {
  unauthorized_http_request_exception(const std::string& msg) : std::runtime_error{msg} {}
};

class align_api_handler;
using http_request = boost::network::http::server<align_api_handler>::request;
using connection_ptr = boost::network::http::server<align_api_handler>::connection_ptr;

class align_api_handler {
 public:
  void operator()(const http_request& req, const connection_ptr& conn_ptr);
};

class align_http_server : public boost::network::http::server<align_api_handler> {
  static std::string password_callback(std::size_t max_length, boost::asio::ssl::context_base::password_purpose purpose);
  static std::shared_ptr<boost::network::utils::thread_pool> make_thread_pool();
  static std::shared_ptr<boost::asio::ssl::context> make_ssl_context(const std::string& cert_chain_file, const std::string& priv_key_file, const std::string& tmp_dh_file);
  static align_http_server::options make_server_options(align_api_handler& api_handler, const std::string& ip_addr, const std::string& port_str, const std::string& cert_chain_file, const std::string& priv_key_file, const std::string& tmp_dh_file);

 public:
  align_http_server(align_api_handler& api_handler, const std::string& ip_addr, const std::string& port_str, const std::string& cert_chain_file, const std::string& priv_key_file, const std::string& tmp_dh_file);
};

class align_api_listener : private align_api_handler, public align_http_server {
  static std::string make_port_str(uint16_t port);

  std::string port_str;

  public :
   align_api_listener(const std::string& ip_addr, uint16_t port, const std::string& cert_chain_file, const std::string& priv_key_file, const std::string& tmp_dh_file);
};
}
#endif
