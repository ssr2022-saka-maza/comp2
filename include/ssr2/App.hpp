#pragma once

#include "ssr2/LimitedVector.hpp"
#include "ssr2/Machine.hpp"
#include "ssr2/Process.hpp"
#include <Arduino.h>

namespace ssr2 {

class App {
private:
    Machine * _machine;
    LimitedVector<Process *, 64> _processes;

public:
    explicit App(Machine * machine) noexcept;

    App(const App &) = delete;
    App & operator=(const App &) = delete;
    App(App &&) = delete;
    App & operator=(App &&) = delete;
    ~App() = default;

    void begin() noexcept;
    void update() noexcept;
    Machine * machine() noexcept;
    void addProcess(Process * process) noexcept;
};  // class App

}  // namespace ssr2
