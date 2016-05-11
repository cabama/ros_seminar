/*
 * matematico_nodo
 * Se trata de un servicio el cual recibe un numero y lo multiplica por dos
 */


// LIBRERIAS
#include "ros/ros.h"
#include "seminario/multiplicador.h"


// Callback del servicio - cada vez que el servicio recibe un dato el software se mete dentro de esta funcion.
bool servicio(seminario::multiplicador::Request &req, seminario::multiplicador::Response &res){

    res.resultado = req.entrada * 2;
    ROS_INFO("Peticion: x = %d", (int)req.entrada);
    ROS_INFO("Respuesta: %d", (int)res.resultado);
    return true;

}

// Funcion main que registra el nodo y el servicio
int main (int argc, char **argv){
    ros::init(argc, argv, "matematico_nodo"); 
    ros::NodeHandle nodo;
    ros::ServiceServer service = nodo.advertiseService("multiplicador_servicio", servicio);
    ROS_INFO("Servicio Registrado");
    ros::spin();

    return 0;
}
