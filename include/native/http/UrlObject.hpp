#ifndef __NATIVE_HTTP_URLOBJECT_HPP__
#define __NATIVE_HTTP_URLOBJECT_HPP__

#include <http_parser.h>
#include <string>

namespace native {
namespace http {

class UrlObject {
public:
  UrlObject();
  ~UrlObject();

  UrlObject(const UrlObject &c);
  UrlObject &operator=(const UrlObject &c);

  std::string schema() const;
  std::string host() const;
  int port() const;
  std::string path() const;
  std::string query() const;
  std::string fragment() const;
  const std::string &str() const { return _buf; }

  void parse(const std::string &buf, bool is_connect = false) { parse(buf.c_str(), buf.size(), is_connect); }

  void parse(const char *buf, std::size_t len, bool is_connect = false);

  bool hasSchema() const { return _handle.field_set & (1 << UF_SCHEMA); }
  bool hasHost() const { return _handle.field_set & (1 << UF_HOST); }
  bool hasPort() const { return _handle.field_set & (1 << UF_PORT); }
  bool hasPath() const { return _handle.field_set & (1 << UF_PATH); }
  bool hasQuery() const { return _handle.field_set & (1 << UF_QUERY); }
  bool hasFragment() const { return _handle.field_set & (1 << UF_FRAGMENT); }

private:
  http_parser_url _handle;
  std::string _buf;
};

} /* namespace http */
} /* namespace native */

#endif /* __NATIVE_HTTP_URLOBJECT_HPP__ */
