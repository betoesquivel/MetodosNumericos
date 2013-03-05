#include <iostream>
using namespace std; 
string tag = "DEBUG::";
const int size = 11; 
class Montante{
	private: 
		double matriz[size][size];//11 es el número máximo de ecuaciones aceptadas y 10 es el número máximo de variables aceptadas. 
		int filas; 
		int columnas;
		double soluciones[size]; 
		
		 //tag de los mensajes
		bool debug; //si este boolean es verdadero, se desplieagan mensajes con el procedimiento
		bool sinSoluciones; //si al final de montante, quedan ecuaciones con soluciones distintas
		bool solucionesInfinitas; //si al final de montante, quedan ecuaciones que den la misma solución 
		

		double pivAnterior; 
		double pivActual; //el valor en la posición kk de la matriz
		int k; //el índice que se utilizará para moverse por la diagonal principal
	
	public:
		Montante(double m[size][size], int f, int c);
		Montante(double m[size][size], int f, int c, bool);//se inicializa en bool el valor de debug para mostrar el proceso
		
		void MetodoPrincipal();//ciclo principal de montante
		
		void conversionACeros();//convierte a 0s todo antes del índice en donde esté menos la diagonal principal
		void operacionesEnPrimerCuadrante();//realiza las operaciones del primer cuadrante
		void operacionesEnSegundoCuadrante();//realiza las operaciones del cuarto cuadrante
		void cambiarRenglones(int fila1, int fila2);//cambia los renglones
		
		
		void calcularSolucion(); //en el caso de que se esté usando un sistema de ecuaciones lineales con montante
		void calcularInversa(); //en el caso de que se haya usado montante para calcular la inversa de una matriz
		
		bool getSinSoluciones();
		bool getSolucionesInfinitas();
		void imprimirSoluciones();
		
		void imprimirMatriz();
};

		Montante::Montante(double m[size][size], int f, int c){
			for(int fila = 0; fila<f; fila++){
				for(int columna = 0; columna<c; columna++)
					matriz[f][c] = m[f][c];
			}
			
			filas = f;
			columnas = c;
			k = 0; 
			pivAnterior = 1; 
			sinSoluciones = false; 
			solucionesInfinitas = false; 
		}
		Montante::Montante(double m[size][size], int f, int c, bool deb){//se inicializa en bool el valor de debug para mostrar el proceso
			filas = f;
			columnas = c;
			debug = true; 
			k = 0; 
			pivAnterior = 1; 
			sinSoluciones = false; 
			solucionesInfinitas = false; 
			
			for(int fila = 0; fila<f; fila++){
				for(int columna = 0; columna<c; columna++){
					matriz[f][c] = m[f][c];
					if(debug){
						cout<<tag<<"Copiando"<<endl; 
						cout<<m[f][c];
					}
				}
			}
			
			
		}
		
		bool Montante::getSinSoluciones(){
			return sinSoluciones;
		}
		bool Montante::getSolucionesInfinitas(){
			return solucionesInfinitas;
		}
		void Montante::imprimirSoluciones(){
			for(int i = 0; i<filas; i++){
				cout<<"Solucion "<<i+1<<": "<<soluciones[i]<<endl;	
			}	
		}
		//ciclo principal de montante
		void Montante::MetodoPrincipal(){
			while(!sinSoluciones && !solucionesInfinitas && k<filas){
				pivActual = matriz[k][k];
				conversionACeros();
				operacionesEnPrimerCuadrante();
				operacionesEnSegundoCuadrante();
				
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
		
		//convierte a 0s todo antes del índice en donde esté menos la diagonal principal
		void Montante::conversionACeros(){
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
		
		void Montante::operacionesEnPrimerCuadrante(){
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
		void Montante::operacionesEnSegundoCuadrante(){
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
		
		void Montante::cambiarRenglones(int fila1, int fila2){
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
		void Montante::calcularSolucion(){
			double determinante = matriz[0][0];
			for(int f = 0; f<filas; f++){
				soluciones[f] = matriz[f][columnas-1]/determinante;
			}
		}
		
		//en el caso de que se haya usado montante para calcular la inversa de una matriz

		void Montante::calcularInversa(){
			//luego lo hago
		}		
		void Montante::imprimirMatriz(){
			for(int f = 0; f<filas; f++){
				for(int c = 0; c<columnas;  c++){
					cout<<matriz[f][c]<<" ";
				}
				cout<<endl; 
			}
			cout<<endl; 
		}



int main(){
	double matrizExtendida[size][size];
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
				cout<<"Solo probando"<<temp<<endl; 
				matrizExtendida[f][c] = temp;
			}
			
		}
		
		Montante miMontante(matrizExtendida, numEcuaciones, variables+1, true);
		miMontante.MetodoPrincipal();
		//Imprimir la respuesta. 
		if(miMontante.getSinSoluciones()){
			cout<<"Sin solución";
		}else{
			if(miMontante.getSolucionesInfinitas()){
				cout<<"Soluciones infinitas";
			}else{
				miMontante.calcularSolucion();
				miMontante.imprimirSoluciones();
			}
		}
		cout<<endl; 
		casos--; 
		
	}
	
	
	return 0; 
}
