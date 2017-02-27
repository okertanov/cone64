//
// Copyright (C) 2017 Oleg Kertanov <okertanov@gmail.com>
//

#include "platform.h"
#include "pubsub.h"
#include "app.h"

int main(int argc, char** argv) {
    const std::string channel_name = "cone::uname";

    auto channel = std::make_unique<cone::pubsub::channel>(channel_name);
    auto handler = std::make_shared<cone::app::handler>([&channel] {
        std::cerr << "handler: " << &channel << std::endl;
    });
    auto app = std::make_unique<cone::app::application>(argc, argv, handler);
    auto result = app->run();

    return result;
}
