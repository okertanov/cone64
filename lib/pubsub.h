//
// Copyright (C) 2017 Oleg Kertanov <okertanov@gmail.com>
//

#pragma once

namespace cone::pubsub {
    class channel {
        public:
            channel(const std::string channel_name)
                : _channel_name(channel_name) {
            }

            virtual ~channel() {
            }

        private:
            const std::string _channel_name;
    };
}
