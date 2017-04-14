#include <cstddef>
#include <cstdint>
#include <iostream>
#include <istream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>

#include <level_logging.h>

#include "asio_https_server.h"
#include "http_msgs.h"

namespace asio_https {
using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace universals;

string
http_session::get_request_line(std::streambuf& sbuf) {
  istream is{&sbuf};
  char buf[1024];
  if (!is.getline(buf, sizeof(buf), '\n'))
    throw runtime_error{"bad request line!"};
  string line{buf};
  trim_if(line, is_any_of("\r\t "));
  return line;
}

void
http_session::start() {
  sock.async_handshake(ssl::stream_base::server, boost::bind(&http_session::handle_handshake, this, asio::placeholders::error));
}

void
http_session::handle_handshake(const system::error_code& ec) {
  log_debug_tee(cout, "handle_handshake");
  if (ec) {
    log_info_tee(cout, static_cast<ostringstream&>(ostringstream{} << "handle_handshake ec=" << ec).str());
    delete this;
    return;
  }
  async_read_until(sock, sbuf, '\n', boost::bind(&http_session::handle_request_resource_line, this, asio::placeholders::error, asio::placeholders::bytes_transferred));
}

void
http_session::handle_request_resource_line(const system::error_code& ec, size_t cnt) {
  log_debug_tee(cout, "handle_request_resource_line");
  if (ec) {
    log_info_tee(cout, static_cast<ostringstream&>(ostringstream{} << "handle_request_resource_line ec=" << ec).str());
    delete this;
    return;
  }
  req = unique_ptr<http_request>{make_http_request_fn(get_request_line(sbuf))};
  async_read_until(sock, sbuf, '\n', boost::bind(&http_session::handle_request_header_line, this, asio::placeholders::error, asio::placeholders::bytes_transferred));
}

void
http_session::handle_request_header_line(const system::error_code& ec, size_t cnt) {
  log_debug_tee(cout, "handle_request_header_line");
  if (ec) {
    log_info_tee(cout, static_cast<ostringstream&>(ostringstream{} << "handle_request_header_line ec=" << ec).str());
    delete this;
    return;
  }
  if (req->add_header(get_request_line(sbuf)))
    async_read_until(sock, sbuf, '\n', boost::bind(&http_session::handle_request_header_line, this, asio::placeholders::error, asio::placeholders::bytes_transferred));
  else {
    const auto content_length{req->content_length()};
    if (content_length > 0) {
      content = make_shared<vector<unsigned char>>(content_length);
      async_read(sock, buffer(content.get(), content_length), boost::bind(&http_session::handle_request_content, this, asio::placeholders::error, asio::placeholders::bytes_transferred));
    } else {
      auto resp{make_shared<string>(req->response().str())};
      async_write(sock, buffer(resp->data(), resp->length()), boost::bind(&http_session::handle_response, this, asio::placeholders::error));
    }
  }
}

void
http_session::handle_request_content(const system::error_code& ec, size_t cnt) {
  log_debug_tee(cout, "handle_request_content");
  if (ec) {
    log_info_tee(cout, static_cast<ostringstream&>(ostringstream{} << "handle_request_content ec=" << ec).str());
    delete this;
    return;
  }
  req->set_content(content);
  std::shared_ptr<string> resp{make_shared<string>(req->response().str())};
  async_write(sock, buffer(resp->data(), resp->length()), boost::bind(&http_session::handle_response, this, asio::placeholders::error));
}

void
http_session::handle_response(const system::error_code& ec) {
  log_debug_tee(cout, "handle_response");
  if (ec) {
    log_info_tee(cout, static_cast<ostringstream&>(ostringstream{} << "handle_response ec=" << ec).str());
    delete this;
    return;
  }
  async_read_until(sock, sbuf, '\n', boost::bind(&http_session::handle_request_resource_line, this, asio::placeholders::error, asio::placeholders::bytes_transferred));
}

https_server::https_server(io_service& service, uint16_t port, const char* ssl_cert_chain_file, const char* ssl_priv_key_file, const char* ssl_tmp_dh_file, http_request_factory make_http_request_fn) : service(service), acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), port)), ctx(service, ssl::context::sslv23), make_http_request_fn{make_http_request_fn} {
  ctx.set_options(ssl::context::default_workarounds | ssl::context::no_sslv2 | ssl::context::single_dh_use);
  ctx.set_password_callback(boost::bind(&https_server::get_password, this));
  ctx.use_certificate_chain_file(ssl_cert_chain_file);
  ctx.use_private_key_file(ssl_priv_key_file, ssl::context::pem);
  ctx.use_tmp_dh_file(ssl_tmp_dh_file);

  http_session* new_session = new http_session(service, ctx, make_http_request_fn);
  acceptor.async_accept(new_session->socket(), boost::bind(&https_server::handle_accept, this, new_session, asio::placeholders::error));
}

string
https_server::get_password() const {
  return "test";
}

void
https_server::handle_accept(http_session* new_session, const system::error_code& ec) {
  log_debug_tee(cout, "handle_accept");
  if (ec) {
    log_info_tee(cout, static_cast<ostringstream&>(ostringstream{} << "handle_accept ec=" << ec).str());
    delete new_session;
    return;
  }
  new_session->start();
  new_session = new http_session(service, ctx, make_http_request_fn);
  acceptor.async_accept(new_session->socket(), boost::bind(&https_server::handle_accept, this, new_session, asio::placeholders::error));
}
}
