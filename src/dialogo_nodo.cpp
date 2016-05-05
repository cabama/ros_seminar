#include "ros/ros.h"
#include "seminario/multiplicador.h"
#include "seminario/usuario.h"
#include <cstdlib>

ros::ServiceClient client;

void functionCallback(const seminario::usuario::ConstPtr& msg){
	seminario::multiplicador mensaje_servicial;
    mensaje_servicial.request.entrada = msg->info.edad;

    if (client.call(mensaje_servicial)){
        printf("Respuesta del servicio: %d", (int)mensaje_servicial.response.resultado);
    }else{
        printf("Un puto Fallo NOOOO!");
    }
}


int main (int argc, char **argv){

	// Iniciamos el nodo
	ros::init(argc,argv, "dialogo_nodo"); // Nombre del nodo.
    // Tenemos el manejador del nodo
    ros::NodeHandle nodo;
    // Advertise del servicio que proporcionara el nodo
    client = nodo.serviceClient<seminario::multiplicador>("multiplicador_servicio");
    ros::Subscriber subscriptor = nodo.subscribe("user_topic",0, functionCallback);
   	// Mantenemos el nodo activo
    ros::spin();

    return 0;
}