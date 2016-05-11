/*
 * Empaquetador_nodo.cpp
 * Carlos Barreiro Mata <barreymata@gmail.com>
 * Este nodo pide al usuario una emocion y la publica por el topic correspondiente.
 */


// LIBRERIAS
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <string>

// NAMESPACE
using namespace std;

// VARIABLES GLOBALES
const string nodo_name = "emocion_usuario_nodo";
const string publicador_name = "emocion_topic";

/**
 * Funcion Main donde se registra el nodo y el publicador.
 * Posteriormente se entra en un bucle el cual pide una emocion y la publica.
 */

int main(int argc, char **argv)
{

	// Registramos el nodo
	ros::init(argc, argv, nodo_name);
	ros::NodeHandle nodo;
	ROS_INFO("nodo_emisor creado y registrado");
	// Registramos el publicador
	ros::Publisher publicador = nodo.advertise<std_msgs::String>(publicador_name, 0);
	// Definimos sleep para pedir la siguiente emocion.
	ros::Duration seconds_sleep(1);


	while (ros::ok())
	{

		// Asignamos espacio de memoria al mensaje.
		std_msgs::String mensaje;
		string nombre;

		// Pedimos el datos y se lo empaquetamos en el mensaje
		cout << "Introduzca la emocion sentida:";
		getline(cin, nombre);
		mensaje.data = nombre;
		publicador.publish(mensaje);

		// Esperamos el tiempo indicado para la siguiente iteraccion
		ros::spinOnce();
		seconds_sleep.sleep();
	}


  return 0;
}