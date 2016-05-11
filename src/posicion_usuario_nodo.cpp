/*
 * posicion_usuario_nodo.cpp - Carlos Barreiro Mata
 * Pide una posicion x,y,z y la publica.
 * Desarrollado por <barreymata@gmail.com>
 */


// LIBRERIAS
#include "ros/ros.h"
#include "geometry_msgs/Vector3.h"
#include <sstream>

// NAMESPACE
using namespace std;

// Variables globales
const int sleep_time = 1;
const string nodo_name = "posicion_usuario_nodo", nodo_topic = "pos_usuario_topic";


// FUNCION MAIN
int main(int argc, char **argv)
{

    // Inicializamos y registramos el nodo.
    ros::init(argc, argv, nodo_name);
    ros::NodeHandle nodo;
    ROS_INFO("Nodo Posicion Usuario: creado y registrado");

    // Registramos el publicador
    ros::Publisher publicador = nodo.advertise<geometry_msgs::Vector3>(nodo_topic, 0);
    // Tiempo
    ros::Duration seconds_sleep(1);


  while (ros::ok())
  {
    
    // Pedimos las coordenadas al usuario.
    float coordenadas[3];
    cout << "Introduzca posicion X:";
    cin >> coordenadas[0];
    cout << "Introduzca posicion Y:";
    cin >> coordenadas[1];
    cout << "Introduzca posicion Z:";
    cin >> coordenadas[2];

    // Creamos el mensaje
    geometry_msgs::Vector3 mensaje;
    // Empaquetamos las coordenadas en el mensaje
    mensaje.x = coordenadas[0];
    mensaje.y = coordenadas[1];
    mensaje.z = coordenadas[2];

    // Publicamos el mensaje
    publicador.publish(mensaje);

    // Esperamos el tiempo necesario
    ros::spinOnce();
    seconds_sleep.sleep();
  }

  return 0;
}	