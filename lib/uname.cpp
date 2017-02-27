//
// Copyright (C) 2017 Oleg Kertanov <okertanov@gmail.com>
//

#include "platform.h"
#include "pubsub.h"
#include "app.h"

int main(int argc, char** argv) {
    const auto channel_name = "cone::uname";

    auto channel = std::make_unique<cone::pubsub::channel>(channel_name);
    auto handler = std::make_shared<cone::app::periodic_handler>([&channel] {
        auto buf = std::make_unique<utsname>();
        auto rc = uname(buf.get());
        if (rc != 0) {
            throw std::runtime_error("Failed to call uname.");
        }
        auto ss = std::make_unique<std::stringstream>();
        *ss << buf->sysname << " " << buf->nodename << " " << buf->release << " "
            << buf->version << " " << buf->machine;
        std::cout << ss->str() << std::endl;
    }, 1000);
    auto app = std::make_unique<cone::app::application>(argc, argv, handler);
    auto result = app->run();

    return result;
}
