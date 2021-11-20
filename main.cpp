#include <iostream>
#include <stdlib.h>
#include <conio.h>

using namespace std;

//estructura de un nodo del arbol
struct nodo{
	
	int elemento; //valor del nodo
	
	//apuntadores de los hijos de izquierda y derecha
	nodo *derecha;
	nodo *izquierda;
	
	nodo *anterior; //aputandor al nodo anterior (nodo padre)
};

nodo *raiz=NULL; //puntero raiz del arbol

//Funcion que crea un nuevo nodo para un elemento
nodo *nuevoNodo(int n, nodo *anterior){
	nodo *nuevo_nodo= new nodo(); //se reserva memoria para un nodo
	
	//asignaciones 
	nuevo_nodo->elemento=n; //el valor recibido por parametro al elemento
	
	//apuntadores a null
	nuevo_nodo->derecha=NULL; 
	nuevo_nodo->derecha=NULL;
	nuevo_nodo->anterior=anterior; //se le asigna el nodo padre
	
	return nuevo_nodo; //se retorna el nuevo nodo
}

//introducir nodo
void introducir(nodo *&arbol, int n, nodo *padre){
	
	
	if(arbol==NULL){ //validacion de que el arbol este vacio
		nodo *nuevo_nodo=nuevoNodo(n, padre); //se crea el nuevo nodo
		arbol=nuevo_nodo; //se almacena en la raiz del arbol (ya que es el primero)
	}
	else{ //si tiene mas de un nodo...
		int valorRaiz=arbol->elemento; //Se obtiene a la raiz (para saber si su hijo ira a la izquierda o la derecha)
		
		//condicion para saber si el hijo ira a la derecha o a la derecha del nodo anterior (padre)
		if(n<valorRaiz){ //si el elemento es menor que el padre
			introducir(arbol->izquierda, n, arbol); //se itroduce el elemento a la izquierda
		}else{
			introducir(arbol->derecha, n, arbol); //sino, se introduce en la derecha
		}
	}
}

//funcion que muestra el arbol
void mostrarArbol(nodo *arbol, int cont){
	int i=0;
	
	if(arbol==NULL){ //si el arbol esta vacio, no hace nada 
		return;
	}else{ //si tiene elementos...
		mostrarArbol(arbol->derecha, cont+1); //mostrar los elementos de la derecha
		for(i=0;i<cont;i++){ //ciclo que recorre tantos elementos tenga el arbol (por la recursividad)
			cout<<"   "; //se dejan 3 espacios entre elementos
		}
		cout<<arbol->elemento<<endl;
		mostrarArbol(arbol->izquierda, cont+1); //ahora se repite el proceso para la izquierda
	}
}

//recorrido preOrden (recorre primero la raiz luego los elementos de la izquierda primero y luego la derecha)
void preOrden(nodo *arbol){
	if(arbol==NULL){ //si el arbol esta vacio, no se muestra nada
		return;
	}else{ //si existen elementos
		cout<<arbol->elemento<<"-";//se muestra primero el valor
		//se llama la funcion nuevamente para mostrar los elementos por la izquierda primero y luego a la derecha del arbol
		preOrden(arbol->izquierda);
		preOrden(arbol->derecha);
	}
}

//recorrido inOrden (recorrido todos los elementos mas a la izquierda luego la raiz y luego los elementos de la derecha)
void inOrden(nodo *arbol){
	if(arbol==NULL){ //si esta vacio el arbol, no se muestra nada
		return;
	}else{
		//se muestra la parte izquierda llamando recursivamente la misma funcion, luego la raiz, y luego la parte deecha
		inOrden(arbol->izquierda); 
		cout<<arbol->elemento<<"-";	
		inOrden(arbol->derecha);
	}
}

//recorrido en postOrden (primero se recorre el lado izquierdo, luego el lado derecho y al final la raiz)
void postOrden(nodo *arbol){
	if(arbol==NULL){ //si esta vacio el arbol, no se muestra nada
		return;
	}else{
		//primero se muestra la parte izquierda luego derecha luego la raiz llamando la misma fincion recursivamente
		postOrden(arbol->izquierda);		
		postOrden(arbol->derecha);
		cout<<arbol->elemento<<"-";	
	}
}

