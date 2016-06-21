/*+------------------------------+------------------------------------+
|       Intel Code             |      AT&T Code                     |
+------------------------------+------------------------------------+
| mov     eax,1                |  movl    $1,%eax                   |   
| mov     ebx,0ffh             |  movl    $0xff,%ebx                |   
| int     80h                  |  int     $0x80                     |   
| mov     ebx, eax             |  movl    %eax, %ebx                |
| mov     eax,[ecx]            |  movl    (%ecx),%eax               |
| mov     eax,[ebx+3]          |  movl    3(%ebx),%eax              | 
| mov     eax,[ebx+20h]        |  movl    0x20(%ebx),%eax           |
| add     eax,[ebx+ecx*2h]     |  addl    (%ebx,%ecx,0x2),%eax      |
| lea     eax,[ebx+ecx]        |  leal    (%ebx,%ecx),%eax          |
| sub     eax,[ebx+ecx*4h-20h] |  subl    -0x20(%ebx,%ecx,0x4),%eax |
+------------------------------+------------------------------------+*/
#include "conio.h" 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void menu();
void suma();
void resta();
void multiplicacion();
void division();
void potenciacion();
void operacionSuma();
void operacionResta();
void operacionMultiplicacion();
void operacionDivision();
void operacionPotenciacion();
void separador(char str[], char s2[],char *ptr, char chartmp[]);
void resultado();
void capturaDatos(int opc);


int numA = 0, numB = 0, decr = 1;;

int main() {
	menu();
	return 0; 
}

void menu()
{
 	char opc;
 	system("CLS");
 	printf("\n\t\t\t Calculadora ASM\n\n");
 	
 	printf("\n 1) Sumar.");
 	printf("\n 2) Restar. ");
 	printf("\n 3) Multiplicar.");
 	printf("\n 4) Dividir.");
 	printf("\n 5) Potenciacion.");
 	printf("\n 6) Salir.");
 	
 	printf("\n\n Escoja una opcion: ");
 	opc = getche();
 	switch(opc)
 	{
	 		   case 49:
			   		suma();
			   		break;
		   	   case 50:
			   		resta();
					break;
 			   case 51:
			   		multiplicacion();
			 	  	break;
	 	  	   case 52:
			   		division();
				  	break;
			   case 53:
			   		potenciacion();
				   	break;
   	           case 54:
				    exit(0);
    		   default:
					system("CLS");
					printf("\n\t\t\t  Opcion invalida.\n\n\n Favor ingrese un numero establecido.\n\n Presione una tecla para ir al menu: ");
					getch();
	}
	menu();
}

void suma()
{
 	fflush(stdin);
    fflush(stdout);
 	system("CLS");
 	printf("\n Operacion de suma.\n\n");
 	printf(" Ingrese la operacion(a+b): ");
 	capturaDatos(1); 	
}

void resta()
{
 	fflush(stdin);
    fflush(stdout);
 	system("CLS");
 	printf("\n Operacion de resta.\n\n");
 	printf(" Ingrese la operacion(a-b): ");
 	capturaDatos(2);
}
void multiplicacion()
{
 	fflush(stdin);
    fflush(stdout);
 	system("CLS");
 	printf("\n Operacion de multiplicacion.\n\n");
 	printf(" Ingrese la operacion(a*b): ");
 	capturaDatos(3);
}
void division()
{
 	fflush(stdin);
    fflush(stdout);
 	system("CLS");
 	printf("\n Operacion de division.\n\n");
 	printf(" Ingrese la operacion(a/b): ");
 	capturaDatos(4);
}
void potenciacion()
{
 	fflush(stdin);
    fflush(stdout);
 	system("CLS");
 	printf("\n Operacion de potenciacion.\n\n");
 	printf(" Ingrese la operacion(a^b): ");
 	capturaDatos(5);
}

void operacionSuma() {
	 //Uso notación AT&T
  __asm("movl _numA, %ebx ") ;  // Muevo lo que hay en la variable global al acumulador b
  __asm("movl _numB, %eax") ;   // Se lee de derecha a izquierda
  __asm("addl %ebx,%eax");      // Adiciono lo que hay en el registro ebx en eax
  __asm("movl %eax, _numA") ;   // Muevo el contenido de lo que hay en el registro a la variable global
} 

