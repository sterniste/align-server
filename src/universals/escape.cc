#include <string>
#include <vector>

namespace universals {
using namespace std;

string
escape(const char* cs) {
  string esc;
  while (*cs) {
    switch (*cs) {
    case ' ':
      esc.push_back('\\');
      esc.push_back(' ');
      break;
    case '\t':
      esc.push_back('\\');
      esc.push_back('t');
      break;
    case '\n':
      esc.push_back('\\');
      esc.push_back('n');
      break;
    case '\r':
      esc.push_back('\\');
      esc.push_back('r');
      break;
    case '\\':
      esc.push_back('\\');
      esc.push_back('\\');
      break;
    default:
      esc.push_back(*cs);
      break;
    }
    ++cs;
  }
  return esc;
}

string
escape(const string& s) {
  return escape(s.c_str());
}

string
escape(const vector<const char*>& vcs) {
  string esc;
  bool prev_cs = false;
  for (const auto cs : vcs) {
    if (prev_cs)
      esc.push_back(' ');
    esc += escape(cs);
    prev_cs = true;
  }
  return esc;
}

string
escape(const vector<string>& vs) {
  string esc;
  bool prev_s = false;
  for (const auto& s : vs) {
    if (prev_s)
      esc.push_back(' ');
    esc += escape(s.c_str());
    prev_s = true;
  }
  return esc;
}

string
escape(int argc, const char* argv[]) {
  string esc;
  for (auto i = 0; i < argc; ++i) {
    if (i)
      esc.push_back(' ');
    esc += escape(argv[i]);
  }
  return esc;
}
}
