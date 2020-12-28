//                       BUDDY SYSTEM CODE

//EN UNIX AGREGAR -lm AL FINAL AL COMPILAR

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//si tree[i].tam vale cero no esta asignado y si vale 1 es un nodo padre vacio
//cualquier otro numero es el tamaño del proceso
//los mid se inicializan en 0

struct Proceso{
	int tam;	//los tamaños son mayores a 1
	int mid;	//los mid son mayorees a 1
};
typedef struct Proceso proceso;


proceso *tree;
//los "procesos" se guardan en tree como un arbol binario completo represntado como una lista, arreglo o vetor
//cada posicion en el arreglo es un nodo del arbol siendo la posicion 0 la raiz

int i, mid=1, pivote=0;
void menu(int),nuevo(int,int),dividir(int),borrar(int),mostrarLIST(int,int),inicializar(int),mostrarMAP(int,int),pendiente(proceso);
int lugarDisponible(int),generarMid(),validar(int),distancia(int),pesoNodo(int,int);

int main(int argc, char* argv[]){
	
	printf("\nSYSTEMA BUDDY DE ADMINISTACION DE MEMORIA\n");
	
	printf("\ningrese el tamaño de la memoria: ");
	int valor;
	
	scanf("%d",&valor);
	
	menu(valor);
	
	return 0;
}

void menu(int totsize)
{
	int opcion,req,id;
	
	if(!validar(totsize)){
		
		printf("Tamaño invalido\n");
		printf("El tamaño de memoria, debe ser potencia de 2 y mayor igual a 2:  ");
		return;
	}
	
	inicializar(totsize);
	
	while(1){
		
		printf("\nB U D D Y  S Y S T E M\n");
		printf("1)	[NEW] : <size>\n");
		printf("2)	[FREE] : <MID>\n");
		printf("3)	[LIST]\n");
		printf("4)	[MAP]\n");
		printf("5)	[EXIT]\n");
		printf("6) Imprimir arreglo (tree[])\n\n");
		printf("\n  	Opcion: ");
		scanf("%d",&opcion);
		printf("\n");
		
		switch(opcion)
		{
			case 1:
				printf("[NEW] : <size>\n");
				printf("Ingrese en tamaño del proceso (debe ser mayor igual a 2): ");
				scanf("%d",&req);
				nuevo(totsize,req);
				break;
			case 2:
				printf("[FREE] : <MID>\n");
				printf("Ingrese el MID del proceso: ");
				scanf("%d",&id);
				borrar(id);
				break;
			case 3:
				printf("[LIST]\n\n");
				mostrarLIST(totsize,0);
				break;
			case 4:
				printf("[MAP]\n\n");
				printf("Direccion	Tamaño		MID\n");	//direccion es el "byte" done cominza el proceso
				mostrarMAP(totsize,0);
				pivote=0;
				break;
			case 5:
				printf("[EXIT]");
				return;
			case 6: 
				printf("Imprimir arreglo\n\n");
				for(i=0; i<totsize-1; i++){
					printf("pos i: %d  tamaño: %d  id:%d\n",i,tree[i].tam, tree[i].mid);
				}
				break;
			default:
				printf("Opcion no valida\n\n");
				continue;
		}
	}
}

int validar(int size){
	
	float aux = log(size)/log(2);
	int aux2=aux;

	if(aux-aux2 == 0 && size>=2) return 1;
	else return 0;
}

void inicializar(int size){

	
	tree = (proceso *) calloc(size-1, sizeof(proceso));	//no se pueden agregar valores de 1 byte, por ende alcanzara con size-1

}

void nuevo(int totsize,int tamProc)
{
	int cont=0,size;
	size=totsize;
	
	if(tamProc>=totsize)
	{
		printf("\nERROR: no hay suficiente espacio en memoria v1***************\n");
		return;
	}


	while(1)
	{
		if(tamProc<=(size/2)){ //si el tamaño del proceso es menor o igual a la mitad del espacio disponible
			size/=2;			//se va dividiendo el espacio en dos segun el algoritmo compañero (buddy)
			cont++;				//contador determina en que nivel va a estar el nodo donde se guardara el proceso
		}
		else
		{
			break;
		}
	}
	
	int auxMid = generarMid();
	
	for(i=pow(2,cont)-1;i<(pow(2,cont+1)-1);i++){	//i es toma el valor del primer nodo en el nivel cont 
													//(pow(2,cont+1)-1);i++) es el nodo siguiente al ultimo nodo en el nivel
		
		if(tree[i].tam == 0 && lugarDisponible(i)){
			
			tree[i].tam= tamProc;
			tree[i].mid= auxMid;
			dividir(i);//
			
			printf("Resultado: Asignacion exitosa de %d bytes\n",tamProc);
			break;
		}
	}

	if(i==pow(2,cont+1)-1)
	{
		printf("\nERROR: No hay sufucuente memoria v2====================\n\n");
	}
}

int generarMid(){

	return mid++;
}

