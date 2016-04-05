//Programa principal para sistema de ventas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct Producto{
	int cantidad;
	float precio;
	char nombre[20];
	struct Producto *Productosig;
	}Producto;


Producto* insertarinicio(Producto* inicio, int valor,float precio,char *nombre);
Producto* RemoverDepartamento(Producto *inicio, unsigned int indice,char *nombre);
Producto* RemoverProducto(Producto *inicio, unsigned int indice);
Producto* leerinventario(Producto *inicio,char *archnom);
Producto* leerDepartamentos(Producto *inicio);
Producto* BorrarList(Producto *inicio);
int Venta(Producto *inicio,int n, unsigned int indice);
void Compra(Producto *inicio,int n, unsigned int indice);
char* Obtener(Producto *inicio, unsigned int indice);
int ValidarOpcion(int x);
int VerificarDepas(char *departamento);
int VerificarProduct(Producto *inicio,char *producto);
int imprimeInventario(Producto *inicio);
int imprimeDepartamento(Producto *inicio);
void AgregarDepartamento(Producto *inicio);
void AgregarProductos(Producto *inicio,char* nombre);
void ModificarProducto(Producto *inicio,int indice);
void ReportesDepartamento(Producto *inicio,char *departamento,int indice,int canti);
void ReporteTotal(Producto *inicio,int indice,int canti);
void BorrarReportes(char *nombre);
void imprimirReporte(Producto *inicio);
void Ticket(Producto *inicio);
void ReporteFinal(Producto *inicio,char *departamento);

