//
//  main.cpp
//  Pratica2
//
//  Created by Francisco Monteiro on 03/03/2019.
//  Copyright © 2019 Francisco Monteiro. All rights reserved.
#include <windows.h>
#include "stdlib.h"
#include "math.h"
#include "stdio.h"
#include <GL\glut.h>
#include "RgbImage.h"
//
//  main.cpp
//  Pratica2


//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED         1.0, 0.0, 0.0, 1.0
#define YELLOW     1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define LARANJA    0.7, 1,1, 1.0
#define PI         3.14159

//================================================================================
//===========================================================Variaveis e constantes
GLuint   texture[4];
RgbImage imag;

//------------------------------------------------------------ Sistema Coordenadas + objectos
GLint        wScreen=1200, hScreen=1000;        //.. janela (pixeis)
GLfloat        xC=10.0, yC=10.0, zC=10.0;        //.. Mundo  (unidades mundo)

//------------------------------------------------------------ Observador
GLfloat  rVisao=150, aVisao=0.5*PI, incVisao=0.05*PI;
GLfloat  obsP[] ={0,50,-100};
GLfloat  angZoom=90;
GLfloat  incZoom=3;
GLdouble larguraEscada=40;
GLdouble comprimentoEscada=7.5;
GLdouble alturaEscada=5;
GLdouble larguraTecla=30;
GLdouble comprimentoTecla=2;
GLdouble alturaTecla=1;
static GLint pretas[]={1,1,0,1,1,1,0,1,1,0,1,1,0,1,1,1,0};
GLdouble tx=0;
GLdouble ty=0;
GLdouble tz=0;
GLint SEGUIDAS=4;
GLint INTERVALO=3;
GLdouble Upx=0;
GLdouble Upy=0;
GLdouble Upz=-1;

// Vetor auxiliar
GLdouble Vx=0;
GLdouble Vz=0;
GLdouble Vy=0;
GLUquadricObj*  bola = gluNewQuadric ( );


//=========================================================== FACES DA MESA
GLboolean   frenteVisivel=1;
static GLuint     cima[] = {8,11, 10,  9};
static GLuint     esquerda[] = {0,1,2,3};
static GLuint     direita[] = {7,6,5,4};


GLfloat tam=2.0; //estão com largura de 800
static GLfloat vertices[]={
-40.000000, -0.000000, 15.000000, 40.000000, -0.000000, 15.000000, 40.000000, 0.000000, 0.000000, -40.000000, 0.000000, 0.000000, -40.000000, 0.000000, 15.000000, 40.000000, 0.000000, 15.000000, 40.000000, 16.000000, 15.000000, -40.000000, 16.000000, 15.000000, -40.000000, 16.000000, 30.000000, 40.000000, 16.000000, 30.000000, 40.000000, 16.000000, 15.000000, -40.000000, 16.000000, 15.000000, -40.000000, 16.000000, 30.000000, 40.000000, 16.000000, 30.000000, 40.000000, 32.000000, 30.000000, -40.000000, 32.000000, 30.000000, -40.000000, 32.000000, 45.000000, 40.000000, 32.000000, 45.000000, 40.000000, 32.000000, 30.000000, -40.000000, 32.000000, 30.000000, -40.000000, 32.000000, 45.000000, 40.000000, 32.000000, 45.000000, 40.000000, 48.000000, 45.000000, -40.000000, 48.000000, 45.000000, -40.000000, 48.000000, 60.000000, 40.000000, 48.000000, 60.000000, 40.000000, 48.000000, 45.000000, -40.000000, 48.000000, 45.000000, -40.000000, 48.000000, 60.000000, 40.000000, 48.000000, 60.000000, 40.000000, 64.000000, 60.000000, -40.000000, 64.000000, 60.000000, -40.000000, 64.000000, 75.000000, 40.000000, 64.000000, 75.000000, 40.000000, 64.000000, 60.000000, -40.000000, 64.000000, 60.000000, -40.000000, 64.000000, 75.000000, 40.000000, 64.000000, 75.000000, 40.000000, 80.000000, 75.000000, -40.000000, 80.000000, 75.000000, -40.000000, 80.000000, 90.000000, 40.000000, 80.000000, 90.000000, 40.000000, 80.000000, 75.000000, -40.000000, 80.000000, 75.000000, -40.000000, 80.000000, 90.000000, 40.000000, 80.000000, 90.000000, 40.000000, 96.000000, 90.000000, -40.000000, 96.000000, 90.000000, -40.000000, 96.000000, 105.000000, 40.000000, 96.000000, 105.000000, 40.000000, 96.000000, 90.000000, -40.000000, 96.000000, 90.000000, -40.000000, 96.000000, 105.000000, 40.000000, 96.000000, 105.000000, 40.000000, 112.000000, 105.000000, -40.000000, 112.000000, 105.000000, -40.000000, 112.000000, 120.000000, 40.000000, 112.000000, 120.000000, 40.000000, 112.000000, 105.000000, -40.000000, 112.000000, 105.000000, -40.000000, 112.000000, 120.000000, 40.000000, 112.000000, 120.000000, 40.000000, 128.000000, 120.000000, -40.000000, 128.000000, 120.000000, -40.000000, 128.000000, 135.000000, 40.000000, 128.000000, 135.000000, 40.000000, 128.000000, 120.000000, -40.000000, 128.000000, 120.000000, -40.000000, 128.000000, 135.000000, 40.000000, 128.000000, 135.000000, 40.000000, 144.000000, 135.000000, -40.000000, 144.000000, 135.000000, -40.000000, 144.000000, 150.000000, 40.000000, 144.000000, 150.000000, 40.000000, 144.000000, 135.000000, -40.000000, 144.000000, 135.000000, -40.000000, 144.000000, 150.000000, 40.000000, 144.000000, 150.000000, 40.000000, 160.000000, 150.000000, -40.000000, 160.000000, 150.000000, -40.000000, 160.000000, 165.000000, 40.000000, 160.000000, 165.000000, 40.000000, 160.000000, 150.000000, -40.000000, 160.000000, 150.000000, -40.000000, 160.000000, 165.000000, 40.000000, 160.000000, 165.000000, 40.000000, 176.000000, 165.000000, -40.000000, 176.000000, 165.000000, -40.000000, 176.000000, 180.000000, 40.000000, 176.000000, 180.000000, 40.000000, 176.000000, 165.000000, -40.000000, 176.000000, 165.000000};

