/*
 * Reloj_nodo.cpp - Carlos Barreiro Mata
 * En este programa se enviara un mensaje cada x milisegundos...
 */

/*
 * TODO:
 * - Add descripcion del programa.
 * - Publicador creado pero sin el mensaje definido en el advertise ni en el callback.
 */

// Incluimos las librerias
#include "ros/ros.h"
#include "seminario/mensajeTest.h"

// Variables globales
int numero_mensajes = 0;
ros::Publisher publicador;

/*
 * Esta funcion se trata del callback cuando llega un mensaje
 */
void funcionCallback(const  seminario::mensajeTest::ConstPtr& msg){
    ROS_INFO("He recibido un mensaje con el numero: %d", msg->numero);
    if (numero_mensajes % 3 == 0){
    	publicador.publish(variable_message);
    }
    numero_mensajes++;
}

/*
 * Main del programa: donde se registra el nodo y se realiza el publicador y subscriptor.
 */
int main (int argc, char ** argv){

	ros::init(argc,argv, "reloj_nodo"); // Nombre del nodo.
	ros::NodeHandle nodo; // Creamos el objeto nodo con el que interactuaremos.
	ROS_INFO("nodo_receptor creado y registrado."); // Mensaje de información
    ros::Subscriber subscriptor = nodo.subscribe("topic_test",0, funcionCallback);
    publicador = nodo.advertise<seminario::message>("topic_name", 0);
    ros::spin();
	return 0;
}