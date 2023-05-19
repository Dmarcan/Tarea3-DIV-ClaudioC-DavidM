# Tarea3-DIV-ClaudioC-DavidM
(1) cómo compilar y ejecutar la tarea:
Para ejecutar la tarea primero compilamos el codigo, para que se cree un archivo ejecutable que es el programa. Al ejecutarlo se mostrara un menu con opciones y se debe escribir por teclado el numero que señale esa opcion y por consiguiente el enter, algunas opciones y recomendaciones son las siguientes:

OPCION 1 AGREGAR TAREA:Se registra una tarea, se debe escribir por teclado el nombre de la tarea y su prioridad. Importante que todo campo que sea letra tiene un maximo de 30 caracteres, si este se supera se volvera a pedir ese dato en concreto.La prioridad debe ser mayor que 0.

OPCION 2 ESTABLECER PRECEDENCIA ENTRE TAREAS :La función establece la precedencia entre dos tareas. Primero verifica que la tarea 1 se ingresó previamente y luego verifica si la tarea 2 también fue ingresada. Si ambas tareas existen, la tarea 1 se agrega al arreglo de precedentes de la tarea 2 y se marca como precedente. Finalmente, se agrega la última acción realizada a la pila.

OPCION 3 MOSTRAR TAREAS PENDIENTES : La función mostrarTareasPendientes muestra las tareas pendientes ordenadas por prioridad y precedencia. Itera a través de las tareas almacenadas en un HashMap y, para cada tarea, verifica si tiene tareas precedentes. Si las tiene, muestra los nombres de las tareas precedentes junto con su prioridad. Luego, muestra el nombre de la tarea actual y su prioridad. Si una tarea precedente esta marcada como completada,no se muestra.

OPCION 4 MARCAR TAREA COMO COMPLETADA : La función "marcarTarea" permite al usuario marcar una tarea como completada. Solicita al usuario ingresar el nombre de la tarea completada y verifica si existe en el HashMap. Si la tarea no existe, se muestra un mensaje indicando que la tarea aún no se ha ingresado y se finaliza la función.Si la tarea existe, se verifica si es una tarea precedente de otras tareas o si tiene tareas precedentes. En ese caso, se le solicita al usuario confirmación para eliminar la tarea. El usuario debe responder "S" para confirmar o "N" para cancelar. Si el usuario confirma, se marca la tarea como completada  y se agrega la acción la pila de ultimas acciones. Luego se muestra un mensaje indicando que la tarea ha sido eliminada y se finaliza la función.
Si la tarea no es precedente de otras tareas ni tiene tareas precedentes, se marca directamente como completada sin reciibir confirmacion del usuario

OPCION 5 DESHACER ULTIMA ACCION : esta función deshace la ultima accion hecha por el usuario. Primero, se verifica si hay tareas presentes en el HashMap,en caso contrario se muestra un mensaje y se retorna. Si no es el caso se saca el último elemento de la pila de acciones. Se obtiene la acción y el valor de la acción realizada y se procede a deshacerla según corresponda.

OPCION 6

(2) las opciones que funcionan correctamente y las que no lo hacen indicando posibles causas;

(3) coevaluación del trabajo en equipo (usando rúbrica) : 
participacion activa: 
resolucion de conflictos: 
colaboracion: 
responsabilidad: 
comunicacion: 

(4) coevaluación del aporte individual de cada integrante (usando rúbrica).

puntaje asignado en coevaluacion:
participacion:Claudio Cabello xx, David Martinez xx 
responsabilidad:Claudio Cabello xx,David Martinez xx
comunicacion:Claudio Cabello xx,David Martinez xx
calidad de trabajo:Claudio Cabello xx,David Martinez xx
trabajo en equipo:Claudio Cabello xx,David Martinez xx
puntaje final:Claudio Cabello xx, David Martinez xx

*APORTE INDIVIDUAL*
iIMPLEMENTACION DE TDAS: 
MENU: 
OPCION 1: 
OPCION 2: 
OPCION 3: 
OPCION 4: 
OPCION 5: 
OPCION 6: 
README: 

(5)Herramientras utilizadas en el desarrollo:

La principal herramienta de trabajo que utilizamos en el desarrollo del menu es el IDE online 'replit'. Esta nos nos permitio trabajar colaborativamente en el mismo codigo y compilarlo. Tambien nos otorgo memoria virtual para crear archivos que separen el codigo.

Otra herramienta que se utilizo es la herramienta de control de versiones 'git' la cual nos permitio añadir, actualizar y subir nuestro avance a un repositorio ubicado en github.

Por ultimo la plataforma 'github' la cual nos permitio crear nuestro repositorio y almacenar el codigo.
