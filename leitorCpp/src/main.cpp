#include <iostream>
#include <string>

#include "leitor_gps/nmea.hpp"
#include "leitor_gps/serial_io.hpp"

int main(int argc, char* argv[]) {
    std::string porta = (argc > 1) ? argv[1] : "/dev/ttyUSB0";

    LeitorSerial leitor(porta);
    if (!leitor.aberta()) {
        std::cout << "Não foi possível abrir a porta " << porta << "\n";
        return 1;
    }
    
    int mostrou = 0;
    while (true) {
        std::string linha = leitor.ler_linha();
        if (linha.empty()) continue;

        std::cout << "RAW: " << linha << "\n";
        auto dados = interpretar(linha);
        if (dados) {
            std::cout << "DADOS: " << dados->hora
                      << " lat " << dados->latitude
                      << " lon " << dados->longitude
                      << " alt " << dados->altitude
                      << " sat " << dados->satelites << "\n";
	    if(!mostrou) std::cout << "MAPA: https://www.google.com/maps?q=" << dados->latitude << "," << dados->longitude << std::endl;
	    mostrou = 1;
        }
    }
}
