#include "strbuf.hpp"

#define STRBUF_DEF_CAP 4096

Strbuf::Strbuf() {
  this->data = new char [STRBUF_DEF_CAP];
  this->len = 0;
  this->cap = STRBUF_DEF_CAP;
}

Strbuf::Strbuf(const char *s) {
  int s_len = strlen(s);
  if (s_len >= STRBUF_DEF_CAP) {
    this->data = new char [s_len + 1];
    strcpy(this->data, s);
    this->cap = s_len;
    this->len = s_len;
  } else {
    this->data = new char [STRBUF_DEF_CAP];
    memset(this->data, 0, STRBUF_DEF_CAP);
    strcpy(this->data, s);
    this->len = s_len;
    this->cap = STRBUF_DEF_CAP;
  }
}

Strbuf::~Strbuf() {
  delete [] this->data;
}

char *Strbuf::toString() {
  char *res = new char [this->len + 1];
  strcpy(res, this->data);
  return res;
}

char *Strbuf::substring(int beg, int end) {
  if (beg >= end) {
    return NULL;
  }
  int len = end - beg;
  char *res = new char [len + 1];
  strncpy(res, this->data, len);
  return res;
}

int Strbuf::find(char c) {
  for(int i = 0; i < this->len; i++) {
    if (this->data[i] == c) {
      return i;
    }
  }
  return -1;
}

int Strbuf::find(const char *s) {
  char *tmp = strstr(this->data, s);
  if (tmp != NULL) {
    return tmp - this->data;
  } else {
    return -1;
  }
}

void Strbuf::operator<<(const char *s) {
  int s_len = strlen(s);
  while (this->cap - this->len <= s_len) {
    this->cap <<= 1;
    char *new_buf = new char [this->cap];
    memset(new_buf, 0, this->cap);
    strcpy(new_buf, this->data);
    delete [] this->data;
    this->data = new_buf;
  }
  strcpy(&this->data[this->len], s);
  this->len += s_len;
}


void Strbuf::operator<<(char c) {
  if (this->len + 1 >= this->cap) {
    this->cap <<= 1;
    char *new_buf = new char [this->cap];
    memset(new_buf, 0, this->cap);
    strcpy(new_buf, this->data);
    delete [] this->data;
    this->data = new_buf;
  }
  this->data[this->len++] = c;
}

void Strbuf::remove(u32 pos, i32 count) {
  if (pos >= this->len) {
    return;
  }
  if (pos + count >= this->len) {
    return;
  }

  char *tmp_buf = new char [this->cap];
  memset(tmp_buf, 0, this->cap);
  strncpy(tmp_buf, this->data, pos);
  strncpy(&tmp_buf[pos], &this->data[pos + count], this->len - (pos + count));
}

void Strbuf::replace(const char *what, const char *s) {
  i32 find_pos;
  i32 what_len = strlen(what);
  i32 s_len = strlen(s);
  while (this->cap - this->len <= s_len - what_len) {
    this->cap <<= 1;
    char *new_buf = new char [this->cap];
    memset(new_buf, 0, this->cap);
    strcpy(new_buf, this->data);
    delete [] this->data;
    this->data = new_buf;
  }

  while((find_pos = find(what)) != -1) {
    char *tmp_buf = new char [this->cap];
    memset(tmp_buf, 0, this->cap);
    strncpy(tmp_buf, this->data, find_pos);
    strncpy(&tmp_buf[find_pos], s, s_len);
    strcpy(&tmp_buf[find_pos + s_len], &this->data[find_pos + what_len]);

    delete [] this->data;
    this->data = tmp_buf;
    this->len = this->len - what_len + s_len;
  }
}

u32 Strbuf::getlen() {
  return this->len;
}

char *Strbuf::getdata() {
  return this->data;
}
