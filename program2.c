#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<libxml/parser.h>
#include<libxml/tree.h>
#include<string.h>
#include<math.h>

#ifdef LIBXML_TREE_ENABLED

//typedef float ***Matrix;
#define PI 3.14159265

typedef struct
{
  int type;//0-brak, 1-step, 2-linear, 3-sine
  float v;
  float c;
  float param1;
  float param2;
  float param3;
}
ResourcesFunctionStruct;



typedef struct
{
  float *fen;
}
Fenotypestruct;


typedef struct
{
	int x[26];//26 maksymalna liczba sąsiadów
	int y[26];
	int z[26];
	//float Fitness[6];
	//Fenotypestruct Population[6];
	int number;//rzeczywista liczba niepustych sąsiadów
}
Neighbourhoodstruct;


void sort(Neighbourhoodstruct *neighbours, Fenotypestruct ***Population, float ***Fitness, int param, unsigned int seed) 
{
    int j,i,min;

    for(i=0;i<param;i++)//zmieniłem żeby sortował tyle ile trzeba
    {
      min=i;
        for(j=i+1;j<(*neighbours).number;j++)
        {
	  //usunąłem lub bo w funkcja FindNeighbourhood nie zwraca pustych komórek
            if((Fitness[(*neighbours).x[j]][(*neighbours).y[j]][(*neighbours).z[j]] >Fitness[(*neighbours).x[min]][(*neighbours).y[min]][(*neighbours).z[min]]&&Population[(*neighbours).x[j]][(*neighbours).y[j]][(*neighbours).z[j]].fen[0]>=0))
            {
	      min=j;  
            }
            else if ((Fitness[(*neighbours).x[j]][(*neighbours).y[j]][(*neighbours).z[j]] ==Fitness[(*neighbours).x[min]][(*neighbours).y[min]][(*neighbours).z[min]]&&Population[(*neighbours).x[j]][(*neighbours).y[j]][(*neighbours).z[j]].fen[0]>=0))
	    {
	      if((rand_r(&seed)/(float)RAND_MAX)>0.5)
	      {
		min=j;  
	      }
	    }
        }
        int temp = (*neighbours).x[min];
        (*neighbours).x[min] =(*neighbours).x[i];
        (*neighbours).x[i] = temp;
	temp = (*neighbours).y[min];
        (*neighbours).y[min] =(*neighbours).y[i];
        (*neighbours).y[i] = temp;
	temp = (*neighbours).z[min];
        (*neighbours).z[min] =(*neighbours).z[i];
        (*neighbours).z[i] = temp;
	    //printf("i: %d j: %d\n",i,j);
	    //ShowNeighbourhood((*neighbours));
    }
}



Neighbourhoodstruct FindNeighbourhood(int i,int j, int k, int size[3], int neighbourmethod)
{
  int n=0;
  Neighbourhoodstruct output;
  
    

  
  
  
    output.x[n]=(i+1)%size[0];
    output.y[n]=j;
    output.z[n]=k;
    n++;
    
        output.x[n]=(size[0]+i-1)%size[0];
    output.y[n]=j;
    output.z[n]=k;
    n++;
    
  	
  if(size[1]>1)//2D lub 3D
  {
    //sąsiedztwo von Neumanna
    output.x[n]=i;
    output.y[n]=(size[1]+j-1)%size[1];
    output.z[n]=k;
    n++;
  
    output.x[n]=i;
    output.y[n]=(j+1)%size[1];
    output.z[n]=k;
    n++;
    
  
    
    //sąsiedztwo Moore'a - dodać if'a, klamra już jest
  if(neighbourmethod)
    {
    output.x[n]=(size[0]+i-1)%size[0];
    output.y[n]=(size[1]+j-1)%size[1];
    output.z[n]=k;
    n++;
     
    output.x[n]=(size[0]+i-1)%size[0];
    output.y[n]=(j+1)%size[1];
    output.z[n]=k;    
    n++;
    
    output.x[n]=(i+1)%size[0];
    output.y[n]=(size[1]+j-1)%size[1];
    output.z[n]=k;
    n++;
      
    output.x[n]=(i+1)%size[0];
    output.y[n]=(j+1)%size[1];
    output.z[n]=k; 
    n++;
    }
  
  
  if(size[2]>1)//3D
  {
    //von Neumanna
  
  
    output.x[n]=i;
    output.y[n]=j;
    output.z[n]=(size[2]+k-1)%size[2];
    n++;
    
    output.x[n]=i;
    output.y[n]=j;
    output.z[n]=(k+1)%size[2];
    n++;
  
  
  //Moore'a - dać if'a
    if(neighbourmethod)
    {
    
    //dla k=size[2]+k-1)%size[2]
    output.x[n]=(size[0]+i-1)%size[0];
    output.y[n]=j;
    output.z[n]=(size[2]+k-1)%size[2];
    n++;
    
    output.x[n]=(i+1)%size[0];
    output.y[n]=j;
    output.z[n]=(size[2]+k-1)%size[2];
    n++;
     
    output.x[n]=i;
    output.y[n]=(size[1]+j-1)%size[1];
    output.z[n]=(size[2]+k-1)%size[2];
    n++;
  
    output.x[n]=i;
    output.y[n]=(j+1)%size[1];
    output.z[n]=(size[2]+k-1)%size[2];
    n++;
     
    output.x[n]=(size[0]+i-1)%size[0];
    output.y[n]=(size[1]+j-1)%size[1];
    output.z[n]=(size[2]+k-1)%size[2];
    n++;
    
    output.x[n]=(size[0]+i-1)%size[0];
    output.y[n]=(j+1)%size[1];
    output.z[n]=(size[2]+k-1)%size[2];    
    n++;
    
    output.x[n]=(i+1)%size[0];
    output.y[n]=(size[1]+j-1)%size[1];
    output.z[n]=(size[2]+k-1)%size[2];        
    n++;
    
    output.x[n]=(i+1)%size[0];
    output.y[n]=(j+1)%size[1];
    output.z[n]=(size[2]+k-1)%size[2];  
    n++;
  
  //dla k=(k+1)%size[2]
    output.x[n]=(size[0]+i-1)%size[0];
    output.y[n]=j;
    output.z[n]=(k+1)%size[2];
    n++;
      
    output.x[n]=(i+1)%size[0];
    output.y[n]=j;
    output.z[n]=(k+1)%size[2];
    n++;
     
    output.x[n]=i;
    output.y[n]=(size[1]+j-1)%size[1];
    output.z[n]=(k+1)%size[2];
    n++;
      
    output.x[n]=i;
    output.y[n]=(j+1)%size[1];
    output.z[n]=(k+1)%size[2];
    n++;
        
    output.x[n]=(size[0]+i-1)%size[0];
    output.y[n]=(size[1]+j-1)%size[1];
    output.z[n]=(k+1)%size[2];
    n++;
    
    output.x[n]=(size[0]+i-1)%size[0];
    output.y[n]=(j+1)%size[1];
    output.z[n]=(k+1)%size[2];    
    n++;
    
    output.x[n]=(i+1)%size[0];
    output.y[n]=(size[1]+j-1)%size[1];
    output.z[n]=(k+1)%size[2];        
    n++;
    
    output.x[n]=(i+1)%size[0];
    output.y[n]=(j+1)%size[1];
    output.z[n]=(k+1)%size[2];  
    n++;
  //
    }
  
  }
  }



  output.number=n;
  
  return output;
}