void operacionResta()
{
	__asm("movl _numA, %eax");
	__asm("movl _numB, %ebx");
	__asm("sub %ebx, %eax");
	__asm("movl %eax, _numA");
}
void operacionMultiplicacion()
{
	__asm("movl _numA, %eax");
	__asm("movl _numB, %ebx");
	__asm("imull %ebx"); // Multiplica ebx con eax y queda en memoria el resultado almacenado en eax
	__asm("movl %eax, _numA");
}
void operacionDivision()
{
	__asm("movl _numA, %eax");
	__asm("movl _numB, %ebx");
	__asm("cltd"); //  Se usa para el signo por lo que se guarda en el registro Data, para GAS en 32 bits es necesario esto
	__asm("idivl %ebx");
	__asm("movl %eax, _numA");
}
void operacionPotenciacion()
{
    
	decr = numB - 1; // Inicializo la condición del loop en un decremento
	__asm("movl _numA, %eax");// Muevo al registro lo que hay en numA
	__asm("movl _numA, %ebx");// Hago lo mismo para no alterar el resultado
	__asm("movl _decr, %ecx");// Asigno la condición que se evalúa hasta que sea cero
	__asm("CICLO_PARA_ELEVAR:"); // Hago el label del loop
	__asm("imull %ebx, %eax"); // Multiplico el registro ebx con eax
	__asm("loop CICLO_PARA_ELEVAR"); // Itero hasta que el registro ecx sea cero
	__asm("movl %eax, _numA"); // Muevo el resultado a la variable para imprimirlo
}

void capturaDatos(int opc)
{
	
 	char str[MAX_PATH], chartmp[MAX_PATH];
 	
 	char *ptr;
 	
 	 fgets(str,MAX_PATH+1,stdin);
 	 fflush(stdin);
     fflush(stdout);
     if(strlen(str)>3)
     {
		if(opc==1)
		{
			char s2[4] = "+\n\t";
			separador(str, s2, ptr, chartmp);
		}
		else if(opc==2)
		{
			char s2[4] = "-\n\t";
		 	separador(str, s2, ptr, chartmp);
		}
		else if(opc==3)
		{
			char s2[4] = "*\n\t";
			separador(str, s2, ptr, chartmp);
		}
		else if(opc==4)
		{
			char s2[4] = "/\n\t";
			separador(str, s2, ptr, chartmp);
		}
		else if(opc==5)
		{
			char s2[4] = "^\n\t";
			separador(str, s2, ptr, chartmp);
		}
	 	
	 	
	    switch(opc)
	    {
		   case 1:
			 	operacionSuma();
			 	break;
			case 2:
				 operacionResta();
				 break;
	 		case 3:
			 	 operacionMultiplicacion();
			 	 break;
	  		case 4:
			  	 operacionDivision();
			  	 break;
	   		case 5:
			   	 operacionPotenciacion();
			   	 break;
			default:
				 system("CLS");
				 printf("\n Ocurrio un evento inesperado, se va a cerrar este programa, presione una tecla y vuelva a abrir: ");
				 getch();
				 exit(0);
   		}

		resultado();
	 }
	 else
	 {
		switch(opc)
	    {
		   case 1:
			 	suma();
			 	break;
			case 2:
				 resta();
				 break;
	 		case 3:
			 	 multiplicacion();
			 	 break;
	  		case 4:
			  	 division();
			  	 break;
	   		case 5:
			   	 potenciacion();
			   	 break;
			default:
				 system("CLS");
				 printf("\n Ocurrio un evento inesperado, se va a cerrar este programa, presione una tecla y vuelva a abrir: ");
				 getch();
				 exit(0);
   		}
	 }
}
void separador(char str[], char s2[],char *ptr, char chartmp[])
{		
	ptr = strtok( str, s2 );
	strcpy(chartmp,ptr); 	
 	if(isdigit(chartmp[0]))
 	{
	 	numA = atoi(chartmp);
	}
	
 	while( (ptr = strtok( NULL, s2 )) != NULL )    // Posteriores llamadas
 	{
	     strcpy(chartmp,ptr); 	
	 	 if(isdigit(chartmp[0]))
	 	 {
		 	numB = atoi(chartmp);
		 }
	     break;
    }
}
void resultado()
{
 	 printf("\n El resultado es: %d", numA);
	 printf("\n\n Presione una tecla para ir al menu: ");
	 getch(); 
}
