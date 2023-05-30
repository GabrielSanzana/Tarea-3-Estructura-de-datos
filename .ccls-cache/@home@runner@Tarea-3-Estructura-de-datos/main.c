#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashmap.h"
#include "list.h"
#include "heap.h"
#include "stack.h"

typedef struct
{
  char *nombre;
  size_t prioridad;
  bool cumplida;
  List *tareasPrecedentes;
  int contadorTareas;
}tipoTarea;

typedef struct
{
  tipoTarea *respaldo;
  int accion;
  char *nombre;
}tipoAccion;

void Agregar_tarea(HashMap *mapaAux, Stack *acciones)
{
  // Declaración de variables locales.
  char *nombre;
  size_t prioridad;
  printf("\n——————————————————————————————————————————————————————————————————————————\n");
  // Solicitar al usuario que ingrese el nombre de la tarea
  printf("Ingrese el nombre de la tarea: ");
  scanf("%m[^\n]", &nombre);
  // Solicitar al usuario que ingrese la prioridad de la tarea.
  printf("Ingrese la prioridad de la tarea: ");
  scanf("%zu", &prioridad);
  getchar();
  
  // Crear una nueva estructura tipoTarea y asignarle los valores ingresados.
  tipoTarea *tarea = malloc(sizeof(tipoTarea));
  tarea->nombre = nombre;
  tarea->prioridad = prioridad;
  tarea->cumplida = false;
  tarea->tareasPrecedentes = createList();
  tarea->contadorTareas = 0;
  // Insertar la tarea en el mapaAux con su nombre como clave
  insertMap(mapaAux, tarea->nombre, tarea);
  // Crear una nueva acción y asignarle los valores correspondientes.
  tipoAccion *accion = malloc(sizeof(tipoAccion));
  accion->respaldo = malloc(sizeof(tipoTarea));
  memcpy(accion->respaldo, tarea, sizeof(tipoTarea));
  accion->accion = 1;
  accion->nombre = strdup(tarea->nombre);
  // Informar al usuario que la tarea se ha agregado con éxito.
  printf("\nTarea agregada con éxito.\n");

  // Apilar la acción en el stack de acciones.
  stack_push(acciones, accion);
  printf("——————————————————————————————————————————————————————————————————————————\n\n");
}

