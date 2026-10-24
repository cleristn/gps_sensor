#include <cassert>
#include <cmath>
#include "leitor_gps/nmea.hpp"

static bool aproximado(double a, double b) {
    return std::abs(a - b) < 0.0001;
}

int main() {
    auto d = interpretar("$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47");
    assert(d.has_value());
    assert(d->satelites == 8);

    assert(aproximado(d->latitude, 48.1173));
    assert(aproximado(d->longitude, 11.51667));

    assert(!interpretar("lixo qualquer").has_value());
    assert(!interpretar("$GNGGA,123519,,,,,1,00,,,,,,,*74").has_value());
    assert(!interpretar("$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A").has_value());
    assert(!interpretar("$GPGGA,123519,4807.038,N,01131.000,E,0,00,0.9,545.4,M,46.9,M,,*4E").has_value());
    return 0;
}
