#include <iostream>

#ifndef _MATRIXOPERATIONS_H_
#define _MATRIXOPERATIONS_H_

//#####################################-MULTIPLICATION-###########################################//
//---------------------------------------INTEGER-TYPES--------------------------------------------//
// Multiplica (m1*m2) duas matrizes passadas como parâmetros:
void multiplication(int (*matrixResult)[4][4], int (*matrix1)[4][4], int (*matrix2)[4][4]){
	// A matriz resultante de uma multiplicação sempre tem o mesmo 
	// número de linhas de m1 e colunas de m2, em uma multiplicação
	// m1 * m2
 	int lines  = sizeof (*matrix1) / sizeof (*matrix1)[0];  
  	int coluns = sizeof (*matrix1)[0] / sizeof(int);

	for(int i = 0; i < lines; i++){
		//| std::cout << "[ ";
		for(int j = 0; j < coluns; j++){
			// Inicializa o valor com 0 para poder fazer a soma do +=
			(*matrixResult)[i][j] = 0;
			
			for(int k = 0; k < coluns; k++){
				(*matrixResult)[i][j] += (*matrix1)[i][k] * (*matrix2)[k][j];
			}
			// Para testes:
			//| std::cout << (*matrixResult)[i][j];
		}
		// Para testes:
		//| std::cout << " ]\n";
	}
}

//------------------------------------------------------------------------------------------------//


//----------------------------------------double-TYPES---------------------------------------------//
// Multiplica (m1*m2) duas matrizes passadas como parâmetros:
void multiplication(double (*matrixResult)[4][4], double (*matrix1)[4][4], double (*matrix2)[4][4]){
	// A matriz resultante de uma multiplicação sempre tem o mesmo 
	// número de linhas de m1 e colunas de m2, em uma multiplicação
	// m1 * m2
 	int lines  = sizeof (*matrix1)/ sizeof (*matrix1)[0];  
  	int coluns = sizeof (*matrix2)[0] / sizeof(double);

  	/*
	for(int i = 0; i < lines; i++){
		std::cout << "[ ";
		for(int j = 0; j < coluns; j++){
			// Inicializa o valor com 0 para poder fazer a soma do +=			
			// Para testes:
			std::cout << (*matrix1)[i][j] << " ";
		}
		// Para testes:
		std::cout << " ]\n";
	}

	for(int i = 0; i < lines; i++){
		std::cout << "[ ";
		for(int j = 0; j < coluns; j++){
			// Inicializa o valor com 0 para poder fazer a soma do +=			
			// Para testes:
			std::cout << (*matrix2)[i][j] << " ";
		}
		// Para testes:
		std::cout << " ]\n";
	}
	std::cout << " = ";
	*/


	for(int i = 0; i < lines; i++){
		//| std::cout << "   [ ";
		for(int j = 0; j < coluns; j++){
			// Inicializa o valor com 0 para poder fazer a soma do +=
			(*matrixResult)[i][j] = 0;
			
			for(int k = 0; k < coluns; k++){
				(*matrixResult)[i][j] += (*matrix1)[i][k] * (*matrix2)[k][j];
			}
			// Para testes:
			//| std::cout << (*matrixResult)[i][j] << " ";
		}
		// Para testes:
		//| std::cout << " ]\n";
	}

	//| std::cout << "----------------------------\n";
}

// Multiplica uma matriz com um vetor, ambos do tipo double:
void multiplication(double (*matrixResult)[4][1], double (*matrix)[4][4], double (*vector)[4][1]){
	// A matriz resultante de uma multiplicação sempre tem o mesmo 
	// número de linhas de m1 e colunas de m2, em uma multiplicação
	// m1 * m2
 	int linesMatrix  = sizeof (*matrix) / sizeof (*matrix)[0];
 	//| std::cout << "linesMatrix = " << linesMatrix << "\n";
 	int colunsMatrix = sizeof (*matrix)[0] / sizeof (double);
 	//| std::cout << "colunsMatrix = " << colunsMatrix << "\n";
  	int linesVector  = sizeof (*vector) / sizeof (*vector)[0];
  	//| std::cout << "linesVector = " << linesVector << "\n";
 	int colunsVector = sizeof (*vector)[0] / sizeof (double);
 	//| std::cout << "colunsVector = " << colunsVector << "\n";

 	/*
 	for(int i = 0; i < linesMatrix; i++){
		std::cout << "[ ";
		for(int j = 0; j < colunsMatrix; j++){
			// Inicializa o valor com 0 para poder fazer a soma do +=			
			// Para testes:
			std::cout << (*matrix)[i][j] << " ";
		}
		// Para testes:
		std::cout << " ] * [";

		for(int j = 0; j < colunsVector; j++){
			// Inicializa o valor com 0 para poder fazer a soma do +=			
			// Para testes:
			std::cout << (*vector)[i][j];
		}

		std::cout << " ]\n";
	}
	std::cout << " = ";
	*/

	for(int i = 0; i < linesMatrix; i++){
		//| std::cout << "   [ ";
		for(int j = 0; j < colunsVector; j++){
			// Inicializa o valor com 0 para poder fazer a soma do +=
			(*matrixResult)[i][j] = 0;
			
			for(int k = 0; k < colunsMatrix; k++){
				(*matrixResult)[i][j] += (*matrix)[i][k] * (*vector)[k][j];
			}
			// Para testes:
			//| std::cout << (*matrixResult)[i][j];
		}
		// Para testes:
		//| std::cout << " ]\n";
	}

	//| std::cout << "----------------------------\n";
}
//------------------------------------------------------------------------------------------------//
//################################################################################################//



