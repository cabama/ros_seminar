#include "ros/ros.h"
#include "geometry_msgs/Vector3.h"
#include <sstream>
using namespace std;


/**
 * Nodo Posicion Usuario que publica las posiciones x y z;
 */


int main(int argc, char **argv)
{

    ros::init(argc, argv, "posicion_usuario_nodo");
    ros::NodeHandle nodo;
    ROS_INFO("Nodo Posicion Usuario: creado y registrado");
    ros::Publisher publicador = nodo.advertise<geometry_msgs::Vector3>("pos_usuario_topic", 0);
    ros::Duration seconds_sleep(1);


  while (ros::ok())
  {
    
    // Pedimos las coordenadas al usuario.
    float coordenadas[3];
    geometry_msgs::Vector3 mensaje;
    cout << "Introduzca posicion X:";
    cin >> coordenadas[0];
    cout << "Introduzca posicion Y:";
    cin >> coordenadas[1];
    cout << "Introduzca posicion Z:";
    cin >> coordenadas[2];

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