#include "ros/ros.h"
#include "seminario/inf_personal_usuario.h"
#include <sstream>
#include <vector>
using namespace std;



/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{


    ros::init(argc, argv, "informacion_personal_nodo");
    ros::NodeHandle nodo;
    ROS_INFO("nodo_emisor creado y registrado");
    ros::Publisher publicador = nodo.advertise<seminario::inf_personal_usuario>("inf_pers_topic", 0);
    ros::Duration seconds_sleep(1);


  int count = 0;
  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    seminario::inf_personal_usuario mensaje;
    int edad;
    string nombre;
    vector<string> idiomas;



    // Pedimos nombre y edad
    cout << "Introduzca el nombre:";
    cin >> nombre;
    cout << "Introduzca la edad"; 
    cin >> edad;
    // Pedimos los distinto idiomas del usuario
    while(true){
    	cout << "Introduzca un idioma (exit para parar el bucle):";
    	string idioma;
    	getline(cin, idioma);

    	if(idioma == "exit")
    		break;
    	else if (idioma!=""){
    		idiomas.push_back (idioma);
    	}

    	ROS_INFO("contador: %d, idioma: %s", count++, idioma.c_str());
    	
    }

    mensaje.nombre = nombre;
    mensaje.edad = edad;
    mensaje.idiomas = idiomas;

    publicador.publish(mensaje);

    ros::spinOnce();

    seconds_sleep.sleep();
    ++count;
  }


  return 0;
}