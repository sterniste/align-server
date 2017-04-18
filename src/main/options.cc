#include <cstdint>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/filesystem/operations.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/value_semantic.hpp>
#include <boost/program_options/variables_map.hpp>

#include <escape.h>
#include <level_logging.h>

#include "options.h"

namespace align_server {
using namespace std;
using namespace boost;
using namespace boost::filesystem;
using namespace boost::program_options;
using namespace universals;

options
options_parser::parse_options() {
  // gather options
  ostringstream opt_headers_oss;
  const char* const usage = "Usage: task_list [options]";
  opt_headers_oss << usage << endl << "Command-line options";
  options_description cmd_line_opts_desc(opt_headers_oss.str());
  cmd_line_opts_desc.add_options()("help", "this help message")("config-file,c", value<string>(), "configuration file");

  options_description config_file_opts_desc("Configuration options");
  config_file_opts_desc.add_options()("ip-addr,i", value<string>()->default_value("0.0.0.0"), "listener IP address")("port,p", value<uint16_t>()->default_value(8888), "listener port")("ssl-cert-chain-file", value<string>()->default_value("server.crt"), "SSL certificate chain file")("ssl-priv-key-file", value<string>()->default_value("server.key"), "SSL private key file")("ssl-tmp-dh-file", value<string>()->default_value("dh512.pem"), "SSL temporary DH file")
#ifdef LEVEL_LOGGING
  ("logs-dir", value<string>()->default_value("task_list_logs"), "logs dir")("log-level", value<string>()->default_value("info"), "log level: [fatal, error, warn, info, debug, trace]")
#endif
  ;
  cmd_line_opts_desc.add(config_file_opts_desc);

  variables_map var_map;
  vector<string> unrecognized_opts;
  try {
    const parsed_options parsed{command_line_parser(argc, argv).options(cmd_line_opts_desc).run()};
    store(parsed, var_map);
    notify(var_map);
    unrecognized_opts = collect_unrecognized(parsed.options, include_positional);
  } catch (const std::exception& e) { throw options_exception{string{"can't parse command line: "} + e.what()}; }
  if (!unrecognized_opts.empty())
    throw options_exception{string{"unrecognized options: "} + escape(unrecognized_opts)};

  // help
  if (var_map.count("help"))
    throw options_exception{static_cast<ostringstream&>(ostringstream{} << cmd_line_opts_desc).str(), true};

  if (var_map.count("config-file")) {
    const char* const config_file = var_map["config-file"].as<string>().c_str();
    if (!exists(config_file) || !is_regular_file(config_file))
      throw options_exception{string{"can't find configuration file '"} + config_file + '\''};
    store(parse_config_file<char>(var_map["config-file"].as<string>().c_str(), config_file_opts_desc), var_map);
  } else {
    const char* const config_file = "ia-core-ape.cfg";
    if (exists(config_file) && is_regular_file(config_file))
      store(parse_config_file<char>(config_file, config_file_opts_desc), var_map);
  }
  notify(var_map);

#ifdef LEVEL_LOGGING
  // validate logging opts
  log_level level = log_level::info;
  try {
    level = parse_log_level(var_map["log-level"].as<string>());
  } catch (const invalid_argument& e) { throw options_exception{string{"log level: '"} + var_map["log-level"].as<string>() + "' not in [fatal, error, warn, info, debug, trace]"}; }
  // logging setup
  init_logging(var_map["logs-dir"].as<string>().c_str(), level);
#endif
  string ip_addr;
  if (var_map.count("ip-addr"))
    ip_addr = var_map["ip-addr"].as<string>();

  const string ssl_cert_chain_file = var_map["ssl-cert-chain-file"].as<string>();
  if (!exists(ssl_cert_chain_file) || !is_regular_file(ssl_cert_chain_file))
    throw options_exception{string{"can't find SSL certificate chain file '"} + ssl_cert_chain_file + '\''};

  const string ssl_priv_key_file = var_map["ssl-priv-key-file"].as<string>();
  if (!exists(ssl_priv_key_file) || !is_regular_file(ssl_priv_key_file))
    throw options_exception{string{"can't find SSL private key file '"} + ssl_priv_key_file + '\''};

  const string ssl_tmp_dh_file = var_map["ssl-tmp-dh-file"].as<string>();
  if (!exists(ssl_tmp_dh_file) || !is_regular_file(ssl_tmp_dh_file))
    throw options_exception{string{"can't find SSL temporary DH file '"} + ssl_tmp_dh_file + '\''};

  return options{ip_addr, var_map["port"].as<uint16_t>(), ssl_cert_chain_file, ssl_priv_key_file, ssl_tmp_dh_file};
}
}