static GLfloat normais[] = {
0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, };
//------------------------------------------------------------ Cores
static GLfloat cores[]={
0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, };

void initTexturas();
//================================================================================
//=========================================================================== INIT
//================================================================================
//=========================================================================== INIT
void inicializa(void)
{
    glClearColor(BLACK);        //………………………………………………………………………………Apagar
    glEnable(GL_DEPTH_TEST);    //………………………………………………………………………………Profundidade
    glShadeModel(GL_SMOOTH);    //………………………………………………………………………………Interpolacao de cores
    
    //glEnable(GL_CULL_FACE);        //………………………………………………………………………………Faces visiveis
    //glCullFace(GL_BACK);        //………………………………………………………………………………Mostrar so as da frente
    
    glVertexPointer(3, GL_FLOAT, 0, vertices); //………………………………………Vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normais);
    glEnableClientState(GL_NORMAL_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, cores);
    glEnableClientState(GL_COLOR_ARRAY);
     initTexturas();
    
    
}



void drawEixos()
{
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
    glColor4f(RED);
    glBegin(GL_LINES);
    glVertex3i( 0, 0, 0);
    glVertex3i(150, 0, 0);
    glEnd();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
    glColor4f(GREEN);
    glBegin(GL_LINES);
    glVertex3i(0,  0, 0);
    glVertex3i(0, 150, 0);
    glEnd();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
    glColor4f(BLUE);
    glBegin(GL_LINES);
    glVertex3i( 0, 0, 0);
    glVertex3i( 0, 0,150);
    glEnd();
    
}