void Establecer_precedencia_entre_tareas(HashMap *mapaAux, HashMap *mapaTareas, Stack *acciones)
{
  printf("\n——————————————————————————————————————————————————————————————————————————\n");
    // Declaración de variables locales.
    char *nombre1, *nombre2;
    tipoTarea *tarea1, *tarea2;
     // Solicitar al usuario que ingrese los nombres de las dos tareas separadas por una coma.
    printf("Ingrese los nombres de las dos tareas separados por una coma y sin espacios antes o después de la coma (ejemplo: tarea1,tarea2):\n");
    scanf("%m[^,],%m[^\n]", &nombre1, &nombre2);

    // Verificar si alguna de las tareas no existe en el mapaAux.
    if (searchMap(mapaAux, nombre1) == NULL || searchMap(mapaAux, nombre2) == NULL) {
        printf("\nUna de las tareas no existe en el mapa.\n");
        free(nombre1);
        free(nombre2);
          printf("——————————————————————————————————————————————————————————————————————————\n\n");
        return;
    }

    // Obtener los punteros a las estructuras de tipoTarea correspondientes a los nombres ingresados.
    tarea1 = searchMap(mapaAux, nombre1)->value;
    tarea2 = searchMap(mapaAux, nombre2)->value;

    // Verificar si tarea2 ya tiene tareas precedentes.
    if(firstList(tarea2->tareasPrecedentes)!=NULL){
    for (char* n = firstList(tarea2->tareasPrecedentes); n != NULL; n = nextList(tarea2->tareasPrecedentes)) {
        // Recorrer la lista de tareas precedentes de tarea2.
        if(strcmp(n, tarea1->nombre) == 0)
        {
            printf("\nNo es posible realizar esta acción.\n");
            free(nombre1);
            free(nombre2);
              printf("——————————————————————————————————————————————————————————————————————————\n\n");
            return;
        }
        // Verificar si el elemento n de las tareas precedentes de tarea2 existe en el mapaAux.
        if (searchMap(mapaAux, n) != NULL) 
        {
          tipoTarea *n2 = searchMap(mapaAux, n)->value;
          // Verificar si el elemento n2 tiene tareas precedentes.
          if(firstList(n2->tareasPrecedentes) != NULL)
          {
            // Recorrer la lista de tareas precedentes de n2.
            for (char *n3 = firstList(n2->tareasPrecedentes); n3 != NULL; n3 = nextList(n2->tareasPrecedentes)) 
            {
              // Verificar si tarea1 ya está establecida como tarea precedente de n3.
              if(strcmp(n3,tarea1->nombre) == 0)
              {
                printf("\nNo es posible realizar esta acción.\n");
                free(nombre1);
                free(nombre2);
                printf("——————————————————————————————————————————————————————————————————————————\n\n");
                return;
              }
            }
          }
        }
        
    }
printf("\nSe establecio %s como precendente de %s.\n",tarea2->nombre,tarea1->nombre);        printf("——————————————————————————————————————————————————————————————————————————\n\n");
}
    // Incrementar el contador de tareas de tarea1.
    tarea1->contadorTareas++;
    // Verificar si tarea2 no existe en el mapaTareas.
    if (searchMap(mapaTareas, tarea2->nombre) == NULL) {
        // Crear una nueva lista para almacenar los lugares donde tarea2 es precedente.
        List *listatareasPrecedentes = createList();
        // Insertar la lista en el mapaTareas con clave tarea2->nombre.
        insertMap(mapaTareas, tarea2->nombre, listatareasPrecedentes); 
    }

    // Agregar tarea1 el lugar donde tarea2 es precedente.
    pushBack(searchMap(mapaTareas, tarea2->nombre)->value, tarea1->nombre);
    pushBack(tarea1->tareasPrecedentes, tarea2->nombre);

    // Crear una nueva acción y asignarle los valores correspondientes.
    tipoAccion *accion = malloc(sizeof(tipoAccion));
    accion->accion = 2;
    accion->nombre = strdup(tarea2->nombre);
    accion->respaldo = malloc(sizeof(tipoTarea));
    memcpy(accion->respaldo, tarea1, sizeof(tipoTarea));
    // Apilar la acción en el stack de acciones.
    stack_push(acciones, accion);
    // Liberar la memoria de las variables nombre1 y nombre2.
    free(nombre1);
    free(nombre2);
}

