#include <math.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "matrixoperations.h"
#include "definitions.h"

using namespace glm;
using namespace std;

#ifndef _GRAPHIC_PIPELINE_H_
#define _GRAPHIC_PIPELINE_H_

float angle = 0.0;
float incrementTranslation = 0;

mat4 matrixIdentify = mat4(vec4(1, 0, 0, 0),
                 	       vec4(0, 1, 0, 0),
                           vec4(0, 0, 1, 0),
                           vec4(0, 0, 0, 1));

// OBS.: as matrizes iniciam igual a identidade, pois assim elas iniciam
// 		 em um estado neutro onde sua não configuração prévia afete o resultado
// 		 da matrixUnion ao ser executada em conjunto com as demais. Assim para
// 		 exibir o pipeline sem uma das matriz ou apenas outras basta comentar
// 		 a parte do código onde sua função de geração é chamada (como, mModel
// 		 , mView, etc)
mat4 matrixModel = matrixIdentify;

mat4 matrixView = matrixIdentify;

mat4 matrixProjection = matrixIdentify;

mat4 matrixViewPort = matrixIdentify;

mat4 matrixUnion = matrixIdentify;

// Gera matriz model através da posição do objeto no espaço fornecida como
// parâmetros de entrada. Além de saber se ela rodará ou não
void mModel(float x, float y, float z, int rotate){
	// OBS.: Nas matrizes do glm declaradas com vec4, cada vec 
	//		 representa uma coluna ao em vez de uma linha

	// Uma matriz de translação para posicionar o objeto no universo e
	// para que seja possível fazer a rotação ao longo desse eixo
	mat4 matrixTranslation = mat4(vec4(1, 0, 0, 0),
                             	  vec4(0, 1, 0, 0),
	                              vec4(0, 0, 1, 0),
	                              vec4(x, y, z, 1));

	mat4 matrixRotation = matrixIdentify;

	// Caso haja roatação:
	if(rotate == 1){
		// Uma matriz que serve para aplicar a rotação do objeto
		// em torno do eixo y
		matrixRotation =  mat4(vec4(cos(angle), 	0	, -sin(angle), 	  0	  ),
	                           vec4(	  0	  , 	1	, 		0	 , 	  0	  ),
	                           vec4(sin(angle), 	0	,  cos(angle), 	  0	  ),
	                           vec4(	  0	  , 	0	, 		0	 , 	  1	  ));

		angle = angle + 0.01;
	}

	// Cálculo da Matriz Model: para que a rotação seja em torno do
	// próprio eixo do objeto ela deve ocorrer primeiro, ou seja, ficar
	// mais à direita na multiplicação de matrizes.
	matrixModel = matrixTranslation * matrixRotation;

	//incrementTranslation += 0.01;

	return;
}