int main(){

	Producto *inicio=NULL;//Aputador para lista de productos
	Producto *cabeza=NULL;//Apuntador para lista de departamentos
	//Producto *comienzo=NULL;//Apuntador para posible pila :0
	char reporte[20]={"Reporte"};
	int accionmenu,accionmenu1,accionmenu2,accionmenu3,depnum,comodin;//Variables para los switch
	int pronum=0;//Cuenta numero de productos en cada inventario
	int verif,canti,i,recibo=0;
	char nomdepa[20],nomprodu[20];
	float nuprecio;


	cabeza=leerDepartamentos(cabeza);
	depnum=imprimeDepartamento(cabeza);
	system("clear");
	printf("\t\tBienvenido al Sistema de ventas\n\n");

	
	for(i=0;i<depnum;i++)
	{
		BorrarReportes(Obtener(cabeza,i));
	}
	BorrarReportes("Total");
	cabeza=BorrarList(cabeza);

	do{
		//system("clear");
		printf("\t\tMenu:\n\n");
		printf("\t\t1. Revisar Inventarios\n\n");
		printf("\t\t2. Realizar Ventas\n\n");
		printf("\t\t3. Realizar Compras\n\n");
		printf("\t\t4. Reportes\n\n");
		printf("\t\t5. Salir\n\n");
		printf("Ingresar el numero de la accion que quieres realizar.\n\n");
		accionmenu=ValidarOpcion(5);
			switch(accionmenu){
				case 1:
				
				do{
					
					printf("Es posible realizar las siguientes acciones:\n\n");
					printf("\t\t1. Revisar Productos.\n");
					printf("\t\t2. Crear nuevo Departamento.\n");
					printf("\t\t3. Eliminar un Departamento.\n");
					printf("\t\t4. Agregar un nuevo producto a un Departamento.\n");
					printf("\t\t5. Eliminar un producto.\n");
					printf("\t\t6. Modificar un producto.\n");
					printf("\t\t7. Regresar.\n");
					printf("Elige una accion (numero):\n");
					accionmenu1=ValidarOpcion(7);
					switch(accionmenu1){
						case 1:
							//system("clear");
							cabeza=leerDepartamentos(cabeza);
							depnum=imprimeDepartamento(cabeza);
							printf("Que Departamento quieres revisar\n\n");
							comodin=ValidarOpcion(depnum);
							inicio=leerinventario(inicio,Obtener(cabeza,comodin-1));
							imprimeInventario(inicio);
							inicio=BorrarList(inicio);
							cabeza=BorrarList(cabeza);
							break;

						case 2:
							//system("clear");
							cabeza=leerDepartamentos(cabeza);
							imprimeDepartamento(cabeza);
							printf("Ingresa el nombre del nuevo Departamento: \n\n");
							scanf("%s",nomdepa);
							verif=VerificarDepas(nomdepa);
							if(verif==1)
							{
								cabeza=insertarinicio(cabeza,0,0,nomdepa);
								AgregarDepartamento(cabeza);
								imprimeDepartamento(cabeza);
							}
							
							cabeza=BorrarList(cabeza);
							break;

						case 3:
							//system("clear");
							cabeza=leerDepartamentos(cabeza);
							depnum=imprimeDepartamento(cabeza);
							printf("Indique el numero del departamento que quieres borrar.\n\n");
							comodin=ValidarOpcion(depnum);
							cabeza=RemoverDepartamento(cabeza,comodin-1,Obtener(cabeza,comodin-1));//Hay que restarle 1 por que empieza de 0
							printf("El Departamento %s ha sido eliminado.\n\n",Obtener(cabeza,comodin-1));
							AgregarDepartamento(cabeza);
							imprimeDepartamento(cabeza);
							cabeza=BorrarList(cabeza);
							break;

						case 4:
							//system("clear");
							cabeza=leerDepartamentos(cabeza);
							depnum=imprimeDepartamento(cabeza);
							printf("A que Departamento quieres Agregar el nuevo Producto.\n\n");
							comodin=ValidarOpcion(depnum);
							inicio=leerinventario(inicio,Obtener(cabeza,comodin-1));
							printf("Escribe el nombre del nuevo producto.\n\n");
							scanf("%s",nomprodu);
							verif=VerificarProduct(inicio,nomprodu);
							if(verif==0)
							{
							printf("Escribe el precio del nuevo producto.\n\n");
							scanf("%f",&nuprecio);
							inicio=insertarinicio(inicio,0,nuprecio,nomprodu);
							AgregarProductos(inicio,Obtener(cabeza,comodin-1));
							imprimeInventario(inicio);
							}
							else
							{
								printf("No se ha creado el nuevo Producto\n\n");
							}
							inicio=BorrarList(inicio);
							cabeza=BorrarList(cabeza);

							break;
						case 5:
							//system("clear");
							cabeza=leerDepartamentos(cabeza);
							depnum=imprimeDepartamento(cabeza);
							printf("De cual Departamento quieres eliminar un Producto.\n\n");
							comodin=ValidarOpcion(depnum);
							inicio=leerinventario(inicio,Obtener(cabeza,comodin-1));
							pronum=imprimeInventario(inicio);
							printf("Escribe el indice del producto que quieres eliminar.\n\n");
							verif=ValidarOpcion(pronum);	
							inicio=RemoverProducto(inicio,verif);
							AgregarProductos(inicio,Obtener(cabeza,comodin-1));
							imprimeInventario(inicio);
							inicio=BorrarList(inicio);
							cabeza=BorrarList(cabeza);
							break;

						case 6:
							cabeza=leerDepartamentos(cabeza);
							depnum=imprimeDepartamento(cabeza);
							printf("De cual Departamento quieres modificar un Producto.\n\n");
							comodin=ValidarOpcion(depnum);
							inicio=leerinventario(inicio,Obtener(cabeza,comodin-1));
							pronum=imprimeInventario(inicio);
							printf("Escribe el indice del producto que quieres modificar.\n\n");
							verif=ValidarOpcion(pronum);	
							ModificarProducto(inicio,verif-1);
							AgregarProductos(inicio,Obtener(cabeza,comodin-1));
							imprimeInventario(inicio);
							inicio=BorrarList(inicio);
							cabeza=BorrarList(cabeza);
							break;


						}

				}while(accionmenu1!=7);
					break;
				case 2:
					do{

					cabeza=leerDepartamentos(cabeza);
					depnum=imprimeDepartamento(cabeza);
					printf("De cual Departamento quieres vender un Producto.\n\n");
					accionmenu1=ValidarOpcion(depnum);
					inicio=leerinventario(inicio,Obtener(cabeza,accionmenu1-1));
					pronum=imprimeInventario(inicio);
					if(pronum!=0)
					{
					printf("Escribe el indice del producto que quieres vender.\n\n");
					verif=ValidarOpcion(pronum);
					printf("Escribe que cantidad de %s quieres vender.\n\n",Obtener(inicio,verif-1));
					scanf("%d",&canti);	
					i=Venta(inicio,canti,verif-1);
					if(i==1)
					{
					ReportesDepartamento(inicio,Obtener(cabeza,accionmenu1-1),verif-1,canti);
					ReporteTotal(inicio,verif-1,canti);
					AgregarProductos(inicio,Obtener(cabeza,accionmenu1-1));
						}
					imprimeInventario(inicio);
					inicio=BorrarList(inicio);
					cabeza=BorrarList(cabeza);
					printf("Quieres realizar otra venta: 1)Si 2) No\n");
					accionmenu=ValidarOpcion(2);
					}
				}while(accionmenu==1);

					break;
				
				case 3:
					do{

					cabeza=leerDepartamentos(cabeza);
					depnum=imprimeDepartamento(cabeza);
					printf("De cual Departamento quieres comprar un Producto.\n\n");
					accionmenu1=ValidarOpcion(depnum);
					inicio=leerinventario(inicio,Obtener(cabeza,accionmenu1-1));
					pronum=imprimeInventario(inicio);
					if(pronum!=0)
					{
					printf("Escribe el indice del producto que quieres comprar.\n\n");
					verif=ValidarOpcion(pronum);
					printf("Escribe que cantidad de %s quieres comprar.\n\n",Obtener(inicio,verif-1));
					scanf("%d",&canti);	
					Compra(inicio,canti,verif-1);
					ReportesDepartamento(inicio,Obtener(cabeza,accionmenu1-1),verif-1,(-1)*canti);
					ReporteTotal(inicio,verif-1,(-1)*canti);
					AgregarProductos(inicio,Obtener(cabeza,accionmenu1-1));
					imprimeInventario(inicio);
					inicio=BorrarList(inicio);
					cabeza=BorrarList(cabeza);
					printf("¿Quieres realizar otra compra?: 1)Si 2) No\n");
					accionmenu2=ValidarOpcion(2);
					}
				}while(accionmenu2==1);

					break;
				case 4:

					printf("A continuacion los reportes de todas las transacciones realizadas, elige que reporte quieres revisar:\n\n");
					printf("1. Reporte de transacciones por departamento\n");
					printf("2. Reporte total de compras/ventas\n");
					printf("3. Regresar\n\n");
					accionmenu2=ValidarOpcion(3);
					recibo=recibo+1;
					switch(accionmenu2)
					{
						
						case 1:

							cabeza=leerDepartamentos(cabeza);
							depnum=imprimeDepartamento(cabeza);
							printf("De cual Departamento quieres revisar su reporte de transacciones.\n\n");
							accionmenu3=ValidarOpcion(depnum);
							inicio=leerinventario(inicio,strcat(reporte,Obtener(cabeza,accionmenu3-1)));
							strcpy(reporte,"Reporte");
							imprimirReporte(inicio);
							cabeza=BorrarList(cabeza);
							inicio=BorrarList(inicio);

							break;

						case 2:

							printf("A continuacion el reporte total de transacciones.\n\n");
							inicio=leerinventario(inicio,"ReporteTotal");
							imprimirReporte(inicio);
							inicio=BorrarList(inicio);
							break;

					}
					break;
						
		}
	
	}while(accionmenu != 5);

	strcpy(reporte,"Reporte");
	printf("Acciones Finalizadas.\n\n");

	inicio=leerinventario(inicio,"ReporteTotal");
	Ticket(inicio);
	inicio=BorrarList(inicio);


	

/*
	for(j=0;j<depnum;j++)
	{
		inicio=leerinventario(inicio,strcat(reporte,Obtener(cabeza,j)));
		ReporteFinal(inicio,Obtener(cabeza,j));
		strcpy(reporte,"Reporte");
		inicio=BorrarList(inicio);
		
	}
	//BorrarReportes("Total");*/

	return 0;
}






