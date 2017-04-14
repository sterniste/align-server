#ifndef SSL_HMAC_HASH_H
#define SSL_HMAC_HASH_H

#include <cstdint>
#include <string>
#include <vector>

namespace jwt_verify {

enum class hash_algorithm : uint8_t { unknown = 0, hs256, hs384, hs512 };

std::vector<unsigned char> ssl_hmac_hash(hash_algorithm alg, const std::string& secret_key, const std::string& msg);
}
#endif
