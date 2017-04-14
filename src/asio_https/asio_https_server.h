#ifndef ASIO_HTTPS_SERVER_H
#define ASIO_HTTPS_SERVER_H

#include <cstddef>
#include <cstdint>
#include <functional>
#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "http_msgs.h"

namespace asio_https {

using ssl_socket = boost::asio::ssl::stream<boost::asio::ip::tcp::socket>;

using http_request_factory = std::function<http_request*(const std::string&)>;

class http_session {
  ssl_socket sock;
  http_request_factory make_http_request_fn;
  boost::asio::streambuf sbuf;
  std::unique_ptr<http_request> req;
  std::shared_ptr<std::vector<unsigned char>> content;

  static std::string get_request_line(std::streambuf& sbuf);

 public:
  http_session(boost::asio::io_service& service, boost::asio::ssl::context& ctx, http_request_factory make_http_request_fn) : sock(service, ctx), make_http_request_fn{make_http_request_fn} {}

  ssl_socket::lowest_layer_type& socket() { return sock.lowest_layer(); }

  void start();

  void handle_handshake(const boost::system::error_code& ec);
  void handle_request_resource_line(const boost::system::error_code& ec, size_t cnt);
  void handle_request_header_line(const boost::system::error_code& ec, size_t cnt);
  void handle_request_content(const boost::system::error_code& ec, size_t cnt);
  void handle_response(const boost::system::error_code& ec);
};

class https_server {
  boost::asio::io_service& service;
  boost::asio::ip::tcp::acceptor acceptor;
  boost::asio::ssl::context ctx;
  http_request_factory make_http_request_fn;

 public:
  https_server(boost::asio::io_service& service, uint16_t port, const char* ssl_cert_chain_file, const char* ssl_priv_key_file, const char* ssl_tmp_dh_file, http_request_factory make_http_request_fn);

  std::string get_password() const;
  void handle_accept(http_session* new_session, const boost::system::error_code& ec);
};
}
#endif
