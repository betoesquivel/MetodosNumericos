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
		
		void cambiarRenglonesNegativosDeSigno(){
			//cambia de signo los renglones que sean completamente negativos
			//-1 -2 -2 => 1 2 2 
			//Esto facilita la comparación para ver si queda un número ilimitado de soluciones o cómo.
			
			for(int f = k; f<filas; f++){
				
				if(matriz[f][k+1]<=0){
					int c = k+1;
					while(c<columnas && matriz[f][c]<=0){
						c++; 
					}
					if(c==columnas && matriz[f][c]<=0){
						//multiplico todo el renglón por -1
						for(int i = k+1; i<columnas; i++){
							matriz[f][i] *= -1; 
						}
					}
				}//fin del if que checa si el primer valor de la columna después de k es menor a 0...
				
			}//fin del for que recorre la matriz cambiando el signo de los renglones que son todos negativos
				
		}
		
		void compararRenglones(){
			//compara los renglones restantes de la matriz para ver si no tiene solución o tiene soluciones infinitas
			//ya se debió haber ejecutado el método cambiarRenglonesNegativosDeSigno
			int f,c = k+1; 
			while(!sinSoluciones && c<columnas){
				f = k; 
				while(!sinSoluciones && f<(filas-1)){
					//compara columna por columna
					//si una columna no es igual, se sale...
					if(matriz[f][c]!=matriz[f+1][c]){
						sinSoluciones = true; 
						if(debug)
							cout<<matriz[f][c]<<" - es diferente de - "<<matriz[f+1][c]<<endl; 
					}
					f++;
				}
				c++;
			}
			if(!sinSoluciones)
				solucionesInfinitas = true; 
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
				if(matriz[sigFila][k]==0 && k<filas){
					//sin solución o soluciones infinitas	
					//En matriz[k][k] tengo un pivote igual a 0 y lo mismo hacia abajo
					//Por lo tanto tengo que comparar desde k+1 hasta columnas y desde k hasta filas
					//si son iguales todas, entonces tengo soluciones infinitas
					//si no, entonces no tiene solución
					
					//antes de comparar tengo que hacer positivas positivas todos los renglones que sean todos negativos
					cambiarRenglonesNegativosDeSigno();
					compararRenglones();
					//ya tengo el valor de los booleanos sin solucion y soluciones infinitas
				}else{
					//cambio el renglón k, por el renglón sigFila en la matriz	
					if(sigFila != k)
						cambiarRenglones(sigFila, k); 
				}
				
			}
		}
		
		void vaciarMatriz(){
			for(int f = 0; f<filas; f++){
				for(int c = 0; c<columnas;  c++){
					matriz[f][c] = 0; 
				}
				cout<<endl; 
			}
			cout<<endl; 
		}

int main(){
	int casos, variables, numEcuaciones; 
	cin>>casos; 
	while(casos>0){
	
		cout<<"Variables y ecuaciones (un número): "<<endl; 
		cin>>variables;
        numEcuaciones = variables; 
		
		double temp; 
		vaciarMatriz();
		k = 0; 
		pivAnterior = 1; 
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
			sinSoluciones = false; 
		}else{
			if(solucionesInfinitas){
				cout<<"Soluciones infinitas";
				solucionesInfinitas = false; 
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