float getR(float H, float param1)
{
  float r;
  if(param1==1.0)
  {
    r=-H+1;
  }
  else if(param1==2.0)
  {
    r=-(H-1)*(H+1);
  }
  else if(param1==3.0)
  {
    r=(2/(H+1))-1;
  }
  else if(param1==4.0)
  {
    r=cos(H*PI*0.5);
  }
  return 1-r;
}

void ChangePayoffMatrix(float *****tab,ResourcesFunctionStruct resources,int g, Fenotypestruct ***Population, int size[3], int neighbourmethod)
{
  float r;
  int i,j,k,n;
  float suma=0.0;
  float H;
  Neighbourhoodstruct neighbours;
    
  if(resources.type==0)
  {
    //do nothing
  }
  else if(resources.type==5)
  {
    for(i=0;i<size[0];i++)
    {
      for(j=0;j<size[1];j++)
      {
	for(k=0;k<size[2];k++)
	{
	  neighbours=FindNeighbourhood(i,j,k,size,neighbourmethod);
	  suma=0.0;
	  for (n=0;n<neighbours.number;n++)
	  {
	    suma+=Population[neighbours.x[n]][neighbours.y[n]][neighbours.z[n]].fen[0];
	  }
	  H=suma/neighbours.number;
	  r=getR(H,resources.param1);
	  r=(r>1.0)?1.0:(r<0.0)?0.0:r;
	  
	  tab[i][j][k][0][0]=resources.v-resources.c;
	  tab[i][j][k][0][1]=2*resources.v;
	  tab[i][j][k][1][0]=r*0.5*resources.v;
	  tab[i][j][k][1][1]=(1.0+r)*resources.v;
	}
      }
    }
  }
  else
  {
    if(resources.type==1)
    {
      r=(g<((int)resources.param3))?resources.param1:resources.param2;
      //return tab;
    }
    if(resources.type==2)
    {
      r=resources.param1*g+resources.param2;
    }
    if(resources.type==3)
    {
      r=resources.param1*sin((2.0*PI*g)/resources.param3)+resources.param2; 
    }
    if(resources.type==4)
    {
      for(i=0;i<size[0];i++)
      {
	for(j=0;j<size[1];j++)
	{
	  for(k=0;k<size[2];k++)
	  {
	    suma+=Population[i][j][k].fen[0];
	  }
	}
      }
      H=suma/(size[0]*size[1]*size[2]);
      r=getR(H,resources.param1);
    }
    
    r=(r>1.0)?1.0:(r<0.0)?0.0:r;
    //printf("r=%f\n",r);
    
    tab[0][0][0][0][0]=resources.v-resources.c;
    tab[0][0][0][0][1]=2*resources.v;
    tab[0][0][0][1][0]=r*0.5*resources.v;
    tab[0][0][0][1][1]=(1.0+r)*resources.v;
    
  }
    
}

float Payoff(float i,float j)
{
  float b=2.0,c=1.0,d=2.0,e=0.0;
  float table[2][2];
  table[1][1]=1+b+e-c;//C-C
  table[1][0]=1+b-c;//C-D
  table[0][1]=1+d;//D-C
  table[0][0]=1;//D-D
  //printf("ok2 i:%d j:%d\n",(int)i,(int)j);
  return table[(int)i][(int)j];
}

