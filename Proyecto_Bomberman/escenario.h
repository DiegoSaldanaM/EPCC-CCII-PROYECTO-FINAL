#ifndef __ESCENARIO_H__
#define __ESCENARIO_H__
#define filas 15
#define columnas 17
class Cescenario{
private:
	int **matriz;
public:
	Cescenario(){
		matriz = new int*[filas];
	}
	~Cescenario(){}
	void generar_matriz(){
		for(int i=0; i<filas; i++){
			matriz[i]=new int[columnas];
		}
		for(int i=0; i<filas; i++){
			for(int j=0;  j<columnas; j++){
				if(i==0 || j==0 || i=filas-1 || j=columnas-1){  //Bloques fijos de los bordes
					matriz[i][j]=1;
				}
				else{
					if(i%2==0 && j%2==0){
						matriz[i][j]=1;
					}
					else{
						
					}
				}
			}
		}
	}
};

#endif