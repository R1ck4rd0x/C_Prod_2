#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h> // Librería necesaria para operacioens con protocolo TCP/IP 
#include <ws2tcpip.h> // Librería complementaria a la anterior
#include <iphlpapi.h> // Librería que incluye tipos de variables de red
#include "Cabeceras.h" // Libreria de encabezados de todas mis funciones

#pragma comment(lib, "Ws2_32.lib")

// Definimos el tamaño máximo para las constantes MAX_LENGTH y MIN_LENGTH

#define MAX_LENGTH 256
#define MIN_LENGTH 64

// CUERPO PRINCIPAL

int main() {
    menu();
    return 0;
}