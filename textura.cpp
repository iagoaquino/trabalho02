//Iago de Aquino oliveira 494017
#include <GL/gl.h>
#include <iostream>
#include <GL/glext.h>
#include<GL\glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_images.h"



using namespace std;

unsigned int id_madeira = 0;
unsigned int id_plastico = 0;


int largura_madeira = 0,altura_madeira = 0,canais_madeira = 0;
int largura_plastico = 0,altura_plastico = 0,canais_plastico = 0;
void carregar_madeira(){
    //gerar textura
    glGenTextures(1,&id_madeira);
    glBindTexture(GL_TEXTURE_2D,id_madeira);
    stbi_set_flip_vertically_on_load(true);
    unsigned char* entrada = stbi_load("madeira.jpg",&largura_madeira,&altura_madeira,&canais_madeira,3);
    if(!entrada){
        cout<<"impossivel de carregar o arquivo"<<endl;
    }else{
        cout<<"arquivo carregado com sucesso"<<endl;
    }
    //configurar textura
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura_madeira, altura_madeira, 0, GL_RGB, GL_UNSIGNED_BYTE, entrada);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(entrada);
}
void carregar_plastico(){
    //gerar textura
    glGenTextures(1,&id_plastico);
    glBindTexture(GL_TEXTURE_2D,id_plastico);
    stbi_set_flip_vertically_on_load(true);
    unsigned char* entrada = stbi_load("madeira.jpg",&largura_plastico,&altura_plastico,&canais_plastico,3);
    if(!entrada){
        cout<<"impossivel de carregar o arquivo"<<endl;
    }else{
        cout<<"arquivo carregado com sucesso"<<endl;
    }
    //configurar textura
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura_plastico, altura_plastico, 0, GL_RGB, GL_UNSIGNED_BYTE, entrada);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(entrada);
}
