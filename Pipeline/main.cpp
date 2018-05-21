#include <math.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include "objLoader.h"
#include "graphicpipeline.h"
#include "definitions.h"
#include "mygl.h"
#include "main.h"

using namespace glm;
using namespace std;

// Ponteiro para o objeto que carregará o modelo 3D (formato OBJ).
objLoader *objData;

//unsigned int ViewPortWidth  = 512;
//unsigned int ViewPortHeight = 512;

// A distância até o near plane:
float distanceNearPlane = 1;
// Serve para apagar a tela pois glCLear, por algum motivo, não estava apagando a tela
int eraser = 0;
// Atualizador para ocorrer a translação:
float moveMonkey = 0.0;

vec3 pointPosition = vec3( 2, 2, 2);
vec3 pointLookAt   = vec3( 0, 0, 0);
vec3 vectorUP 	   = vec3( 0, 1, 0);

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{	
	// Se eraser for positivo rasteriza a cena, senão apaga a tela
	if((eraser % 2) == 0){
		// Formação e condesação das matrizes com objeto sem rotação e na origem para poder printar os eixos do sistema
		// de coordenada 
		mUnion (pointLookAt, vectorUP, pointPosition, distanceNearPlane, 0.0, 0.0, 0.0 , 0, IMAGE_WIDTH, IMAGE_HEIGHT);


		// ###################################################################### //
		// #######################// EXIBINDO OS EIXOS \\######################## //

		TypeColor colorAxisX;
	    colorAxisX.R = 255;
	    colorAxisX.G = 0;
	    colorAxisX.B = 0;
	    colorAxisX.A = 255;

	    TypeColor colorAxisY;
	    colorAxisY.R = 0;
	    colorAxisY.G = 255;
	    colorAxisY.B = 0;
	    colorAxisY.A = 255;

	    TypeColor colorAxisZ;
	    colorAxisZ.R = 0;
	    colorAxisZ.G = 0;
	    colorAxisZ.B = 255;
	    colorAxisZ.A = 255;

	    // Vértice pertencente aos eixos X, Y e Z:
	   	vec3 originPoint = vec3(0, 0, 0);
	   	vec3 axisXPoint  = vec3(1.5, 0, 0);
	   	vec3 axisYPoint  = vec3(0, 1.5, 0);
	   	vec3 axisZPoint  = vec3(0, 0, 1.5);

	    // Pontos após sua passagem pelo pipeline gráfico:
	    vec4 originPostPipeline;
	    vec4 axisXPostPipeline;
	    vec4 axisYPostPipeline;
	    vec4 axisZPostPipeline;

	    // Passando os vértices para o pipeline:
	    originPostPipeline = pipelineAplication(originPostPipeline, originPoint, distanceNearPlane);
	    axisXPostPipeline  = pipelineAplication(axisXPostPipeline , axisXPoint , distanceNearPlane);
	    axisYPostPipeline  = pipelineAplication(axisYPostPipeline , axisYPoint , distanceNearPlane);
	    axisZPostPipeline  = pipelineAplication(axisZPostPipeline , axisZPoint , distanceNearPlane);

	    TypePixel origin, axisX, axisY, axisZ;

	    origin.pX 	 = (int) originPostPipeline.x;
	    origin.pY 	 = (int) originPostPipeline.y;
	    origin.color = colorAxisX;

	    axisX.pX 	= (int) axisXPostPipeline.x;
	    axisX.pY 	= (int) axisXPostPipeline.y;
	    axisX.color = colorAxisX;

	    axisY.pX 	= (int) axisYPostPipeline.x;
	    axisY.pY 	= (int) axisYPostPipeline.y;
	    axisY.color = colorAxisY;

	    axisZ.pX 	= (int) axisZPostPipeline.x;
	    axisZ.pY 	= (int) axisZPostPipeline.y;
	    axisZ.color = colorAxisZ;	

	    // Desenha os eixos de coordenadas:
	    DrawLine(axisX, origin);
	    DrawLine(axisY, origin);
	    DrawLine(axisZ, origin);	

		// ######################\\-------------------//######################### //
		// ###################################################################### //

	    // Agora a matriz union está configurada para exibir um objeto deslocado -2 em seu eixo z e rodando em torno de
	    // seu próprio eixo (relativo ao eixo y)
		mUnion (pointLookAt, vectorUP, pointPosition, distanceNearPlane, 0.0, 0.0, 0.0, 1, IMAGE_WIDTH, IMAGE_HEIGHT);

		// Vértice pertencente aos triangulos do arquivo .obj:
	    vec3 vertexObj1;
	    vec3 vertexObj2;
	    vec3 vertexObj3;
	    // Vértice após sua passagem pelo pipeline gráfico:
	    vec4 vertexPostPipeline1;
	    vec4 vertexPostPipeline2;
	    vec4 vertexPostPipeline3;

	    //| std::cout << "Iniciando o FOR \n";
		//| std::cout << "Entrou no GLLines \n";
		for(int i=0; i < objData->faceCount; i++){
		    //| std::cout << "\n\n\n&&&&&&&&&&&&&&&&&&&&&&&&&&&" << (i+1) << "ª Iteração do For &&&&&&&&&&&&&&&&&&&&&&&&& \n";
		    //| std::cout << "Pegando o objeto \n";
		    obj_face *o = objData->faceList[i];

		    // Coordenadas de um vértice entregues pelo código de importação do .obj fornecido
		    // pelo professor
		    //| std::cout << "Chegou até os vértices \n";
		    
		    vertexObj1.x = objData->vertexList[o->vertex_index[0]]->e[0]; // Coordenada X
		    vertexObj1.y = objData->vertexList[o->vertex_index[0]]->e[1]; // Coordenada Y
		    vertexObj1.z = objData->vertexList[o->vertex_index[0]]->e[2]; // Coordenada Z
		   
		    vertexObj2.x = objData->vertexList[o->vertex_index[1]]->e[0]; // Coordenada X
		    vertexObj2.y = objData->vertexList[o->vertex_index[1]]->e[1]; // Coordenada Y
		    vertexObj2.z = objData->vertexList[o->vertex_index[1]]->e[2]; // Coordenada Z
		    
		    vertexObj3.x = objData->vertexList[o->vertex_index[2]]->e[0]; // Coordenada X
		    vertexObj3.y = objData->vertexList[o->vertex_index[2]]->e[1]; // Coordenada Y
		    vertexObj3.z = objData->vertexList[o->vertex_index[2]]->e[2]; // Coordenada Z

		    // Passando os vértices para o pipeline:
		    //| std::cout << "Chegou até o pipeline \n";
		    vertexPostPipeline1 = pipelineAplication(vertexPostPipeline1, vertexObj1, distanceNearPlane);
		    vertexPostPipeline2 = pipelineAplication(vertexPostPipeline2, vertexObj2, distanceNearPlane);
		    vertexPostPipeline3 = pipelineAplication(vertexPostPipeline3, vertexObj3, distanceNearPlane);

		    //|cout << "vertexPostPipeline1: x = " << vertexPostPipeline1.x << "; y = " << vertexPostPipeline1.y << endl;
		    //|cout << "vertexPostPipeline2: x = " << vertexPostPipeline2.x << "; y = " << vertexPostPipeline2.y << endl;
		    //|cout << "vertexPostPipeline3: x = " << vertexPostPipeline3.x << "; y = " << vertexPostPipeline3.y << endl;

		    // Definindo a coloração:
		    //| std::cout << "Chegou até as cores \n";
		    TypeColor c1;
		    c1.R = 255;
		    c1.G = 255;
		    c1.B = 255;
		    c1.A = 255;

		    TypeColor c2;
		    c2.R = 255;
		    c2.G = 255;
		    c2.B = 255;
		    c2.A = 255;

		    TypeColor c3;
		    c3.R = 255;
		    c3.G = 255;
		    c3.B = 255;
		    c3.A = 255;

		    TypePixel p1, p2, p3;

		    //| std::cout << "Instanciou os pontos \n";
		    p1.pX = (int) vertexPostPipeline1.x;
		    p1.pY = (int) vertexPostPipeline1.y;
		    p1.color = c1;		

		    p2.pX = (int) vertexPostPipeline2.x;
		    p2.pY = (int) vertexPostPipeline2.y;
		    p2.color = c2;
			
		    p3.pX = (int) vertexPostPipeline3.x;
		    p3.pY = (int) vertexPostPipeline3.y;
		    p3.color = c3;

		    //| std::cout << "Desenhou os pontos \n";
		    DrawTriangle(p1, p2, p3);
		    //| std::cout << "Terminou de desenhar \n";

		}

	}else{
		// Faz dois triângulos pretos prenchidos para formar um quadrado e
		// sobrescreve a rasterização com ele para apagar
		TypeColor black;
	    black.R = 0;
	    black.G = 0;
	    black.B = 0;
	    black.A = 255;

	    TypePixel p1, p2, p3;

	    //| std::cout << "Instanciou os pontos \n";
	    p1.pX = 0;
	    p1.pY = 0;
	    p1.color = black;		

	    p2.pX = 0;
	    p2.pY = IMAGE_HEIGHT-1;
	    p2.color = black;
		
	    p3.pX = IMAGE_WIDTH-1;
	    p3.pY = 0;
	    p3.color = black;

	    DrawTriangleColor(p1, p2, p3);

	    p1.pX = IMAGE_WIDTH-1;
	    p1.pY = IMAGE_HEIGHT-1;
	    p1.color = black;		

	    p2.pX = 0;
	    p2.pY = IMAGE_HEIGHT-1;
	    p2.color = black;
		
	    p3.pX = IMAGE_WIDTH-1;
	    p3.pY = 0;
	    p3.color = black;

	    DrawTriangleColor(p1, p2, p3);
	}

	eraser++;
	moveMonkey += 0.1;
}

