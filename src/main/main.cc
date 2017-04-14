#include <exception>
#include <iostream>
#include <thread>

#include <https_listener.h>
#include <level_logging.h>

#include "options.h"

namespace {
using namespace std;
using namespace universals;
using namespace task_list;
}

int
main(int argc, const char* argv[]) {
  try {
    const options opts{options_parser{argc, argv}.parse_options()};
    log_info_start(argc, argv);

    https_listener listener{opts.port, opts.ssl_cert_chain_file.c_str(), opts.ssl_priv_key_file.c_str(), opts.ssl_tmp_dh_file.c_str()};
    this_thread::sleep_for(3600s);
  } catch (const options_exception& e) {
    if (e.not_an_error) {
      cout << e.what() << endl;
      return 0;
    }
    log_fatal_tee(cerr, string{"options error: "} + e.what());
    return 1;
  } catch (const exception& e) {
    log_fatal_tee(cerr, string{"caught exception: "} + e.what());
    return 1;
  } catch (...) {
    log_fatal_tee(cerr, "caught ...");
    return 1;
  }
}
