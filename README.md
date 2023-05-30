# Tarea-Estructura-2v2
 En la resolución del problema planteado para la tarea 3, se optó por utilizar los TDA mapa, lista, pila y cola de prioridad debido a la efectividad que presentan para las funciones requeridas.

 Para almacenar las tareas, se utilizaron mapas, dado que los nombres de las tareas representan de forma efectiva la clave en una tupla clave-valor de un mapa; implicando una complejidad temporal eficiente con respecto a las funciones que se puedan realizar; se creó un mapaAux que guarda los tipoTarea y se creó un mapaTarea, se almacena en la clave nombre de tarea y el valor es una lista de tareas que tienen de requisito la tarea clave. Para las acciones, se utilza el TDA pila, dado que es eficiente en operaciones en las que se procesa primero el último dato ingresado. 


(1)Como compilar y ejecutar el codigo:

 Para que el código funcione, se debe tener un compilador de C, además, se deben tener en la misma carpeta de directorio los siguientes archivos:
-main.c, es el código ejecutable.
-hashmap.c y hashmap.h, son la implementación del TDA mapa y son la base para la construcción de este código.
-list.c y list.h
-heap.c y heap.h
-stack.h
-El archivo tareas.csv , dado que es el archivo a analizar principalmente, por lo que si no está incluido en el directorio, el código tiene error de segmentación y falla.
-En cuanto a consideraciones generales, no se analiza el caso en el cuál se forme un grafo ciclico, es decir, que una tarea implique otra y viceversa, dado que no tienen solución y comprobar si un grafo es cíclico pierde eficacia temporal. Además, no se puede agregar una tarea con el mismo nombre de otra tarea existente, dado que considermos que no es lógico perder eficiencia en usar un TDA que permita más dos claves iguales, ello para un caso que es fácilmente evitable.
(2) Las opciones que funcionan correctamente y las que no lo hacen indicando posibles causas;

Todas las funciones presentan un aparente buen funcionamiento 

-Agregar_tarea: Esta función permite agregar una nueva tarea al mapa mapaAux. Solicita al usuario que ingrese el nombre y la prioridad de la tarea. Luego, crea una estructura tipoTarea con los valores ingresados y la inserta en el mapa. También crea una nueva acción de tipo tipoAccion y la apila en el stack acciones.

-Establecer_precedencia_entre_tareas: Esta función permite establecer una relación de precedencia entre dos tareas en el mapa mapaAux. Solicita al usuario que ingrese los nombres de las dos tareas separados por una coma. Verifica si ambas tareas existen en el mapa y si cumplen ciertas condiciones. Si cumplen las condiciones, se incrementa el contador de tareas de la primera tarea y se agrega la segunda tarea como precedente de la primera. Además, crea una nueva acción de tipo tipoAccion y la apila en el stack acciones.

-mostrarTareasPorHacer: Esta función muestra las tareas por hacer ordenadas por prioridad y precedencia. Utiliza un mapa auxiliar mapaEstado para marcar las tareas visitadas y un montículo monticulo para ordenar las tareas. Itera sobre las tareas del mapa mapaAux, inserta las tareas sin precedentes en el montículo y marca las demás como "0" si no están exploradas. Luego, realiza iteraciones hasta que todas las tareas estén completadas. En cada iteración, obtiene la tarea de menor prioridad del montículo, la marca como visitada y agrega las tareas dependientes que aún no han sido completadas al montículo. Finalmente, muestra las tareas en el orden determinado por el montículo.

-Marcar_tarea_como_completada: Esta función permite marcar una tarea como completada en el mapa mapaAux. Solicita al usuario que ingrese el nombre de la tarea y verifica si existe en el mapa. Si la tarea tiene tareas precedentes, muestra una advertencia y solicita confirmación para eliminarla. Luego, crea una nueva acción de tipo tipoAccion, guarda los datos necesarios y la apila en el stack acciones. También elimina la tarea de la lista de tareas precedentes de sus sucesores en el mapa mapaTareas.

-Cargar_datos_de_tareas_desde_un_archivo_de_texto: Esta función carga las tareas desde un archivo de texto y las devuelve como una lista. Recibe como parámetro el nombre del archivo y lee todas las líneas del archivo. Luego, elimina los espacios en blanco alrededor de cada línea y agrega cada tarea a una lista. Si el archivo no existe, muestra un mensaje de error y devuelve una lista vacía.

