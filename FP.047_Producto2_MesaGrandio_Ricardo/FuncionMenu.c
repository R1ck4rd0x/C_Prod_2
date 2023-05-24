/* Funci�n MENU principal donde se dan las opciones al usuario o salir */

#include "Cabeceras.h"

void menu() {
    int opcion = 0;

    while (opcion != 5) {
        printf("==== MENU de INFO-Sistema v 0.5 ------(^^)-------- 2023 (C) Code-Cluster ====\n");
        printf("==== -------------------------- ------------------ --------------------- ====\n");
        printf("\n");
        printf("1. Informar sobre las MAC de los dispositivos adaptadores de red instalados en el sistema \n");
        printf("2. Mostrar la configuraci�n de red completa de la m�quina local para los diferentes adaptadores \n");
        printf("3. Mostrar la informaci�n relativa a un adaptador de red de anteriores escogido por el usuario.\n");
        printf("4. Mostrar la IP de un conjunto de p�ginas web que se encuentran en un archivo .txt.\n");
        printf("5. Salir.\n\n");
        printf("Seleccione una opci�n (1-5): ");
        scanf("%d", &opcion);
        printf("\n");

        switch (opcion) {
        case 1:
            printMac();
            break;
        case 2:
            printNetworkConfig();
            break;
        case 3:
            printAdapterInfo();
            break;
        case 4:
            printWebIP();
            break;
        case 5:
            printf("............... Gracias por tu tiempo........�Hasta lueguito!\n");
            break;
        default:
            printf("Opci�n no v�lida. Intente de nuevo.\n\n");
        }
    }
}