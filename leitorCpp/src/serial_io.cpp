#include "leitor_gps/serial_io.hpp"

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

LeitorSerial::LeitorSerial(const std::string& porta) {

    fd = open(porta.c_str(), O_RDWR | O_NOCTTY);
    if (fd < 0) return;

    termios tty;
    tcgetattr(fd, &tty);
    cfmakeraw(&tty);
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 10;
    tcsetattr(fd, TCSANOW, &tty);
}

LeitorSerial::~LeitorSerial() {
    if (fd >= 0) close(fd);
}

bool LeitorSerial::aberta() const {
    return fd >= 0;
}

std::string LeitorSerial::ler_linha() {
    std::string linha;
    char c;
    // lê um byte por vez até o fim da linha \n ou timeout
    while (read(fd, &c, 1) == 1) {
        if (c == '\n') break;
        if (c != '\r') linha += c;
    }
    return linha;
}