void Show(Fenotypestruct ***population, int size[3], int fenotypes)
{
  int i,j,k,l;
   for(i=0;i<size[0];i++)
   {
     for(j=0;j<size[1];j++)
     {
       for(k=0;k<size[2];k++)
       {
	 for(l=0;l<fenotypes;l++)
	 {
	   printf("%f/",population[i][j][k].fen[l]);
	 }
	 printf("\t");
       }
       printf("\n");
     }
     printf("\n");
   }
   printf("\n");
}

void ShowFitness(float ***Fitness, int size[3])
{
  int i,j,k,l;
   for(i=0;i<size[0];i++)
   {
     for(j=0;j<size[1];j++)
     {
       for(k=0;k<size[2];k++)
       {
	 
	   printf("%f",Fitness[i][j][k]);
	 
	 printf("\t");
       }
       printf("\n");
     }
     printf("\n");
   }
   printf("\n");
}




void ShowChosenCells(int ***Fitness, int size[3])
{
  int i,j,k,l;
   for(i=0;i<size[0];i++)
   {
     for(j=0;j<size[1];j++)
     {
       for(k=0;k<size[2];k++)
       {
	 
	   printf("%d",Fitness[i][j][k]);
	 
	 printf("\t");
       }
       printf("\n");
     }
     printf("\n");
   }
   printf("\n");
}



void FillArray(int ***array, int size[3], int value)
{
  int i,j,k; 
#pragma omp parallel for private(i,j,k) shared(size,value,array)
  for (i=0;i<size[0];i++)
  {
    for(j=0;j<size[1];j++)
    {
      for(k=0;k<size[2];k++)
      {
	array[i][j][k]=value;
      }
    }
  }
    
}


void InitialisePopulation(Fenotypestruct ***Population, int size[3], int fenotypes, int MSEG, int initPopulation, char *initPopulationPath)
{
  int i,j,k,l;
  float suma=0;
  int random;
  unsigned int seed;
 // srand(time(NULL));//można odkomentować, jeśli wyniki nie mają być takie same przy każdym uruchomieniu
  random=rand()+1;
  float *buffer;//na pointer
  
FILE *ptr;


if(initPopulation)
{
buffer=malloc(size[0]*size[1]*size[2]*fenotypes*sizeof(float));
//int i=0;

ptr = fopen(initPopulationPath,"rb");  // r for read, b for binary
fread(buffer,size[0]*size[1]*size[2]*fenotypes*sizeof(float),1,ptr); // read 10 bytes to our buffer
}
//printf("----%d-----",size[0]*size[1]*size[2]*fenotypes*sizeof(float));
	  //to dodałem - odczyt z pliku
	  //Population[i][j][k].fen[l]=buffer[i*size[1]*size[2]*fenotypes+j*size[2]*fenotypes+fenotypes*k+l];
  
  #pragma omp parallel shared(Population, fenotypes, size,random) private(i, j, k,l, suma, seed)
  {  
  seed = random+omp_get_thread_num();
  #pragma omp for
  for(i=0;i<size[0];i++)
  {
    for(j=0;j<size[1];j++)
    {
      for(k=0;k<size[2];k++)
      {
	if(initPopulation)
	{
	  	for(l=0;l<fenotypes;l++)
	{
	  Population[i][j][k].fen[l]=buffer[i*size[1]*size[2]*fenotypes+j*size[2]*fenotypes+fenotypes*k+l];
	}
	}
	//opcja na MSEG i SEGT - bez odczytu pliku
	else
	{
	  if(MSEG)
	{
	suma=0;
	for(l=0;l<fenotypes;l++)
	{
	  Population[i][j][k].fen[l]=(rand_r(&seed)/(float)RAND_MAX);////UWAGA NA RANDA!!!
	  suma=suma+Population[i][j][k].fen[l];
	}
	for(l=0;l<fenotypes;l++)
	{
	  Population[i][j][k].fen[l]=Population[i][j][k].fen[l]/suma;
	}
	}
	
	else
	{
	  for(l=0;l<fenotypes;l++)
	  {
	    Population[i][j][k].fen[l]=0.0;
	  }
	  Population[i][j][k].fen[rand_r(&seed)%fenotypes]=1.0;
	}
	}
      }
    }
  }
  }
}

//liczy fitness komórki o danej współrzędnej
void CalculatePayoff(Fenotypestruct ***Population,float ***Fitness,int x,int y, int z, int size[3],int fenotypes,float **tab,int neighbourmethod)
{
  int n,l,m;
  Neighbourhoodstruct neighbours;
  Fitness[x][y][z]=0;
  
  //printf("thread = %d i=%d j%d k=%d\n", tid,x,y,z);
  
	neighbours=FindNeighbourhood(x,y,z,size,neighbourmethod);
	for (n=0;n<neighbours.number;n++)
	{
	  for(l=0;l<fenotypes;l++)
	  {
	    for (m=0;m<fenotypes;m++)
	    {//n to numer sąsiada, a neighbours[n].x y z to jego współrzędne
	      //przelatujemy przez wszystkie fenotypy komórki, mnożymy je przez wszystkie fenotypy sąsiadów i przez tablicę z tabeli korzyści
	      Fitness[x][y][z]=Fitness[x][y][z]+Population[x][y][z].fen[l]*Population[neighbours.x[n]][neighbours.y[n]][neighbours.z[n]].fen[m]*tab[l][m];
	    }
	  }
	}
}


