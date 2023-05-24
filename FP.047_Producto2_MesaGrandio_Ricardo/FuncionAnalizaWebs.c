/* Esta función solicita al usuario el nombre y la ruta del archivo (si no está en la misma carpeta) que contiene un listado
   con los nombres de las páginas web que desea consultar, para que no quedara tan larga llamará y pasará el archivo a la
   función que hará todo el proceso
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h> // Librería necesaria para operacioens con protocolo TCP/IP
#include <ws2tcpip.h> // Librería complementaria a la anterior
#include <iphlpapi.h> // Librería que incluye tipos de variables de red
#include "Cabeceras.h" // Libreria de encabezados de todas mis funciones

#define MAX_LENGTH 256
#define MIN_LENGTH 64

void printWebIP() {

    char fileName[MAX_LENGTH];

    // Pedimos al usuario que ingrese el nombre y ruta del archivo

    printf("------------< Ingrese el nombre y ruta del archivo con el siguiente formato:  \n");
    printf("c:\\carpeta\\...\\archivo.txt   ----------------> o sin ruta si esta en la misma carpeta\n");
    scanf("%s", fileName);

    // Eliminamos el salto de línea final del nombre de archivo
    fileName[strcspn(fileName, "\n")] = '\0';

    // Llamamos a la función que leerá el archivo para buscar info y hacer el Ping
    readFromFileAndPing(fileName);

}

/* Esta función muestra la dirección IP de un conjunto de páginas web que se
encuentran en un archivo.txt pasado como parámetro por la función printWebIP
*/
void readFromFileAndPing(char* fileName) {

    char line[MAX_LENGTH] = { 0 }; // Será el búfer temporal para almacenar el archivo x linea
    char salida[MAX_LENGTH] = { 0 }; // Será el búfer temporal para almacenar la salida del comando x linea
    char command[MIN_LENGTH] = { 0 }; // Cadena para construir el comando a utilizar
    char command2[MIN_LENGTH] = { 0 }; // Cadena para construir otro comando a utilizar
    char salida2[MAX_LENGTH] = { 0 }; // Cadena para la salida del comando a utilizar
    char resp;

    FILE* pIP;  // Puntero para obtener la IP de una salida del otro comando

    // Creamos el puntero  tipo file apuntando al incio del archivo abierto por fopen en modo lectura
    FILE* fp = fopen(fileName, "r");

    // Comprobamos que el puntero pude posicionarse
    if (fp == NULL) {
        printf("*************** O se ha equivocado o No se pudo abrir el archivo %s ********************\n", fileName);
        printf("--------------< Volviendo al menú principal para que no estalle todo!! >----------- XD \n");
        system("pause");
        system("cls");
        return 0;
    }
    // Abrimos el archivo ip.txt en modo escritura para almacenar las ips según se vayan leyendo
    FILE* ipFile = fopen("ip.txt", "w");

    // Comprobamos que el puntero pude posicionarse
    if (ipFile == NULL) {
        printf("No se pudo abrir el archivo ip.txt\n");
        exit(1);
    }


    //Lectura del tamaño MAX_LENGTH del flujo apuntado por fp y volcado de su contenido en line
    fgets(line, MAX_LENGTH, fp);

    //Mientras no se encuentre la marca de final de archivo el programa irá leyendo cada linea del archivo almacenado en el buffer line
    while (!feof(fp))
    {
        //Impresión de la lectura anterior
        printf("\n");
        printf("...... Analizando la pagina web: \n");
        printf("------> %s \n", line);

        printf("A continuacion obtendremos la ip de la pagina... \n");

        /* Construimos el commando para consultar la IP nslookout + nombre pagina web
           con la opcion -type=A filtramos para que nos devuelva solo la ipv4  y hacemos
           un grep con | para filtrar la salida solo a las direcciones que son lo que buscamos
        */
        snprintf(command, MIN_LENGTH, "nslookup -type=A %s | findstr \"Address:\"", line);
        pIP = _popen(command, "r");

        // Comprobamos.....
        if (pIP == NULL) {
            printf("Error al abrir el comando\n");
            return;
        }
        // Buscamos la IP dentro de la salida
        int encontrado = 0;
        while (fgets(salida, MAX_LENGTH, pIP) != NULL && (encontrado == 0))
        {
            // Con este if esquivamos el primer valor ip de la DNS que no es el que buscamos (8.8.8.8 /  8.8.4.4)
            if (strncmp(salida, "Address:  8.", 12) != NULL) {

                // Con este if nos aseguramos que la IP es la que uscamos
                if (strstr(salida, "Address:  ") != NULL) {
                    encontrado = 1;
                    printf("------------< Introduciendo la IP de %s------------> %s------------>> en el archivo IP.txt \n", line, salida);
                    fprintf(ipFile, "%s", line); // Introducimos el nombre de la pagina web en el archivo
                    fprintf(ipFile, "%s", salida); // Introducimos la IP de la pagina web en el archivo
                    printf(". . . . Hecho! \n");
                    printf("------------< Acontinuación haremos un Ping >-----------------\n");
                    system("pause");

                    // Construimos el comando a utilizar con el parámetro pasado a la función
                    snprintf(command2, MAX_LENGTH, "ping %s", line);
                    system(command2);
                }

            }

        }
        // Damos la opción al usuario de salir si se cansa de analizar páginas web ^^

        printf("\n");
        printf("Desea continuar analizando la siguiente página web? (S/N)");
        scanf(" %c", &resp);
        if (resp == 'N' || resp == 'n') {
            printf("------------< El archivo ip.txt ha sido actualizado SOLO con las direcciones IP de las páginas que ha analizado >------------------\n");
            system("pause");
            system("cls");
            return 0;
        }

        //Lectura de un máximo de 256 caracteres del flujo apuntado por fp y asignación en line para volver a repetir la búsqueda
        fgets(line, MAX_LENGTH, fp);

    }

    fclose(fp);    // Cerramos los archivos
    // fclose(pIP);
    fclose(ipFile);

    printf("\n");
    printf("------------< No quedan más páginas web en el archivo %s para analizar  >------------------\n", fileName);
    printf("------------< El archivo ip.txt ha sido actualizado con las direcciones IP. >------------------\n");
    system("pause");
    system("cls");
}

