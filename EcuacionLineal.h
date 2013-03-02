
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
