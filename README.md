# Tarea3-DIV-ClaudioC-DavidM
(1) cómo compilar y ejecutar la tarea:
Para ejecutar la tarea primero compilamos el codigo, para que se cree un archivo ejecutable que es el programa. Al ejecutarlo se mostrara un menu con opciones y se debe escribir por teclado el numero que señale esa opcion y por consiguiente el enter, algunas opciones y recomendaciones son las siguientes:

OPCION 1 AGREGAR TAREA: Se registra una tarea, se debe escribir por teclado el nombre de la tarea y su prioridad. Importante que todo campo que sea letra tiene un maximo de 30 caracteres, si este se supera se volvera a pedir ese dato en concreto. La prioridad debe ser mayor que 0.

OPCION 2 ESTABLECER PRECEDENCIA ENTRE TAREAS: La opcion establece la precedencia entre dos tareas. Primero verifica que la tarea 1 se ingresó previamente y luego verifica si la tarea 2 también fue ingresada. Si ambas tareas existen, la tarea 1 se agrega al arreglo de precedentes de la tarea 2 y se marca como precedente. Finalmente, se agrega la última acción realizada a la pila de acciones. Si no se encuentra alguno de los nombres de las tareas ingresadas por el usuario se mostrara mensaje por pantalla que no se encuentra en la base de datos. Por ultimo ambas tareas deben ser distintas.

OPCION 3 MOSTRAR TAREAS PENDIENTES: Muestra las tareas pendientes ordenadas por prioridad y precedencia. Itera en un arreglo ordenado por prioridad con el cual recorremos las tareas almacenadas en un HashMap en base a su nombre como clave, y para cada tarea, verifica si tiene tareas precedentes. Si las tiene, muestra los nombres de las tareas precedentes junto con su prioridad. Luego, muestra el nombre de la tarea actual y su prioridad. Si una tarea precedente esta marcada como completada, no se muestra.

OPCION 4 MARCAR TAREA COMO COMPLETADA : La opcion permite al usuario marcar una tarea como completada. Solicita al usuario ingresar el nombre de la tarea completada y verifica si existe en el HashMap. Si la tarea no existe, se muestra un mensaje indicando que la tarea aún no se ha ingresado y se finaliza la función. Si la tarea existe, se verifica si es una tarea precedente de otras tareas o si tiene tareas precedentes. En ese caso, se le solicita al usuario confirmación para eliminar la tarea. El usuario debe responder "S" para confirmar o "N" para cancelar. Si el usuario confirma, se marca la tarea como completada y se agrega la acción la pila de ultimas acciones. Luego se muestra un mensaje indicando que la tarea ha sido eliminada y se finaliza la función. 
Si la tarea no es precedente de otras tareas ni tiene tareas precedentes, se marca directamente como completada sin reciibir confirmacion del usuario.

OPCION 5 DESHACER ULTIMA ACCION : Esta función deshace la ultima accion hecha por el usuario. Primero, se verifica si hay tareas presentes en el HashMap, en caso contrario se muestra un mensaje y se retorna. Si no es el caso se saca el último elemento de la pila de acciones. Se obtiene la acción y el valor de la acción realizada y se procede a deshacerla según corresponda.

OPCION 6 CARGAR DATOS DESDE UN ARCHIVO : Esta funcion recibe como parámetros el nombre de un archivo y un mapa HashMap. La función abre el archivo y lee su contenido línea por línea utilizando la función getline. Luego, separa cada línea en campos utilizando la función strtok. En caso de que no se pueda abrir el archivo, la función muestra un mensaje de error. Al finalizar, muestra un mensaje indicando que la carga de datos ha sido completada.

(2) las opciones que funcionan correctamente y las que no lo hacen indicando posibles causas;
Todas las funciones funcionan correctamente.

(3) coevaluación del trabajo en equipo (usando rúbrica) : 
participacion activa: 20
resolucion de conflictos: 20
colaboracion: 20
responsabilidad: 20
comunicacion: 20

(4) coevaluación del aporte individual de cada integrante (usando rúbrica).

puntaje asignado en coevaluacion:
participacion:Claudio Cabello 20, David Martinez 20
responsabilidad:Claudio Cabello 20,David Martinez 20
comunicacion:Claudio Cabello 20,David Martinez 20
calidad de trabajo:Claudio Cabello 20,David Martinez 20
trabajo en equipo:Claudio Cabello 20,David Martinez 20
puntaje final:Claudio Cabello 100, David Martinez 100

*ASPECTOS POSITIVOS*

CLAUDIO CABELLO:
Siempre viene a clases y participativo
Tiene la iniciativa
Buena participacion


DAVID MARTINEZ:
Asiste a clases y aporta tarea
Pariticpativo en tarea y actividades en clases
Dispuesto ayudar

*ASPECTOS A MEJORAR*
CLAUDIO CABELLO: NO HAY A MEJORAR, TRABAJA BIEN

DAVID MARTINEZ: NO HAY A MEJORAR, TRABAJA BIEN

*APORTE INDIVIDUAL*
IMPLEMENTACION DE TDAS: Claudio Cabello
MENU: David martinez
OPCION 1: Claudio Cabello
OPCION 2: Claudio Cabello
OPCION 3: Claudio Cabello / David Martinez
OPCION 4: Claudio Cabello / David Martinez
OPCION 5: Claudio Cabello / David Martinez
OPCION 6: David martinez 
README: David Martinez

(5)Herramientras utilizadas en el desarrollo:

La principal herramienta de trabajo que utilizamos en el desarrollo del menu es el IDE online 'replit'. Esta nos nos permitio trabajar colaborativamente en el mismo codigo y compilarlo. Tambien nos otorgo memoria virtual para crear archivos que separen el codigo.

Otra herramienta que se utilizo es la herramienta de control de versiones 'git' la cual nos permitio añadir, actualizar y subir nuestro avance a un repositorio ubicado en github.

Por ultimo la plataforma 'github' la cual nos permitio crear nuestro repositorio y almacenar el codigo.
