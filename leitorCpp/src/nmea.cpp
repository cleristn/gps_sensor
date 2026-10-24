#include "leitor_gps/nmea.hpp"

#include <iostream>
#include <sstream>
#include <vector>

static std::vector<std::string> separar(const std::string& linha) {
    std::vector<std::string> campos;
    std::stringstream ss(linha);
    std::string campo;
    while (std::getline(ss, campo, ',')) {
        campos.push_back(campo);
    }
    return campos;
}

static double para_graus(const std::string& valor, int graus_digitos) {
    double graus = std::stod(valor.substr(0, graus_digitos));
    double minutos = std::stod(valor.substr(graus_digitos));
    return graus + minutos / 60.0;
}

std::optional<Dados> interpretar(const std::string& linha) {
    try {
        std::vector<std::string> campos = separar(linha);

        if (campos.size() < 10) {
            std::cout << "ignorada: linha inválida\n";
            return std::nullopt;
        }

        std::string tipo = campos[0].substr(campos[0].size() - 3);
        if (tipo != "GGA") {
            std::cout << "ignorada: tipo " << tipo << "\n";
            return std::nullopt;
        }

        if (campos[6].empty() || std::stoi(campos[6]) == 0) {
            std::cout << "ignorada: GGA sem fix\n";
            return std::nullopt;
        }

        if (campos[2].empty() || campos[4].empty()) {
            std::cout << "ignorada: GGA sem coordenadas\n";
            return std::nullopt;
        }

        Dados d;
        d.hora = campos[1].substr(0, 2) + ":" +
                 campos[1].substr(2, 2) + ":" +
                 campos[1].substr(4, 2);

        d.latitude = para_graus(campos[2], 2);
        if (campos[3] == "S") d.latitude = -d.latitude;

        d.longitude = para_graus(campos[4], 3);
        if (campos[5] == "W") d.longitude = -d.longitude;

        d.qualidade = std::stoi(campos[6]);
        d.satelites = std::stoi(campos[7]);
        d.altitude = std::stod(campos[9]);

        return d;

    } catch (const std::exception& e) {
	std::cout << "ignorada: campo inválido: " << e.what() << "\n"; 
        return std::nullopt;
    }
}
