//
// Copyright (C) 2017 Oleg Kertanov <okertanov@gmail.com>
//

#pragma once

#include "platform.h"

namespace cone::app {
    class base_handler {
        public:
            base_handler(const std::function<void(void)>& fn) :
                _fn(std::move(fn)) {
            }

            virtual void invoke() const = 0;

            virtual ~base_handler() {
            }

        protected:
            void sleep(unsigned long ms) const {
                std::this_thread::sleep_for(std::chrono::milliseconds(ms));
            }

        protected:
            const std::function<void(void)> _fn;
    };

    class periodic_handler : public base_handler {
        public:
            periodic_handler(const std::function<void(void)>& fn, unsigned long period_ms) :
                base_handler(fn), _period_ms(period_ms) {
            }

            virtual void invoke() const {
                auto thread = std::make_unique<std::thread>([&](){
                    while (true) {
                        _fn();
                        sleep(_period_ms);
                    }
                });
                thread->join();
            }

            virtual ~periodic_handler() {
            }

        private:
            const unsigned long _period_ms;
    };
}