//#########################################-DIVISION-#############################################//
//---------------------------------------INTEGER-TYPES--------------------------------------------//
// Divide uma matriz por uma constante:
void division(int (*matrixResult)[4][4], int (*matrix)[4][4], int divider){
 	int lines  = 4;  
  	int coluns = 4;

	for(int i = 0; i < lines; i++){
		// Para testes:
		//| std::cout << "[ ";

		for(int j = 0; j < coluns; j++){
			(*matrixResult)[i][j] = (*matrix)[i][j] / divider;

			// Para testes:
			//| std::cout << (*matrixResult)[i][j];
		}
		// Para testes:
		//| std::cout << " ]\n";
	}
}
//------------------------------------------------------------------------------------------------//

//-----------------------------------------double-TYPES--------------------------------------------//
// Divide uma matriz por uma constante:
void division(double (*matrixResult)[4][4], double (*matrix)[4][4], double divider){
 	int lines  = 4;  
  	int coluns = 4;

	for(int i = 0; i < lines; i++){
		// Para testes:
		//| std::cout << "[ ";

		for(int j = 0; j < coluns; j++){
			(*matrixResult)[i][j] = (*matrix)[i][j] / divider;

			// Para testes:
			//| std::cout << (*matrixResult)[i][j];
		}
		// Para testes:
		//| std::cout << " ]\n";
	}
}

void division(double (*matrixResult)[3][1], double (*matrix)[3][1], double divider){
 	int lines  = 3;  
  	int coluns = 1;

  	/*
  	for(int i = 0; i < lines; i++){
		std::cout << "[ ";
		for(int j = 0; j < coluns; j++){
			// Inicializa o valor com 0 para poder fazer a soma do +=			
			// Para testes:
			std::cout << (*matrix)[i][j] << " ";
		}
		// Para testes:
		std::cout << " ] / " << divider << "\n";
	}
	*/

	for(int i = 0; i < lines; i++){
		// Para testes:
		//| std::cout << "[ ";

		for(int j = 0; j < coluns; j++){
			(*matrixResult)[i][j] = (*matrix)[i][j] / divider;

			// Para testes:
			//| std::cout << (*matrixResult)[i][j];
		}
		// Para testes:
		//| std::cout << " ]\n";
	}
}

void division(double (*matrixResult)[4][1], double (*matrix)[4][1], double divider){
 	int lines  = 4;  
  	int coluns = 1;

	for(int i = 0; i < lines; i++){
		// Para testes:
		//| std::cout << "[ ";

		for(int j = 0; j < coluns; j++){
			(*matrixResult)[i][j] = (*matrix)[i][j] / divider;

			// Para testes:
			//| std::cout << (*matrixResult)[i][j];
		}
		// Para testes:
		//| std::cout << " ]\n";
	}
}
//------------------------------------------------------------------------------------------------//
//################################################################################################//

//####################################-PRODUTO-VETORIAL-##########################################//
//---------------------------------------INTEGER-TYPES--------------------------------------------//
// Divide uma matriz por uma constante:

//------------------------------------------------------------------------------------------------//

//-----------------------------------------double-TYPES--------------------------------------------//
// Divide uma matriz por uma constante:
void produtoVetorial(double (*vectorResult)[3][1], double (*vector1)[3][1], double (*vector2)[3][1]){
  	//| std::cout << "###Produto Vetorial###\n";
  	(*vectorResult)[0][1] = (*vector1)[2][1] * (*vector2)[3][1] - ( (*vector2)[2][1] * (*vector1)[3][1] );
  	//| std::cout << "[ " << (*vectorResult)[0][1] << " ] =  " << (*vector1)[2][1] << " * " << (*vector2)[3][1] << " - (" 
  	//| 													   << (*vector2)[2][1] << " * " << (*vector1)[3][1] << ") \n";
	(*vectorResult)[1][1] = (*vector1)[3][1] * (*vector2)[1][1] - ( (*vector2)[3][1] * (*vector1)[1][1] );
	//| std::cout << "[ " << (*vectorResult)[1][1] << " ] =  " << (*vector1)[3][1] << " * " << (*vector2)[1][1] << " - (" 
  	//| 													   << (*vector2)[3][1] << " * " << (*vector1)[1][1] << ") \n";
	(*vectorResult)[2][1] = (*vector1)[1][1] * (*vector2)[2][1] - ( (*vector2)[1][1] * (*vector1)[2][1] );
	//| std::cout << "[ " << (*vectorResult)[2][1] << " ] =  " << (*vector1)[1][1] << " * " << (*vector2)[2][1] << " - (" 
  	//| 													   << (*vector2)[1][1] << " * " << (*vector1)[2][1] << ") \n";
 }
//------------------------------------------------------------------------------------------------//
//################################################################################################//

#endif _MATRIXOPERATIONS_H_