void PayoffUpdate(Fenotypestruct ***Population,float ***Fitness, int size[3], float *****tab, int fenotypes, int neighbourmethod)
{
  
  int i,j,k;
  //pomyśleć nad przerobieniem tego fora na to żeby zaczynał od 1 i osobno robić krańcowe pozycje
  #pragma omp parallel for shared(Population, Fitness,size,fenotypes) private(i, j, k)
  for(i=0;i<size[0];i++)
  {
    for(j=0;j<size[1];j++)
    {
      for(k=0;k<size[2];k++)
      {
	CalculatePayoff(Population,Fitness,i,j,k,size,fenotypes,tab[i][j][k],neighbourmethod);
	
      }
    }
  }
}

void Mortality(int ***ChosenCells, float MortalityProbability, int size[3], int updating)//ok
{
  int i,j,k;
  int x,y,z,sum=0;
  int max=size[0]*size[1]*size[2];
  int random;
  int n;
  unsigned int seed;
  
 ////////Usunięcie jednego elementu - asynchroniczna metoda/////////////////
 if(updating==0)
 {
  ChosenCells[(rand()%size[0])][(rand()%size[1])][(rand()%size[2])]=1;
 }
  if(updating==1)
  {
  
  ////////Usunięcie MortalityProbability wszystkich komórek - półsynchroniczna metoda//
  //n=(int)(MortalityProbability*max);
  //printf("n:%d max:%d\n",n,max);
  
  random=rand()+1;//różny początek dla kolejnych iteracji
  
  
  //można porównać jakby na czas wpływa gdyby zrobić fora po wszystkich komórkach i losować liczbę od 0 do 1 i sprawdzać czy liczba>MortalityProbability
  
  /*
  #pragma omp parallel private(seed,i,x,y,z) shared(ChosenCells,n) 
  {
    seed = random + omp_get_thread_num();
  #pragma omp for
  for (i=0;i<=n;i++)
  {
     //trzeba losować tak długo aż wylosuje komórkę, która nie została jeszcze usunięta
    do
    {
    x=rand_r(&seed)%size[0];
    y=rand_r(&seed)%size[1];
    z=rand_r(&seed)%size[2];
    }while(ChosenCells[x][y][z]==1);
    ///////////TU MÓGŁ INNY RDZEŃ WYLOSOWAĆ TO SAMO ZANIM NASTĄPIŁA ZMIANA
    ChosenCells[x][y][z]=1;
  }
  }
  //printf("\n");
  */
  #pragma omp parallel private(seed,i,j,k) shared(ChosenCells,MortalityProbability) 
  {
    seed = random + omp_get_thread_num();
  #pragma omp for
  for (i=0;i<size[0];i++)
  {
    for(j=0;j<size[1];j++)
    {
      for(k=0;k<size[2];k++)
      {
	if((rand_r(&seed)/(float)RAND_MAX)>MortalityProbability)
	{
	  ChosenCells[i][j][k]=0;
	}
	else
	{
	  ChosenCells[i][j][k]=1;
	}
	
      }
    }

  }
  }
  }
  
  
  //////////usunięcie wszystkich komórek - metoda synchroniczna ///////////////
  if(updating==2)
  {
  FillArray(ChosenCells,size,1);
  }
}

