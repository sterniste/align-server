#ifndef HTTP_MSGS_FWD_H
#define HTTP_MSGS_FWD_H

namespace boost {
namespace network {
namespace http {
namespace tags {
struct http_server;
}
template <typename Tag> class basic_request;
template <typename Tag> class basic_response;
}
}
}

namespace align_server {
using http_request = boost::network::http::basic_request<boost::network::http::tags::http_server>;
using http_response = boost::network::http::basic_response<boost::network::http::tags::http_server>;
}
#endif