void mostrarTareasPorHacer(HashMap *mapaTareas, HashMap *mapaAux) {
  printf("\n——————————————————————————————————————————————————————————————————————————\n");
  // Variable para controlar si todas las tareas están completadas.
  bool tareasCompletadas = false;
  // Mostrar encabezado.
  printf("Tareas por hacer, ordenadas por prioridad y precedencia:\n");
  // Variable para contar las tareas
  int contador;
  // Crear un mapa auxiliar para marcar las tareas visitadas.
  HashMap *mapaEstado = createMap((long)100);
  char *nombre;
  // Variables para manejar el montículo y una lista auxiliar.
  Heap *monticulo = createHeap();
  List *listaAuxiliarMonticulo = createList();
  
  // Explorar las tareas y marcarlas como exploradas (0 = ninguna de las dos, 1 = explorada, 2 = visitada).
  Pair *aux = firstMap(mapaAux);
  while (aux != NULL) {
    tipoTarea *tarea = (tipoTarea*) aux->value;
     // Insertar la tarea sin precedentes en el montículo y marcarla como explorada si no marcar como ninguna de las dos.
    if (tarea->contadorTareas == 0) {
      insertMap(mapaEstado, tarea->nombre, "1");
      
      heap_push(monticulo, tarea, tarea->prioridad + tarea->contadorTareas*1000);
    } else {
      insertMap(mapaEstado, tarea->nombre, "0");
    }
    aux = nextMap(mapaAux);
  }

  // Realizar iteraciones hasta que todas las tareas estén completadas.
  while (tareasCompletadas == false) {
    // Obtener la tarea actual de menor prioridad del montículo.
    tipoTarea *tareaActual = (tipoTarea*) heap_top(monticulo);
    heap_pop(monticulo);
    // Marcar la tarea actual como visitada.
    Pair *auxEstado = searchMap(mapaEstado, tareaActual->nombre);
          auxEstado->value = "2";
    // Agregar la tarea actual a la lista auxiliar del montículo.
    pushBack(listaAuxiliarMonticulo,tareaActual);
    // Inicializar la variable que indica si todas las tareas están completadas.
    tareasCompletadas = true;

    // Iterar sobre todas las tareas del mapaAux.
    aux = firstMap(mapaAux);
    while (aux != NULL) {
      tipoTarea *tarea = (tipoTarea*) aux->value;
	    // Buscar las tareas que tienen precedentes y todavía no están completadas.
      if (tarea->contadorTareas != 0 && strcmp((searchMap(mapaEstado, tarea->nombre)->value), "0" ) == 0) {
        contador = 0;
	      // Revisar si todas las tareas en su lista de precedentes fueron completadas.
        for (char *n = firstList(tarea->tareasPrecedentes); n != NULL; n = nextList(tarea->tareasPrecedentes)) {
            if (strcmp((searchMap(mapaEstado, n)->value), "2") == 0)
              contador++;
        }
        // Si todas las tareas precedentes están completadas, marcar la tarea actual como explorada y agregarla al montículo.
        if (contador == tarea->contadorTareas) {
          Pair *auxEstado = searchMap(mapaEstado, tarea->nombre);
          auxEstado->value = "1";
          heap_push(monticulo, tarea, tarea->prioridad);
        }
      }
      aux = nextMap(mapaAux);
    }

    // Verificar si todas las tareas están completadas.
    for (Pair *auxEstadosMapa = firstMap(mapaEstado) ; auxEstadosMapa!=NULL ; auxEstadosMapa = nextMap(mapaEstado))
    {
        if(strcmp(auxEstadosMapa->value, "2") != 0)
          tareasCompletadas = false;
    }
  }
  
  contador = 1;

  // Mostrar las tareas.
  for (tipoTarea *tareaCompletada = firstList(listaAuxiliarMonticulo); tareaCompletada != NULL; tareaCompletada = nextList(listaAuxiliarMonticulo)) {
    printf("%d. %s (Prioridad: %lu) ", contador, tareaCompletada->nombre, tareaCompletada->prioridad);
    contador++;

    // Mostrar las tareas precedentes si existen.
    if (firstList(tareaCompletada->tareasPrecedentes) != NULL) {
      printf("Tareas precedentes:");
      for (char *predecente = firstList(tareaCompletada->tareasPrecedentes); predecente != NULL; predecente = nextList(tareaCompletada->tareasPrecedentes)) {
        printf(" %s", predecente);
      }
    }
    printf("\n");
  }

  // Liberar la memoria utilizada por el mapaEstado, el montículo y la lista auxiliar.
  free(listaAuxiliarMonticulo);
  free(monticulo);
  free(mapaEstado);
  printf("——————————————————————————————————————————————————————————————————————————\n\n");
}         

