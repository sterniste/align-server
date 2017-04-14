#include <cstdint>

#include "https_listener.h"

namespace task_list {
using namespace std;

https_listener::https_listener(uint16_t port, const char* ssl_cert_chain_file, const char* ssl_priv_key_file, const char* ssl_tmp_dh_file) : server{service, port, ssl_cert_chain_file, ssl_priv_key_file, ssl_tmp_dh_file} {
  service.run();
}
}
