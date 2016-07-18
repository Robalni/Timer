#pragma once

enum InputKey {
    start_stop_reset, reset, n_keys
};

class Input {
public:
    static void read();
    static bool is_down(InputKey key);
    static bool pressed(InputKey key);
    static bool released(InputKey key);

private:
    static void handle_event(InputKey key, int type);
    static void next_step();
};
