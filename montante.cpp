#include <iostream>
using namespace std; 








class Montante{
	private: 
		double matrizAumentada[11][11];//11 es el número máximo de ecuaciones aceptadas y 10 es el número máximo de variables aceptadas. 
		int filas; 
		int columnas;
		double soluciones[11]; 
		
		string tag = "DEBUG::"; //tag de los mensajes
		bool debug; //si este boolean es verdadero, se desplieagan mensajes con el procedimiento
		bool sinSoluciones; //si al final de montante, quedan ecuaciones con soluciones distintas
		bool solucionesInfinitas; //si al final de montante, quedan ecuaciones que den la misma solución 
		

		double pivAnterior; 
		double pivActual; //el valor en la posición kk de la matriz
		int k; //el índice que se utilizará para moverse por la diagonal principal
	
	public:
		Montante(double m[11][11], int f, int c);
		Montante(double m[11][11], int f, int c, true);//se inicializa en true el valor de debug para mostrar el proceso
		
		void MetodoPrincipal();//ciclo principal de montante
		
		void conversionACeros();//convierte a 0s todo antes del índice en donde esté menos la diagonal principal
		void operacionesEnPrimerCuadrante();//realiza las operaciones del primer cuadrante
		void operacionesEnSegundoCuadrante();//realiza las operaciones del cuarto cuadrante
		
		void calcularSolucion(); //en el caso de que se esté usando un sistema de ecuaciones lineales con montante
		void calcularInversa(); //en el caso de que se haya usado montante para calcular la inversa de una matriz
};



void imprimirMatriz(double m[11][11], int filas, int columnas){
	for(int f = 0; f<filas; f++){
		for(int c = 0; c<columnas;  c++){
			cout<<m[f][c]<<" ";
		}
		cout<<endl; 
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
		double soluciones[variables]; 
		
		//llenar la matriz extendida fila por fila
		for(int f = 0; f<numEcuaciones; f++){
			
			for(int c = 0; c<variables+1;  c++){
				cin>>matrizExtendida[f][c];
			}
			
		}
		
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
