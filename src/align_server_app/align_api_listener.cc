#include <cstddef>
#include <cstdint>
#include <exception>
#include <memory>
#include <sstream>
#include <string>

#include <boost/asio/ssl.hpp>
#include <boost/network/include/http/server.hpp>
#include <boost/network/protocol/http/server/options.hpp>

#include <level_logging.h>

#include "align_api_listener.h"

namespace align_server {
using namespace std;
using std::exception;
using std::make_shared;
using std::make_unique;
using std::ostringstream;
using std::shared_ptr;
using std::string;
using namespace boost;
using namespace boost::asio;
using namespace boost::network;
using namespace universals;

void
align_api_handler::operator()(const http_request& req, const connection_ptr& conn_ptr) {
  try {
  } catch (const unauthorized_http_request_exception& e) {
  } catch (const exception& e) { log_info_tee(cout, string{"caught exception: "} + e.what()); } catch (...) {
    log_info_tee(cout, "caught unknown exception!");
  }
}

string
align_http_server::password_callback(size_t max_length, ssl::context_base::password_purpose purpose) {
  return string{"test"};
}

shared_ptr<utils::thread_pool>
align_http_server::make_thread_pool() {
  return make_shared<utils::thread_pool>(2);
}

shared_ptr<ssl::context>
align_http_server::make_ssl_context(const string& cert_chain_file, const string& priv_key_file, const string& tmp_dh_file) {
  const shared_ptr<ssl::context> ssl_ctx{make_shared<ssl::context>(ssl::context::sslv23)};
  ssl_ctx->set_options(ssl::context::default_workarounds | ssl::context::no_sslv2 | ssl::context::single_dh_use);
  ssl_ctx->set_password_callback(password_callback);
  ssl_ctx->use_certificate_chain_file(cert_chain_file);
  ssl_ctx->use_private_key_file(priv_key_file, ssl::context::pem);
  ssl_ctx->use_tmp_dh_file(tmp_dh_file);
  return ssl_ctx;
}

align_http_server::options
align_http_server::make_server_options(align_api_handler& api_handler, const string& ip_addr, const string& port_str, const string& cert_chain_file, const string& priv_key_file, const string& tmp_dh_file) {
  return align_http_server::options{api_handler}.address(ip_addr).port(port_str).reuse_address(true).thread_pool(make_thread_pool()).context(make_ssl_context(cert_chain_file, priv_key_file, tmp_dh_file));
}

align_http_server::align_http_server(align_api_handler& api_handler, const string& ip_addr, const string& port_str, const string& cert_chain_file, const string& priv_key_file, const string& tmp_dh_file) : http::server<align_api_handler>{make_server_options(api_handler, ip_addr, port_str, cert_chain_file, priv_key_file, tmp_dh_file)} {}

string
align_api_listener::make_port_str(uint16_t port) {
  ostringstream oss;
  oss << port;
  return oss.str();
}

align_api_listener::align_api_listener(const string& ip_addr, uint16_t port, const string& cert_chain_file, const string& priv_key_file, const string& tmp_dh_file) : align_http_server{*this, ip_addr, make_port_str(port), cert_chain_file, priv_key_file, tmp_dh_file} {}
}
