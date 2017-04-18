#ifndef OPTIONS_H
#define OPTIONS_H

#include <cstdint>
#include <stdexcept>
#include <string>

namespace align_server {

struct options_exception : public std::runtime_error {
  bool not_an_error;

  options_exception(const std::string& msg, bool not_an_error = false) : std::runtime_error{msg}, not_an_error{not_an_error} {}
};

struct options {
  const std::string ip_addr;
  const uint16_t port;
  const std::string ssl_cert_chain_file;
  const std::string ssl_priv_key_file;
  const std::string ssl_tmp_dh_file;

  options(const std::string& ip_addr, uint16_t port, const std::string& ssl_cert_chain_file, const std::string& ssl_priv_key_file, const std::string& ssl_tmp_dh_file) : ip_addr{ip_addr}, port{port}, ssl_cert_chain_file{ssl_cert_chain_file}, ssl_priv_key_file{ssl_priv_key_file}, ssl_tmp_dh_file{ssl_tmp_dh_file} {}
};

class options_parser {
  const int argc;
  const char* const* argv;

 public:
  options_parser(int argc, const char* argv[]) : argc{argc}, argv{argv} {}

  options parse_options();
};
}
#endif
