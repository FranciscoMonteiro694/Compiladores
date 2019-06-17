//
//  main.cpp
//  Pratica2
//
//  Created by Francisco Monteiro on 03/03/2019.
//  Copyright ? 2019 Francisco Monteiro. All rights reserved.
#include <windows.h>
#include "stdlib.h"
#include "math.h"
#include "stdio.h"
#include <GL\glut.h>
#include "RgbImage.h"
#include "materiais.h"
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
static GLint rodar[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
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
int is_1_pressed = 0;
int is_2_pressed = 0;
int is_3_pressed = 0;
int is_4_pressed = 0;
int is_5_pressed = 0;
int is_6_pressed = 0;
int is_7_pressed = 0;
int is_8_pressed = 0;
int is_9_pressed = 0;
int is_0_pressed = 0;

GLfloat Teto[4] ={ 0.0, 100, 0.0, 1.0}; 

//=========================================================== FACES DA MESA
GLboolean   frenteVisivel=1;
static GLuint     cima[] = {8,11, 10,  9};
static GLuint     esquerda[] = {0,1,2,3};
static GLuint     direita[] = {7,6,5,4};

GLfloat focoCorDif[4] ={ 0.9, 0.9, 0.9, 1.0}; 
GLfloat focoCorEsp[4] ={ 1.0, 1.0, 1.0, 1.0}; 

//------------------------------------------------------------ Iluminacao Ambiente
GLint   dia=0;
GLfloat intensidade=0.0;
GLfloat luzGlobalCorAmb[4]={intensidade,intensidade,intensidade,1.0};   //


//…………………………………………………………………………………………………………………………………………… Lanterna (local) - FOCO
GLint   ligaLuz=0;
GLfloat rFoco=1.1, aFoco=aVisao;
GLfloat incH =0.0, incV=0.0;
GLfloat incMaxH =0.5, incMaxV=0.35;
GLfloat focoPini[]= { obsP[0], obsP[1], obsP[2], 1.0 };
GLfloat focoPfin[]= { obsP[0]-rFoco*cos(aFoco), obsP[1], obsP[2]-rFoco*sin(aFoco), 1.0};
GLfloat focoDir[] = { focoPfin[0]-focoPini[0], 0, focoPfin[2]-focoPini[2]};
GLfloat focoExp   = 10.0;
GLfloat focoCut   = 60.0;
GLfloat localPos[4]   = {20, 50, 20, 1.0};
GLfloat localCorAmb[4]= { 1.0, 1.0, 1.0, 1.0};
GLfloat localCorDif[4]= { 1.0, 1.0, 1.0, 1.0};
GLfloat localCorEsp[4]= { 1.0, 1.0, 1.0, 1.0};

GLfloat tam=2.0; //est„o com largura de 800
static GLfloat vertices[]={
    -40.000000, -0.000000, 15.000000, 40.000000, -0.000000, 15.000000, 40.000000, 0.000000, 0.000000, -40.000000, 0.000000, 0.000000, -40.000000, 0.000000, 15.000000, 40.000000, 0.000000, 15.000000, 40.000000, 16.000000, 15.000000, -40.000000, 16.000000, 15.000000, -40.000000, 16.000000, 30.000000, 40.000000, 16.000000, 30.000000, 40.000000, 16.000000, 15.000000, -40.000000, 16.000000, 15.000000, -40.000000, 16.000000, 30.000000, 40.000000, 16.000000, 30.000000, 40.000000, 32.000000, 30.000000, -40.000000, 32.000000, 30.000000, -40.000000, 32.000000, 45.000000, 40.000000, 32.000000, 45.000000, 40.000000, 32.000000, 30.000000, -40.000000, 32.000000, 30.000000, -40.000000, 32.000000, 45.000000, 40.000000, 32.000000, 45.000000, 40.000000, 48.000000, 45.000000, -40.000000, 48.000000, 45.000000, -40.000000, 48.000000, 60.000000, 40.000000, 48.000000, 60.000000, 40.000000, 48.000000, 45.000000, -40.000000, 48.000000, 45.000000, -40.000000, 48.000000, 60.000000, 40.000000, 48.000000, 60.000000, 40.000000, 64.000000, 60.000000, -40.000000, 64.000000, 60.000000, -40.000000, 64.000000, 75.000000, 40.000000, 64.000000, 75.000000, 40.000000, 64.000000, 60.000000, -40.000000, 64.000000, 60.000000, -40.000000, 64.000000, 75.000000, 40.000000, 64.000000, 75.000000, 40.000000, 80.000000, 75.000000, -40.000000, 80.000000, 75.000000, -40.000000, 80.000000, 90.000000, 40.000000, 80.000000, 90.000000, 40.000000, 80.000000, 75.000000, -40.000000, 80.000000, 75.000000, -40.000000, 80.000000, 90.000000, 40.000000, 80.000000, 90.000000, 40.000000, 96.000000, 90.000000, -40.000000, 96.000000, 90.000000, -40.000000, 96.000000, 105.000000, 40.000000, 96.000000, 105.000000, 40.000000, 96.000000, 90.000000, -40.000000, 96.000000, 90.000000, -40.000000, 96.000000, 105.000000, 40.000000, 96.000000, 105.000000, 40.000000, 112.000000, 105.000000, -40.000000, 112.000000, 105.000000, -40.000000, 112.000000, 120.000000, 40.000000, 112.000000, 120.000000, 40.000000, 112.000000, 105.000000, -40.000000, 112.000000, 105.000000, -40.000000, 112.000000, 120.000000, 40.000000, 112.000000, 120.000000, 40.000000, 128.000000, 120.000000, -40.000000, 128.000000, 120.000000, -40.000000, 128.000000, 135.000000, 40.000000, 128.000000, 135.000000, 40.000000, 128.000000, 120.000000, -40.000000, 128.000000, 120.000000, -40.000000, 128.000000, 135.000000, 40.000000, 128.000000, 135.000000, 40.000000, 144.000000, 135.000000, -40.000000, 144.000000, 135.000000, -40.000000, 144.000000, 150.000000, 40.000000, 144.000000, 150.000000, 40.000000, 144.000000, 135.000000, -40.000000, 144.000000, 135.000000, -40.000000, 144.000000, 150.000000, 40.000000, 144.000000, 150.000000, 40.000000, 160.000000, 150.000000, -40.000000, 160.000000, 150.000000, -40.000000, 160.000000, 165.000000, 40.000000, 160.000000, 165.000000, 40.000000, 160.000000, 150.000000, -40.000000, 160.000000, 150.000000, -40.000000, 160.000000, 165.000000, 40.000000, 160.000000, 165.000000, 40.000000, 176.000000, 165.000000, -40.000000, 176.000000, 165.000000, -40.000000, 176.000000, 180.000000, 40.000000, 176.000000, 180.000000, 40.000000, 176.000000, 165.000000, -40.000000, 176.000000, 165.000000};

static GLfloat normais[] = {
    0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, };
//------------------------------------------------------------ Cores
static GLfloat cores[]={
    0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, };

void initTexturas();
void initLights();
void worker();
void initMaterials(int material);
//================================================================================
//=========================================================================== INIT
//================================================================================
//=========================================================================== INIT
void inicializa(void)
{
    glClearColor(BLACK);        //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖApagar
    glEnable(GL_DEPTH_TEST);    //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖProfundidade
    glEnable(GL_NORMALIZE);   
    glShadeModel(GL_SMOOTH);    //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖInterpolacao de cores
    
    //glEnable(GL_CULL_FACE);        //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖFaces visiveis
    //glCullFace(GL_BACK);        //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖMostrar so as da frente
    
    glVertexPointer(3, GL_FLOAT, 0, vertices); //Vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normais);
    glEnableClientState(GL_NORMAL_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, cores);
    glEnableClientState(GL_COLOR_ARRAY);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    initTexturas();
    glEnable(GL_LIGHTING); //Ativar esta linha deixa tudo a preto
    initLights();
    initMaterials(1);
    
}

//========================================================= ILUMINACAO
void initLights(void){
    //…………………………………………………………………………………………………………………………………………… Ambiente
    
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
    
    glLightfv(GL_LIGHT0, GL_POSITION,      localPos );
    glLightfv(GL_LIGHT0, GL_AMBIENT,       localCorAmb );
    glLightfv(GL_LIGHT0, GL_DIFFUSE,       localCorDif );
    glLightfv(GL_LIGHT0, GL_SPECULAR,      localCorEsp );
    //--------------------------------------------------------Pontual
    glLightfv(GL_LIGHT2, GL_POSITION,Teto);
	//	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,focoDir );
	//glLightf (GL_LIGHT1, GL_SPOT_EXPONENT ,focoExp);
  //  glLightf (GL_LIGHT1, GL_SPOT_CUTOFF,   focoCut);
	glLightfv(GL_LIGHT2, GL_DIFFUSE,       focoCorDif );   
	glLightfv(GL_LIGHT2, GL_SPECULAR,      focoCorEsp  );
	glDisable(GL_LIGHT0);
	if (ligaLuz){
		printf("wow\n");
			
		glEnable(GL_LIGHT2);
		 
		
	}
       
    else{
    		printf("wow1\n");
    			glDisable(GL_LIGHT2);
    }
        


    
}


void initMaterials(int material) {
	
	switch (material){
	case 0: //……………………………………………………………………………………………esmerald
		glMaterialfv(GL_FRONT,GL_AMBIENT,  esmeraldAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  esmeraldDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, esmeraldSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,esmeraldCoef);
		break;
	case 1: //……………………………………………………………………………………………jade
		glMaterialfv(GL_FRONT,GL_AMBIENT,  jadeAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  jadeDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, jadeSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,jadeCoef);
		break;
	case 2: //……………………………………………………………………………………………obsidian
		glMaterialfv(GL_FRONT,GL_AMBIENT,  obsidianAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  obsidianDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, obsidianSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,obsidianCoef);
		break;
	case 3: //……………………………………………………………………………………………pearl
		glMaterialfv(GL_FRONT,GL_AMBIENT,  pearlAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  pearlDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, pearlSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,pearlCoef);
		break;
	case 4: //……………………………………………………………………………………………ruby
		glMaterialfv(GL_FRONT,GL_AMBIENT,  rubyAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  rubyDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, rubySpec);
		glMaterialf (GL_FRONT,GL_SHININESS,rubyCoef);
		break;
	case 5: //……………………………………………………………………………………………turquoise
		glMaterialfv(GL_FRONT,GL_AMBIENT,  turquoiseAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  turquoiseDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, turquoiseSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,turquoiseCoef);
		break;
	case 6: //……………………………………………………………………………………………brass
		glMaterialfv(GL_FRONT,GL_AMBIENT,  brassAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  brassDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, brassSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,brassCoef);
		break;
	case 7: //……………………………………………………………………………………………bronze
		glMaterialfv(GL_FRONT,GL_AMBIENT,  bronzeAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  bronzeDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, bronzeSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,bronzeCoef);
		break;
	case 8: //……………………………………………………………………………………………chrome
		glMaterialfv(GL_FRONT,GL_AMBIENT,  chromeAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  chromeDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, chromeSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,chromeCoef);
		break;
	case 9: //……………………………………………………………………………………………copper
		glMaterialfv(GL_FRONT,GL_AMBIENT,  copperAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  copperDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, copperSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,copperCoef);
		break;
	case 10: //……………………………………………………………………………………………gold
		glMaterialfv(GL_FRONT,GL_AMBIENT,  goldAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  goldDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, goldSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,goldCoef);
		break;
	case 11: //……………………………………………………………………………………………silver
		glMaterialfv(GL_FRONT,GL_AMBIENT,  silverAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  silverDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, silverSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,silverCoef);
		break;
	case 12: //……………………………………………………………………………………………blackPlastic
		glMaterialfv(GL_FRONT,GL_AMBIENT,  blackPlasticAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  blackPlasticDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, blackPlasticSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,blackPlasticCoef);
		break;
	case 13: //……………………………………………………………………………………………cyankPlastic
		glMaterialfv(GL_FRONT,GL_AMBIENT,  cyanPlasticAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  cyanPlasticDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, cyanPlasticSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,cyanPlasticCoef);
		break;
	case 14: //……………………………………………………………………………………………greenPlastic
		glMaterialfv(GL_FRONT,GL_AMBIENT,  greenPlasticAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  greenPlasticDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, greenPlasticSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,greenPlasticCoef);
		break;
	case 15: //……………………………………………………………………………………………redPlastic
		glMaterialfv(GL_FRONT,GL_AMBIENT,  redPlasticAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  redPlasticDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, redPlasticSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,redPlasticCoef);
		break;
	case 16: //……………………………………………………………………………………………yellowPlastic
		glMaterialfv(GL_FRONT,GL_AMBIENT,  whitePlasticAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  whitePlasticDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, whitePlasticSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,whitePlasticCoef);
		break;
	case 17: //……………………………………………………………………………………………yellowPlastic
		glMaterialfv(GL_FRONT,GL_AMBIENT,  yellowPlasticAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  yellowPlasticDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, yellowPlasticSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,yellowPlasticCoef);
		break;
	case 18: //……………………………………………………………………………………………blackRubber
		glMaterialfv(GL_FRONT,GL_AMBIENT,  blackRubberAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  blackRubberDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, blackRubberSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,blackRubberCoef);
		break;
	case 19: //……………………………………………………………………………………………cyanRubber
		glMaterialfv(GL_FRONT,GL_AMBIENT,  cyanRubberAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  cyanRubberDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, cyanRubberSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,cyanRubberCoef);
		break;
	case 20: //……………………………………………………………………………………………greenRubber
		glMaterialfv(GL_FRONT,GL_AMBIENT,  greenRubberAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  greenRubberDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, greenRubberSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,greenRubberCoef);
		break;
	case 21: //……………………………………………………………………………………………redRubber
		glMaterialfv(GL_FRONT,GL_AMBIENT,  redRubberAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  redRubberDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, redRubberSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,redRubberCoef);
		break;
	case 22: //……………………………………………………………………………………………redRubber
		glMaterialfv(GL_FRONT,GL_AMBIENT,  whiteRubberAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  whiteRubberDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, whiteRubberSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,whiteRubberCoef);
		break;
	case 23: //……………………………………………………………………………………………redRubber
		glMaterialfv(GL_FRONT,GL_AMBIENT,  yellowRubberAmb  );
		glMaterialfv(GL_FRONT,GL_DIFFUSE,  yellowRubberDif );
		glMaterialfv(GL_FRONT,GL_SPECULAR, yellowRubberSpec);
		glMaterialf (GL_FRONT,GL_SHININESS,yellowRubberCoef);
		break;
	}		
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
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[1]);
    initMaterials(16);
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
void drawCubo2(GLdouble x ,GLdouble y,GLdouble z,int i){
    
    //    glColor4f(YELLOW);glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture[0]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    if(rodar[i]==1){
        
        glRotatef (       10, -1, 0, 0);
        //rodar[i]=0; // Com esta linha comentada, ele continua rodado
    }
    glTranslatef(x,y,z);
    glScalef(comprimentoEscada, alturaEscada, larguraEscada);
    glBegin(GL_QUADS);
    glNormal3i(0,
 	 0,
 	 1);

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

void drawCubo(GLdouble x ,GLdouble y,GLdouble z,int i){
    glColor4f(BLACK);
    glBindTexture(GL_TEXTURE_2D,texture[2]);
    glColor4f(BLACK);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    if(rodar[i]==1){
        glRotatef (       10, -1, 0, 0);
        //rodar[i]=0; // Com esta linha comentada, ele continua rodado
    }
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
    auxx=0;
    auxy=0;
    auxz=0;
    for(i=0;i<10;i++){
        glColor4f(cores[i],cores[i+1],cores[i+2],0);
        
        
        drawCubo2(auxx,auxy,auxz,i);//Desenha normais
        if(pretas[i]==1){
            // Desenha pretas
            drawCubo(auxx+comprimentoEscada-comprimentoTecla,auxy+alturaEscada+alturaTecla,auxz+(larguraEscada-larguraTecla),i);
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
    
    
    

    
    
    
}

void initTexturas()
{
    //----------------------------------------- Chao
    
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    imag.LoadBmpFile("marmore.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
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
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
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
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
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
    
    // Função para tratar da rotação das teclas
    printf("hhhhaaaa %d\n",ligaLuz);
    worker();
    
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
    initLights();
    //gluLookAt(0, 0, -50, 0,0,50, 0, 1, 0);
    //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖObjectos/modelos
    drawEixos();
    drawScene();
    
    
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Actualizacao
    glutSwapBuffers();
}


//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y){
    float normaVetor;
    
    switch (key) {
        case '1':
            printf("Carreguei no 1\n");
            is_1_pressed=1;
            glutPostRedisplay();
            break;
        case '2':
            printf("Carreguei no 2\n");
            is_2_pressed=1;
            glutPostRedisplay();
            break;
            
        case '3':
            printf("Carreguei no 3\n");
            is_3_pressed=1;
            glutPostRedisplay();
            break;
        case '4':
            printf("Carreguei no 4\n");
            is_4_pressed=1;
            glutPostRedisplay();
            break;
        case '5':
            printf("Carreguei no 5\n");
            is_5_pressed=1;
            glutPostRedisplay();
            break;
        case '6':
            printf("Carreguei no 6\n");
            is_6_pressed=1;
            glutPostRedisplay();
            break;
        case '7':
            printf("Carreguei no 7\n");
            is_7_pressed=1;
            glutPostRedisplay();
            break;
        case '8':
            printf("Carreguei no 8\n");
            is_8_pressed=1;
            glutPostRedisplay();
            break;
        case '9':
            printf("Carreguei no 9\n");
            is_9_pressed=1;
            glutPostRedisplay();
            break;
        case '0':
            printf("Carreguei no 0\n");
            is_0_pressed=1;
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
        case 'l':
        case 'L':
            printf("Carreguei no L\n");
            //ligaLuz=!ligaLuz;
            if(ligaLuz==0){
            	ligaLuz=1;
            }
            else{
            	ligaLuz=0;
            }
            glutPostRedisplay();
            /*glutPostRedisplay();
            glutPostRedisplay();*/
            break;
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
    if(key == GLUT_KEY_LEFT)
        aVisao = (aVisao - 0.3) ;
    if(key == GLUT_KEY_RIGHT)
        aVisao = (aVisao + 0.3) ;
    
    
    
    tx=rVisao*cos(aVisao)+obsP[0];
    tz=rVisao*sin(aVisao)+obsP[2];
    
    glutPostRedisplay();
    
}
void keyboard2(unsigned char key, int x, int y)
{
    switch( key ) {
        case '1':
            is_1_pressed = 0;
            printf("Soltei o 1\n");
            glutPostRedisplay();
            break;
        case '2':
            is_2_pressed = 0;
            printf("Soltei o 1\n");
            glutPostRedisplay();
            break;
        case '3':
            is_3_pressed = 0;
            printf("Soltei o 1\n");
            glutPostRedisplay();
            break;
        case '4':
            is_4_pressed = 0;
            printf("Soltei o 1\n");
            glutPostRedisplay();
            break;
        case '5':
            is_5_pressed = 0;
            printf("Soltei o 1\n");
            glutPostRedisplay();
            break;
        case '6':
            is_6_pressed = 0;
            printf("Soltei o 1\n");
            glutPostRedisplay();
            break;
        case '7':
            is_7_pressed = 0;
            printf("Soltei o 1\n");
            glutPostRedisplay();
            break;
        case '8':
            is_8_pressed = 0;
            printf("Soltei o 1\n");
            glutPostRedisplay();
            break;
        case '9':
            is_9_pressed = 0;
            printf("Soltei o 1\n");
            glutPostRedisplay();
            break;
        case '0':
            is_0_pressed = 0;
            printf("Soltei o 1\n");
            glutPostRedisplay();
            break;
    }
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
    glutKeyboardUpFunc(keyboard2);
    glutMainLoop();
    
    return 0;
}

void worker(){
    if(is_1_pressed==1)
        rodar[0]=1;
    if(is_1_pressed==0)
        rodar[0]=0;
    if(is_2_pressed==1)
        rodar[1]=1;
    if(is_2_pressed==0)
        rodar[1]=0;
    if(is_3_pressed==1)
        rodar[2]=1;
    if(is_3_pressed==0)
        rodar[2]=0;
    if(is_4_pressed==1)
        rodar[3]=1;
    if(is_4_pressed==0)
        rodar[3]=0;
    if(is_5_pressed==1)
        rodar[4]=1;
    if(is_5_pressed==0)
        rodar[4]=0;
    if(is_6_pressed==1)
        rodar[5]=1;
    if(is_6_pressed==0)
        rodar[5]=0;
    if(is_7_pressed==1)
        rodar[6]=1;
    if(is_7_pressed==0)
        rodar[6]=0;
    if(is_8_pressed==1)
        rodar[7]=1;
    if(is_8_pressed==0)
        rodar[7]=0;
    if(is_9_pressed==1)
        rodar[8]=1;
    if(is_9_pressed==0)
        rodar[8]=0;
    if(is_0_pressed==1)
        rodar[9]=1;
    if(is_0_pressed==0)
        rodar[9]=0;
    
    
    
}

