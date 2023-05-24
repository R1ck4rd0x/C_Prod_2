/* Esta funci�n muestra la informaci�n relativa a un adaptador de red especificado por el usuario.
   Utiliza el archivo informacionlocal.txt generado previamente por las funciones printMAC() y
   printNetworkConfig() para buscar y mostrar la informaci�n correspondiente
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h> // Librer�a necesaria para operacioens con protocolo TCP/IP
#include <ws2tcpip.h> // Librer�a complementaria a la anterior
#include <iphlpapi.h> // Librer�a que incluye tipos de variables de red
#include "Cabeceras.h" // Libreria de encabezados de todas mis funciones
//#pragma comment(lib, "Ws2_32.lib")

void printAdapterInfo() {
    char adapter[100];
    char line[200];
    char resp;
    int linia;

    // Abrimos el archivo donde guardamos toda la configuraci�n de red del sistema con fopen y apuntamos al inicio con *fp

    FILE* fp = fopen("informacionlocal.txt", "r");
    if (fp == NULL) {
        printf("No se pudo abrir el archivo para leer\n");
        exit(1);
    }

    /* Vamos leyendo con fgets, cada linea del archivo hasta que lleguemos al final y cuando detecta un adaptador preguntamos
       al usuario si quiere ver la informaci�n de este, para dectectarlo buscamos la descripci�n para as� poder imprimir el nombre
    */
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, "Descrip") != NULL) {
        //if (strcmp(line, "Adap") == 0) {
            
            printf("%s\n", line);
            printf("deseas informaci�n de este adaptador? (S/N)");
            scanf(" %c", &resp);

            if (resp == 'S' || resp == 's')
            {
                int Visto = 0;
                linia = 1;
                // Recorrer el buffer a partir de la l�nea del adaptador para buscar informaci�n de IP, m�scara y puerta de enlace

                while (fgets(line, sizeof(line), fp) != NULL && linia < 7 ) {
                    if (strstr(line, "IPv4") != NULL) {
                        printf(line);
                        while (fgets(line, sizeof(line), fp) != NULL) {
                            if (strstr(line, "M\240scara") != NULL) {
                                printf(line);
                            }
                            if (strstr(line, "Puerta") != NULL) {
                                printf(line);
                                Visto = 1;
                                break;
                            }
                        }

                    }
                    linia++;
                    if (linia > 5 && Visto == 0) {
                        printf("------------< Ese adaptador no tiene IPv4 ni m�scara ni defaultgateway! >------------------\n");
                        Visto = 1;
                    }
                    if (Visto) {
                        break;
                    }

                }

            }
            printf("\n");

        }
    }

    fclose(fp);
    printf("------------< Ya no quedan m�s adaptadores para analizar  >------------------\n");
    system("pause");
    system("cls");
}