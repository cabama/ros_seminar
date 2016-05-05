#include "ros/ros.h"
#include "seminario/inf_personal_usuario.h"
#include "seminario/usuario.h"
#include "geometry_msgs/Vector3.h"
#include "std_msgs/String.h"

/*
 * Variables globales
 */

// Flags para saber que mensajes han llegado
bool personalMsg=false, emocionMsg=false, posicionMsg=false; 
seminario::usuario usuario_msg;
ros::Publisher publicador;



// Compruba que han llegado los tres mensajes
// Funcion que se llama cuando llega uno de los mensajes
void checkAllMessages(){
    if(personalMsg == true && emocionMsg == true && posicionMsg == true){
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
    }else{
    	printf("Aun no estan todos positivos\n");
    }
}


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


