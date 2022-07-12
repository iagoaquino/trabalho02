#include <iostream>
#include "tabuleiro.h"
#include "objeto.h"
#include "textura.cpp"
#include "leitura.cpp"
#define FPS 60
using namespace std;
float w = 1200,h = 600;
int ativar_movimento = 0;
Objeto* objeto_rei = ler_arquivo("rei.obj");
Objeto* objeto_rainha = ler_arquivo("rainha.obj");
Quadrado tabuleiro[64];
glm::vec3 cam_inicial;
float t = 0;
void movimento_animado(int v){
    glutTimerFunc(1000.0/FPS,movimento_animado,0);
    if(ativar_movimento == 1){
        t+= 0.007;
        cout<<t<<endl;

        pos_camera = ((1-t)*cam_inicial) + (t*prox_pos_camera);
        if(t >= 1){
            ativar_movimento = 0;
            t = 0;
            switch(estado_camera){
                case 1:
                    cout<<estado_camera<<endl;
                    estado_camera = 2;
                    prox_pos_camera = glm::vec3(-5,20,10);
                break;
                case 2:
                    cout<<estado_camera<<endl;
                    estado_camera = 3;
                    prox_pos_camera = glm::vec3(-5,-5,10);
                break;
                case 3:
                    cout<<estado_camera<<endl;
                    estado_camera = 4;
                    prox_pos_camera = glm::vec3(20,-5,10);
                break;
                case 4:
                    cout<<estado_camera<<endl;
                    estado_camera = 1;
                    prox_pos_camera = glm::vec3(20,20,10);
                break;

            }
        }
    }
    glutPostRedisplay();
}
glm::vec2 planarX(glm::vec3 ponto){
    return glm::vec2(1-ponto.z,ponto.y);
}
glm::vec2 planarY(glm::vec3 ponto){
    return glm::vec2(ponto.x,1-ponto.z);
}
glm::vec2 planarZ(glm::vec3 ponto){
    return glm::vec2(ponto.x*ponto.y,0);
}
void desenhar_tabuleiro(){
    glBindTexture(GL_TEXTURE_2D,id_madeira);
    for(int i = 0;i<64;i++){
        glBegin(GL_QUADS);
            glm::vec3 cor1 = aplicar_luz(glm::vec3(0,0,1),glm::vec3(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y+1,tabuleiro[i].pos.z),glm::vec3(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]),glm::vec3(0.2,0.2,0.2),glm::vec3(0.9,0.9,0.9),1);
            glColor3f(cor1.x,cor1.y,cor1.z);
            glTexCoord2f(0,1);
            glVertex3f(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y+1,tabuleiro[i].pos.z);
            glm::vec3 cor2 = aplicar_luz(glm::vec3(0,0,1),glm::vec3(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y+1,tabuleiro[i].pos.z),glm::vec3(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]),glm::vec3(0.2,0.2,0.2),glm::vec3(0.9,0.9,0.9),1);
            glColor3f(cor2.x,cor2.y,cor2.z);
            glTexCoord2f(1,1);
            glVertex3f(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y+1,tabuleiro[i].pos.z);
            glm::vec3 cor3 = aplicar_luz(glm::vec3(0,0,1),glm::vec3(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y-1,tabuleiro[i].pos.z),glm::vec3(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]),glm::vec3(0.2,0.2,0.2),glm::vec3(0.9,0.9,0.9),1);
            glColor3f(cor3.x,cor3.y,cor3.z);
            glTexCoord2f(1,0);
            glVertex3f(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y-1,tabuleiro[i].pos.z);
            glm::vec3 cor4 = aplicar_luz(glm::vec3(0,0,1),glm::vec3(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y-1,tabuleiro[i].pos.z),glm::vec3(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]),glm::vec3(0.2,0.2,0.2),glm::vec3(0.9,0.9,0.9),1);
            glColor3f(cor4.x,cor4.y,cor4.z);
            glTexCoord2f(0,0);
            glVertex3f(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y-1,tabuleiro[i].pos.z);
        glEnd();
    }
    glBindTexture(GL_TEXTURE_2D,0);
}
void desenhar_objeto(){
    glPushMatrix();
    glTranslatef(objeto_rei->translate.x,objeto_rei->translate.y,objeto_rei->translate.z);
    glScalef(3,3,3);
    glBegin(GL_TRIANGLES);
        for(int i = 0;i < objeto_rei->quant_lados;i++){
           glm::vec3 cor1 = aplicar_luz(objeto_rei->pontos[objeto_rei->faces[i].id_ponto_1 - 1].normal,objeto_rei->pontos[objeto_rei->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.2,0.2,0.2),glm::vec3(0.2,0.2,0.2),glm::vec3(0.9,0.9,0.9),29);
           glColor3f(cor1.x,cor1.y,cor1.z);
           glVertex3f(objeto_rei->pontos[objeto_rei->faces[i].id_ponto_1-1].coord.x,objeto_rei->pontos[objeto_rei->faces[i].id_ponto_1-1].coord.y,objeto_rei->pontos[objeto_rei->faces[i].id_ponto_1-1].coord.z);
           glm::vec3 cor2 = aplicar_luz(objeto_rei->pontos[objeto_rei->faces[i].id_ponto_2 - 1].normal,objeto_rei->pontos[objeto_rei->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.2,0.2,0.2),glm::vec3(0.2,0.2,0.2),glm::vec3(0.9,0.9,0.9),29);
           glColor3f(cor2.x,cor2.y,cor2.z);
           glVertex3f(objeto_rei->pontos[objeto_rei->faces[i].id_ponto_2-1].coord.x,objeto_rei->pontos[objeto_rei->faces[i].id_ponto_2-1].coord.y,objeto_rei->pontos[objeto_rei->faces[i].id_ponto_2-1].coord.z);
           glm::vec3 cor3 = aplicar_luz(objeto_rei->pontos[objeto_rei->faces[i].id_ponto_3 - 1].normal,objeto_rei->pontos[objeto_rei->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.2,0.2,0.2),glm::vec3(0.2,0.2,0.2),glm::vec3(0.9,0.9,0.9),29);
           glColor3f(cor3.x,cor3.y,cor3.z);
           glVertex3f(objeto_rei->pontos[objeto_rei->faces[i].id_ponto_3-1].coord.x,objeto_rei->pontos[objeto_rei->faces[i].id_ponto_3-1].coord.y,objeto_rei->pontos[objeto_rei->faces[i].id_ponto_3-1].coord.z);
        }
    glEnd();
    glPopMatrix();
}
void desenhar(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90,1,1,40);
    glMatrixMode(GL_MODELVIEW);
    glm::mat4 camera = glm::lookAt(pos_camera,
                                   glm::vec3(5,5,0),
                                   glm::vec3(0,0,1));
    glLoadMatrixf(glm::value_ptr(camera));
    glBegin(GL_POINTS);
        glColor3f(1,1,1);
        glVertex3f(pos_luz.x,pos_luz.y,pos_luz.z);
    glEnd();
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(20,0,0);

        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,20,0);

        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,20);
    glEnd();
    desenhar_tabuleiro();
    desenhar_objeto();
    glFlush();
}
void criarTabuleiro(){
    int x = 1, y = 1,z = 0,pos = 0,cont = 0;
    for(int i = 0; i < 8 ;i++){
        for(int j = 0;j < 8;j++){
            Quadrado quadrado;
            if(cont % 2 == 0){
                quadrado.color[0] = 1;
                quadrado.color[1] = 1;
                quadrado.color[2] = 1;
            }else{
                quadrado.color[0] = 0;
                quadrado.color[1] = 0;
                quadrado.color[2] = 0;
            }
            quadrado.pos.x = x;
            quadrado.pos.y = y;
            quadrado.pos.z = z;
            tabuleiro[pos] = quadrado;
            x += 2;
            pos++;
            cont++;
        }
        cont++;
        y +=2;
        x = 1;
    }
}
void pegar_posicao(int button,int state,int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        cam_inicial = pos_camera;
        ativar_movimento = 1;
    }
}
void inicializar(){
    glEnable(GL_TEXTURE_2D);
    glPointSize(10);
    glClearColor(0.5,0.5,0.5,1);
    glPointSize(10);
    glLineWidth(5);
    criarTabuleiro();
    objeto_rei->translate = glm::vec3(1,15,0);
    carregar_madeira();
}
int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100,20);
    glutInitWindowSize(1200,600);
    glutCreateWindow("Trabalho 1");
    inicializar();
    glutDisplayFunc(desenhar);
    glutMouseFunc(pegar_posicao);
    glutTimerFunc(1000/FPS,movimento_animado,0);
    glutMainLoop();
}