void CompetitiveReproduction(Fenotypestruct ***Population,Fenotypestruct ***NewPopulation, float ***Fitness, int ***ChosenCells, int size[3], int fenotypes, int neighbourmethod, int nrmethod, int param)
{
  Neighbourhoodstruct neighbours;
  int i,j,k,l,n,ok,max,random1, abc;
  float temp, temp2, random;
  //Fenotypestruct newPopulation;
  unsigned int seed;
  
  //int nrmethod=2;
  //int param=1;//ile do średniej - przy method=1 param=1
  random1=rand()+1;
  
  
  #pragma omp parallel shared(Population, NewPopulation, Fitness, ChosenCells, size, fenotypes, nrmethod, param, random1, neighbourmethod) private(seed,i, j, k, l, n,max, neighbours,temp,temp2,ok,random)
  {
    seed=random1+omp_get_thread_num();
  #pragma omp for
  for(i=0;i<size[0];i++)
   {
     for(j=0;j<size[1];j++)
     {
       for(k=0;k<size[2];k++)
       {
	 if (ChosenCells[i][j][k])//jeśli wybrana komórka ma być zastąpiona
	 {
	   ChosenCells[i][j][k]=0;
	   temp=0.0;
	   neighbours=FindNeighbourhood(i,j,k,size, neighbourmethod);

	   ////////////metoda 1, 2//////////////////
	   //param - ile komórek wziąć do średniej
	   // 
	   if(nrmethod)
	   {
	    sort(&neighbours,Population,Fitness,param,seed);
	   //wyzerowanie NewPopulation
	   for (l=0;l<fenotypes;l++)
	   {
	     //printf("%d\n",l);
	     NewPopulation[i][j][k].fen[l]=0;
	   }
	   
	   temp=0.0;
	   temp2=0.0;//równoważenie wag - tak żeby nie były ujemne
	   if(Fitness[neighbours.x[param-1]][neighbours.y[param-1]][neighbours.z[param-1]]<=0)
	   {
	     temp2=-Fitness[neighbours.x[param-1]][neighbours.y[param-1]][neighbours.z[param-1]];
	     if(Fitness[neighbours.x[0]][neighbours.y[0]][neighbours.z[0]]+temp2<=0)
	     {
	       temp2+=1.0;//wszystkie wagi są zerami więc dajemy wszystkie na 1 (bo są tak samo istotne)
	     }
	   }
	   for (n=0;n<param;n++)
	   {
	     //printf("OK1\n");
	     //ok=1;
	    
	     for (l=0;l<fenotypes;l++)
	     {
	       //sumowanie z odpowiednią wagą
	     NewPopulation[i][j][k].fen[l]=NewPopulation[i][j][k].fen[l]+(Population[neighbours.x[n]][neighbours.y[n]][neighbours.z[n]].fen[l]*(Fitness[neighbours.x[n]][neighbours.y[n]][neighbours.z[n]]+temp2));
	     }
	     //suma wag
	     temp=temp+Fitness[neighbours.x[n]][neighbours.y[n]][neighbours.z[n]]+temp2;
	   }
	   
	   
	   for (l=0;l<fenotypes;l++)
	   {
	     //Obliczenie średniej ważonej
	     NewPopulation[i][j][k].fen[l]=NewPopulation[i][j][k].fen[l]/temp;
	   }
	   
	   
	   }
	   else//probabilistyczna
	   {
	   for (n=0;n<neighbours.number;n++)
	   {
	     temp=temp+Fitness[neighbours.x[n]][neighbours.y[n]][neighbours.z[n]];
	     //printf("i=%d,j=%d,k=%d,n=%d,temp=%f\n",i,j,k,n,temp);
	   }
	   random=rand_r(&seed)/(float)RAND_MAX;
	   temp2=0.0;// do sumowania fitnessów już sprawdzonych sąsiadów
	   for (n=0;n<neighbours.number;n++)
	   {
	     temp2=temp2+Fitness[neighbours.x[n]][neighbours.y[n]][neighbours.z[n]];
	     if(random<(temp2/temp))
	     {
	       for(l=0;l<fenotypes;l++)
	       {
		NewPopulation[i][j][k].fen[l]=Population[neighbours.x[n]][neighbours.y[n]][neighbours.z[n]].fen[l];
	       }
	       break;
	     }
	   }
	   }

	 }
	 else
	 {
	   for (l=0;l<fenotypes;l++)
	   {
	     //Przepisanie wartości do nowej populacji
	     NewPopulation[i][j][k].fen[l]=Population[i][j][k].fen[l];
	   }
	 }
       }
     }
  }
  }
  
}

