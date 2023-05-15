#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashmap.h"
#include "list.h"
#include "heap.h"

typedef struct
{
  char *nombre;
  size_t prioridad;
  bool cumplida;
  List *tareasProcendetes;
}tipoTarea;

void Agregar_tarea(Heap *tareas, HashMap *mapaTareas)
{
  char* nombre;
  size_t prioridad;
  tipoTarea *local = malloc(sizeof(tipoTarea));
  local->cumplida = false;
  scanf("%m[^,],%zu\n",&nombre, &prioridad);
  heap_push(tareas, local, local->prioridad);
  
}

void Establecer_precedencia_entre_tareas(Heap *tareas,HashMap *mapaTareas)
{
  char *nombre1, * nombre2;
  scanf("%m[^,],%m[^\n]",&nombre1, &nombre2);
  tipoTarea *tarea1 = searchMap(mapaTareas, nombre1)->value;
  tipoTarea *tarea2 = searchMap(mapaTareas, nombre2)->value;
  pushBack(tarea1->tareasProcendetes, tarea2);
  insertMap(mapaTareas, tarea2->nombre, tarea1);
} 

int main()
{
   HashMap *mapaTareas = createMap((long)100);
    char caracter[100], *nombre, *tareasProcedentes;
    size_t prioridad, opcion;
    FILE *archivoCsv = fopen("tareas.csv", "r");
    fgets(caracter, 99, archivoCsv);
    Heap *tareas = createHeap();
    puts("KK");
    while (fscanf(archivoCsv, "%m[^,],%zu,%m[^\n]", &nombre, &prioridad, &tareasProcedentes) != EOF) {
        tipoTarea *tarea = malloc(sizeof(tipoTarea));
        tarea->nombre = nombre;
        tarea->prioridad = prioridad;
        tarea->cumplida = false;
        char *tareaProcedente = strtok(tareasProcedentes, " ");
        while (tareaProcedente != NULL) {
            insertMap(mapaTareas, tareaProcedente, tarea);
            tareaProcedente = strtok(NULL, " ");
        }
        printf("%s %zu ", tarea->nombre, tarea->prioridad);
        heap_push(tareas, tarea, tarea->prioridad);
    }
    fclose(archivoCsv);

 /* while (true) {

    printf("Elije opcion\n");
    printf("1.- Agregar tarea \n");
    printf("2.- Establecer precedencia entre tareas\n");
    printf("3.- Mostrar tareas por hacer\n");
    printf("4.- Marcar tarea como completada\n");
    printf("5.- Deshacer última acción\n");
    printf("6.- Cargar datos de tareas desde un archivo de texto\n");
    scanf("%zu", &opcion);
    getchar();

    switch (opcion) 
    {
      case 1:  
        Agregar_tarea(tareas,mapaTareas);
        break;
      case 2:
        Establecer_precedencia_entre_tareas(tareas,mapaTareas);
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
      case 6:  
        break;
      default:
        return 0;
    }*/
  
}