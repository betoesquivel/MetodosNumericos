#include <iostream>

using namespace std;

const int tamMat = 11;
string tag = "DEBUG::";
bool debug = true; 

double matriz[tamMat][tamMat];
double soluciones[tamMat];
int columnas;
int filas;

bool sinSoluciones = false;
bool solucionesInfinitas = false;
int k = 0;
double pivAnterior = 1;
double pivActual; 

		void imprimirMatriz(){
			for(int f = 0; f<filas; f++){
				for(int c = 0; c<columnas;  c++){
					cout<<matriz[f][c]<<" ";
				}
				cout<<endl; 
			}
			cout<<endl; 
		}

		
		//convierte a 0s todo antes del índice en donde esté menos la diagonal principal
		void conversionACeros(){
			for(int f = 0; f<filas; f++){
				for(int c = 0; c<=k; c++){
					if(f!=c)
						matriz[f][c] = 0;
					else
						matriz[f][c] = pivActual;
				}
			}
			if(debug){
				cout<<tag<<"Conversión a Ceros"<<endl;
				imprimirMatriz();
			}
		}
		
		void operacionesEnPrimerCuadrante(){
			//uso la matriz, el índice en el que me encuentro k, y el pivote actual y anterior
			for(int f = 0; f<k; f++){
				for(int c = k+1; c<columnas; c++){
					matriz[f][c] = (-1)*( matriz[f][k]*matriz[k][c] - matriz[f][c]*pivActual ) / pivAnterior;
				}
			}
			if(debug){
				cout<<tag<<"Operaciones Primer Cuadrante"<<endl;
				imprimirMatriz();
			}
		}
		void operacionesEnSegundoCuadrante(){
			for(int f = k+1; f<filas; f++){
				for(int c = k+1; c<columnas; c++){
					matriz[f][c] = ( pivActual*matriz[f][c] - matriz[k][c]*matriz[f][k] ) / pivAnterior;
				}
			}	
			if(debug){
				cout<<tag<<"Operaciones Segundo Cuadrante"<<endl;
				imprimirMatriz();
			}			
		}
		
		void cambiarRenglones(int fila1, int fila2){
			double temp;
			for(int c = 0; c<columnas; c++){
				temp = matriz[fila2][c];
				matriz[fila2][c] = matriz[fila1][c];
				matriz[fila1][c] = temp;
			}
			if(debug){
				cout<<tag<<"Cambiar renglones"<<endl;
				imprimirMatriz();
			}			
		}
		 //en el caso de que se esté usando un sistema de ecuaciones lineales con montante
		void calcularSolucion(){
			double determinante = matriz[0][0];
			for(int f = 0; f<filas; f++){
				soluciones[f] = matriz[f][columnas-1]/determinante;
			}
		}
		
		void imprimirSoluciones(){
			for(int i = 0; i<filas; i++){
				cout<<"x"<<i+1<<" = "<<soluciones[i]<<endl; 
			}
		}
		//en el caso de que se haya usado montante para calcular la inversa de una matriz

		void calcularInversa(){
			//luego lo hago
		}	
		
    	void MetodoPrincipal(){
    
			while(!sinSoluciones && !solucionesInfinitas && k<filas){
				pivActual = matriz[k][k];
				
				operacionesEnPrimerCuadrante();
				operacionesEnSegundoCuadrante();
				conversionACeros();
				//esojo la siguiente fila y cambio la k; 
				pivAnterior = pivActual; 
				k++;
				int sigFila = k; 
				while(matriz[sigFila][k]==0 && sigFila<filas){
					sigFila++;
				}
				if(matriz[sigFila][k]==0){
					//sin solución o soluciones infinitas	
					
				}else{
					//cambio el renglón k, por el renglón sigFila en la matriz	
					cambiarRenglones(sigFila, k); 
				}
				
			}
		}

int main(){
	int casos, variables, numEcuaciones; 
	cin>>casos; 
	while(casos>0){
	
		cout<<"Variables: "<<endl; 
		cin>>variables;
		cout<<"Ecuaciones: "<<endl;
		cin>>numEcuaciones; 
		
		double temp; 
		//llenar la matriz extendida fila por fila
		for(int f = 0; f<numEcuaciones; f++){
			
			for(int c = 0; c<variables+1;  c++){
				cin>>temp;
				matriz[f][c] = temp;
			}
			
		}
		filas = numEcuaciones;
        columnas = variables+1;
        MetodoPrincipal(); 
		
		//Hago Montante Montante miMontante(matriz, numEcuaciones, variables+1, true);
		//Hago Montante miMontante.MetodoPrincipal();
		//Imprimir la respuesta. 
		if(sinSoluciones){
			cout<<"Sin solución";
		}else{
			if(solucionesInfinitas){
				cout<<"Soluciones infinitas";
			}else{
				calcularSolucion();
				imprimirSoluciones();
			}
		}
		cout<<endl; 
		casos--; 
		
	}
	
	
	return 0; 
}