void dividir(int nodo)
{
	while(nodo!=0)
	{
		if(nodo%2==0) nodo=(nodo-1)/2;		//el nodo es derecho?
		else	nodo=nodo/2;				//el nodo es izquierdo
		
		tree[nodo].tam=1;
	}
}

int lugarDisponible(int nodo) //esto verifica si esta ocupado
{
	while(nodo!=0)
	{
		if(nodo%2==0) nodo=(nodo-1)/2;		//el nodo es derecho?
		else	nodo=nodo/2;				//el nodo es izquierdo
		
		if(tree[nodo].tam>1)	return 0;	//si el nodo esta ocupado

	}
	return 1;	//el nodo esta libre
}

void borrar(int id){
	
	if(id==0 || id >= mid){
		printf("\n No es un MID valido \n");
		return;
	}
	
	int nodo=0;	
	
	while(1)
	{
		if(tree[nodo].mid==id)
			break;
		else
			nodo++;
	}

	tree[nodo].tam=0; 
	tree[nodo].mid=0;

	while(nodo!=0)
	{
		if(tree[nodo%2==0?nodo-1:nodo+1].tam==0 && tree[nodo].tam==0)
		{
			tree[nodo%2==0?(nodo-1)/2:nodo/2].tam=0;
			nodo=nodo%2==0?(nodo-1)/2:nodo/2;
		}
		else break;
	}
}

void mostrarLIST(int totsize,int nodo){
	
	int permiso=0,llimit,ulimit,tab;
	
	if(nodo==0){ //es la raiz?
		permiso=1;
	}
	else if(nodo%2==0){ //el hijo es derecho?
		
		if(tree[(nodo-1)/2].tam==1) permiso=1;//el padre esta vacio? (tiene que valer 1)
		else permiso=0;
	}
	else{ //el hijo es izquierdo
		
		if(tree[nodo/2].tam==1) permiso=1;//el padre esta vacio? (tiene que valer 1)
		else permiso=0;
	}
	
	if(permiso){
		
		llimit=ulimit=tab=0;
		
		while(1){
			
			if(nodo>=llimit && nodo<=ulimit)
				break;
			else
			{
				tab++;
				printf("       ");
				llimit=ulimit+1;
				ulimit=2*ulimit+2;
			}
		}		
		
		printf(" %d ",(totsize/(int)pow(2,tab)));
		
		if(tree[nodo].tam>1) printf("---> Asignado: proceso %d, tamaño %d\n",tree[nodo].mid,tree[nodo].tam);
		else if(tree[nodo].tam==1) printf("---> Dividido\n");
		else printf("---> NULL\n");
		
		mostrarLIST(totsize,2*nodo+1);
		mostrarLIST(totsize,2*nodo+2);
	}
}
	
void mostrarMAP(int totsize, int nodo){
	
	int permiso=0,padre,espacio; //izq vale 1 si es un nodo izquiero y 0 si es derecho
	
	if(nodo==0){ //es la raiz?
		permiso=1;
	}
	else if(nodo%2==0){	//el hijo es derecho?
		
		padre=tree[(nodo-1)/2].tam;
		if(padre==1) permiso=1;//el padre esta vacio? (tiene que valer 1)
		else permiso=0;
	}
	else{ //el hijo es izquierdo
		
		padre=tree[nodo/2].tam;
		if(padre==1) permiso=1;//el padre esta vacio? (tiene que valer 1)
		else permiso=0;
	}
	
	
	if(permiso){
		
		if(tree[nodo].tam>1){
			
			pendiente(tree[nodo]);
		}
		
		else if(tree[nodo].tam==0){
			
			espacio = pesoNodo(nodo,totsize);
			
			printf("%d		%d		NULL\n",pivote,espacio);
			pivote = pivote + espacio;		
			
		}
		
		mostrarMAP(totsize,2*nodo+1);
		mostrarMAP(totsize,2*nodo+2);
	}
	
}
	
void pendiente(proceso p){
	
	int espacio = distancia(p.tam);
	printf("%d		%d		%d\n",pivote,espacio,p.mid);
	pivote=pivote+espacio; 
}
	
int distancia(int tam){
	
	int n = ceil(log(tam) / log(2));
	return pow(2,n);
}
	
int pesoNodo(int nodo, int totsize){
	
	int tamHermano,padre;
	
	if(nodo==0){ //es la raiz?
		return totsize/2;
	}
	else if(nodo%2==0){	//el hijo es derecho?
		
		tamHermano=tree[nodo-1].tam;
		
		if(tamHermano>1){
			return tamHermano;
		}
		else{
			padre = (nodo-1)/2;
			
			if(padre==0) return totsize/2;
			else return pesoNodo(padre,totsize)/2;
		}
	}
	else{ //el hijo es izquierdo
		
		tamHermano=tree[nodo+1].tam;
		
		if(tamHermano>1){
			return tamHermano;
		}
		else{
			padre = nodo/2;
			
			if(padre==0) return totsize/2;
			else return pesoNodo(padre,totsize)/2;
			
		}
	}
}
