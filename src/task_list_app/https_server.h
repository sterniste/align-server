#ifndef HTTPS_SERVER_H
#define HTTPS_SERVER_H

#include <cstdint>
#include <string>

namespace boost {
namespace asio {
class io_service;
}
}

#include <asio_https_server.h>

#include <http_msgs.h>

namespace task_list {

class task_list_http_request : public asio_https::http_request {
  static void log_request(const asio_https::http_request& req);
  static void log_response(const asio_https::http_request& req, const asio_https::http_response& resp);

  std::string build_get_tasks_reply_json() const;
  asio_https::http_response handle_tasks_get_request() const;

 public:
  static asio_https::http_request* make_http_request(const std::string& http_resource_line);

  task_list_http_request(const std::string& http_resource_line);

  asio_https::http_response response() const override;
};

struct https_server : private asio_https::https_server {
  https_server(boost::asio::io_service& service, uint16_t port, const char* ssl_cert_chain_file, const char* ssl_priv_key_file, const char* ssl_tmp_dh_file);
};
}
#endif
