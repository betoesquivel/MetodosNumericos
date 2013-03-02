#include <iostream>
using namespace std; 


bool debug = true; 
bool sinSoluciones = false; 
bool solucionesInfinitas = false; 
string tag = "DEBUG::";

void imprimirMatriz(double m[11][11], int filas, int columnas){
	for(int f = 0; f<filas; f++){
		for(int c = 0; c<columnas;  c++){
			cout<<m[f][c]<<" ";
		}
		cout<<endl; 
	}
}


void montante(double matriz[11][11], int vars, int numE, double soluciones[11]){
	int k = 0; 
	double pAnterior = 1, pActual; 
	int k_temp = 0; 
	double filTemp; 
	while(k<vars && !sinSoluciones && !solucionesInfinitas){
		pActual = matriz[k][k];
		//sustituyo por 0s o por el valor de la matriz en kk
		for(int f = 0; f<=k; f++){
			for(int c = 0; c<=k; c++){
				if(f==c)	
					matriz[f][c] = matriz[k][k];
				else
					matriz[f][c] = 0;
			}
		}
		if(debug){
			cout<<tag<<"Poniendo 0s"<<endl;
			imprimirMatriz(matriz, numE, vars+1); 
		}
		//calculo los valores faltantes
		for(int f = 0; f<numE; f++){
			if(f!=k){//se brinca la fila k
				for(int c = k+1; c<vars+1;  c++){//empieza después de la columna k
					
					if(k<f){
						//estoy en el cuadrante 4
						matriz[f][c] = (pActual*matriz[f][c]-matriz[k][c]*matriz[f][k])/pAnterior;
					}else{
						//estoy en el cuadrante 1
						matriz[f][c] = (matriz[k][c]*matriz[f][k]-matriz[f][c]*pActual)*(-1)/pAnterior;
					}
					
				}
			}
		}
		if(debug){
			cout<<tag<<"Valores calculados"<<endl;
			imprimirMatriz(matriz, numE, vars+1); 
		}
		//aquí tengo que escoger los pivotes, y verificar que el pivote actual no sea 0; 
		pAnterior = pActual; 
		k++;
		/*
		k_temp = k; 
		//qué pasa si el último es 0
		while(matriz[k][k_temp]==0 && k<numE){
			k++;
		}
		if(matriz[k][k_temp]==0){
			//todas empiezan con 0 desde k, inclusive. 
			//no puedo seguir con el proceso
			//tengo que escoger si me va a dar a número infinito de soluciones o qué
			k = k_temp; 
			if(k == numE)
				sinSoluciones = true; 
			else{
				//comparar renglones, y si hay dos soluciones iguales, es número infinito
				solucionesInfinitas = true; 
			}
		}else{
			//cambio de filas
			//cambio la fila k_temp por la fila k
			for(int c = 0; c<vars+1; c++){
				filTemp = matriz[k_temp][c];
				matriz[k_temp][c] = matriz[k][c];
				matriz[k][c] = filTemp; 
			}
		}
		*/
		
	}//fin del while de montante
}

int main(){
	double matrizExtendida[11][11];
	int casos, variables, numEcuaciones; 
	cin>>casos; 
	while(casos>0){
	
		cout<<"Variables: "<<endl; 
		cin>>variables;
		cout<<"Ecuaciones: "<<endl;
		cin>>numEcuaciones; 
		double soluciones[variables]; 
		
		//llenar la matriz extendida fila por fila
		for(int f = 0; f<numEcuaciones; f++){
			
			for(int c = 0; c<variables+1;  c++){
				cin>>matrizExtendida[f][c];
			}
			
		}
		
		montante(matrizExtendida, variables, numEcuaciones, soluciones); 
		
		//Imprimir la respuesta. 
		if(sinSoluciones){
			cout<<"Sin solución";
			sinSoluciones = false;
		}else{
			if(solucionesInfinitas){
				cout<<"Soluciones infinitas";
				solucionesInfinitas = false; 
			}else{
				for(int i = 0; i<variables; i++){
					cout<<"x"<<i+1<<" = "<<soluciones[i]<<" ";	
				}
			}
		}
		cout<<endl; 
		casos--; 
		
	}
	
	
	return 0; 
}
