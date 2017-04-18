#ifndef ALIGN_SERVER_APP_H
#define ALIGN_SERVER_APP_H

#include <cstdint>
#include <string>

#include "align_api_listener.h"

namespace align_server {

class align_server_app {
  align_api_listener api_listener;

 public:
  align_server_app(const std::string& ip_addr, uint16_t port, const std::string& cert_chain_file, const std::string& priv_key_file, const std::string& tmp_dh_file);
};
}
#endif
