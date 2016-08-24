//Tarea Programada 1
#include <mpi.h>
#include <stdio.h>
#include <math.h>



int main(int argc,char **argv)
{
    /* n -> cantidad de procesos 
       myid -> identificador de cada proceso
       numorocs -> cantidad de procesos
       tp -> cantidad total de primos*/
    int n = 0, myid, numprocs, tp = 0;
    int P[n]; /*Vector P para contar los primos por filas */
    int M [n][n]; /*Creacion de la matriz M */
    int V [n]; /*Creacion de la matriz V */
    int B [n][n]; /*Creacion de la matriz B */
    
    int Q [n]; /*Creacion del vector Q, resultado de multiplicar M*V */
    
    /* startwtime hora inicial endwtime hora final*/
    double startwtime, endwtime;

    MPI_Init(&argc,&argv);
/*  Se inicia el trabajo con MPI */
           
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
/*  MPI almacena en numprocs el número total de procesos que se pusieron a correr */
 
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
/*  MPI almacena en myid la identificación del proceso actual */

   // fprintf(stdout,"Proceso %d de %d", myid, numprocs);
/*  Impresión por proceso con su id y número de procesos
    Comentada porque se usa para haccer pruebas */

	MPI_Barrier(MPI_COMM_WORLD); /* Barrera de sincronizacion. Hasta que todos los procesos lleguen aqui se puede seguir*/
    if (myid == 0)
    {
        bool multiplo = false;
        
        while (!multiplo)
	    {
    		 printf("Digite el tamanno de la matriz M y vector V (Debe ser mutiplo de la cantidad de procesos) \n");
    		 fflush(stdout);
             scanf("%d",&n);
             
             if((n>numorocs) && (n%numorocs == 0)) //se comprueba que n sean multiplo de los procesos
             {
                multiplo = true;                 
             }
	    }
	    /*Acá se realizan todas las tareas que le corresponden al proceso raíz*/
         /*Generacion aleatoria de los elementos de la matriz M y vector V*/
         for(int i=0, i<n,i++)
         {
            V[i]=rand() % 10;
            P[i] = 0;           // inicializacon del vector de primos en 0
            
            for(int j=0, j<n,j++)
            {
                M[i][j]=rand() % 10;
            }
         }
     
        startwtime = MPI_Wtime(); //Toma del tiempo inicial para saber cuanto se tarda en resolved los problemas
    }

        //ACÁ SE DEBE DE HACER LA REPARTICION DE LOS DATOS
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
/* Esta rutina funciona para el proceso raíz (en este caso el proceso 0) realmente como un broadcast, es decir le envía a 
TODOS los n procesos. Para los demás procesos (incluyendo el proceso raíz) funciona como un me espero a recibir n */  

//****     LO QUE LE CORRESPONDE A CADA PROCESO***//


// Calcular primos, ya que son numeros entre 0-9, serian los numeros: 2-3-5-7
   int evaluado;
  
  if(evaluado == 2 || evaluado == 3|| evaluado == 5 || evaluado == 7)
  {    
     p[filaActual]++; 
  }

 
 
 //Multiplicacion de Matriz por vector
  int q; //resultado parcial
  
  for(int i = 0; i < n; ++i ) //(i,j)esto es lo que hay q cambiar porque no se sabe como se reparte
  {    
       q = 0;
       for(int j = 0; j < n; ++j )
       {
            q += M[i][j]*P[j];
        }
     
        Q[i] = q;
    }
  
 //Oceano  se deben modificar los i,j por lo que correpsondan asi como la M y l B
 switch(myid)   
 {
    case 0: //quien tenga la fila 0
    
        switch(columna)
        {
            case 0:     B[i,j] = M[i,j] + M[i,j+1] + M[i+1,j]
            break;
            
            case n-1:   B[i,j] = M[i,j] + M[i,j -1] + M[i+1,j]
            break;
            
            default:    B[i,j] = M[i,j] + M[i,j -1] + M[i,j+1] + M[i+1,j]
        }    
    break;
    
    case n-1: //quien tenga la ultima fila
        switch(columna)
        {
            case 0:     B[i,j] = M[i,j] + M[i -1,j] + M[i,j+1]
            break;
            
            case n-1:   B[i,j] = M[i,j] + M[i,j -1] + M[i -1,j]
            break;
            
        }    
    break;
    
    default: 
        switch(columna)
        {
            case 0:     B[i,j] = M[i,j] + M[i -1,j] + M[i,j+1] + M[i+1,j];
            break;
            
            case n-1:   B[i,j] = M[i,j] + M[i,j -1] + M[i -1,j] + M[i+1,j]
                
            break;
            
            default:    B[i,j] = M[i,j] + M[i,j -1] + M[i -1,j] + M[i,j+1] + M[i+1,j]
        }    
 }
  
        //ACA SE DEBE DE RECIBIR LOS DATOS DE TODOS LOS PROCESOS
          MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
/* Esta rutina funciona así:
-para todos los procesos es el envío de su resultado final (mypi)
-para el proceso raíz (además de servír como el envío de su resultado final también) es un espere a que: 
    . todos los procesos envíen su resultado final, 
    . a que con ellos el MPI haga una suma (porque se especificó la función MPI_SUM) 
    . y a que le almacene esta suma en la variable pi   */ 


    if (myid == 0) /* lo que sigue entre llaves solo lo hace el proceso 0 */
    {
        
        for(int i = 0; i < n; ++i)  //Suma los primos en total de la matriz
		{
            tp += P[i];
		}
        
               
		endwtime = MPI_Wtime(); /* Se toma el tiempo actual, para luego calcular la duración del cálculo por 
		                        diferencia con el tiempo inicial*/
		printf("Tiempo = %f\n", endwtime-startwtime);
		for(int i = 0; i < n; ++i)
		{
            printf("Primos de la fila %d: %d\n",i,P[i]);
		}
		
		printf("Total de Primos en la Matriz: %d\n", tp);
		
		for(int i = 0; i < n; ++i)
		{
            printf("Resultado de multipicar la Matriz por un Vector: %d\n",Q[i]);
		}
		for(int i = 0; i < n; ++i)
		{
            for(int j=0, j<n,j++)
            {
                M[i][j]=rand() % 10;
            }
         }
		
		
		printf("Adriana Mora Calvo B24385\n Lisbeth Rojas Montero B15745");
		fflush( stdout );
	}
           
    MPI_Finalize();
    return 0;

