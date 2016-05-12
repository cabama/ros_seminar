/*
 * Reloj_nodo.cpp - Carlos Barreiro Mata
 * El programar debe de tener un timmer
 * Desarrollado por <barreymata@gmail.com>
 */


// INCLUIMOS LAS LIBRERIAS
// Librerias de ros + servicios y mensajes.
#include "ros/ros.h"
#include "std_msgs/Bool.h"      // Mensaje que envia cada 60 segundos para demostrar que esta vivo
#include "std_msgs/String.h"    // Mensaje que recibe por los topic start y reset de dialogo_nodo.
// Librerias para obtener el tiempo.
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
// Para manejo de string
#include <string>

// NAMESPACES
using namespace std;

// VARIABLES GLOBALES
// Nombre de nodos y topics.
const string nodo_name = "reloj_nodo";
const string topic_name = "still_alive";
const string topic_subscriber_start = "start_topic";
const string topic_subscriber_reset = "reset_topic";
// Mensaje actual y maximo de mensajes.
const int max_mensajes = 5;
int cont_mensajes = 0;
int tiempo_ultimo_mensaje;
// Formato para la fecha que se muestra por pantalla.
const char* fmt = "%a, %d %b %y %T %z";
// Publicadores y subscriptores globales.
ros::Publisher publicador_alive;
ros::NodeHandle *nodoGlobal; // Creamos el objeto nodo con el que interactuaremos.
ros::Timer timer_pantalla; // Objeto timer que mostrara por pantalla 3 veces por segundo


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


/*
 * GET_TIME
 * Esta funcion optiene simplemente el tiempo sin formato
 */
int get_time()
{
    return time(NULL);
}


/*
 * GET_UTC_TIME
 * La siguiente funcion sirve para obtener la fecha en formato UTC.
 */
string get_utc_time()
{
    // Variables locales.
    char fecha_utc[200];
    time_t t;
    struct tm *tmp;
    // Tomamos el tiempo.
    t = time(NULL);
    tmp = gmtime(&t);
    // Si no hay error lo formateamos con el formato indicado.
    if (tmp == NULL) {
        perror("No se pudo tomar fecha.");
    }
    if (strftime(fecha_utc, sizeof(fecha_utc), fmt, tmp) == 0) {
        fprintf(stderr, "strftime devolvio 0");
    } 
    // Devolvemos el resultado en un string.
    return string(fecha_utc);
}



/*
 * TimerCallbackStart
 * Cuando llega el mensaje start se inicializa el timer que llama a este callback.
 * Imprimir en pantalla la hora actual en formato UTC a una frecuencia de 3 veces por segundo.
 * Además la diferencia de tiempo desde que recibio el ultimo mensaje de start o reset
 */
void timerCallbackStart (const ros::TimerEvent&)
{
    //ROS_INFO("Estamos dentro del callback de time");
    cout << get_utc_time() << endl;
}



/*
 * TimerCallbackAlive
 * Es llamado cada 60 segundos por el timer del main.
 * La funcionalidad es enviar un mensaje para demostrar que este nodo sigue vivo.
 */
void timerCallbackAlive(const ros::TimerEvent&)
{
    ROS_INFO("Estamos vivos");
    std_msgs::Bool mensaje;
    mensaje.data = true;
    publicador_alive.publish(mensaje);
}


/*
 * FUNCIONCALLBACKSTART
 * Esta funcion se trata del callback cuando llega un mensaje por el topic start.
 * Entonces se inicializa el timer y muestra por pantalla el tiempo una vez cada 3 segundos.
 */

void funcionCallbackStart(const  std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("He recibido mi primer mensaje <start>");
    timer_pantalla = nodoGlobal->createTimer(ros::Duration((float)1/3), timerCallbackStart, false);
    tiempo_ultimo_mensaje = get_time();
    cout << "Terminamos la funcion Start";
}


/*
 * FUNCIONCALLBACKRESET
 * Callback al que se accede cuando llega un mensaje por el topic reset.
 */
void funcionCallbackReset(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("He recibido un mensaje <reset>");
    tiempo_ultimo_mensaje = get_time();
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -



/*
 * Main del programa: donde se registra el nodo y se realiza el publicador y subscriptor.
 */
int main (int argc, char ** argv)
{

    ros::init(argc,argv, nodo_name); // Nombre del nodo.
    ROS_INFO("nodo_receptor creado y registrado."); // Mensaje de información
    ros::NodeHandle nodo; // Creamos el objeto nodo con el que interactuaremos.
    nodoGlobal = &nodo;

    
    // SUBSCRIPTORES
    // Registramos la subscripcion al topic startopic en roscore.
    ros::Subscriber subscriptor_start = nodo.subscribe(topic_subscriber_start, 0, funcionCallbackStart);
    // Registramos la subscripcion al topic reset en roscore.
    ros::Subscriber subscriptor_reset = nodo.subscribe(topic_subscriber_reset, 0, funcionCallbackReset);
    
    //PUBLICADOR: registramos el publicador en roscore.
    publicador_alive = nodo.advertise<std_msgs::Bool>(topic_name, 0);

    // Timer que demuestra cada 60 segundos que este nodo de reloj sigue funcionando.
    ros::Timer timer_alive = nodo.createTimer(ros::Duration(60), timerCallbackAlive, false);
    ros::spin();
    return 0;
}