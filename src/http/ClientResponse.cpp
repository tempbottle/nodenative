#include "native/http/ClientResponse.hpp"
#include "native/http/ClientRequest.hpp"
#include "native/net/Tcp.hpp"

namespace native {
namespace http {

ClientResponse::ClientResponse(std::shared_ptr<ClientRequest> iReq)
    : IncomingMessage(false /*iIsRequest*/) {}

ClientResponse::~ClientResponse() {}

void ClientResponse::onMessageComplete() {}

} /* namespace http */
} /* namespace native */
