//Iago de Aquino oliveira 494017
#include<iostream>
#include <GL/gl.h>
#include <GL/glext.h>
#include<GL\glut.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include<math.h>
int estado_camera = 1;
glm::vec3 pos_luz(5,-5,3);
glm::vec3 ambiente(0.25f,0.25f,0.25f);
glm::vec3 difusa(1.0f,1.0f,1.0f);
glm::vec3 especular(0.5f,0.5f,0.5f);
glm::vec3 pos_camera(20,20,10);
glm::vec3 prox_pos_camera(0,20,10);
glm::vec3 aplicar_luz(glm::vec3 normal,glm::vec3 pos,glm::vec3 cor_objeto,glm::vec3 ambiente_objeto, glm::vec3 especular_objeto,float shines){
    glm::vec3 lp = normalize(pos_luz-pos);
    glm::vec3 vw = normalize(pos_camera-pos);
    glm::vec3 rf = 2*glm::dot(lp,normal)*normal -lp;
    glm::vec3 ambiente_final = ambiente * ambiente_objeto;
    glm::vec3 difusa_final = (difusa * cor_objeto) * glm::dot(normal,lp);
    glm::vec3 especular_final;
    if(glm::dot(vw,rf) < 0){
        especular_final = glm::vec3(0.0f,0.0f,0.0f);
    }else{
        especular_final = especular * especular_objeto * pow(glm::dot(vw,rf),shines);
    }
    glm::vec3 resultado_final = ambiente_final+difusa_final+especular_final;
    return resultado_final;
}