void Marcar_tarea_como_completada(HashMap *mapaTareas, HashMap *mapaAux, Stack *acciones, List *listaCopia, Stack *pilaListasCopia)
{
  printf("\n——————————————————————————————————————————————————————————————————————————\n");
  char *nombre; 
  tipoTarea * tarea;
  // Solicitar el nombre de la tarea al usuario.
  printf("Ingrese el nombre de la tarea: ");
  scanf("%m[^\n]", &nombre);
  getchar();
  // Buscar la tarea en el mapa de tareas.
  if (searchMap(mapaAux, nombre) != NULL) 
  {
    tarea = searchMap(mapaAux, nombre)->value;
  }
  else {
    printf("\nLa tarea no existe en el mapa.");
    free(nombre);
    printf("\n——————————————————————————————————————————————————————————————————————————\n\n");
    return;
  }

  // Si la tarea tiene tareas precedentes, mostrar una advertencia.
  
    if (tarea->contadorTareas > 0) {
      printf("La tarea tiene tareas precedentes. ¿Está seguro que desea eliminarla? (s/n): ");
      char confirmacion;
      scanf("%c", &confirmacion);
      if (confirmacion != 's') {
        free(nombre);
        return;
      }
    }
    // Crear una nueva acción y guardar los datos necesarios.
    tipoAccion *accion = malloc(sizeof(tipoAccion));
    accion->accion = 3;
    accion->nombre = strdup(tarea->nombre);
    accion->respaldo = malloc(sizeof(tipoTarea));
    accion->respaldo->contadorTareas = tarea->contadorTareas;
    accion->respaldo->cumplida = tarea->cumplida;
    accion->respaldo->nombre = strdup(tarea->nombre);
    accion->respaldo->prioridad = tarea->prioridad;
    accion->respaldo->tareasPrecedentes = createList();
    for (char *procedente  = firstList(tarea->tareasPrecedentes); procedente != NULL; procedente = nextList(tarea->tareasPrecedentes))
    {
      pushFront(accion->respaldo->tareasPrecedentes, procedente);
    }
    // Apilar la acción en el stack de acciones.
    stack_push(acciones, accion);
    
  // Eliminar la tarea de la lista de tareas precedentes de sus sucesores.
  if(searchMap(mapaTareas, nombre)!=NULL)
  {
    
    List *listaAux = searchMap(mapaTareas, nombre)->value;
    for (char *procedente  = firstList(listaAux); procedente != NULL; procedente = nextList(listaAux))
    {
      pushFront(listaCopia, procedente);
    }
    stack_push(pilaListasCopia, listaCopia);
    if (listaAux != NULL) {
      for (char *n = firstList(listaAux); n != NULL; n = nextList(listaAux)) 
      {
          
        if (searchMap(mapaAux, n) != NULL) {
          tipoTarea *n2 = searchMap(mapaAux, n)->value;
          for (char *n3 = firstList(n2->tareasPrecedentes); n3 != NULL; n3 = nextList(n2->tareasPrecedentes)) 
          {
            if(strcmp(n3,nombre) == 0)
            {
              popCurrent(n2->tareasPrecedentes);
              n2->contadorTareas--; 
              break;
            }
          }
        }
      }
      }
  }

  // Establecer la tarea como cumplida y eliminarla de la lista de tareas por hacer.
  tarea->cumplida = true;
  eraseMap(mapaAux, tarea->nombre); 
  printf("\nTarea marcada como completada y eliminada de la lista de tareas por hacer.\n");
  free(nombre);
  printf("——————————————————————————————————————————————————————————————————————————\n\n");
}

void Cargar_datos_de_tareas_desde_un_archivo_de_texto(char* nombre_archivo, HashMap* mapaAux,HashMap* mapaTareas){
  char caracter[100];
  FILE *archivoCsv = fopen(nombre_archivo, "r");
  if (archivoCsv == NULL) 
    {
      printf("\n——————————————————————————————————————————————————————————————————————————\n");
      printf("El archivo %s no existe en el directorio actual o esta mal escrito.\n", nombre_archivo);
      printf("——————————————————————————————————————————————————————————————————————————\n\n");
      return;
    }
  fgets(caracter, 99, archivoCsv); // Lee la primera línea (cabecera) del archivo
  size_t prioridad;
  char *nombre, *tareasPrecedentes;
  
  // Lee los datos de cada jugador del archivo mientras no llegue al final
  while (fscanf(archivoCsv, "%m[^,],%zu,%m[^\n]\n", &nombre, &prioridad, &tareasPrecedentes) != EOF) {
   tipoTarea *tarea = malloc(sizeof(tipoTarea));
        tarea->nombre = strdup(nombre);
        tarea->prioridad = prioridad;
        tarea->cumplida = false;
        tarea->tareasPrecedentes = createList();
        tarea->contadorTareas = 0;
        if (tareasPrecedentes[0] == '\r')
            tareasPrecedentes[0] = '\0';
        if(tareasPrecedentes[strlen(tareasPrecedentes) - 1] == ' ' || tareasPrecedentes[strlen(tareasPrecedentes) - 1] == '\r')
            tareasPrecedentes[strlen(tareasPrecedentes) - 1] = '\0';
        
        char *tareaProcedente = strtok(tareasPrecedentes, " ");
        while (tareaProcedente != NULL) {
            if (tareaProcedente[0] == '\r') {
                tareaProcedente[0] = '\0';
                break;
            }
            tarea->contadorTareas++;
            if (searchMap(mapaTareas, tareaProcedente) == NULL) {
                List *listatareasPrecedentes = createList();
                insertMap(mapaTareas, tareaProcedente, listatareasPrecedentes);
            }
            pushBack(searchMap(mapaTareas, tareaProcedente)->value, tarea->nombre);
            pushBack(tarea->tareasPrecedentes, tareaProcedente);
            tareaProcedente = strtok(NULL, " ");
        }
        insertMap(mapaAux, tarea->nombre, tarea);
      
      
  }  
  printf("\nArchivo importado.\n");
  fclose(archivoCsv);
}


