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
#include "std_msgs/String.h"            // Libreria del mensaje String   
//#include <cstdlib>                    // Libreria de prueba

// NAMESPACE
using namespace std;


// VARIABLES GLOBALES
// Variables constante que especifican el nombre del nodo, servicio o topic.
const string nodo_name = "dialogo_nodo";                // nombre que le vamos a dar a este nodo.
const string subscriber_name = "user_topic";            // nombre de topic al que nos subscribimos para obtener los mensajes del empaquetador.
const string service_name = "multiplicador_servicio";   // nombre del servicio que multiplica la edad.
const string publicador_name_start = "start_topic";     // nombre del topic publicador que envia un string la primera vez.
const string publicador_name_reset = "reset_topic";     // nombre del topic publicador que envia el string el resto de veces.
// Ponemos el servicio y publicador como variable global para poder usuarlo en el callback.
ros::ServiceClient client;
ros::Publisher publicador_start;
ros::Publisher publicador_reset;
std_msgs::String reloj_message;
// Flag para establecer cuando se ha realizado la primera publicacion y pasar de start a reset.
bool start = false;



/**
 * Funcion de Callback para cuando recibe 
 * @param msg mensaje recibido del topic "user_topic".
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
        // Ahora debemos mandar un mensaje a reloj_nodo. (deberemos determinar con el if si es start o reset).
        if (start == false)
        {
            publicador_start.publish(reloj_message);
            start = true;
        }
        else
        {
            publicador_reset.publish(reloj_message);
        }

    }
    else
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
	ros::init(argc,argv, nodo_name); // Nombre del nodo.
    // Tenemos el manejador del nodo
    ros::NodeHandle nodo;
    // Advertise del servicio que proporcionara el nodo
    client = nodo.serviceClient<seminario::multiplicador>(service_name);
    // Subscribtor al user_topic
    ros::Subscriber subscriptor = nodo.subscribe(subscriber_name,0, functionCallback);
    // Registramos el publicador
    publicador_start = nodo.advertise<std_msgs::String>(publicador_name_start, 0);
    publicador_reset = nodo.advertise<std_msgs::String>(publicador_name_reset, 0);
   	// Mantenemos el nodo activo
    ros::spin();

    return 0;
}