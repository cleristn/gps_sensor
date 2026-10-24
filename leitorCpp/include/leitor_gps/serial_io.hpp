#pragma once
#include <string>

class LeitorSerial {
public:
    LeitorSerial(const std::string& porta);
    ~LeitorSerial();
    bool aberta() const;
    std::string ler_linha();

private:
    int fd;
};
