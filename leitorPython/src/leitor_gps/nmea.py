import pynmea2


def interpretar(linha):

    try:
        msg = pynmea2.parse(linha)
        
        if msg.sentence_type != 'GGA':
            print(f"ignorada: tipo {msg.sentence_type}")
            return None

        if msg.gps_qual == 0:
            print("ignorada: GGA sem fix")
            return None

        dados = {"hora": str(msg.timestamp),"latitude": msg.latitude, "qualidade": msg.gps_qual,"altitude": msg.altitude,"satelites": int(msg.num_sats),"longitude": msg.longitude}

        return dados

    except (pynmea2.ParseError, ValueError):
        print("ignorada: linha inválida")
        return None
    
