#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <string>
using namespace std;
/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{


	ros::init(argc, argv, "emocion_usuario_nodo");
	ros::NodeHandle nodo;
	ROS_INFO("nodo_emisor creado y registrado");
	ros::Publisher publicador = nodo.advertise<std_msgs::String>("emocion_topic", 0);
	ros::Duration seconds_sleep(1);


	int count = 0;
	while (ros::ok())
	{
	/**
	 * This is a message object. You stuff it with data, and then publish it.
	 */
	std_msgs::String mensaje;

	// Pedimos el datos y se lo empaquetamos en el mensaje
 	string nombre;
 	cout << "Introduzca la emocion sentida:";
   	getline(cin, nombre);
   	mensaje.data = nombre;
	publicador.publish(mensaje);

	ros::spinOnce();

	seconds_sleep.sleep();
	++count;
	}


  return 0;
}