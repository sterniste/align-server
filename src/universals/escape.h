#pragma once

#include <string>
#include <vector>

namespace universals {

std::string escape(const char *cs);

std::string escape(const std::string &s);

std::string escape(const std::vector<const char *> &vcs);

std::string escape(const std::vector<std::string> &vs);

std::string escape(int argc, const char* argv[]);
}