//Obtiene la informacion de los archivos
Producto* leerinventario(Producto *inicio,char *archnom){
	FILE * archivo;
	int valor;
	float precio;
	char nombre[20];
	archivo=fopen(archnom,"r");
	Producto *ProductoActual = inicio;
	if(archivo==NULL){
		printf("Archivo %s.txt no se pudo abrir\n",archnom);
		
	}
	else
	{
		printf("Se Abrio %s",archnom);
		while(!feof(archivo)){

			fscanf(archivo,"%s %f %d",nombre,&precio,&valor);
			
			if(!feof(archivo)){//Evita la repeticion del Ultimo renglon del archivo
				if(inicio==NULL){
						ProductoActual = malloc(sizeof(Producto));
						ProductoActual->cantidad = valor;
						ProductoActual->precio = precio;
						strcpy(ProductoActual->nombre,nombre);
						ProductoActual->Productosig = NULL;
						inicio = ProductoActual;
				}
				else{
						while(ProductoActual->Productosig != NULL){
							ProductoActual = ProductoActual->Productosig;
						}

						Producto *nuevoProducto = malloc(sizeof(Producto));
						nuevoProducto->cantidad = valor;
						nuevoProducto->precio = precio;
						strcpy(nuevoProducto->nombre,nombre);
						nuevoProducto->Productosig = NULL;
						ProductoActual->Productosig = nuevoProducto;
					}
			}
			}
	}
	fclose(archivo);
	return inicio;
}
int ValidarOpcion(int x)//Recibe el rango maximo de opciones de un menu
{
	char dato[20];
	int n=0,numero,i;
	do
	{
		numero=0;
		fflush(stdin);
		scanf("%s",dato);
		n=strlen(dato);
		for(i=0;i<n;i++)
		{
			if(!isdigit(dato[i]))
			{
				numero=numero+1;
			}
			
		}
		if(numero!=0 || atoi(dato)<1 || atoi(dato)>x)
		{
			printf("La opcion no es valida,vuelve a intentarlo\n\n");
		}
	}while(numero!=0 || atoi(dato)<1 || atoi(dato)>x);
	return (numero=atoi(dato));
}
//Lee El archivo de Departamentos disponibles
Producto* leerDepartamentos(Producto *inicio){
	FILE * archivo;
	char nombre[20];
	archivo=fopen("Departamentos","r");
	Producto *ProductoActual = inicio;
	if(archivo==NULL){
		printf("Archivo no se pudo abrir\n");
		
	}
	else
	{

		while(!feof(archivo)){

			fscanf(archivo,"%s",nombre);
			
			if(!feof(archivo)){//Evita la repeticion del Ultimo renglon del archivo
				if(inicio==NULL){
						ProductoActual = malloc(sizeof(Producto));
						strcpy(ProductoActual->nombre,nombre);
						ProductoActual->Productosig = NULL;
						inicio = ProductoActual;
				}
				else{
						while(ProductoActual->Productosig != NULL){
							ProductoActual = ProductoActual->Productosig;
						}

						Producto *nuevoProducto = malloc(sizeof(Producto));
						strcpy(nuevoProducto->nombre,nombre);
						nuevoProducto->Productosig = NULL;
						ProductoActual->Productosig = nuevoProducto;
					}
			}
			}
	}
	fclose(archivo);
	return inicio;
}