void GetInformationFromXml(xmlNode *a_node, int *dimension, int *size, int *cores, int *maxgeneration, float *mortality, float ***tab, int *rows, int *columns, int *ok, int *neighbourmethod, int *reproductionmethod, int *reproductionparam, int *updating, int *MSEG, int *save, char *savepath, int *initPopulation, char *initPopulationPath, ResourcesFunctionStruct *resources)
{
  xmlNode *cur_node = NULL;
  xmlChar *content = NULL;
  xmlChar *prop = NULL;
  int temp, i=0;
  char korektor[] = " ,";
  xmlChar *schowek;
  float tempfloat=0.0;
  //void *tmp;
  
  for (cur_node = a_node; cur_node; cur_node = cur_node->next)
  {
    //wejście poziom niżej 
    if (xmlStrEqual(cur_node->name, (const xmlChar*)"data")  ||xmlStrEqual(cur_node->name, (const xmlChar*)"inputs")||xmlStrEqual(cur_node->name, (const xmlChar*)"outputs")||xmlStrEqual(cur_node->name, (const xmlChar*)"payoff")) 
    {
      GetInformationFromXml(cur_node->children, dimension, size, cores, maxgeneration, mortality, tab, rows, columns,ok,neighbourmethod,reproductionmethod,reproductionparam,updating,MSEG,save,savepath,initPopulation,initPopulationPath,resources);
    }
    else
    {
      if(cur_node->type == XML_ELEMENT_NODE)
      {
      
	content=xmlNodeGetContent(cur_node);
	//printf("%s\n",cur_node->name);
	if(xmlStrEqual(cur_node->name, "dimension"))
	{
	  *dimension=atoi(content);
	  xmlFree(content);
	  continue;
	}
	if(xmlStrEqual(cur_node->name, "size"))
	{
	  *size=atoi(content);
	  xmlFree(content);
	  continue;
	}
	if(xmlStrEqual(cur_node->name, "cores"))
	{
	  *cores=atoi(content);
	  xmlFree(content);
	  continue;
	}
	if(xmlStrEqual(cur_node->name, "maxgeneration"))
	{
	  *maxgeneration=atoi(content);
	  xmlFree(content);
	  continue;
	}
	if(xmlStrEqual(cur_node->name, "mortality"))
	{
	  *mortality=atof(content);
	  xmlFree(content);
	  continue;
	}
	if(xmlStrEqual(cur_node->name, "neighbourhood"))
	{
	  *neighbourmethod=atoi(content);
	  xmlFree(content);
	  continue;
	}
	if(xmlStrEqual(cur_node->name, "reproduction"))
	{
	  *reproductionmethod=atoi(content);
	  xmlFree(content);
	  continue;
	}
	if(xmlStrEqual(cur_node->name, "param"))
	{
	  *reproductionparam=atoi(content);
	  xmlFree(content);
	  continue;
	}
	if(xmlStrEqual(cur_node->name, "updating"))
	{
	  *updating=atoi(content);
	  xmlFree(content);
	  continue;
	}
	if(xmlStrEqual(cur_node->name, "MSEG"))
	{
	  *MSEG=atoi(content);
	  xmlFree(content);
	  continue;
	}
	if(xmlStrEqual(cur_node->name, "init-population"))
	{
	  strcpy(initPopulationPath, content);
	  *initPopulation=1;
	  xmlFree(content);
	  continue;
	}
	if(xmlStrEqual(cur_node->name, "save-path"))
	{
	  //savepath=(char*)content;
	  strcpy(savepath, content);
	  *save=1;
	  xmlFree(content);
	  continue;
	}
	if(xmlStrEqual(cur_node->name, "resources"))
	{
	  if(xmlStrEqual(content,"step"))
	  {
	    resources->type=1;
	  }
	  else if(xmlStrEqual(content,"linear"))
	  {
	    resources->type=2; 
	  }
	  else if(xmlStrEqual(content,"sine"))
	  {
	    resources->type=3;
	  }
	  else if(xmlStrEqual(content,"globalH"))
	  {
	    resources->type=4;
	  }
	  else if(xmlStrEqual(content,"localH"))
	  {
	    resources->type=5;
	  }
	  else
	  {
	    resources->type=0;
	    printf("Błędna nazwa funkcji - tablica wzięta z payoffMatrix \n");
	    xmlFree(content);
	    continue;
	  }
	  
	  prop=xmlGetProp(cur_node, "param1");
	  tempfloat=atof(prop);
	  resources->param1=tempfloat;
	  xmlFree(prop);
	   
	  if(resources->type==1||resources->type==2||resources->type==3)
	  {
	    prop=xmlGetProp(cur_node, "param2");
	    tempfloat=atof(prop);
	    resources->param2=tempfloat;
	    xmlFree(prop);
	  }
	  
	  if(resources->type==1||resources->type==3)
	  {
	    prop=xmlGetProp(cur_node, "param3");
	    tempfloat=atof(prop);
	    resources->param3=tempfloat;
	    xmlFree(prop);
	  }
	  
	  prop=xmlGetProp(cur_node, "v");
	  tempfloat=atof(prop);
	  resources->v=tempfloat;
	  xmlFree(prop);
	  
	  prop=xmlGetProp(cur_node, "c");
	  tempfloat=atof(prop);
	  resources->c=tempfloat;
	  xmlFree(prop);
	  
	  *tab=realloc(*tab,2*sizeof(**tab));
	  (*tab)[0]=malloc(2*sizeof(***tab));
	  (*tab)[1]=malloc(2*sizeof(***tab));
	  *rows=2;
	  *columns=2;
	  xmlFree(content);
	  continue;
	}
	if(xmlStrEqual(cur_node->name, "row"))
	{
	  if(resources->type==0)
	  {
	    prop=xmlGetProp(cur_node, "r");
	    temp=atoi(prop);
	    printf("temp=%d\n",temp);
	    if (temp+1>*rows)
	    {
	      *tab=realloc(*tab,(temp+1)*sizeof(**tab));
	      //tab=tmp;
	      *rows=temp+1;
	      /*
	      if( (tmp = realloc(tab,(temp+1)*sizeof(*tab))) == NULL )
	      {
		//Jeśli brakuje pamięci to coś tu trzeba zrobić!!!
	      }
	      else
	      {
	      tab=tmp;
	      *rows=temp+1;
	      }*/
	    }
	    
	    
	    (*tab)[temp]=malloc(sizeof(***tab));
	    schowek = strtok( content, korektor );
	    //printf("0 %s\n",schowek);
	    for (i=0;schowek != NULL;i++)
	    {
	      //printf("1 %s\n",schowek);
	      (*tab)[temp] = realloc((*tab)[temp],(i+1)*sizeof(***tab));
	      //printf("2 %s\n",schowek);
	      (*tab)[temp][i]=atof(schowek);
	      //printf("3 %s\n",schowek);
	      schowek=strtok(NULL,korektor);
	      /*
	      if( (tmp = realloc(tab[temp],(i+1)*sizeof(**tab))) == NULL )
	      {
		//Jeśli brakuje pamięci to coś tu trzeba zrobić!!!
	      }
	      else
	      {
	      tab[temp]=tmp;
	      tab[temp][i]=atof(schowek);
	      schowek=strtok(NULL,korektor); neighbourhood
	      }*/
	      
	    }
	    xmlFree(prop);
	    if (*columns==0||*columns==i)
	    {
	    *columns=i;
	    }
	    else
	    {
	      printf("Nierowna liczba elementow w wierszach\n");
	      *ok=0;
	      //BŁĄD!!!
	    }
	  }
	  xmlFree(content);
	}
	else
	{
	  xmlFree(content);
	}
      }
    }
  }
}

void Save(char *filename, Fenotypestruct ***Population,  int fenotypes, int size[3])
{
  FILE *file;

int i,j,k,l;

float suma;
file=fopen(filename,"ab");

    if (file == NULL)
    {
        printf("Unable to open file!\n");
        exit(0);
    }

//fprintf(fp,"%d",g);

//for(l=0;l<fenotypes;l++)
//{
  suma=0.0;
  for(i=0;i<size[0];i++)
  {
    for(j=0;j<size[1];j++)
    {
      for(k=0;k<size[2];k++)
      {
	//printf("%p\n%p\n", &Population[i][j][k].fen[0],Population[i][j][k].fen);
	fwrite(Population[i][j][k].fen,sizeof(float), fenotypes, file);
	//suma=suma+Population[i][j][k].fen[l];
      }
    }
  }
  
  //fprintf(fp,";%f",suma);
//}
//fprintf(fp,"\n");
fclose(file);
}


