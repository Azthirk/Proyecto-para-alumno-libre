/*************************************************/
/* Proyecto Lista                                */
/*                                               */ 
/* Descripcion: Se encarga de leer/crear una     */ 
/* lista de tareas que se ubican dependiendo     */
/* su priodad.                                   */ 
/*                                               */ 
/* Autores: Quiroga Agustin                      */
/*                                               */
/* Fecha: 20/12/2021                             */
/*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define max 1000

typedef struct{
    int d;
    int m;
    int a;
}TFecha;

typedef struct{
    int ID;
    char descripcion[max];
    char apellidoEncargado[20];
    char prioridad[20];
    TFecha fechaCreacion;
    TFecha fechaLimite;
}TDatos;

//Declaraciones globales
int cantTareas;
int diaActual;
int mesActual;
int anioActual;
int op;
int idBuscar;
char nombresito[20];
TDatos actividad[max];


//Funcionas y Acciones
int listaVacia(TDatos actx[max]); //Funcion que revisa si la lista esta vacia.
int listaLlena(TDatos actx[max]); //Funcion que revisa si la lista esta llena.
void muestroMenu(); //Accion que muestra un menu de texto.
void cargoTarea(TDatos actx[max]); //Accion que carga una tarea al arreglo.
void muestroTareas(TDatos actx[max]); //Accion que muestra los elementos de la lista.
void revisoPreCargado(TDatos actx[max]); //Accion que revisa si el archivo tiene previamente elementos cargados y los agrega al arreglo.
void modificoTarea(TDatos actx[max], int idBuscar); //Accion que permite modificar un elemento de la lista dependiendo su ID.
void buscoTareaUsuario(TDatos actx[max], char nombreUsuario[20]); //Accion que muestra las tareas dependiendo el nombre del empleado ingresado.
void buscoTareasUrgentes(TDatos actx[max]); //Accion que muestra las tareas urgentes del mes.
void muestroText(int numActual); //Accion que utilizo para mostrar los elementos en muestroTarea, buscoTareaUsuario y buscoTareasUrgentes.
void ingresoDatos(TDatos actx[max], int numActual); //Accion que utilizo para cargar datos en cargoTarea.
void guardoLista(TDatos actx[max]); //Accion que guarda el arreglo en el archivo.
void completoTarea(TDatos actx[max], int idBuscar); //Accion que completa borra una tarea por ID seleccionado.

int main()
{
    //Ingreso la fecha actual
    printf("Ingrese el dia actual: ");
    scanf("%d", &diaActual);
    printf("Ingrese el mes actual: ");
    scanf("%d", &mesActual);
    printf("Ingrese el año actual: ");
    scanf("%d", &anioActual);
    printf("\nFecha actual: %d/%d/%d\n", diaActual,mesActual,anioActual);
    
    revisoPreCargado(actividad);    //Reviso si ya tiene algo cargado.
    muestroMenu();  //Muestro el menu

    while(op != 7){ //Selecciono una opcion.
        printf("\nIngrese su opcion: ");
        scanf("%d", &op);
        
        if(op == 1){
            if(listaLlena(actividad) == false){
                muestroTareas(actividad);
                cargoTarea(actividad);
                muestroTareas(actividad);
            }else{
                printf("\nLa lista esta llena, no puedes hacer esto.\n");fflush(stdout);
            }
        }else if(op == 2){
            
            if(listaVacia(actividad) == false){
                muestroTareas(actividad);
                printf("\nIngrese el ID de la tarea: ");fflush(stdout);
                scanf("%d", &idBuscar);
                modificoTarea(actividad, idBuscar);
            }else{
                printf("\nLa lista esta vacia, no puedes hacer esto.\n");fflush(stdout);
            }
            

        }else if(op == 3){
            if(listaVacia(actividad) == false){
                muestroTareas(actividad);
                printf("\nIngrese el ID de la tarea: ");fflush(stdout);
                scanf("%d", &idBuscar);
                completoTarea(actividad, idBuscar);
            }else{
                printf("\nLa lista esta vacia, no puedes hacer esto.\n");fflush(stdout);
            }
        }else if(op==4){
            if(listaVacia(actividad) == false){
                muestroTareas(actividad);
            }else{
                printf("\nLa lista esta vacia, no puedes hacer esto.\n");fflush(stdout);
            }
        }else if(op == 5){
            if(listaVacia(actividad) == false){
                buscoTareasUrgentes(actividad);
            }else{
                printf("\nLa lista esta vacia, no puedes hacer esto.\n");fflush(stdout);
            }
        }else if(op == 6){
            if(listaVacia(actividad) == false){
                printf("Ingrese el nombre del empleado: ");fflush(stdout);
                scanf("%s", &*nombresito);
                buscoTareaUsuario(actividad, nombresito);
            }else{
                printf("\nLa lista esta llena, no puedes hacer esto.\n");fflush(stdout);
            }
        }else if(op == 7){
            guardoLista(actividad);
        }
        
        muestroMenu();

    }
    return 0;
}

//Accion que muestra un menu de texto.
void muestroMenu(){
    printf("\n[Lista de opciones]\n[1]Carga de tareas\n[2]Modificar una tarea\n[3]Completar una tarea\n[4]Listar tareas\n[5]Tareas urgentes\n[6]Tareas de empleado\n[7]Guardar y salir\n");
}

//Accion que revisa si el archivo tiene previamente elementos cargados y los agrega al arreglo.
void revisoPreCargado(TDatos actx[max]){
    FILE *arch;
    int i;
    
    arch=fopen("tareas.dat","a+");
        while(!feof(arch)){ //Si tiene elementos cargados los cuento.
            i++;
            fread(&actx[i],sizeof(actx[i]),1,arch);
        };
    fclose(arch);
    
    cantTareas = i;
}

//Accion que carga una tarea al arreglo.
void cargoTarea(TDatos actx[max]){
    int i = cantTareas, k = 1;
    int l, contadorPrioridad = 0;
    TDatos aux[max];
    l = 1;
    
        ingresoDatos(actx, i);
        actx[i].fechaCreacion.d = diaActual;
        actx[i].fechaCreacion.m = mesActual;
        actx[i].fechaCreacion.a = anioActual;
        actx[i].ID = i;
        cantTareas = cantTareas + 1;
        
        
        if(strcmp(actx[i].prioridad, "ALTA") == 0){
            strcpy(aux[1].apellidoEncargado, actx[i].apellidoEncargado);
            strcpy(aux[1].prioridad, actx[i].prioridad);
            strcpy(aux[1].descripcion, actx[i].descripcion);
            aux[1].fechaCreacion.d = actx[i].fechaCreacion.d;
            aux[1].fechaCreacion.m = actx[i].fechaCreacion.m;
            aux[1].fechaCreacion.a = actx[i].fechaCreacion.a;
            
            aux[1].fechaLimite.d = actx[i].fechaLimite.d;
            aux[1].fechaLimite.m = actx[i].fechaLimite.m;
            aux[1].fechaLimite.a = actx[i].fechaLimite.a;
            aux[1].ID = actx[i].ID; 
        
        for(int k = cantTareas + 1; k > 1; k--){
            strcpy(actx[k].apellidoEncargado, actx[k - 1].apellidoEncargado);
            strcpy(actx[k].prioridad, actx[k - 1].prioridad);
            strcpy(actx[k].descripcion, actx[k - 1].descripcion);
            actx[k].fechaCreacion.d = actx[k - 1].fechaCreacion.d;
            actx[k].fechaCreacion.m = actx[k - 1].fechaCreacion.m;
            actx[k].fechaCreacion.a = actx[k - 1].fechaCreacion.a;
            
            actx[k].fechaLimite.d = actx[k - 1].fechaLimite.d;
            actx[k].fechaLimite.m = actx[k - 1].fechaLimite.m;
            actx[k].fechaLimite.a = actx[k - 1].fechaLimite.a;
            actx[k].ID = actx[k - 1].ID; 
        }
        
            strcpy(actx[1].apellidoEncargado, aux[1].apellidoEncargado);
            strcpy(actx[1].prioridad, aux[1].prioridad);
            strcpy(actx[1].descripcion, aux[1].descripcion);
            actx[1].fechaCreacion.d = aux[1].fechaCreacion.d;
            actx[1].fechaCreacion.m = aux[1].fechaCreacion.m;
            actx[1].fechaCreacion.a = aux[1].fechaCreacion.a;
            
            actx[1].fechaLimite.d = aux[1].fechaLimite.d;
            actx[1].fechaLimite.m = aux[1].fechaLimite.m;
            actx[1].fechaLimite.a = aux[1].fechaLimite.a;
            actx[1].ID = aux[1].ID; 
        }else if(strcmp(actx[i].prioridad, "NORMAL") == 0){
            
                while(strcmp(actx[l].prioridad, "ALTA") == 0){
                    l++;
                    contadorPrioridad++;
                }
                
            contadorPrioridad = contadorPrioridad + 1;
            
            printf("%d", contadorPrioridad);
            
            strcpy(aux[1].apellidoEncargado, actx[i].apellidoEncargado);
            strcpy(aux[1].prioridad, actx[i].prioridad);
            strcpy(aux[1].descripcion, actx[i].descripcion);
            aux[1].fechaCreacion.d = actx[i].fechaCreacion.d;
            aux[1].fechaCreacion.m = actx[i].fechaCreacion.m;
            aux[1].fechaCreacion.a = actx[i].fechaCreacion.a;
            
            aux[1].fechaLimite.d = actx[i].fechaLimite.d;
            aux[1].fechaLimite.m = actx[i].fechaLimite.m;
            aux[1].fechaLimite.a = actx[i].fechaLimite.a;
            aux[1].ID = actx[i].ID; 
        
        for(int k = cantTareas + 1; k > contadorPrioridad; k--){
            strcpy(actx[k].apellidoEncargado, actx[k - 1].apellidoEncargado);
            strcpy(actx[k].prioridad, actx[k - 1].prioridad);
            strcpy(actx[k].descripcion, actx[k - 1].descripcion);
            actx[k].fechaCreacion.d = actx[k - 1].fechaCreacion.d;
            actx[k].fechaCreacion.m = actx[k - 1].fechaCreacion.m;
            actx[k].fechaCreacion.a = actx[k - 1].fechaCreacion.a;
            
            actx[k].fechaLimite.d = actx[k - 1].fechaLimite.d;
            actx[k].fechaLimite.m = actx[k - 1].fechaLimite.m;
            actx[k].fechaLimite.a = actx[k - 1].fechaLimite.a;
            actx[k].ID = actx[k - 1].ID; 
        }
        
            strcpy(actx[contadorPrioridad].apellidoEncargado, aux[1].apellidoEncargado);
            strcpy(actx[contadorPrioridad].prioridad, aux[1].prioridad);
            strcpy(actx[contadorPrioridad].descripcion, aux[1].descripcion);
            actx[contadorPrioridad].fechaCreacion.d = aux[1].fechaCreacion.d;
            actx[contadorPrioridad].fechaCreacion.m = aux[1].fechaCreacion.m;
            actx[contadorPrioridad].fechaCreacion.a = aux[1].fechaCreacion.a;
            
            actx[contadorPrioridad].fechaLimite.d = aux[1].fechaLimite.d;
            actx[contadorPrioridad].fechaLimite.m = aux[1].fechaLimite.m;
            actx[contadorPrioridad].fechaLimite.a = aux[1].fechaLimite.a;
            actx[contadorPrioridad].ID = aux[1].ID; 
            
        }
}


//Accion que permite modificar un elemento de la lista dependiendo su ID.
void modificoTarea(TDatos actx[max], int idBuscar){
    int n=1;
    
        if(idBuscar > cantTareas || idBuscar <= 0){
            printf("\n¡Ese ID no existe!\n");
        }else{
            while(actx[n].ID != idBuscar){
                n++;
            }   
            printf("\n[MODIFICAR TAREA] %d\n", n);
            ingresoDatos(actx, n);
        }
}


//Accion que completa borra una tarea por ID seleccionado.
void completoTarea(TDatos actx[max], int idBuscar){
        int n=1;
        
        if(idBuscar > cantTareas || idBuscar <= 0){
            printf("\n¡Ese ID no existe!\n");
        }else{
        while(actx[n].ID != idBuscar){
            n++;
        }   
        for(int j = n; j < cantTareas; j++){
            strcpy(actx[j].apellidoEncargado, actx[j + 1].apellidoEncargado);
            strcpy(actx[j].prioridad, actx[j + 1].prioridad);
            strcpy(actx[j].descripcion, actx[j + 1].descripcion);
            
            actx[j].fechaCreacion.d = actx[j + 1].fechaCreacion.d;
            actx[j].fechaCreacion.m = actx[j + 1].fechaCreacion.m;
            actx[j].fechaCreacion.a = actx[j + 1].fechaCreacion.a;
            
            actx[j].fechaLimite.d = actx[j + 1].fechaLimite.d;
            actx[j].fechaLimite.m = actx[j + 1].fechaLimite.m;
            actx[j].fechaLimite.a = actx[j + 1].fechaLimite.a;
            actx[j].ID = actx[j + 1].ID;    //Acá cuando pedia eliminar, no sabia si el ID tenia que pasar a tomar el valor del ID eliminado, como en el enunciado no lo especiifca lo deje así sin cambiar el ID.
        }
        
        cantTareas = cantTareas - 1;
        }
}

//Accion que muestra las tareas dependiendo el nombre del empleado ingresado.
void buscoTareaUsuario(TDatos actx[max], char nombreUsuario[20]){
        printf("\n[LISTA DE TAREAS DEL EMPLEADO]\n");
        for(int i=1; i < cantTareas; i++){
            if(strcmp(actx[i].apellidoEncargado, nombreUsuario) == 0){
                muestroText(i);
            }
        }
}

//Accion que muestra las tareas urgentes del mes.
void buscoTareasUrgentes(TDatos actx[max]){
        printf("\n[LISTA DE TAREAS URGENTES]\n");
        for(int i=1; i < cantTareas; i++){
            if(actx[i].fechaLimite.m == mesActual){
                muestroText(i);
            }
        }
}

//Accion que muestra los elementos de la lista.
void muestroTareas(TDatos actx[max]){
    printf("\n[LISTA DE TAREAS]\n");
        for(int i=1; i < cantTareas; i++){
            muestroText(i);
        }
}

//Accion que guarda el arreglo en el archivo.
void guardoLista(TDatos actx[max]){
    FILE *arch;
        printf("\nGuardando lista...");
        
        arch=fopen("tareas.dat","wb");
            for(int i=1; i < cantTareas; i++){
                fwrite(&actx[i],sizeof(actx[i]),1,arch);
            }
        fclose(arch);
        
        printf("\n¡Lista guardada con exito!\n");
}

//Accion que utilizo para mostrar los elementos en muestroTarea, buscoTareaUsuario y buscoTareasUrgentes.
void muestroText(int numActual){
        printf("\nID: %d", actividad[numActual].ID);
        printf("\nApellido del encargado: %s", actividad[numActual].apellidoEncargado);
        printf("\nDescripcion de la tarea: %s", actividad[numActual].descripcion);
        printf("\nPrioridad de la tarea: %s", actividad[numActual].prioridad);
        printf("\nFecha de creacion: %d/%d/%d", actividad[numActual].fechaCreacion.d, actividad[numActual].fechaCreacion.m, actividad[numActual].fechaCreacion.a);
        printf("\nFecha Limite: %d/%d/%d\n", actividad[numActual].fechaLimite.d, actividad[numActual].fechaLimite.m, actividad[numActual].fechaLimite.a);
}

//Accion que utilizo para cargar datos en cargoTarea.
void ingresoDatos(TDatos actx[max], int numActual){
        printf("Ingrese el apellido del encargado: ");fflush(stdout);
        scanf("%s", actx[numActual].apellidoEncargado);
        
        printf("Ingrese la prioridad de la tarea (NORMAL o ALTA): ");fflush(stdout);
        scanf("%s", actx[numActual].prioridad);
        
        while(strcmp(actx[numActual].prioridad, "ALTA") != 0 && strcmp(actx[numActual].prioridad, "NORMAL") != 0){
            printf("Ingrese la prioridad de la tarea (NORMAL o ALTA): ");fflush(stdout);
            scanf("%s", actx[numActual].prioridad);
        }
        
        printf("Ingrese la descripcion de la tarea: ");fflush(stdout);
        while(getchar() != '\n');
        fgets(actx[numActual].descripcion, max, stdin);
        if ((strlen(actx[numActual].descripcion) > 0) && (actx[numActual].descripcion[strlen(actx[numActual].descripcion) - 1] == '\n'))
        {
            actx[numActual].descripcion[strlen(actx[numActual].descripcion) - 1] = '\0';
        }

        printf("Ingrese el dia limite: ");fflush(stdout);
        scanf("%d", &actx[numActual].fechaLimite.d);
        printf("Ingrese el mes limite: ");fflush(stdout);
        scanf("%d", &actx[numActual].fechaLimite.m);
        printf("Ingrese el año limite: ");fflush(stdout);
        scanf("%d", &actx[numActual].fechaLimite.a);
}

//Funcion que revisa si la lista esta llena.
int listaLlena(TDatos actx[max]){
    int m = 0;
        while(actx[m].ID != 0){
            m++;
        }
        
        if(m == max){
            return true;
        }else{
            return false;
        }
}

//Funcion que revisa si la lista esta vacia.
int listaVacia(TDatos actx[max]){
    int m = 1, contador = 0;
    
        while(actx[m].ID != 0){
            contador++;
            m++;
        }
        
        if(contador == 0){
            return true;
        }else{
            return false;
        }
}