//Imprime Los productos en inventario
int imprimeInventario(Producto *inicio){
	Producto *ProductoActual = inicio;
	int i=0;
	if(ProductoActual==NULL)
	{
		printf("No hay nada en el inventario.\n");
	}
	else
	{
	printf("\tNombre de Producto");
		printf("\t\tPrecio");
		printf("\t\tEn existencia\n");
		printf("\t-------------------------------------------------------------\n\n");
	while(ProductoActual != NULL){
		i++;
		printf("%d)\t%s",i,ProductoActual->nombre);
		printf("\t\t%.2f",ProductoActual->precio);
		printf("\t\t\t%d\n",ProductoActual->cantidad);
		
		
		ProductoActual = ProductoActual->Productosig;
	}
	printf("\n\n");
	}
	return i;
}

//Imprime los Departamentos disponibles
int imprimeDepartamento(Producto *inicio){
	Producto *ProductoActual = inicio;
	int i=0;
	if(ProductoActual==NULL)
	{
		printf("No hay ningun departamento.\n");
	}
	printf("\n\tLos Departamentos disponibles son los siguientes:\n\n");
		
	while(ProductoActual != NULL){

		i++;
		printf("\t\t%d)%s\n\n",i,ProductoActual->nombre);
		ProductoActual = ProductoActual->Productosig;
	}
	return i;
}
//Adquiere valores
Producto* insertarinicio(Producto* inicio, int valor,float precio,char *nombre){
	
	Producto *ProductoActual = inicio;
	if(inicio==NULL){
		ProductoActual = malloc(sizeof(Producto));
		ProductoActual->cantidad = valor;
		ProductoActual->precio = precio;
		strcpy(ProductoActual->nombre,nombre);
		ProductoActual->Productosig = NULL;
		inicio = ProductoActual;
	}
	else{
		while(ProductoActual->Productosig != NULL){
			ProductoActual = ProductoActual->Productosig;
		}
		Producto *nuevoProducto = malloc(sizeof(Producto));
		nuevoProducto->cantidad = valor;
		nuevoProducto->precio = precio;
		strcpy(nuevoProducto->nombre,nombre);
		nuevoProducto->Productosig = NULL;
		ProductoActual->Productosig = nuevoProducto;
	}
	return inicio;
}

