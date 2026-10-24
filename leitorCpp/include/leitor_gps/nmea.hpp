#pragma once
#include <optional>
#include <string>

struct Dados {
    std::string hora;
    double latitude;
    double longitude;
    double altitude;
    int qualidade;
    int satelites;
};

std::optional<Dados> interpretar(const std::string& linha);
