cmake_minimum_required(VERSION 3.28)
project(ConversorDeUnidadesV2 C)

set(CMAKE_C_STANDARD 11)

add_executable(ConversorDeUnidadesV2 main.c
        unidades.c
        unid.h
        multunid.c
        validarentrada.c
        verifstring.c
        dadossalvos.c
        convunit.c
        temperatura.c
        funçãocategoria.c
        salvarconv.c
)
