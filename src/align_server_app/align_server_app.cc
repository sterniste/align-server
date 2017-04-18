#include <cstdint>

#include "align_api_listener.h"
#include "align_server_app.h"

namespace align_server {

align_server_app::align_server_app(const char* host, uint16_t port, const char* cert_chain_file, const char* priv_key_file, const char* tmp_dh_file) : api_listener{host, port, cert_chain_file, priv_key_file, tmp_dh_file} {
  api_listener.run();
}
}