//menu de recorridos
void menuRecorridos(){
	//variable local que almacenara la opcion del submenu
	int opc=4;
	
	do{
		//submenu
		system("cls");
		cout<<"          SUBMENU DE RECORRIDOS DEL ARBOL"<<endl<<endl;
		cout<<"*Ingrese 1 para visualizar recorrido preOrden del arbol"<<endl<<endl;
		cout<<"*Ingrese 2 para visualizar recorrido inOrden del arbol"<<endl<<endl;
		cout<<"*Ingrese 3 para visualizar recorrido postOrden arbol"<<endl<<endl;
		cout<<"*Ingrese 0 para Volver al menu principal\n\n->";
		cin>>opc; //lectura de la opcion
		
		system("cls"); //borra pantalla
		
		switch(opc){ //estudio de casos de la opcion del recorrido solicitado por el usuario
			
			case 0:{
				cout<<"Volviendo al menu principal"<<endl;
				system("pause");
				system("cls");				
				break;
			}
			
			case 1:{
				cout<<"Recorrido en preOrden:"<<endl<<endl;
				preOrden(raiz);
				cout<<endl<<endl;
				system("pause");
				break;
			}
			
			case 2:{
				cout<<"Recorrido en inOrden:"<<endl<<endl;
				inOrden(raiz);
				cout<<endl<<endl;
				system("pause");
				break;
			}
			
			case 3:{
				cout<<"Recorrido en postOrden:"<<endl<<endl;
				postOrden(raiz);
				cout<<endl<<endl;
				system("pause");
				break;
			}
			
			default:{
				cout<<"*parametro no valido"<<endl;
				system("pause");
				system("pause");
				break;
			}
		}
	}while(opc!=0);
}

//nivel del arbol
int nivel_arbol(nodo *arbol){
	
	if(arbol!=NULL){ //si el arbol no esta vacio
		int izq = nivel_arbol(arbol->izquierda)+1; //se llama a la funcion recursivamente aumentando uno en el valor de retorno para ambos subarboles hijos
		int der = nivel_arbol(arbol->derecha)+1;
		
		if(izq>der){ //se muestra el valor mayor entre ambos subarboles pues determinara el nivel del arbol total
			return izq;
		}else{
			return der;
		}
	}
	
	return -1;
}

//buscar un elemento en el arbol
bool buscarElemento(nodo *arbol, int n){
	
	if(arbol==NULL){ //si el arbol esta vacio se retorna false
		return false;
	}else if(arbol->elemento==n){ //si el elemento que se esta buscando es igual al elemento del arbol
		return true;
	}else if(n<arbol->elemento){ //si es menor, se llama a la funcion otra ves por la izquierda
		return buscarElemento(arbol->izquierda,n);
	}else{
		return buscarElemento(arbol->derecha,n); //caso contrario se asume que puede estar en los elementos mayores (la derecha)
	} 

}

//minimo
nodo *min(nodo *arbol){
	if(arbol==NULL){
		return NULL;
	}
	if(arbol->izquierda){
		return min(arbol->izquierda);
	}else{
		return arbol;
	}
}

//funcion que reemplaza un nodo por otro
void reemplazar(nodo* arbol, nodo *nuevoNodo){
	if(arbol->anterior){
		if(arbol->elemento==arbol->anterior->izquierda->elemento){
			arbol->anterior->izquierda=nuevoNodo;
		}else if(arbol->elemento==arbol->anterior->derecha->elemento){
			arbol->anterior->derecha=nuevoNodo;
		}
	}
	if(nuevoNodo){
		nuevoNodo->anterior=arbol->anterior;
	}
}

//destruir nodo
void destruirNodo(nodo *nodoEli){
	//si tiene hijos, los punteros apuntaran a null 
	nodoEli->izquierda=NULL;
	nodoEli->derecha=NULL;
	
	delete nodoEli; //se libera la memoria del nodo que almacenaba el elemento que se desea borrar
}