//Agrega Departamentos al achivo de departamentos existentes
void AgregarDepartamento(Producto *inicio)
{
	FILE *archivo;
	Producto *ProductoActual = inicio;
	archivo=fopen("Departamentos","w");
	if(archivo==NULL){
		printf("Ha ocurrido un error\n\n");
	}
	else
	{
		
		while(ProductoActual != NULL){

		fprintf(archivo,"%s\n",ProductoActual->nombre);
		ProductoActual = ProductoActual->Productosig;
	}
	}
	fclose(archivo);

}

//Agrega Productos al archivo de departamentos existentes
void AgregarProductos(Producto *inicio,char* nombre)
{
	FILE *archivo;
	Producto *ProductoActual = inicio;
	archivo=fopen(nombre,"w");
	if(archivo==NULL){
		printf("Ha ocurrido un error\n\n");
	}
	else
	{

		while(ProductoActual != NULL){

		fprintf(archivo,"%s %.2f %d\n",ProductoActual->nombre,ProductoActual->precio,ProductoActual->cantidad);
		ProductoActual = ProductoActual->Productosig;
	}
	}
	fclose(archivo);

}

//Verifica si ya existe un Departamento, envia 1 si no existe y envia 0 si ya existe
int VerificarDepas(char *departamento)
{
	FILE * archivo;
	FILE *archi;
	int i;
	char depa[20]={"Reporte"};
	archivo=fopen(departamento,"r");
	if(archivo==NULL){
		printf("Se ha creado el Departamento de %s\n\n",departamento);
		archivo=fopen(departamento,"w");
		archi=fopen(strcat(depa,departamento),"w");
		i=1;
	}
	else
	{
		printf("Ese Departamento ya existe\n\n");
		i=0;
	}
	fclose(archivo);
	fclose(archi);
	return i;

}
//Verificar Productos,si manda 0 si no existe y manda 1 si si existe
int VerificarProduct(Producto *inicio,char* producto){
	Producto *ProductoActual = inicio;
	int i=0;
	
	while(ProductoActual != NULL){
		if(strcmp(ProductoActual->nombre,producto)==0)
		{
			printf("El producto ya existe.\n\n");
			i=i+1;
		}
		ProductoActual = ProductoActual->Productosig;
	}
	return i;
}
//Remueve Productos de algun Departamento
Producto* RemoverProducto(Producto *inicio, unsigned int indice){
	Producto *ProductoActual = inicio;
	if(inicio==NULL){
		return NULL;
	}
	else if(indice == 0){
		ProductoActual = inicio->Productosig;
		free(inicio);
		return ProductoActual;
	}
	else{
		Producto *anterior = inicio;
		int i = 0;
		while(i<indice && ProductoActual->Productosig != NULL){
			anterior = ProductoActual;
			ProductoActual = ProductoActual->Productosig;
			i++;
		}
		anterior->Productosig = ProductoActual->Productosig;
		free(ProductoActual);
		if(i==0){
			return NULL;
		}
	}
	return inicio;
}
//Remueve un departamento y su archivo respectivo
Producto* RemoverDepartamento(Producto *inicio, unsigned int indice,char *nombre){
	Producto *ProductoActual = inicio;
	char depa[20]={"Reporte"};
	remove(nombre);
	remove(strcat(depa,nombre));
	int i=0;
	if(inicio==NULL){
		return NULL;
	}
	else if(indice == 0){
		ProductoActual = inicio->Productosig;
		free(inicio);
		return ProductoActual;
	}

	else{
		Producto *anterior = inicio;
		while(i<indice && ProductoActual->Productosig != NULL){
			anterior = ProductoActual;
			ProductoActual = ProductoActual->Productosig;
			i++;
		}
		anterior->Productosig = ProductoActual->Productosig;
		free(ProductoActual);
		if(i==0){
			return NULL;
		}
	}
	return inicio;
}
//Obtener departamento para usar o borrar
char* Obtener(Producto *inicio, unsigned int indice){
	Producto *ProductoActual = inicio;
	int i = 0;
	if(inicio==NULL){
		return 0;
	}
	while(i<indice && ProductoActual->Productosig != NULL){
		ProductoActual = ProductoActual->Productosig;
		i++;
	}
	return ProductoActual->nombre;
}

