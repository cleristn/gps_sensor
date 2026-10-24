import pynmea2


def interpretar(linha):

    try:
        msg = pynmea2.parse(linha)
       
        if msg.sentence_type != 'GGA':
            print(f"ignorada: tipo {msg.sentence_type}")
            return None
        if not msg.gps_qual or msg.gps_qual == 0:
            print("ignorada: GGA sem fix")
            return None

        if not msg.lat or not msg.lon:
            print("ignorada: GGA sem coordenadas")
            return None

        dados = {"hora": str(msg.timestamp),"latitude": msg.latitude, "qualidade": msg.gps_qual,"altitude": msg.altitude,"satelites": int(msg.num_sats),"longitude": msg.longitude}

        return dados

    except pynmea2.ParseError as e:
        print("ignorada: checksum ou formato inválido:", e)
        return None
    except ValueError as e:
        print("ignorada: campo não numérico:", e)
        return None
    
