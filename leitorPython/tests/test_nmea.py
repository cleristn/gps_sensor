from pytest import approx
import datetime as dt
from leitor_gps.nmea import interpretar


def test_interpretar():
    GGA = '$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47'
    valores = {"hora": "12:35:19+00:00","latitude": approx(48+ 7.036 / 60), "qualidade": 1,"altitude": 545.4,"satelites": 8,"longitude": approx(11+ 31 / 60)}
    dados = interpretar(GGA)
    assert dados["hora"] == valores["hora"]
    assert dados["latitude"] == valores["latitude"]
    assert dados["qualidade"] == valores["qualidade"]
    assert dados["satelites"] == valores["satelites"]
    assert dados["altitude"] == valores["altitude"]
    assert dados["longitude"] == valores["longitude"]


def test_lixo():
    GGA = 'sdkasjfsdfkds'
    dados = interpretar(GGA)
    assert dados is None

# teste com fix igual a zero
def test_fix():
    GGA = '$GPGGA,123519,4807.038,N,01131.000,E,0,00,0.9,545.4,M,46.9,M,,*4E'
    dados = interpretar(GGA)
    assert dados is None

# testar utilizando o identificador GN
def test_interpretar_gn():
    GGA = '$GNGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*59'
    valores = {"hora": "12:35:19+00:00","latitude": approx(48+ 7.036 / 60), "qualidade": 1,"altitude": 545.4,"satelites": 8,"longitude": approx(11+ 31 / 60)}
    dados = interpretar(GGA)
    assert dados["hora"] == valores["hora"]
    assert dados["latitude"] == valores["latitude"]
    assert dados["qualidade"] == valores["qualidade"]
    assert dados["satelites"] == valores["satelites"]
    assert dados["altitude"] == valores["altitude"]
    assert dados["longitude"] == valores["longitude"]

def test_campo_vazio():
    GGA = '$GNGGA,123519,,,,,0,00,,,,,,,,*75'
    dados = interpretar(GGA)
    assert dados is None

def test_fix_sem_coordenadas():
    GGA = '$GNGGA,123519,,,,,1,00,,,,,,,*74'
    assert interpretar(GGA) is None
