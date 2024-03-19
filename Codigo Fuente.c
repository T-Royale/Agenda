#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

//Mensages//
#define menu "<<<<<Gestor De Tareas>>>>>           Made by T_Royale\n===Menu Principal===\n1-Mostrar Tareas\n2-Tarea Completada\n3-Anadir Tarea\n4-Mas Opciones\nX-Salir\n" // MENU DEL PROGRAMA//
#define MasInfoMenu "---Mas Opciones---\n1-Guardar\n2-Resetear Tareas\n3-T_Royale on GitHub\nX-Menu Principal\n" //Menú Mas Opciones

#define TareasMaximas 9     //Número máximo de tareas
#define sizeTareas 21       //Tamaño de las tareas
//Forma que tomarán las tareas que se marquen como vacias//
#define TareaVacia "Vacio"

// Numero de tareas
int nTareas;

char Tareas[TareasMaximas][sizeTareas]; // Crea las tareas en un array

//////////// Funciones ////////////
void Imprimirtareas() { // Lista de tareas lista para ser impresa
    for (int i = 0; i < TareasMaximas; i++) {
        int Y;
        Y = i+1;
        char snum[5];
        printf(itoa(Y, snum, 10));
        printf("-");
        printf("%s\n", Tareas[i]);
    }
}
//Guardar las tareas tal como estan en el .txt//
void Guardar() {
    FILE *archivo = fopen("ArchivoGuardado.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    for (int i = 0; i < TareasMaximas; i++) {
        fprintf(archivo, "%s\n", Tareas[i]);
    }
    fclose(archivo);
}
//Vacia todas las tareas//
void Resetear() {
    for (int i = 0; i < TareasMaximas; i++) {
        strcpy(Tareas[i], TareaVacia);
    }
}
//Carga las tareas desde el archivo de guardado//
void Cargar() {
    FILE *archivo = fopen("ArchivoGuardado.txt", "r");
    if (archivo == NULL) {
        fopen("ArchivoGuardado.txt", "w");
        Resetear();
        return;
    }
    char linea[sizeTareas];
    int Y = 0;
    while (fgets(linea, sizeTareas, archivo) != NULL || Y < TareasMaximas) {
        // Eliminar el carácter de nueva línea si está presente
        linea[strcspn(linea, "\n")] = '\0';
        strcpy(Tareas[Y], linea);
        Y++;
    }
    fclose(archivo);
}
//Busca un lugar para escribir la siguiente tarea//
int Buscahueco() {
    for (int i = 0; i < TareasMaximas; i++) {
        if (strcmp(Tareas[i], TareaVacia) == 0){
            return i;
        }
    }
    return 0;
}
//cuenta las tareas que hay//
int CuentaTareas() {
    int a = TareasMaximas;
    for (int i = 0; i < TareasMaximas; i++) {
        if (strcmp(Tareas[i], TareaVacia) == 0){
            a = a-1;
        }
    } 
    return a;
}
//Codigo que se va a mostrar al solicitar mas información//
void MasInfoCode() {
    int MasInfo = system("choice /C 123X");
    switch (MasInfo) {
    case 1:             //Guardar
        Guardar();
        Sleep(500);
        system("cls");
        printf("Tareas Guardadas Con Exito\n");
        break;
    case 2:             //Resetear tareas
        Resetear();
        system("cls");
        printf("Tareas Reseteadas Con Exito\n");
        Guardar();
        break;
    case 3:             //T_Royale on GitHub
        system("start https://github.com/T-Royale");
        system("cls");
        system("color 1");
        printf("Gracias, \nSigueme para mas proyectos\n");
        break;
    case 4:             //Volver menú principal
        break;
    default:
        break;
    }
}

int main() {
    Cargar(); // Cargar tareas al inicio del programa
inicio:
    system("color a");
    system("cls");  //Limpiar la terminal
    printf(menu);
    int MenuChoice = system("choice /C:1234X");
    system("cls");
    switch (MenuChoice) {
    case 1: // Mostrar Tareas
        Imprimirtareas();
        break;
    case 2: // Marcar tarea completada
        Imprimirtareas();
        Sleep(500);
        printf("Selecciona el numero de la tarea que has completado\n");
        int TareaHecha;
        scanf("%d", &TareaHecha);        
        getchar();
        TareaHecha--;
        if (TareaHecha < 0 || TareaHecha >= TareasMaximas) {
            printf("Ese numero no es valido");
            getchar();
        } else {
            strcpy(Tareas[TareaHecha], TareaVacia);
            Guardar();
        }
        break;
    case 3: // Añadir tarea
        nTareas = CuentaTareas();
        if (nTareas == TareasMaximas) {
            printf("Tienes demasiadas tareas\nCompleta algunas de tus tareas para continuar\n");
        } 
        else {
            printf("Como se llama la tarea\n");
            int Hueco = Buscahueco();
        MuyGrandeVuelveAIntentarlo:
            scanf("%[^\n]", Tareas[Hueco]);
            getchar();
            if (strlen(Tareas[Hueco])>(sizeTareas-1)) { //sizetareas -1 será 30 caracteres + el salto de línea (31)
                system("color 4");
                printf("El nombre de esa tarea es demasiado largo\nVuelve a introducir el nombre de la tarea\n");
                goto MuyGrandeVuelveAIntentarlo;
            }
            char *newline_ptr = strchr(Tareas[Hueco], '\n'); // Busca el \n en la cadena de tareas
                if (newline_ptr != NULL) {
                *newline_ptr = '\0';                        // Si lo encuentra, lo reemplaza por un \0 que es un caracter nulo
            }
            Guardar();
        }
        break;
    case 4: // Mas información
        printf(MasInfoMenu);
        MasInfoCode();
        break;
    case 5: // Salir
        goto final;
        break;
    default:
        break;
    }
    Sleep(500);
    system("pause");
    goto inicio;    //Al terminar todo vuelve al principio//

final: // Funcion de cierre del programa//
    Sleep(500);
    system("pause");
    return 0;
}
