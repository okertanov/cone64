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

            void invoke() const {
                auto thread = std::make_unique<std::thread>([&](){
                    invoke_impl();
                });
                thread->join();
            }

            virtual ~handler() {
            }

        private:
            void invoke_impl() const {
                while (true) {
                    _fn();
                    sleep(1000);
                }
            }

            void sleep(unsigned long ms) const {
                std::this_thread::sleep_for(std::chrono::milliseconds(ms));
            }

        private:
            const std::function<void(void)> _fn;
    };

    class application {
        public:
            application(int argc, char** argv, const std::shared_ptr<cone::app::handler>& handler) :
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
            const std::shared_ptr<cone::app::handler> _handler;
    };
}