void drawBola()
{
    //------------------------- Bola
  //  glEnable(GL_TEXTURE_2D);
   glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[1]);
    glPushMatrix();
    glRotatef (       90, -1, 0, 0);
    glTranslatef ( 2,4,2);
    gluQuadricDrawStyle ( bola, GLU_FILL   ); // estava GLU_FILL
    gluQuadricNormals   ( bola, GLU_SMOOTH );
    gluQuadricTexture   ( bola, GL_TRUE    );
    gluSphere ( bola, 350, 150, 150);
    glPopMatrix();
   glDisable(GL_TEXTURE_2D);
    
}
void drawChao(){
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Chao y=0
    //glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glColor4f(WHITE);
    glTranslatef(0,-5,0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f);       glVertex3i( -500,  0, -500 );
    glTexCoord2f(1.0f, 0.0f);      glVertex3i( -500,   0,  500 );
    glTexCoord2f(1.0f, 1.0f);    glVertex3i(  500,   0,  500);
    glTexCoord2f(0.0f, 1.0f);    glVertex3i(  500,     0,  -500);
    glEnd();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
}
void drawCubo2(GLdouble x ,GLdouble y,GLdouble z){
//	glColor4f(YELLOW);glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(x,y,z);
    glScalef(comprimentoEscada, alturaEscada, larguraEscada);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f); glVertex3f( 1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f,0.0f);  glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f,1.0f); glVertex3f(-1.0f, 1.0f,  1.0f);
    glTexCoord2f(0.0f,1.0f); glVertex3f( 1.0f, 1.0f,  1.0f);
    glTexCoord2f(0.0f,0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f,0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f,1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f,1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    
    glTexCoord2f(0.0f,0.0f); glVertex3f( 1.0f,  1.0f, 1.0f);
    glTexCoord2f(1.0f,0.0f); glVertex3f(-1.0f,  1.0f, 1.0f);
    glTexCoord2f(1.0f,1.0f);  glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f,1.0f);glVertex3f( 1.0f, -1.0f, 1.0f);
    
    // Back face (z = -1.0f)
    glTexCoord2f(0.0f,0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f,0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f,1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f,1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    
    // Left face (x = -1.0f)
    glTexCoord2f(0.0f,0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f,0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(1.0f,1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f,1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    
    // Right face (x = 1.0f)
     glTexCoord2f(0.0f,0.0f); glVertex3f(1.0f,  1.0f, -1.0f);
     glTexCoord2f(1.0f,0.0f);glVertex3f(1.0f,  1.0f,  1.0f);
     glTexCoord2f(1.0f,1.0f);glVertex3f(1.0f, -1.0f,  1.0f);
     glTexCoord2f(0.0f,1.0f);glVertex3f(1.0f, -1.0f, -1.0f);
     glDisable(GL_TEXTURE_2D);
     glEnd();  // End of drawing color-cube
     glPopMatrix();
      glDisable(GL_TEXTURE_2D);
}

void drawCubo(GLdouble x ,GLdouble y,GLdouble z){
		glColor4f(BLACK);
		glBindTexture(GL_TEXTURE_2D,texture[2]);
			glColor4f(BLACK);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glColor4f(BLACK);
	glTranslatef(x,y,z);
    glScalef(comprimentoTecla, alturaTecla, larguraTecla);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f); glVertex3f( 1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f,0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f,1.0f); glVertex3f(-1.0f, 1.0f,  1.0f);
    glTexCoord2f(0.0f,1.0f); glVertex3f( 1.0f, 1.0f,  1.0f);
    
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    
    glVertex3f( 1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, 1.0f);
    
    // Back face (z = -1.0f)
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    
    // Left face (x = -1.0f)
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    
    // Right face (x = 1.0f)
    glVertex3f(1.0f,  1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();  // End of drawing color-cube
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void drawScene(){
    int i,auxx,auxy,auxz,aux,auy,auz;
    //levar double checkkkk <----------------------------------------------------------------------------------------------------------
    //glColorPointer(3, GL_FLOAT, 0, cor);     podia ser modificada a cor !
    /*for(i=0;i<=23;i++){
        glPushMatrix();
        esquerda[0]=4*i;
        esquerda[1]=4*i+1;
        esquerda[2]=4*i+2;
        esquerda[3]=4*i+3;
       if((i/SEGUIDAS)%INTERVALO==0){
       
        auxy=vertices[(4*i)*3+1]+alturaTecla;
        auxx=vertices[(4*i)*3]+larguraEscada/2-((larguraEscada/2)-larguraTecla);
        auxz=vertices[(4*i)*3+2]-comprimentoEscada/2;
        glPushMatrix();
        printf("teste...%d %d %d\n",auxx,auxy,auxz);
        drawCubo(auxx,auxy,auxz);
   glPopMatrix();
}
    
	
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);auxz+larguraTecla/2-5
        glPopMatrix();
    }*/
    auxx=0;
    auxy=0;
    auxz=0;
    for(i=0;i<10;i++){
    	glColor4f(cores[i],cores[i+1],cores[i+2],0);
    	drawCubo2(auxx,auxy,auxz);
    	if(pretas[i]==1){
    		drawCubo(auxx+comprimentoEscada-comprimentoTecla,auxy+alturaEscada+alturaTecla,auxz+(larguraEscada-larguraTecla));
    	}
        
    	auxx+=comprimentoEscada*2;
    	auxy+= alturaEscada*2;
    	
       auy=auxy+alturaTecla;
        aux=auxx+larguraEscada/2-((larguraEscada/2)-larguraTecla);
        auz=auxz-comprimentoEscada/2;
        
    	//auxz+=comprimentoEscada;
}
    glColor4f(LARANJA);
    drawBola();
   // drawChao();

    
    
    //==================================== PAralelipipedo Amarelo
    
    
    
}

void initTexturas()
{   
	//----------------------------------------- Chao
		
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("marmore.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());  		   
		
	//
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	imag.LoadBmpFile("pano3.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
		
 		glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	imag.LoadBmpFile("pls.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData()); 
}





// Calcula a norma de um vetor
GLfloat norma(int x, int y, int z){
    return sqrt((pow(x,2)+pow(y,2)+pow(z,2)));
}


void display(void){
    
    //================================================================= APaga ecran/profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
   

    //================================================================= NAO MOFIFICAR
    glViewport (0, 0, wScreen, hScreen);                                // ESQUECER PoR AGORA
    glMatrixMode(GL_PROJECTION);                                        // ESQUECER PoR AGORA
    glLoadIdentity();
    //glOrtho(-200, 200, -200, 200, -200, 200);
    // ESQUECER PoR AGORA
    //gluPerspective(angZoom, (float)wScreen/hScreen, 0.1, 30*zC);            // ESQUECER PoR AGORA
    gluPerspective(90, (float)wScreen/hScreen, 1, 10000);
    glMatrixMode(GL_MODELVIEW);                                            // ESQUECER PoR AGORA
    glLoadIdentity();                                                    // ESQUECER PoR AGORA
    //================================================================= NAO MOFIFICAR
    
    
    //-------------------------------------------------------------- observador
    gluLookAt(obsP[0], obsP[1], obsP[2], tx,ty,tz, 0, 1, 0);
    
    //gluLookAt(0, 0, -50, 0,0,50, 0, 1, 0);
    //…………………………………………………………………………………………………………………………………………………………Objectos/modelos
    drawEixos();
    drawScene();
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Actualizacao
    glutSwapBuffers();
}


//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y){
    float normaVetor;
    
    switch (key) {
        case 'f':
        case 'F':
            frenteVisivel=!frenteVisivel;
            glutPostRedisplay();
            break;
        case 'A':
        case 'a':
            glutPostRedisplay();
            break;
            
        case 'S':
        case 's':
            Vx=tx-obsP[0];
            Vy=ty-obsP[1];
            Vz=tz-obsP[2];
            normaVetor=norma(Vx,Vy,Vz);
            obsP[0]-=Vx/normaVetor*10;
            obsP[1]-=Vy/normaVetor*10;
            obsP[2]-=Vz/normaVetor*10;
            tx-=Vx/normaVetor*10;
            ty-=Vy/normaVetor*10;
            tz-=Vz/normaVetor*10;
            glutPostRedisplay();
            break;
            
        case 'e':
        case 'E':
            glutPostRedisplay();
            break;
            
        case 'd':
        case 'D':
            glutPostRedisplay();
            break;
        case 'w':
        case 'W':
            Vx=tx-obsP[0];
            Vy=ty-obsP[1];
            Vz=tz-obsP[2];
            normaVetor=norma(Vx,Vy,Vz);
            obsP[0]+=Vx/normaVetor*10;
            obsP[1]+=Vy/normaVetor*10;
            obsP[2]+=Vz/normaVetor*10;
            tx+=Vx/normaVetor*10;
            ty+=Vy/normaVetor*10;
            tz+=Vz/normaVetor*10;
            glutPostRedisplay();
            break;
            //--------------------------- Escape
        case 27:
            exit(0);
            break;
    }
    
}





void teclasNotAscii(int key, int x, int y){
    
    if(key == GLUT_KEY_UP){
        ty+=rVisao*sin(incVisao);
    }
    if(key == GLUT_KEY_DOWN){
        ty-=rVisao*sin(incVisao);
    }
    
//    if (obsP[1]>yC)
//        obsP[1]=yC;
//    if (obsP[1]<-yC)
//        obsP[1]=-yC;
    
    if(key == GLUT_KEY_LEFT)
        aVisao = (aVisao - 0.3) ;
    if(key == GLUT_KEY_RIGHT)
        aVisao = (aVisao + 0.3) ;
    
    
    
    tx=rVisao*cos(aVisao)+obsP[0];
    tz=rVisao*sin(aVisao)+obsP[2];
    
    glutPostRedisplay();
    
}


//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize (wScreen, hScreen);
    glutInitWindowPosition (300, 100);
    glutCreateWindow ("{jh,pjmm}@dei.uc.pt|       |FaceVisivel:'f'|      |Observador:'SETAS'|        |Andar-'a/s'|        |Rodar -'e/d'| ");
    
    inicializa();
    
    glutSpecialFunc(teclasNotAscii);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    
    return 0;
}