//Venta de Producto
int Venta(Producto *inicio,int n, unsigned int indice){
	Producto *ProductoActual = inicio;
	int i = 0;//n es la cantidad que el cliente quiere comprar
	int eleccion;//Elige si acepta comprar la cantidad disponible
	int x;
	if(inicio==NULL){
		printf("No se ha vendido nada.\n\n");
	}
	while(i<indice && ProductoActual->Productosig != NULL){
		ProductoActual = ProductoActual->Productosig;
		i++;
	}
	if((ProductoActual->cantidad)-n<0)
	{
		printf("No hay suficientes productos en inventario.\n\n");
	
		while((ProductoActual->cantidad)-n<0)
		{
			n=n-1;
		}
			if(n!=0)
			{
			printf("Solo es posible vender %d %s, ¿Deseas vender tal cantidad?\n1)Si\n2)No",n,ProductoActual->nombre);
			
			eleccion=ValidarOpcion(2);
			if(eleccion==1)
			{
				ProductoActual->cantidad=(ProductoActual->cantidad)-n;
			}
			else
			{
				printf("No se ha realizado la venta.");
				x=0;
			}
		}
	}
	else{
		ProductoActual->cantidad=(ProductoActual->cantidad)-n;
		x=1;

	}	
	return x;

}
void ModificarProducto(Producto *inicio,int indice)
{
	Producto *ProductoActual = inicio;
	int i = 0;
	int eleccion;
	float preci;
	char nombre[20];
	if(inicio==NULL){
		printf("No hay producto que modificar.\n\n");
	}
	while(i<indice && ProductoActual->Productosig != NULL){
		ProductoActual = ProductoActual->Productosig;
		i++;
	}
	printf("Cambiar nombre:\n1)Si\2)No\n\n");
	eleccion=ValidarOpcion(2);
	if(eleccion==1)
		{
			printf("Escribe el nuevo nombre:\n");
			scanf("%s",nombre);
			strcpy(ProductoActual->nombre,nombre);
		}
	printf("Cambiar precio:\n1)Si\2)No\n\n");
	eleccion=ValidarOpcion(2);
	if(eleccion==1)
		{
			printf("Escribe el nuevo precio:\n");
			scanf("%f",&preci);
			ProductoActual->precio=preci;
		}
}

