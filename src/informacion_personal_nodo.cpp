/*
 * informacion_personal_nodo.cpp
 * Este nodo pide los datos personales del usuario y los envia por el topic correspondiente.
 */


// LIBRERIAS
#include "ros/ros.h"
#include "seminario/inf_personal_usuario.h"
#include <sstream>
#include <vector>

// NAMESPACE
using namespace std;

// VARIABLES GLOBALES
const string nodo = "informacion_personal_nodo";
const string topic = "inf_pers_topic";


/*
 * Funcion main
 * En esta funcion se pedira y publicara constantemente los datos personales
 */

int main(int argc, char **argv)
{

    // Iniciamos y registramos el nodo.
    ros::init(argc, argv, nodo);
    ros::NodeHandle nodo;
    ROS_INFO("nodo_emisor creado y registrado");

    // Registramos el publicador
    ros::Publisher publicador = nodo.advertise<seminario::inf_personal_usuario>(topic, 0);
    ros::Duration seconds_sleep(1);

    // Bucle en el que entrara el programa mientras el nodo funcione correctamente
    // En este blucle se piden los datos personales y se publican.
    while (ros::ok())
    {

        // Iniciamos la variable que guardara el mensaje.
        seminario::inf_personal_usuario mensaje;
        // Iniciamos variables auxiliares para introducir más adelante en el mensaje.
        int edad;
        string nombre;
        vector<string> idiomas;

        // Pedimos nombre y edad
        cout << "Introduzca el nombre:";
        cin >> nombre;
        cout << "Introduzca la edad"; 
        cin >> edad;

        // Pedimos los distinto idiomas del usuario.
        // El usuario podra insertar tantos idomas como quiera hasta escribir la palabra "exit".
        while(true){
        	cout << "Introduzca un idioma (exit para parar el bucle):";
        	string idioma;
        	getline(cin, idioma);

        	if(idioma == "exit")
        		break;
        	else if (idioma!=""){
        		idiomas.push_back (idioma);
        	}        	
        }

        // Introducimos los datos de las variables auxiliares en el mensaje
        mensaje.nombre = nombre;
        mensaje.edad = edad;
        mensaje.idiomas = idiomas;

        // Publicamos el mensaje
        publicador.publish(mensaje);

        // Mantenemos el nodo activo.
        ros::spinOnce();
        seconds_sleep.sleep();
    }

    return 0;
}