//
// Copyright (C) 2017 Oleg Kertanov <okertanov@gmail.com>
//

#pragma once

#include "platform.h"

namespace cone::app {
    class handler {
        public:
            handler(const std::function<void(void)>& fn) :
                _fn(std::move(fn)) {
            }

            virtual ~handler() {
            }

        private:
            const std::function<void(void)>& _fn;
    };

    class application {
        public:
            application(int argc, char** argv, const cone::app::handler& handler) :
                _args(), _handler(std::move(handler)) {
                for(int i = 0; i < argc; i++) {
                    _args.push_back(std::string(argv[i]));
                }
            }

            virtual application* daemonize() {
                auto rc = daemon(0, 0);
                if (rc != 0) {
                    throw std::runtime_error(std::string("Failed to daemonize."));
                }
                return this;
            }

            virtual int run() {
                return EXIT_SUCCESS;
            }

            virtual ~application() {
            }

        private:
            std::vector<std::string> _args;
            const cone::app::handler& _handler;
    };
}
