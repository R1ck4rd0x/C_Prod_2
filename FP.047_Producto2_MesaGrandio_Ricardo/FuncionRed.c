/* Esta funci�n obtiene la configuraci�n de red completa de la m�quina local para
  los diferentes adaptadores y los almacena en el archivo informacionlocal.txt */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h> // Librer�a necesaria para operacioens con protocolo TCP/IP
#include <ws2tcpip.h> // Librer�a complementaria a la anterior
#include <iphlpapi.h> // Librer�a que incluye tipos de variables de red
#include "Cabeceras.h" // Libreria de encabezados de todas mis funciones

void printNetworkConfig() {

    // Se declaran dos punteros a un archivo fp y fp2, y NetInfo, que es un buffer donde se guardar� la salida
    FILE* fp, * fp2;
    char NetInfo[4096] = { 0 }; // Inicializamos el buffer a 0

    /* El comando ipconfig /all muestra informaci�n detallada sobre la configuraci�n de red en la computadora,
       mientras que  _popen es el comando que abre el proceso ipconfig
       Si falla al posicionar el puntero, nos devuelve NULL dar� el error y sale de la funci�n
    */
    fp = _popen("ipconfig /all", "r");
    if (fp == NULL) {
        printf("No se pudo abrir el archivo de salida\n");
        exit(1);
    }
    // Abrimos el archivo de texto modo escritura y posicionamos el puntero fp2
    fp2 = fopen("informacionlocal.txt", "w");
    if (fp2 == NULL) {
        printf("No se pudo abrir el archivo para escribir\n");
        exit(1);
    }
    /* Imprimimos por pantalla la salida del comando anterior haciendo un bucle para que la funci�n fgets() lea
       la salida del proceso adem�s de almacenarla en NetInfo hasta que se alcance el final de archivo (NULL),
       o se alcance el tama�o m�ximo del buffer asignado
    */
    printf("La configuraci�n total de Red de este PC con Sistema Windows es:\n");

    while (fgets(NetInfo, sizeof(NetInfo), fp) != NULL) {
        printf("%s", NetInfo);
        fprintf(fp2, "%s", NetInfo); // el volcado lo hac�a al final pero siempre daba un contenido raro, linea a linea lo imprime bien
    }
    // Cerramos el proceso ipconfig con _pclose por si hay que volver a abrirlo
    _pclose(fp);
    // Cerramos el archivo de texto
    fclose(fp2);

    printf("\n");
    printf("------------< Informaci�n almacenada en el archivo informacionLocal.txt >------------------\n\n");
    system("pause");
    system("cls");
}