// Recebe para onde a câmera está olhando, sua posição e o up do universo
// através disso gera a Matriz View
void mView(vec3 lookAt, vec3 up, vec3 position){
	float vectorNorm;

	// EIXO Z:
	// Vetor d que aponta para onde a camera está olhando
	vec3 d = lookAt - position;
	// Cálcula o módulo do vetor:
	vectorNorm = sqrt(d.x*d.x + d.y*d.y + d.z*d.z);
	// Vetor referente ao eixo z da camera dado pelo cálculo
	// zc = - (d/|d|), o normalize aqui serve para deixar o vetor unitário
	vec3 zCamera;
	zCamera.x = -(d.x/vectorNorm);
	zCamera.y = -(d.y/vectorNorm);
	zCamera.z = -(d.z/vectorNorm);

	// EIXO X:
	// Vetor que resulta do produto vetorial, sendo cross o método que
	// traz esse retorno
	vec3 upXd = cross(up, zCamera);
	// Cálcula o módulo do vetor:
	vectorNorm = sqrt(upXd.x*upXd.x + upXd.y*upXd.y + upXd.z*upXd.z);
	// Vetor que geral o unitário baseado na fórmula xc = (ucXzc)/|ucXzc|
	vec3 xCamera;
	xCamera.x = (upXd.x/vectorNorm);
	xCamera.y = (upXd.y/vectorNorm);
	xCamera.z = (upXd.z/vectorNorm);

	// EIXO Y:
	// Retorna o produto vetorial do eixo z com o eixo x para encontrar
	// o eixo y (perpendicular a x e z)
	vec3 ezXex = cross(xCamera, zCamera);
	// Cálcula o módulo do vetor:
	//vectorNorm = sqrt(ezXex.x*ezXex.x + ezXex.y*ezXex.y + ezXex.z*ezXex.z);
	// O produto vetorial entre dois vetores unitários gera um vetor unitário
	/*
	vec3 yCamera;
	yCamera.x = (ezXex.x/vectorNorm);
	yCamera.y = (ezXex.y/vectorNorm);
	yCamera.z = (ezXex.z/vectorNorm);
	*/
	vec3 yCamera = ezXex;

	// CONSTRUINDO A MATRIX VIEW:
	// Matriz que passa os vértices para do espaço do universo para o de câmera
	mat4 matrixBt = mat4(vec4( xCamera.x, yCamera.x, zCamera.x, 0),
                 		 vec4( xCamera.y, yCamera.y, zCamera.y, 0),
                  		 vec4( xCamera.z, yCamera.z, zCamera.z, 0),
                  		 vec4(         0,         0,         0, 1));
	// Matriz que movimenta a câmera de sua posição original para a origem:
	mat4 matrixT = mat4(vec4(			1, 			 0, 		  0, 	0),
                  		vec4(		   	0, 			 1, 		  0, 	0),
                  		vec4(		   	0, 			 0, 		  1, 	0),
                  		vec4( -position.x, -position.y, -position.z, 	1));

	// Combina as matrizes Bt e T através de uma multiplicação:
	matrixView = matrixBt * matrixT; 

   	return;

}

// Recebe a distância d até o near plane e gera a Matriz Projection
void mProjection(float d){
	// Essa é uma matriz de translação que leva o centro focal para a origem
	mat4 matrixT = mat4(vec4(1, 0, 0, 0),
                      	vec4(0, 1, 0, 0),
                      	vec4(0, 0, 1, 0),
                        vec4(0, 0, d, 1));
	// Essa matriz efetivamente aplica a distorção perspectiva:
	mat4 matrixP = mat4(vec4(  1,   0,   0,   0),
                      	vec4(  0,   1,   0,   0),
                      	vec4(  0,   0,   1,-1/d),
                        vec4(  0,   0,   0,   1));
	// Para obter a matriz de projeção basta multiplicar uma matriz
    // pela outra e combiná-las
	matrixProjection = matrixP * matrixT;

	return;
}

// Recebe a largura e altura de tela e monta a matriz view port
void mViewPort(int w, int h){
	// É preciso transladar para mover os pontos para não ficarem na
    // na origem como centro
	mat4 matrixTranslation = mat4(vec4(		  1, 	  0, 	0, 	 0),
                   				  vec4(		  0, 	  1, 	0, 	 0),
                   				  vec4(		  0, 	  0, 	1, 	 0),
                   				  vec4( (w-1)/2, (h-1)/2, 	0, 	 1));
	// Também é necessário escalar a imagem para que se adeque ao tamanho
	// da tela (representado pelos parâmetros w(width) e h(height))
	mat4 matrixScale = mat4(vec4(w/2,   0,  0,  0),
           				  	vec4(  0, h/2,  0,  0),
           				  	vec4(  0,   0,  1,  0),
           				  	vec4(  0,   0,  0,  1));
	// É preciso fazer uma escala e inverter o Y da imagem pois usualmente o pixel
	// 0,0 da tela fica no canto superior esquerdo
	mat4 matrixInvertion = mat4(vec4(1, 0, 0, 0),
                   				vec4(0,-1, 0, 0),
                   				vec4(0, 0, 1, 0),
                   				vec4(0, 0, 0, 1));

	// Nesse caso a inversão apenas fazia a imagem ser exibida efetivamente invertida
	// Para obter a matriz view port basta multiplicar as matrizes obtidas
	matrixViewPort = matrixTranslation * matrixScale; //* matrixInvertion;

	return;
}