//eliminar el nodo encontrado
void eliminarNodo(nodo *nodoEliminar){
	
	if(nodoEliminar->izquierda && nodoEliminar->derecha){ //si el nodo tiene 2 hijos
		nodo *menor = min(nodoEliminar->derecha);
		nodoEliminar->elemento=menor->elemento;	
		eliminarNodo(menor);
	}
	else if(nodoEliminar->izquierda){ //si tiene un hijo en la izquierda
		reemplazar(nodoEliminar, nodoEliminar->izquierda);
		destruirNodo(nodoEliminar);
	}else if(nodoEliminar->derecha){ //si tiene un hijo en la derecha
		reemplazar(nodoEliminar, nodoEliminar->derecha);
		destruirNodo(nodoEliminar);
	}else{ //si es una hoja
		reemplazar(nodoEliminar, NULL);
		destruirNodo(nodoEliminar);
	}
	
}

//eliminar nodo
void eliminar(nodo *arbol, int n){
	if(arbol==NULL){
		return;
	}else if(n<arbol->elemento){
		eliminar(arbol->izquierda,n);
	}else if(n>arbol->elemento){
		eliminar(arbol->derecha,n);
	}else{
		eliminarNodo(arbol);
	}
}

//funcion principal
int main(){
	//variables locales del main
	int opc=0, elemento=0, cont=0;
	
	do{
		//menu 
		system("cls");
		cout<<"          MENU DEL ARBOL"<<endl<<endl;
		cout<<"*Ingrese 1 para ingresar nodo"<<endl<<endl;
		cout<<"*Ingrese 2 para imprimir el arbol"<<endl<<endl;
		cout<<"*Ingrese 3 para elegir un recorrido (preOrden, inOrden, postOrden)"<<endl<<endl;
		cout<<"*Ingrese 0 para Salir\n\n->";
		cin>>opc;//lectura de la opcion
		
		system("cls"); //borra pantalla
		
		switch(opc){ //estudio de casos de la opcion que desea el usuario, entre salir/llenar arbol/imprimir/submenu recorridos
			
			case 0:{
				cout<<"saliendo..."<<endl;
				system("pause");
				system("cls");				
				break;
			}
			
			case 1:{
				
				cout<<"*Ingrese el dato del nuevo elemento del arbol\n->"; //solicitud del elemento que se desea ingresar al arbol
				cin>>elemento;
				
				if(buscarElemento(raiz, elemento)==true) //si el valor existe, no se permite ingresar al arbol
					cout<<"El elemento "<<elemento<<" Ya existe en el arbol, digite otro elemento"<<endl;
					
				else{ //sino...
					
					introducir(raiz, elemento, NULL); //se ingresa al arbol
					
					if(nivel_arbol(raiz)<4){ //si aun no es el nivel 4 entones se deja el elemento en el arbol para continuar
						cout<<"Elemento ingresado correctamente"<<endl;	
					}else{//si ya se sobrepasa el nivel 4
						cout<<"El valor "<<elemento<<" Iria en el nivel 5."<<endl<<"Ingrese un valor que no sobrepase el nivel 4"<<endl; //mensaje de desaprovacion para el elemento
						eliminar(raiz, elemento); //se elimina del arbol ya que sobrepasa el nivel 4
					}
				}

				system("pause");
				break;
			}
			
			case 2:{
				
				mostrarArbol(raiz, cont); //invocacion de la funcion mostrar arbol
				cout<<endl;
				system("pause");
				break;
			}
			
			case 3:{
				
				menuRecorridos();//invocacion del submenu para las rutinas de recorrio de arboles (preorden, inorden, postorden)				
				break;
			}

			default:{
				cout<<"*parametro no valido"<<endl;
				system("pause");
				break;
			}
			
		}
		
	}while(opc!=0); //ciclo que asegura que se repita el sistema hasta que el usuario desee salir

	return 0;
}

