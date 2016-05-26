#include <gmock/gmock.h>
#include <native/native.hpp>

using namespace native;

TEST(DISABLED_ServerPlugin, CallbackData) {
  auto loop = Loop::GetInstanceOrCreateDefault();
  std::weak_ptr<Loop> loopWeak = Loop::GetInstanceOrCreateDefault();

  auto cbCallGet = [loopWeak](const std::string &uriTemplate, const std::string &uri, const bool iFullMatch) -> bool {
    std::shared_ptr<http::Server> server = http::Server::Create();
    std::weak_ptr<http::Server> serverWeak = server;
    bool called = false;
    std::string bodyText("TestData body");

    server->getSync(uriTemplate, [&called, loopWeak, bodyText](http::TransactionInstance iTransaction) {
      called = true;
      http::ServerResponse &res = iTransaction->getResponse();
      res.setStatus(200);
      res.setHeader("Content-Type", "text/plain");
      res.end(bodyText);
    });

    bool retVal = server->listen("0.0.0.0", 8080);
    EXPECT_EQ(true, retVal);

    // Send request
    http::get(loopWeak.lock(), "http://127.0.0.1:8080" + uri)
        .then([serverWeak](std::shared_ptr<http::ClientResponse>) { serverWeak.lock()->close(); })
        .error([serverWeak](const FutureError &err) { serverWeak.lock()->close(); });
    // TODO: replace above waiters with bellow finally method
    //.finally([serverWeak]() { serverWeak.close(); });

    loopWeak.lock()->run();
    return called;
  };

  EXPECT_EQ(true, cbCallGet("/", "/", true));
  EXPECT_EQ(true, cbCallGet("/test", "/test", true));
  EXPECT_EQ(false, cbCallGet("/test", "/tests", true));
}