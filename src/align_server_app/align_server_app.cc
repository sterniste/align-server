#include <cstdint>
#include <string>

#include "align_api_listener.h"
#include "align_server_app.h"

namespace align_server {
using namespace std;

align_server_app::align_server_app(const string& ip_addr, uint16_t port, const string& cert_chain_file, const string& priv_key_file, const string& tmp_dh_file) : api_listener{ip_addr, port, cert_chain_file, priv_key_file, tmp_dh_file} {
  api_listener.run();
}
}
