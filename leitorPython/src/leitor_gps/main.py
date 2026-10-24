import sys

from leitor_gps.nmea import interpretar
from leitor_gps.serial_io import LeitorSerial


def main():
    porta = sys.argv[1] if len(sys.argv) > 1 else "/dev/ttyUSB0"
    leitor = LeitorSerial(porta)

    try:
        mostrou = False
        while True:
            linha = leitor.ler_linha()
            if not linha:
                continue
            print("RAW:", linha)
            dados = interpretar(linha)
            if dados:
                print("DADOS:", dados)
                if not mostrou:
                    print(f"MAPA: https://www.google.com/maps?q={dados['latitude']},{dados['longitude']}")
                    mostrou = True
    except KeyboardInterrupt:
        pass
    finally:
        leitor.fechar()


if __name__ == "__main__":
    main()
