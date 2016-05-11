/*
 * dialogo_nodo.cpp
 * Carlos Barreiro Mata <barreymata@gmail.com>
 * - - - - - - - - - - - - - - - - - - - - - - -
 * Se encarga de publicar los mensajes que publica el nodo empaquetador.
 * Utiliza el servicio nodo_matematico para multiplicar la edad.
 * Se comunica con el reloj.
 */


// LIBRERIAS
#include "ros/ros.h"                    // Libreria de ros.
#include "seminario/multiplicador.h"    // Libreria del servicio multiplicador.
#include "seminario/usuario.h"          // Libreria del mensaje usuario.
#include <cstdlib>                      // Libreria de prueba

// VARIABLES GLOBALES
ros::ServiceClient client;  // Ponemos el servicio como variable global para poder usuarlo en el callback.


/**
 * Funcion de Callback para cuando recibe 
 * @param msg [description] mensaje recibido del topic "user_topic".
 */
void functionCallback(const seminario::usuario::ConstPtr& msg)
{
	// Declaramos la variable mensaje servicial (mensaje para el servicio nodo_matematico).
    seminario::multiplicador mensaje_servicial;
    // Introducimos en este la edad recibidad por el mensaje usuario del topic "user_topic".
    mensaje_servicial.request.entrada = msg->info.edad;

    // Lanzamos el servicio.
    if (client.call(mensaje_servicial))
    {
        // Si el servicio sale exitoso mostrara este mensaje.
        printf("Respuesta del servicio: %d", (int)mensaje_servicial.response.resultado);
    }else
    {   
        // Si el servicio falla mostrara el siguiente mensaje por pantalla.
        printf("UN FALLO EN EL SERVICIO!!");
    }
}


/** 
 * FUNCION MAIN.
 * En esta funcion se registra el nodo, el subscriptor y el servicio.
 */

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