//
// Copyright (C) 2017 Oleg Kertanov <okertanov@gmail.com>
//

#pragma once

#include "platform.h"
#include "handler.h"

namespace cone::app {
    class application {
        public:
            application(int argc, char** argv, const std::shared_ptr<cone::app::base_handler>& handler) :
                _args(), _handler(handler) {
                for(int i = 0; i < argc; i++) {
                    _args.push_back(std::string(argv[i]));
                }
            }

            virtual const application* daemonize() const {
                auto rc = daemon(0, 0);
                if (rc != 0) {
                    throw std::runtime_error(std::string("Failed to daemonize."));
                }
                return this;
            }

            virtual int run() const {
                _handler->invoke();
                return EXIT_SUCCESS;
            }

            virtual ~application() {
            }

        private:
            std::vector<std::string> _args;
            const std::shared_ptr<cone::app::base_handler> _handler;
    };
}
