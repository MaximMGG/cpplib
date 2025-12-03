#ifndef CPPLIG_CORE_STRBUF_HPP
#define CPPLIG_CORE_STRBUF_HPP
#include <string.h>
#include "types.hpp"

class Strbuf {

public:
  Strbuf();
  Strbuf(const char *s);
  ~Strbuf();
  char *toString();
  char *substring(int beg, int end);
  int find(const char c);
  int find(const char *s);
  void operator<<(const char *s);
  void operator<<(const char c);
  void remove(u32 pos, int count);
  void replace(const char *what, const char *s);
  u32 getlen();
  char *getdata();
private:
  char *data;
  u32 len;
  u32 cap;
};

#endif //CPPLIG_CORE_STRBUF_HPP
