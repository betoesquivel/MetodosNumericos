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
