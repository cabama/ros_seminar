/*
 * Empaquetador_nodo.cpp
 * Carlos Barreiro Mata <barreymata@gmail.com>
 * Este fichero recoge tres mensajes de diferentes topics: inf_personal, emocion_callback y posicion.
 * Combina estos tres mensajes en uno y lo publica. Solo publica cuando han llegado los tres mensajes.
 */


// LIBRERIAS
#include "ros/ros.h"                        // Libreria de ROS
#include "seminario/inf_personal_usuario.h" // Libreria de mensaje.
#include "seminario/usuario.h"              // Libreria de mensaje.
#include "geometry_msgs/Vector3.h"          // Libreria de mensaje.
#include "std_msgs/String.h"                // Libreria de mensaje.

// NAMESPACE
using namespace std;

// VARIABLES GLOBALES
bool personalMsg=false, emocionMsg=false, posicionMsg=false; // Flags para saber que mensajes se han recibido.
seminario::usuario usuario_msg; // Inicializamos mensaje usuario que se publicara al recibir todos los mensajes.
ros::Publisher publicador; // Publicador, se inicializa en el main y se pone como variable global para acceder desde callback.


/*
 * Esta funcion comprueba que han llegado todos los mensajes.
 * Si han llegado toddolos los mensaje, se publica usuario_msg.
 * Es llamado por los diferentes callbacks de los subscriptores.
 */

void checkAllMessages(){

    // Si han llegado todos los mensajes (Todos los flags == true), publica y resetea.
    if(personalMsg == true && emocionMsg == true && posicionMsg == true)
    {
    	printf("He recibido todos los mensajes y publicare\n");
        // Publicamos el mensaje
        publicador.publish(usuario_msg);
        // Reseteamos los flags
    	personalMsg = false;
    	emocionMsg = false;
    	posicionMsg = false;
        // Vaciamos el mensaje
        seminario::usuario u;
        usuario_msg = u;
    }
    // Si no han llegado todos los mensajes, no se publica solo se escribe un mensaje por pantalla.
    else
    {
    	printf("Aun no estan todos positivos\n");
    }
}


/*
 * Las siguientes tres funciones son callbacks de los diferentes topics subscritos.
 * Guardan el mensaje recibido en la parte de usuario_msg correspondiente.
 * Finalmente llaman a checkAllMessages para comprobar si todos han sido recibidos y se debe pasar a su publicacion.
 */


//  Callback para cuando llegue un mensaje con informacion personal.
void personalCallback(const  seminario::inf_personal_usuario::ConstPtr& msg){
    ROS_INFO("He recibido informacion personal");
    personalMsg = true;
    usuario_msg.info = *msg;
    checkAllMessages();
}

//  Callback para cuando llegue un mensaje con una emocion.
void emocionCallback(const std_msgs::String::ConstPtr& msg){
	ROS_INFO("He recibido una emocion");
	emocionMsg = true;
    usuario_msg.emocion = msg->data;
	checkAllMessages();
}

//  Callback para cuando llegue un mensaje con una posicion.
void posicionCallback(const geometry_msgs::Vector3::ConstPtr& msg){
	ROS_INFO("He recibido una posicion");
	posicionMsg = true;
    usuario_msg.posicion = *msg;
	checkAllMessages();
}


/*
 * Finalmente la funcion main.
 * Donde se registran el nodo, las subscripciones a los diferentes topics y el publicador.
 */


int main (int argc, char ** argv){

	ros::init(argc,argv, "empaquetador_nodo"); // Nombre del nodo.
    ros::NodeHandle nodo; // Creamos el objeto nodo con el que interactuaremos.
	ROS_INFO("nodo_receptor creado y registrado."); // Mensaje de información

	// Distintos callback
    ros::Subscriber subspersonal = nodo.subscribe("inf_pers_topic",0, personalCallback);
    ros::Subscriber subsemocion = nodo.subscribe("emocion_topic",0, emocionCallback);
    ros::Subscriber subsposicion = nodo.subscribe("pos_usuario_topic",0, posicionCallback);
    //publicador
    publicador = nodo.advertise<seminario::usuario>("user_topic", 0);

    // loop infinito para que no se cierre el nodo
    ros::spin();
	return 0;
}


