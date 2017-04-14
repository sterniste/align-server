#include <functional>
#include <sstream>
#include <string>

#include <boost/asio.hpp>

#include <asio_https_server.h>
#include <http_msgs.h>
#include <level_logging.h>

#include "https_server.h"

namespace task_list {
using namespace std;
using namespace boost::asio;
using namespace universals;
using namespace asio_https;

void
task_list_http_request::log_request(const http_request& req) {
  ostringstream oss;
  oss << "HTTP request: " << req.get_method() << ' ' << req.uri_str();
  for (const auto& header : req.get_headers())
    oss << '<' << header.first << "='" << header.second << "'>";
  const auto content_length = req.content_length();
  if (content_length > 0) {
    assert(req.get_content() && req.get_content()->size() == content_length);
    oss << '{';
    for (unsigned char c : *req.get_content()) {
      switch (c) {
      case '\\':
        oss << "\\\\";
        break;
      case '\t':
        oss << "\\t";
        break;
      case '\r':
        oss << "\\r";
        break;
      case '\n':
        oss << "\\n";
        break;
      case '?':
        oss << "\\?";
        break;
      default:
        if (c < ' ' || c >= 0x7f)
          oss << '?';
        else
          oss << c;
        break;
      }
    }
    oss << '}';
  }
  log_info(oss.str());
}

void
task_list_http_request::log_response(const http_request& req, const http_response& resp) {
  ostringstream oss;
  oss << "HTTP reply to: " << req.get_method() << ' ' << req.uri_str();
  for (const auto& header : resp.get_headers())
    oss << '<' << header.first << "='" << header.second << "'>";
  log_info(oss.str());
}

string
task_list_http_request::build_get_tasks_reply_json() const {
  return "[]";
}

http_response
task_list_http_request::handle_tasks_get_request() const {
  return http_response{http_status_code::ok, {{http_response::content_type_key, "application/json"}}, build_get_tasks_reply_json()};
}

http_request*
task_list_http_request::make_http_request(const string& http_resource_line) {
  return new task_list_http_request{http_resource_line};
}

task_list_http_request::task_list_http_request(const string& http_resource_line) {
  const auto resource{parse_resource_line(http_resource_line)};
  method = resource.first;
  uri_path = resource.second.first;
  uri_query = resource.second.second;
}

http_response
task_list_http_request::response() const {
  log_request(*this);
  http_response resp{};
  if (method == "GET" && uri_str() == "/task-lists")
    resp = handle_tasks_get_request();
  log_response(*this, resp);
  return resp;
}

https_server::https_server(io_service& service, uint16_t port, const char* ssl_cert_chain_file, const char* ssl_priv_key_file, const char* ssl_tmp_dh_file) : asio_https::https_server{service, port, ssl_cert_chain_file, ssl_priv_key_file, ssl_tmp_dh_file, std::bind(&task_list_http_request::make_http_request, std::placeholders::_1)} {}
}