//Compra de Producto
void Compra(Producto *inicio,int n, unsigned int indice){
	Producto *ProductoActual = inicio;
	int opcion;
	int i = 0;//n es la cantidad que el cliente quiere comprar

	if(inicio==NULL){
		printf("No se ha comprado nada.\n\n");
	}
	while(i<indice && ProductoActual->Productosig != NULL){
		ProductoActual = ProductoActual->Productosig;
		i++;
	}

	printf("Usted ha dicho que quiere %d %s, ¿Es correcta tal cantidad?\n1)Si\n2)No\n\n",n,ProductoActual->nombre);
	opcion=ValidarOpcion(2);
	
			if(opcion==1)
			{
				ProductoActual->cantidad=(ProductoActual->cantidad)+n;
			}
			else
			{
				printf("No se ha realizado la compra de mercancia.");
			}
}

//Libera memoria de toda la lista

Producto* BorrarList(Producto *inicio){
	if(inicio==NULL){
		return NULL;
	}
	Producto *ProductoActual = inicio;
	Producto *nodoSig = inicio->Productosig;
	while(nodoSig != NULL){
		free(ProductoActual);
		ProductoActual = nodoSig;
		nodoSig = ProductoActual->Productosig;
	}
	free(ProductoActual);
	return NULL;
}
//Guarda una transaccion de un departamento especifico en un archivo
void ReportesDepartamento(Producto *inicio,char *departamento,int indice,int canti)
{
	
	FILE *archivo;
	Producto *ProductoActual = inicio;
	char nombre[20]={"Reporte"};
	strcat(nombre,departamento);
	printf("%s",nombre);
	archivo=fopen(nombre,"a");
	int i=0;
	if(archivo==NULL){
		printf("Ha ocurrido un error\n\n");
	}
	else
	{
	while(i<indice && ProductoActual->Productosig != NULL){
		ProductoActual = ProductoActual->Productosig;
		i++;
	}
		fprintf(archivo,"%s %.2f %d\n",ProductoActual->nombre,ProductoActual->precio,canti);
	}
	fclose(archivo);

}
//Guarda todas las transacciones en su archivo
void ReporteTotal(Producto *inicio,int indice,int canti)
{
	FILE *archivo;
	Producto *ProductoActual = inicio;
	archivo=fopen("ReporteTotal","a");
	int i=0;
	if(archivo==NULL){
		printf("Ha ocurrido un error\n\n");
	}
	else
	{
		while(i<indice && ProductoActual->Productosig != NULL){
		ProductoActual = ProductoActual->Productosig;
		i++;
	}
		fprintf(archivo,"%s %.2f %d\n",ProductoActual->nombre,ProductoActual->precio,canti);
	}
	fclose(archivo);

}
void BorrarReportes(char *nombre)
{
	FILE * archivo;
	char reporte[20]={"Reporte"};
	strcat(reporte,nombre);
	archivo=fopen(reporte,"w");
	fclose(archivo);
}

