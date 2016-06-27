#ifndef __NATIVE_HTTP_HPP__
#define __NATIVE_HTTP_HPP__

#include "http/ClientRequest.hpp"
#include "http/ClientResponse.hpp"
#include "http/HttpUtils.hpp"
#include "http/Server.hpp"
#include "http/ServerConnection.hpp"
#include "http/ServerPlugin.hpp"
#include "http/ServerRequest.hpp"
#include "http/ServerResponse.hpp"
#include "http/UrlObject.hpp"

namespace native {
namespace http {

/**
 * Encode a URL to a percent-encoded form.
 * @param  url URL to encode
 * @param allowedChars allowed chars. This value can be change if it is required to encode a parameter value
 * @return     encoded URL
 */
std::string encodeUrl(const std::string &url,
                      const std::string &allowedChars = "/?=&#",
                      const std::string &valueAllowedShars = "-_.:[]~!$()'*,;@");

/**
 * Decode a URL from a percent-encoded form.
 * @param  url URL to decode
 * @return     decoded URL
 */
std::string decodeUrl(const std::string &url, const bool spaceAsPlus = true);

Future<std::shared_ptr<ClientResponse>> request(std::shared_ptr<Loop> iLoop,
                                                const std::string &method,
                                                const std::string &host,
                                                const int port,
                                                const std::string &path);

Future<std::shared_ptr<ClientResponse>> get(std::shared_ptr<Loop> iLoop, const std::string &uri);
Future<std::shared_ptr<ClientResponse>>
get(std::shared_ptr<Loop> iLoop, const std::string &host, const int port, const std::string &path);

} /* namespace http */
} /* namespace native */

#endif /* __NATIVE_HTTP_HPP__ */
