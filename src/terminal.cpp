#include "terminal.h"
#include <unistd.h>
#include <iostream>

Terminal::Terminal() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
        throw std::runtime_error("Failed to get terminal attributes");
    }

    struct termios raw = orig_termios;

    raw.c_lflag &= ~(ECHO | ICANON | ISIG);
   // raw.c_oflag &= ~OPOST;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        throw std::runtime_error("Failed to set raw mode");
    }

    is_raw_enabled = true;
}

Terminal::~Terminal() {
    if (is_raw_enabled) {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
        is_raw_enabled = false;
    }
}