#ifndef ALIGN_SERVER_APP_H
#define ALIGN_SERVER_APP_H

#include <cstdint>

#include "align_api_listener.h"

namespace align_server {

class align_server_app {
  align_api_listener api_listener;

 public:
  align_server_app(const char* host, uint16_t port, const char* cert_chain_file, const char* priv_key_file, const char* tmp_dh_file);
};
}
#endif
