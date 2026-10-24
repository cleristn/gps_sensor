cmake_minimum_required(VERSION 3.10)
project(leitor_gps CXX)

set(CMAKE_CXX_STANDARD 17)

# pasta dos headers (.hpp)
include_directories(include)

# biblioteca com a lógica (usada pelo programa e pelo teste)
add_library(leitor_gps_lib src/nmea.cpp)

# programa principal
add_executable(leitor_gps src/main.cpp)
target_link_libraries(leitor_gps leitor_gps_lib)

# teste
enable_testing()
add_executable(test_nmea tests/test_nmea.cpp)
target_link_libraries(test_nmea leitor_gps_lib)
add_test(NAME test_nmea COMMAND test_nmea)