void agregar_tarea_deshacer(HashMap *mapaTareas, HashMap *mapaAux, Stack *acciones, char *nombre)
{
  // Buscar la tarea en el mapa auxiliar.
  tipoTarea *tarea = searchMap(mapaAux, nombre)->value;
  
  // Establecer la tarea como cumplida y eliminarla de la lista de tareas por hacer.
  printf("\nSe deshizo la acción anterior, por lo que la tarea %s ha sido eliminada.\n", tarea->nombre);
  eraseMap(mapaAux, tarea->nombre); 
  // Eliminar la acción de la pila de acciones.
}

void procedencia_deshacer(HashMap *mapaTareas, HashMap *mapaAux, Stack *acciones,  tipoAccion *accion)
{
  // Obtener los nombres de las tareas involucradas en la acción.
  char *nombre = accion->respaldo->nombre; 
  char *nombre2 = accion->nombre;
  // Eliminar la tarea de lista del mapaTareas.
  popBack(searchMap(mapaTareas, nombre2)->value);
  tipoTarea *tarea = searchMap(mapaAux, nombre)->value;
  // Eliminar la tarea precedente de la lista de tareas precedentes de la tarea principal.
  popBack(tarea->tareasPrecedentes);
  printf("Se deshizo la acción de establecer como tarea precedente la tarea %s a la tarea %s.", nombre2, tarea->nombre);
  // Actualizar el contador de tareas precedentes.
  tarea->contadorTareas--;
  // Eliminar la acción de la pila de acciones.
}

void deshacerEliminar(HashMap *mapaTareas, HashMap *mapaAuxiliar, Stack *acciones, tipoAccion *accion, Stack *pilaListasCopia)
{
  List *listaCopia = stack_top(pilaListasCopia);
  tipoTarea *tarea = accion->respaldo;
  insertMap(mapaAuxiliar, tarea->nombre, tarea);
  for(char *i = firstList(listaCopia); i != NULL; i = nextList(listaCopia))
    {
      tipoTarea *tareaAux = searchMap(mapaAuxiliar, i)->value;
      tareaAux->contadorTareas++;
      pushBack(tareaAux->tareasPrecedentes, tarea->nombre);
      pushBack(searchMap(mapaTareas, tarea->nombre)->value, tareaAux->nombre);
    }
  stack_pop(pilaListasCopia);
  printf("Se deshizo la acción de marcar como completada la tarea %s, por lo que se agrega de nuevo a la lista de tareas.",accion->respaldo->nombre);
}

void deshacerAccion(HashMap *mapaTareas, HashMap *mapaAuxiliar, Stack *acciones, Stack * pilaListasCopia)
{
  printf("\n——————————————————————————————————————————————————————————————————————————\n");
  tipoAccion *aux = stack_top(acciones);
  if(aux == NULL)
  {
    puts("No se han realizado acciones anteriores.");
    printf("——————————————————————————————————————————————————————————————————————————\n\n");
    return;
  } 

  if(aux->accion == 1)
  {
    agregar_tarea_deshacer(mapaTareas, mapaAuxiliar, acciones, aux->nombre);
  }
  else if (aux->accion == 2)
  {
    procedencia_deshacer(mapaTareas, mapaAuxiliar, acciones, aux);
  }
  else if (aux->accion == 3)
  {
    deshacerEliminar(mapaTareas, mapaAuxiliar, acciones, aux, pilaListasCopia);
  }
    stack_pop(acciones);
  printf("\n——————————————————————————————————————————————————————————————————————————\n\n");
}
  
