#include <array>
#include <string>
#include <vector>

#include <openssl/evp.h>
#include <openssl/hmac.h>

#include "ssl_hmac_hash.h"

namespace jwt_verify {
using namespace std;

typedef const EVP_MD* (*evp_type)();

evp_type
hash_algorithm_evp_type(hash_algorithm alg) {
  switch (alg) {
  case hash_algorithm::hs256:
    return EVP_sha256;
  case hash_algorithm::hs384:
    return EVP_sha384;
  case hash_algorithm::hs512:
    return EVP_sha512;
  default:
    return nullptr;
  }
}

vector<unsigned char>
ssl_hmac_hash(hash_algorithm alg, const string& secret_key, const string& msg) {
  array<unsigned char, EVP_MAX_MD_SIZE> md_buf;
  unsigned int md_len{};
  HMAC(hash_algorithm_evp_type(alg)(), secret_key.data(), secret_key.length(), reinterpret_cast<const unsigned char*>(msg.data()), msg.length(), md_buf.data(), &md_len);
  return vector<unsigned char>(md_buf.cbegin(), md_buf.cbegin() + md_len);
}
}
