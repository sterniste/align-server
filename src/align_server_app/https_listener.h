#ifndef HTTPS_LISTENER_H
#define HTTPS_LISTENER_H

#include <cstdint>

#include <boost/asio.hpp>

#include "https_server.h"

namespace task_list {

class https_listener {
  boost::asio::io_service service;
  https_server server;

 public:
  https_listener(uint16_t port, const char* ssl_cert_chain_file, const char* ssl_priv_key_file, const char* ssl_tmp_dh_file);
};
}
#endif
