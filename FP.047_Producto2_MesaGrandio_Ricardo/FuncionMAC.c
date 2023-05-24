/* Esta funci�n obtiene las direcciones MAC de los dispositivos adaptadores de red
instalados en el sistema utilizando el comando getmac y los almacena en un archivo
llamado informacionMac.txt */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h> // Librer�a necesaria para operacioens con protocolo TCP/IP
#include <ws2tcpip.h> // Librer�a complementaria a la anterior
#include <iphlpapi.h> // Librer�a que incluye tipos de variables de red
#include "Cabeceras.h" // Libreria de encabezados de todas mis funciones

void printMac() {

    // Se declaran dos punteros a un archivo fp y fp2, y DirecMAC, que es un buffer donde se guardar� la salida
    FILE* fp, * fp2;
    char DirecMAC[4096] = { 0 }; // Inicializamos el buffer a 0

    /* Apuntamos nuestro puntero al comando "getmac /v" que nos dar� como resultado
       la direcci�n MAC de los dispositivos de red. _popen es el comando que abre el proceso
       Si falla al posicionar el puntero, nos devuelve NULL dar� el error y sale de la funci�n
    */
    fp = _popen("getmac /v", "r");
    if (fp == NULL) {
        printf("No se pudo abrir el archivo de salida\n");
        exit(1);
    }
    /* Abrimos el archivo de texto modo escritura y posicionamos el puntero fp2.He preferido guardar las MAC's
       de los adaptadores en otro archivo al de la configuraci�n global de la siguiente opci�n del menu
    */
    fp2 = fopen("informacionMAC.txt", "w");
    if (fp2 == NULL) {
        printf("No se pudo abrir el archivo para escribir\n");
        exit(1);
    }

    /* Imprimimos por pantalla la salida del comando anterior haciendo un bucle para que la funci�n fgets() lea
       la salida del proceso adem�s de almacenarla en DirecMAC hasta que se alcance el final de archivo (NULL),
       o se alcance el tama�o m�ximo del buffer asignado a DirecMAC
    */
    printf("Las direcciones MAC de los interfaces de Red de este Sistema Windows son:\n");

    while (fgets(DirecMAC, sizeof(DirecMAC), fp) != NULL) {
        printf("%s", DirecMAC);

        //fprintf(fp2, "%s", DirecMAC); // *** Este volcado funcion� con la salida de ipconfig pero no con la de getmac
        // por eso en vez de cada cadena hacemos una introducci�n car�cter a car�cter por cada string y as� funciona bien.
        int i = 0;
        while (DirecMAC[i] != '\0') {
            fputc(DirecMAC[i], fp2);
            i++;
        }
    }
    // Cerramos el proceso ipconfig con _pclose por si hay que volver a abrirlo
    _pclose(fp);
    // Cerramos el archivo de texto
    fclose(fp);
    printf("\n");
    printf("------------< Informaci�n almacenada en el archivo informacionMac.txt >------------------\n\n");

    system("pause");
    system("cls");

}