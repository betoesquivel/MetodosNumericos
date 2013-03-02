#include <iostream>
using namespace std; 


bool debug = false; 

class EcuacionLineal{
	private: 
		double coeficientes[11]; 
		int grado;
		int tam; 
	public:
		EcuacionLineal();
		EcuacionLineal(double c[], int g);
		
		void imprimir();
	
		EcuacionLineal operator * (double x);//multiplicar una ecuacion por una constante
		void operator + (EcuacionLineal e);//sumar dos ecuaciones lineales
};

	EcuacionLineal::EcuacionLineal(){
		grado = 0; 
		tam = 0;
	}
	EcuacionLineal::EcuacionLineal(double c[], int g){
		grado = g; 
		tam = g+1;
		for(int i = 0; i<tam; i++)
			coeficientes[i] = c[i]; 
	}

	void EcuacionLineal::imprimir(){
		
		for(int i = 0; i<tam; i++){
			if(coeficientes[i]>0){
				cout<<"+"<<coeficientes[i]<<"x"<<i+1;
			}else{
				if(coeficientes[i]!=0)
					cout<<coeficientes[i]<<"x"<<i+1;	
			}
		}
		cout<<endl; 
			
	}

	EcuacionLineal EcuacionLineal::operator * (double x){
	//la ecuaciónlineal multiplicada es regresada con la repuesta
		double coef[11];
		EcuacionLineal multiplicada(coef, grado);
		for(int i = 0; i<multiplicada.tam; i++)
			multiplicada.coeficientes[i] *= x; 
			
		return multiplicada;
	}

	void EcuacionLineal::operator + (EcuacionLineal e){
	//la ecuacionlineal a la que se le está sumando otra ecuacion lineal, es modificada
		for(int i = 0; i<tam; i++)
			coeficientes[i] += e.coeficientes[i]; 
	}


class SistemaDeEcuacionesLineales{
	//ocupo una variable global gradoMax.
	private:
		EcuacionLineal ecuaciones[11];
		int grado; 
		int numEcuaciones;
		
		double soluciones[11];
		bool solucionesInfinitas;
		bool sinSolucion; 
		
	public:
		SistemaDeEcuacionesLineales();
		SistemaDeEcuacionesLineales(int g, int num_e, EcuacionLineal e[]);
		
		void imprimirSoluciones();
		bool getSolucionesInfinitas();
		bool getSinSolucion(); 
		
		void Montante(); //va a cambiar la variable soluciones de clase, o los booleanos
};
	SistemaDeEcuacionesLineales::SistemaDeEcuacionesLineales(){
		grado = 0;
		numEcuaciones = 0; 
	}
	SistemaDeEcuacionesLineales::SistemaDeEcuacionesLineales(int g, int num_e, EcuacionLineal e[]){
		grado = g; 
		numEcuaciones = num_e; 
		for(int i = 0; i<numEcuaciones; i++){
			ecuaciones[i] = e[i];
		}	
	}
	
	void SistemaDeEcuacionesLineales::imprimirSoluciones(){
		for(int i = 0; i<grado; i++){
			cout<<"x"<<i+1<<"="<<soluciones[i]<<endl; 	
		} 
	}
	bool SistemaDeEcuacionesLineales::getSolucionesInfinitas(){
		return solucionesInfinitas;
	}
	bool SistemaDeEcuacionesLineales::getSinSolucion(){
		return sinSolucion; 
	}
	
	void SistemaDeEcuacionesLineales::Montante(){
		//hago el método montante y modifico los valores de la matriz con soluciones
		int k = 0; 
		while(!sinSolucion && !solucionesInfinitas && k<numEcuaciones){
			
			
			
			k++;	
		}
	}



int main(){
	
	double pivoteAnterior = 1; 
	double pivoteActual = 1; 
	
	return 0; 
}