//-----------------------------------------------------------------------------
// Funcao que imprime as coordenadas de um vertice. 
// Pode ser utilizada para fazer debug de código.
void printVector(obj_vector *v)
{
	printf("%.2f,", v->e[0] );
	printf("%.2f,", v->e[1] );
	printf("%.2f  ", v->e[2] );
}

//-----------------------------------------------------------------------------
// Esta funcao apenas imprime informacoes referentes ao modelo que foi carregado, 
// tais como numero de vertices, normais, fontes de luz, etc.
void PrintModelInfo(objLoader* ptr)
{
	printf("Number of vertices: %i\n", ptr->vertexCount);
	printf("Number of vertex normals: %i\n", ptr->normalCount);
	printf("Number of texture coordinates: %i\n", ptr->textureCount);
	printf("\n");
	
	printf("Number of faces: %i\n", ptr->faceCount);
	for(int i=0; i<ptr->faceCount; i++)
	{
		obj_face *o = ptr->faceList[i];
		printf(" face ");
		for(int j=0; j<3; j++)
		{
			printVector(ptr->vertexList[ o->vertex_index[j] ]);
		}
		printf("\n");
	}

	printf("\n");
	
	printf("Number of spheres: %i\n", ptr->sphereCount);
	for(int i=0; i<ptr->sphereCount; i++)
	{
		obj_sphere *o = ptr->sphereList[i];
		printf(" sphere ");
		printVector(ptr->vertexList[ o->pos_index ]);
		printVector(ptr->normalList[ o->up_normal_index ]);
		printVector(ptr->normalList[ o->equator_normal_index ]);
		printf("\n");
	}

	printf("\n");
	
	printf("Number of planes: %i\n", ptr->planeCount);
	for(int i=0; i<ptr->planeCount; i++)
	{
		obj_plane *o = ptr->planeList[i];
		printf(" plane ");
		printVector(ptr->vertexList[ o->pos_index ]);
		printVector(ptr->normalList[ o->normal_index]);
		printVector(ptr->normalList[ o->rotation_normal_index]);
		printf("\n");
	}

	printf("\n");
	
	printf("Number of point lights: %i\n", ptr->lightPointCount);
	for(int i=0; i<ptr->lightPointCount; i++)
	{
		obj_light_point *o = ptr->lightPointList[i];
		printf(" plight ");
		printVector(ptr->vertexList[ o->pos_index ]);
		printf("\n");
	}

	printf("\n");
	
	printf("Number of disc lights: %i\n", ptr->lightDiscCount);
	for(int i=0; i<ptr->lightDiscCount; i++)
	{
		obj_light_disc *o = ptr->lightDiscList[i];
		printf(" dlight ");
		printVector(ptr->vertexList[ o->pos_index ]);
		printVector(ptr->normalList[ o->normal_index ]);
		printf("\n");
	}

	printf("\n");
	
	printf("Number of quad lights: %i\n", ptr->lightQuadCount);
	for(int i=0; i<ptr->lightQuadCount; i++)
	{
		obj_light_quad *o = ptr->lightQuadList[i];
		printf(" qlight ");
		printVector(ptr->vertexList[ o->vertex_index[0] ]);
		printVector(ptr->vertexList[ o->vertex_index[1] ]);
		printVector(ptr->vertexList[ o->vertex_index[2] ]);
		printVector(ptr->vertexList[ o->vertex_index[3] ]);
		printf("\n");
	}

	printf("\n");
	
	if(ptr->camera != NULL)
	{
		printf("Found a camera\n");
		printf(" position: ");
		printVector(ptr->vertexList[ ptr->camera->camera_pos_index ]);
		printf("\n looking at: ");
		printVector(ptr->vertexList[ ptr->camera->camera_look_point_index ]);
		printf("\n up normal: ");
		printVector(ptr->normalList[ ptr->camera->camera_up_norm_index ]);
		printf("\n");
	}

	printf("\n");

	printf("Number of materials: %i\n", ptr->materialCount);
	for(int i=0; i<ptr->materialCount; i++)
	{
		obj_material *mtl = ptr->materialList[i];
		printf(" name: %s", mtl->name);
		printf(" amb: %.2f ", mtl->amb[0]);
		printf("%.2f ", mtl->amb[1]);
		printf("%.2f\n", mtl->amb[2]);

		printf(" diff: %.2f ", mtl->diff[0]);
		printf("%.2f ", mtl->diff[1]);
		printf("%.2f\n", mtl->diff[2]);

		printf(" spec: %.2f ", mtl->spec[0]);
		printf("%.2f ", mtl->spec[1]);
		printf("%.2f\n", mtl->spec[2]);
		
		printf(" reflect: %.2f\n", mtl->reflect);
		printf(" trans: %.2f\n", mtl->trans);
		printf(" glossy: %i\n", mtl->glossy);
		printf(" shiny: %i\n", mtl->shiny);
		printf(" refact: %.2f\n", mtl->refract_index);

		printf(" texture: %s\n", mtl->texture_filename);
		printf("\n");
	}

	printf("\n");
	
	//vertex, normal, and texture test
	if(ptr->textureCount > 2 && ptr->normalCount > 2 && ptr->faceCount > 2)
	{
		printf("Detailed face data:\n");

		for(int i=0; i<3; i++)
		{
			obj_face *o = ptr->faceList[i];
			printf(" face ");
			for(int j=0; j<3; j++)
			{
				printf("%i/", o->vertex_index[j] );
				printf("%i/", o->texture_index[j] );
				printf("%i ", o->normal_index[j] );
			}
			printf("\n");
		}
	}
}

//-----------------------------------------------------------------------------
// Libera a memoria do objeto responsavel por guardar dados do modelo.
void FreeMemFunc(void)
{
	std::clog << "Exiting...\n";

	if (!objData)
		delete objData;
}

//-----------------------------------------------------------------------------
// Programa principal
int main(int argc, char **argv)
{
	objData = new objLoader();			// cria o objeto que carrega o modelo
	objData->load("monkey_head2.obj");	// a carga do modelo é indicada atraves do nome do arquivo. 
										// Neste caso, deve ser sempre do tipo OBJ.

	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	DrawFunc = MyGlDraw;

	//glutDisplayFunc(display);
	// Habilite esta função se você deseja imprimir na tela dados do modelo
	// gerados durante a sua carga.
	//PrintModelInfo(objData);

	//atexit(FreeMemFunc);

	glutMainLoop();

	return 0;
}