void imprimirReporte(Producto *inicio)
{
	Producto *ProductoActual = inicio;
	float resultado=0;
	int i=0;
	if(ProductoActual==NULL)
	{
		printf("No hay nada Registrado.\n");
	}
	else
	{

	printf("\tNombre de Producto");
		printf("\t\tPrecio");
		printf("\t\tCantidad\n");
		printf("\t-------------------------------------------------------------\n\n");
	while(ProductoActual != NULL){
		i++;
		printf("%d)\t%s",i,ProductoActual->nombre);
		printf("\t\t\t%.2f",ProductoActual->precio);
		printf("\t\t\t%d",ProductoActual->cantidad);
		if((ProductoActual->cantidad)<0)
		{
			printf("\tCompra\n");
		}
		else
		{
			printf("\tVenta\n");
		}
		resultado=resultado+((ProductoActual->precio)*(ProductoActual->cantidad));
		ProductoActual = ProductoActual->Productosig;

	}
	printf("\n\nLa Ganancia/Perdida total es de: %.2f",resultado);
	printf("\n\n");
	}
}

void Ticket(Producto *inicio){
	Producto *ProductoActual = inicio;
	FILE * archivo;
	archivo=fopen("Ticket","a");
	float resultado=0;
	int i=0;
	if(ProductoActual==NULL)
	{
		printf("No hay nada Registrado.\n");
	}
	else
	{

	fprintf(archivo,"\tNombre de Producto");
		fprintf(archivo,"\t\tPrecio");
		fprintf(archivo,"\t\tCantidad\n");
		fprintf(archivo,"\t-------------------------------------------------------------\n\n");
	while(ProductoActual != NULL){
		i++;
		fprintf(archivo,"%d)\t%s",i,ProductoActual->nombre);
		fprintf(archivo,"\t\t\t%.2f",ProductoActual->precio);
		fprintf(archivo,"\t\t\t%d",ProductoActual->cantidad);
		if((ProductoActual->cantidad)<0)
		{
			fprintf(archivo,"\tCompra\n");
		}
		else
		{
			fprintf(archivo,"\tVenta\n");
		}
		resultado=resultado+((ProductoActual->precio)*(ProductoActual->cantidad));
		ProductoActual = ProductoActual->Productosig;

	}
	fprintf(archivo,"\t\n-------------------------------------------------------------\n\n");
	fprintf(archivo,"\n\nLa Ganancia/Perdida total es de: %.2f",resultado);
	fprintf(archivo,"\t\n-------------------------------------------------------------\n\n");
	fprintf(archivo,"\n\n\n\n");
	}
	fclose(archivo);
}
void ReporteFinal(Producto *inicio,char *departamento){
	Producto *ProductoActual = inicio;
	FILE * archivo;
	char depa[20]={"Reporte"};
	archivo=fopen(strcat(depa,departamento),"w");
	float resultado=0;
	int i=0;
	if(ProductoActual==NULL)
	{
		printf("No hay nada Registrado.\n");
	}
	else
	{
	fprintf(archivo,"Departamento de %s\n\n",departamento);
	fprintf(archivo,"\tNombre de Producto");
		fprintf(archivo,"\t\tPrecio");
		fprintf(archivo,"\t\tCantidad\n");
		fprintf(archivo,"\t-------------------------------------------------------------\n\n");
	while(ProductoActual != NULL){
		i++;
		fprintf(archivo,"%d)\t%s",i,ProductoActual->nombre);
		fprintf(archivo,"\t\t\t%.2f",ProductoActual->precio);
		fprintf(archivo,"\t\t\t%d",ProductoActual->cantidad);
		if((ProductoActual->cantidad)<0)
		{
			fprintf(archivo,"\tCompra\n");
		}
		else
		{
			fprintf(archivo,"\tVenta\n");
		}
		resultado=resultado+((ProductoActual->precio)*(ProductoActual->cantidad));
		ProductoActual = ProductoActual->Productosig;

	}
	fprintf(archivo,"\t-------------------------------------------------------------\n\n");
	fprintf(archivo,"\n\nLa Ganancia/Perdida total es de: %.2f",resultado);
	}
	fclose(archivo);
}