void Save2(char *filename, Fenotypestruct ***Population,  int fenotypes, int g, int size[3])
{
  FILE *fp;

int i,j,k,l;

float suma;
fp=fopen(filename,"a");

fprintf(fp,"%d",g);

for(l=0;l<fenotypes;l++)
{
  suma=0.0;
  for(i=0;i<size[0];i++)
  {
    for(j=0;j<size[1];j++)
    {
      for(k=0;k<size[2];k++)
      {
	suma=suma+Population[i][j][k].fen[l];
      }
    }
  }
  fprintf(fp,",%f",suma/(size[0]*size[1]*size[2]));
}
fprintf(fp,"\n");
fclose(fp);
}


int main(int argc, char ** argv)
{
  int maxgeneration=0;
  int size[3]={1,1,1};
  int g,i,j,k,l,cores=1,dimension=1,rows=0,columns=0,xmlok=1,flag;
  float ***fitness;
  Fenotypestruct ***population, ***Newpopulation;
  Fenotypestruct ****PopulationTab;
  int ***ChosenCells;
  float MortalityProbability=0,suma=0;
  int ile=0;
  float **tab;
  float *****tabMatrix;
  int neighbourmethod=0,reproductionmethod=0,reproductionparam=1,updating=0, MSEG=0,save=0,initPopulation=0;
  char savepath[100], savepath2[100], initPopulationPath[100];
  FILE *file;
  ResourcesFunctionStruct resources;
  resources.type=0;
  
  srand( time( NULL ) );
  
  
  //printf("Start\n");
  
  ////////////////Odczyt XML///////////////////
  xmlDoc *doc = NULL;
  xmlNode *root_element = NULL;
  if (argc != 2)
  {
    printf("Nieprawidlowa liczba argumentow wejsciowych\n");
    return(1);
  }
  
  
  /*
  * this initialize the library and check potential ABI mismatches
  * between the version it was compiled for and the actual shared
  * library used.
  */
  LIBXML_TEST_VERSION

  /*parse the file and get the DOM */
  doc = xmlReadFile(argv[1], NULL, 0);
  
  
  if (doc == NULL) 
  {
    printf("error: could not parse file %s\n", argv[1]);
  }
  root_element = xmlDocGetRootElement(doc);
  
  //alokacja jednego miejsca pamięci - żeby używać później funkcji realloc
  tab = malloc(sizeof(*tab)); 

  GetInformationFromXml(root_element,&dimension,&size[0],&cores,&maxgeneration,&MortalityProbability,&tab,&rows,&columns,&xmlok,&neighbourmethod,&reproductionmethod,&reproductionparam,&updating,&MSEG,&save,savepath,&initPopulation,initPopulationPath, &resources);
      /*free the document */
    xmlFreeDoc(doc);


    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();
  

    printf("col: %d, rows: %d\n",columns,rows);
  //macierz payoff musi być kwaratowa
  if(columns!=rows)
  {
    printf("Macierz nie jest kwadratowa\n");
    xmlok=0;
  }
  
  if(xmlok)
  {
    //Odkomentować, jeśli używamy cores w xml a nie ustawiając zmienną OMP_NUM_THREADS
   //omp_set_num_threads(cores); 
  
    //cores=omp_get_max_threads();
    //printf("Cores=%d",cores);
    
  //przepisanie rozmiaru na każdy wymiar (max 3D)
  for (i=1;i<dimension&&i<3;i++)
  {
    size[i]=size[i-1];
  }
  
  //dynamiczna alokacja pamięci
  
  //dwa miejsca które na zmianę będą uzupełniane
  PopulationTab=malloc(2*sizeof(*PopulationTab));
  
  
  population = malloc( size[0] * sizeof( *population ) );
  for( i = 0; i < size[0]; i++ )
  {
      population[ i ] = malloc( size[1] * sizeof( **population ) );
      for (j=0;j<size[1];j++)
      {
	population[i][j]=malloc(size[2]*sizeof(***population));
	for (k=0;k<size[2];k++)
	{
	  population[i][j][k].fen=malloc(rows*sizeof(float));
	}
      }
  }
  
  Newpopulation = malloc( size[0] * sizeof( *Newpopulation ) );
  for( i = 0; i < size[0]; i++ )
  {
      Newpopulation[ i ] = malloc( size[1] * sizeof( **Newpopulation ) );
      for (j=0;j<size[1];j++)
      {
	Newpopulation[i][j]=malloc(size[2]*sizeof(***Newpopulation));
	for (k=0;k<size[2];k++)
	{
	  Newpopulation[i][j][k].fen=malloc(rows*sizeof(float));
	}
      }
  }
  PopulationTab[0]=population;
  PopulationTab[1]=Newpopulation;

  
  fitness = malloc( size[0] * sizeof( *fitness ) );
  for( i = 0; i < size[0]; i++ )
  {
      fitness[ i ] = malloc( size[1] * sizeof( **fitness ) );
      for (j=0;j<size[1];j++)
      {
	fitness[i][j]=malloc(size[2]*sizeof(***fitness));
      }
  }
  
  ChosenCells = malloc( size[0] * sizeof( *ChosenCells ) );
  for( i = 0; i < size[0]; i++ )
  {
      ChosenCells[ i ] = malloc( size[1] * sizeof( **ChosenCells ) );
      for (j=0;j<size[1];j++)
      {
	ChosenCells[i][j]=malloc(size[2]*sizeof(***ChosenCells));
      }
  }
  
  
  tabMatrix = malloc( size[0] * sizeof( *tabMatrix ) );
  for( i = 0; i < size[0]; i++ )
  {
      tabMatrix[ i ] = malloc( size[1] * sizeof( **tabMatrix ) );
      for (j=0;j<size[1];j++)
      {
	tabMatrix[i][j]=malloc(size[2]*sizeof(***tabMatrix));
	for(k=0;k<size[2];k++)
	{
	  
	  if(resources.type==5)
	  {  
	      //2 bo H-D ma 2 wiersze i 2 kolumny
	      tabMatrix[i][j][k]=malloc(2*sizeof(****tabMatrix));
	      tabMatrix[i][j][k][0]=malloc(2*sizeof(*****tabMatrix));
	      tabMatrix[i][j][k][1]=malloc(2*sizeof(*****tabMatrix)); 
	  }
	  else
	  {
	    tabMatrix[i][j][k]=tab;
	  }
	}
      }
  }
  
  
  FillArray(ChosenCells,size,0);//wypełnienie tablicy chosencells zerami
  

  //losowanie populacji - dodać odczyt z pliku binarnego
  InitialisePopulation(PopulationTab[0],size,rows,MSEG,initPopulation,initPopulationPath);
  
  
  
 //jeśli metoda jest deterministyczna to komórka ma być zastępowana przez najsilniejszą
 if(reproductionmethod==1)
 {
   reproductionparam=1;
 }
 
 
 if(save)
 {
   strcpy(savepath2,savepath);
   strcat(savepath, ".bin");
   strcat(savepath2, ".csv");
   file=fopen(savepath,"wb");
   fclose(file);
   file=fopen(savepath2,"w");
   fclose(file);
   Save(savepath, PopulationTab[0],  rows, size);
   Save2(savepath2, PopulationTab[0], rows, 0, size);
 }
 

 
  for(g=0;g<maxgeneration;g++)
  {
    //printf("%d\n",g);
    
    ChangePayoffMatrix(tabMatrix,resources,g+1,PopulationTab[g%2], size, neighbourmethod);
        
    
    PayoffUpdate(PopulationTab[g%2],fitness,size,tabMatrix,rows,neighbourmethod);
    
   
    Mortality(ChosenCells,MortalityProbability,size,updating);
    
    CompetitiveReproduction(PopulationTab[g%2],PopulationTab[(g+1)%2],fitness,ChosenCells,size,rows,neighbourmethod,reproductionmethod,reproductionparam);
    
    
    if(save)
    {   
      Save(savepath, PopulationTab[(g+1)%2],  rows, size);
      Save2(savepath2, PopulationTab[(g+1)%2], rows, g+1, size);
    }
  }
  //Show(population, size,rows);
  /*
  suma=0;
  ile=0;
  
printf("\nKoniec:\n");

for(l=0;l<rows;l++)
{
  suma=0.0;
  for(i=0;i<size[0];i++)
  {
    for(j=0;j<size[1];j++)
    {
      for(k=0;k<size[2];k++)
      {
	suma=suma+PopulationTab[maxgeneration%2][i][j][k].fen[l];
      }
    }
  }
  printf("suma %d: %f\n",l,suma);
}

  */
  
  for( i = 0; i < size[0]; i++ )
  {
      for (j=0;j<size[1];j++)
      {
	for(k=0;k<size[2];k++)
	{
	  free(population[i][j][k].fen);
	}
	free(population[i][j]);
      }
      free(population[i]);
  }
  free(population);
  
    for( i = 0; i < size[0]; i++ )
  {
      for (j=0;j<size[1];j++)
      {
	for(k=0;k<size[2];k++)
	{
	  free(Newpopulation[i][j][k].fen);
	}
	free(Newpopulation[i][j]);
      }
      free(Newpopulation[i]);
  }
  free(Newpopulation);
  
  
  for( i = 0; i < size[0]; i++ )
  {
      for (j=0;j<size[1];j++)
      {
	free(fitness[i][j]);
      }
      free(fitness[i]);
  }
  free(fitness);
  
  for( i = 0; i < size[0]; i++ )
  {
      for (j=0;j<size[1];j++)
      {
	free(ChosenCells[i][j]);
      }
      free(ChosenCells[i]);
  }
  free(ChosenCells);
  
  free(PopulationTab);
  
  }
  
  for( i = 0; i < size[0]; i++ )
  {
      for (j=0;j<size[1];j++)
      {
	for(k=0;k<size[2];k++)
	{
	  
	  if(resources.type==5)
	  {
	    free(tabMatrix[i][j][k][0]);
	    free(tabMatrix[i][j][k][1]);
	    free(tabMatrix[i][j][k]);
	  }
	  else if(i==0&&j==0&&k==0)
	  {
	    tabMatrix[i][j][k]=tab;
	    for(l=0;l<rows;l++)
	    {
	      free(tabMatrix[i][j][k][l]);
	    }
	    free(tabMatrix[i][j][k]);
	  }
	}
	free(tabMatrix[i][j]);
      }
      free(tabMatrix[i]);
  }
  free(tabMatrix);
  
  return 0;
}

#else
int main(void) {
    fprintf(stderr, "Tree support not compiled in\n");
    exit(1);
}
#endif