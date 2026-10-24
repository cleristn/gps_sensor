import serial


class LeitorSerial:
    def __init__(self, porta, baud=9600):
        self.ser = serial.Serial(porta, baud, timeout=1)

    def ler_linha(self):
        bruto = self.ser.readline()                          
        return bruto.decode("ascii", errors="ignore").strip()

    def fechar(self):
        self.ser.close()