// Esse pipeline faz a passagem dos vertices dos triângulos para o espaço de tela
// sem aplicar uma multiplicação para condensar as matrizes de cada passagem de espaço
// em uma só
void mUnion(vec3 lookAt, vec3 up, vec3 position, float distanceNearPlane,
		    float objX, float objY, float objZ , int rotate, int width, int height){

	// Toda vez que a mUnion é chamada de novo, as matrizes tem que retornar a serem
	// iguais a identidade, senão haverá interferência com multiplas chamadas.
	matrixModel = matrixIdentify;
	matrixView = matrixIdentify;
	matrixProjection = matrixIdentify;
	matrixViewPort = matrixIdentify;
	matrixUnion = matrixIdentify;

	// Geração das matrizes de mudança de espaço;
	mModel(objX, objY, objZ, rotate);
	mView(lookAt, up, position);
	mProjection(distanceNearPlane);
	mViewPort(width, height);

	// Combinação de todas as matrizes do pipeline gráfico:
	// OBS.: É possível combinar todas as matrizes do pipeline em uma só para só em
	// 		 seguida aplicar a divisão para a passagem do espaço canônico, mesmo
	// 		 sem estar na ordem, o resultado continua válido e igual, mas com ganho
	//		 de desempenho
	matrixUnion = matrixViewPort * matrixProjection * matrixView * matrixModel;

	return;
}

vec4 pipelineAplication(vec4 outputVertex, vec3 inputVertex, float distanceNearPlane){
	// Atribuições:
	float homogeneosCoordinate = 1;
	//float wCoordinate = (1 - inputVertex.z) / distanceNearPlane;
	// Passagem dos vétores para o espaço homogêneo:
	vec4 pipelineVertex;

	//|cout << "inputVertex.x = " << inputVertex.x << "\n";
	//|cout << "inputVertex.y = " << inputVertex.y << "\n";
	//|cout << "inputVertex.z = " << inputVertex.z << "\n";

	pipelineVertex.x = inputVertex.x * homogeneosCoordinate;
	pipelineVertex.y = inputVertex.y * homogeneosCoordinate;
	pipelineVertex.z = inputVertex.z * homogeneosCoordinate;
	pipelineVertex.w = homogeneosCoordinate;

	//|cout << "pipelineVertex.x = " << pipelineVertex.x << "\n";
	//|cout << "pipelineVertex.y = " << pipelineVertex.y << "\n";
	//|cout << "pipelineVertex.z = " << pipelineVertex.z << "\n";
	//|cout << "pipelineVertex.w = " << pipelineVertex.w << "\n";


	// Aplica a transformação ao longo do pipeline:
	outputVertex = matrixUnion * pipelineVertex;

	// Divisão de w para normalizar todas as coordenadas:
	/*
	outputVertex.x = outputVertex.x / wCoordinate;
	outputVertex.y = outputVertex.y / wCoordinate;
	outputVertex.z = outputVertex.z / wCoordinate;
	outputVertex.w = outputVertex.w / wCoordinate;
	*/
	outputVertex.x = outputVertex.x / outputVertex.w;
	outputVertex.y = outputVertex.y / outputVertex.w;
	outputVertex.z = outputVertex.z / outputVertex.w;
	outputVertex.w = outputVertex.w / outputVertex.w;

	//|cout << "outputVertex.x = " << outputVertex.x << "\n";
	//|cout << "outputVertex.y = " << outputVertex.y << "\n";
	//|cout << "outputVertex.z = " << outputVertex.z << "\n";
	//|cout << "outputVertex.w = " << outputVertex.w << "\n";

	return outputVertex;
}

#endif // _GRAPHIC_PIPELINE_H_

