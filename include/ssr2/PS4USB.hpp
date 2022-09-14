#pragma once

#include <Arduino.h>

#include <PS4Parser.h>
#include <PS4USB.h>
#include <usbhub.h>

#include <SPI.h>

#ifdef dobogusinclude
// https://github.com/stevenvo/arduino-libraries/tree/master/spi4teensy3
// Arduino Megaなので、多分消しても大丈夫
#include <spi4teensy3.h>
#endif /* dobogusinclude */

#include "ssr2/PS4Value.hpp"

namespace ssr2 {
    class PS4USB {
    private:
        USB _usb;
        ::PS4USB _ps4;

    public:
        explicit PS4USB();
        ~PS4USB() = default;

        PS4USB(const PS4USB &) = delete;
        PS4USB & operator=(const PS4USB &) = delete;
        PS4USB(PS4USB&&) = delete;
        PS4USB & operator=(PS4USB&&) = delete;

        int begin();
        void update();
        bool connected();

        void read(ssr2::PS4Value * output);
        PS4Value * read();
    }; // class PS4USB
} // namespace ssr2
