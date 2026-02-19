cmake_minimum_required(VERSION 3.16)

project(Desafio1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Desafio1 main.cpp
    README.md
    .gitignore
    io.h io.cpp
    crypto.h crypto.cpp
    auxiliares.h auxiliares.cpp
    detectarydescomprimir.h detectarydescomprimir.cpp)

include(GNUInstallDirs)
install(TARGETS Desafio1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