-deshacerAccion: Esta función se encarga de deshacer la última acción realizada por el usuario, ya sea agregar tarea, marcar una tarea como completada o establecer precedencia; esta función se divide en 3 subfunciones, las cuales se deciden dependiendo de la última acción realizada, esto para facilitar la lectura del código y entendimiento de dividir un problema en problemas más pequeños.

-Agregar_tarea_deshacer: Esta función agrega una tarea a la pila de acciones para deshacer.La función añade una tupla con dos elementos a la pila, el primero indicando que se está realizando una acción de "agregar" y el segundo siendo la tarea en sí.

-Procedencia_deshacer(pila_acciones): Esta función verifica si hay acciones para deshacer en la pila. Si la pila está vacía, muestra un mensaje indicando que no hay acciones para deshacer y devuelve None. Si hay acciones en la pila, devuelve la procedencia de la acción más reciente.

-deshacerEliminar: Esta funcíon se encarga de deshacer la eliminación (marcar) de una tarea. La funcion restaura el mapaTareas, el mapaAux y las listas de precedentes en las que estaba presente la tarea eliminada. Para esto se utiliza una pila que almacena la lista del mapaTareas y otra 

(3) coevaluación del trabajo en equipo (usando rúbrica).

 Nuestro equipo se destaca por nuestra excelente colaboración a través de la plataforma Repl.it para realizar todas nuestras tareas de manera eficiente. Todos compartimos un objetivo común y trabajamos juntos para alcanzarlo. Nos comunicamos de manera fluida y clara, lo que nos mantiene en sintonía en todo momento. Cada miembro del equipo aporta habilidades y conocimientos únicos que se complementan mutuamente, lo que nos permite abordar cualquier tarea con éxito. La confianza y el respeto son valores fundamentales en nuestro equipo, lo que nos permite trabajar con eficacia y obtener resultados de alta calidad

╔═════════════════════╦═══════════════════════════════════╦══════════════════════════╦══════════════╦══════════════════╦═════════════╦═══════════╗
║    Nombre           ║ Participación activa y equitativa ║ Resolución de conflictos ║ Colaboración ║  Responsabilidad ║ Comunicación║ Pje Total ║
╠═════════════════════╬═══════════════════════════════════╬══════════════════════════╬══════════════╬══════════════════╬═════════════╩═══════════╝
║Gabriel y Patricio   ║               20                  ║            20            ║      20      ║        20        ║      20     ║    100    ║
╚═════════════════════╩═══════════════════════════════════╩══════════════════════════╩══════════════╩══════════════════╩═════════════╩═══════════╝

(4) coevaluación del aporte individual de cada integrante (usando rúbrica).

╔══════════════════╦═══════════════╦══════════════════╦══════════════╦════════════════════╦═══════════════════════════════╗
║    Nombre        ║ Participación ║  Responsabilidad ║ Comunicacion ║ Calidad de Trabajo ║ Trabajo en Equipo ║ Pje Total ║
╠══════════════════╬═══════════════╬══════════════════╬══════════════╬════════════════════╬═══════════════════════════════╣
║  Gabriel Cuibin  ║      20       ║        20        ║      20      ║         20         ║          20       ║    100    ║
╠══════════════════╬═══════════════╬══════════════════╬══════════════╬════════════════════╬═══════════════════════════════╣
║Patricio Figueroa ║      20       ║        20        ║      20      ║         20         ║          20       ║    100    ║
╚══════════════════╩═══════════════╩══════════════════╩══════════════╩════════════════════╩═══════════════════════════════╝

Gabriel Cuibin: demostró ser un miembro muy valioso del equipo, con habilidades destacadas para identificar rápidamente errores en el código y encontrar soluciones efectivas. Su capacidad para comprender y poner en práctica las ideas propuestas por el grupo fue notable, lo que contribuyó significativamente al éxito del proyecto.

Patricio Figueroa: fue un participante activo y altamente productivo en el trabajo del equipo. Constantemente aportó ideas para resolver los desafíos que surgieron, lo que nos permitió encontrar soluciones originales y eficientes. Además, mantuvo una comunicación efectiva con el equipo y siempre colaboró para alcanzar los objetivos del proyecto dentro de los plazos establecidos. Su contribución fue invaluable para el éxito general del proyecto.