int main()
{
   Stack *acciones = stack_create(); // Crear una pila para almacenar las acciones.
   HashMap *mapaTareas = createMap((long)100); // Crear un mapa para almacenar las tareas.
   tipoTarea *value;
   Stack *pilaTareasProcedencias = stack_create();
   List *procedenciasTareas = createList();
   HashMap *mapaAux = createMap((long)100);
    char caracter[100], *nombre, *tareasPrecedentes, *archivoCargado;
    size_t prioridad, opcion;
    FILE *archivoCsv = fopen("tareas.csv", "r"); // Abrir el archivo de tareas en modo lectura.
    fgets(caracter, 99, archivoCsv); // Leer la primera línea (cabecera) del archivo
  
    while (fscanf(archivoCsv, "%m[^,],%zu,%m[^\n]\n", &nombre, &prioridad, &tareasPrecedentes) != EOF) {
        tipoTarea *tarea = malloc(sizeof(tipoTarea));
        tarea->nombre = strdup(nombre);
        tarea->prioridad = prioridad;
        tarea->cumplida = false;
        tarea->tareasPrecedentes = createList();
        tarea->contadorTareas = 0;
      // Eliminar caracteres de retorno de carro (\r) al final del string.
        if (tareasPrecedentes[0] == '\r')
            tareasPrecedentes[0] = '\0';
        if(tareasPrecedentes[strlen(tareasPrecedentes) - 1] == ' ' || tareasPrecedentes[strlen(tareasPrecedentes) - 1] == '\r')
            tareasPrecedentes[strlen(tareasPrecedentes) - 1] = '\0';
        
        char *tareaProcedente = strtok(tareasPrecedentes, " ");
        while (tareaProcedente != NULL) {
            if (tareaProcedente[0] == '\r') {
                tareaProcedente[0] = '\0';
                break;
            }
            tarea->contadorTareas++;
            if (searchMap(mapaTareas, tareaProcedente) == NULL) {
                List *listatareasPrecedentes = createList();
                insertMap(mapaTareas, tareaProcedente, listatareasPrecedentes);
            }
            pushBack(searchMap(mapaTareas, tareaProcedente)->value, tarea->nombre);
            pushBack(tarea->tareasPrecedentes, tareaProcedente);
            tareaProcedente = strtok(NULL, " ");
        }
      // Agregar la tarea al mapa auxiliar.
        insertMap(mapaAux, tarea->nombre, tarea);
      
    }
   fclose(archivoCsv); // Cerrar el archivo
    
   while (true) 
   {
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
        Agregar_tarea(mapaAux, acciones);
        break;
      case 2:
        Establecer_precedencia_entre_tareas(mapaAux,mapaTareas,acciones);
        break;
      case 3:
        mostrarTareasPorHacer(mapaTareas,mapaAux);
        break;
      case 4:
        Marcar_tarea_como_completada(mapaTareas,mapaAux, acciones, procedenciasTareas,pilaTareasProcedencias);
        break;
      case 5:
        deshacerAccion(mapaTareas, mapaAux, acciones, pilaTareasProcedencias);
        break;
      case 6:
        printf("\n————————————————————————————————————————————————————————————\n");
      printf("Ingrese el nombre del archivo, introduzca el formato (.csv)\n");
      scanf("%m[^\n]",&archivoCargado);
      getchar();
      if (strstr(archivoCargado,".csv")==0)
      {
        printf("\nEl formato del archivo '%s' es incorrecto.\n", archivoCargado);
        printf("————————————————————————————————————————————————————————————\n\n");
        break;
      }
      Cargar_datos_de_tareas_desde_un_archivo_de_texto(archivoCargado, mapaAux, mapaTareas);
      printf("————————————————————————————————————————————————————————————\n\n");
        break;
      default:
        break;
    }
   }
  return 0;
}