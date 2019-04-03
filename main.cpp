#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>


using namespace std;
//QUICKSORT
void zamien(int tablica[], int pierwszy,int  drugi){
  int temp=tablica[drugi];
  tablica[drugi]=tablica[pierwszy];
  tablica[pierwszy]=temp;
}

int podziel (int tablica[],int l,int p){
  int pivot_indeks=l+(p-l)/2; //wybor pivota- wartosci do ktorej porownuje elementy
  int pivot_wartosc=tablica[pivot_indeks];
  zamien(tablica, pivot_indeks, p);
  int aktywny=l; //proedura porownywania i przenoszenia elementow na wlasciwa strone pivota
  for(int i=l;i<p;i++){
    if(tablica[i]<pivot_wartosc){
      zamien(tablica, i, aktywny);
      aktywny=aktywny+1;
    }
  }
  zamien(tablica, aktywny, p);
  return aktywny;
}
  

void quicksort (int tablica[],int l,int p){
  if(l<p){
    int i=podziel(tablica,l,p);  
    quicksort(tablica, l, i-1);  
    quicksort(tablica, i+1, p);
  }
}

//SCALANIE

void scalanie (int tablica[], int l, int s, int p){
  int i, j, k;
  int n1 =s-l+1;
  int n2 =p-s;
  int *L=new int[n1];
  int *P=new int[n2];
  //kopiowanie liczb do tymczasowych tablic
  for (i=0;i<n1;i++){
    L[i]=tablica[l+i];
  }
  for (j=0;j<n2;j++){
    P[j]=tablica[s+1+j];
  }
  //Iteracja po tablicach tymaczasowych i wybieranie mniejszej wartosci
  i=0; j=0; k=l;
  while(i<n1 && j<n2){
    if (L[i]<=P[j]){
      tablica[k]=L[i];
      i++;
    }
    else{
      tablica[k]=P[j];
      j++;
    }
    k++;
  }
  //Kopiowanie pozostalych wartosci z tablic tymczasowych
  while(i<n1){
    tablica[k]=L[i];
    i++;
    k++;
  }
  while(j<n2){
    tablica[k]=P[j];
    j++;
    k++;
  }
  delete []L; delete []P;
}
	 
void mergesort (int tablica[], int l, int p){
  if(l<p){
    int s=(l+p)/2;
    mergesort(tablica,l,s);
    mergesort(tablica,s+1,p);
    scalanie(tablica,l,s,p);
  }
}
    
//INTROSORT
int sortowaniewstawianie(int tablica[],int poczatek, int koniec)
{
  for(int i=1;i<=koniec;i++){
    int wstawiany=tablica[i];
    int j=i-1;
    while(j>=poczatek && tablica[j]>wstawiany){
      tablica[j+1]=tablica[j];
      j=j-1;
    }
    tablica[j+1]=wstawiany;
  }
}
int medianatrzech(int tablica[], int a, int b, int c){
  if(tablica[a]<tablica[b]&&tablica[b]<tablica[c])
    return b;
  if(tablica[a]<tablica[c]&&tablica[c]<=tablica[b])
    return c;
  if(tablica[b]<=tablica[a]&&tablica[a]<tablica[c])
    return a;
  if(tablica[b]<tablica[c]&&tablica[c]<=tablica[a])
    return c;
  if(tablica[c]<=tablica[a]&&tablica[a]<tablica[b])
    return a;
  if(tablica[c]<=tablica[b]&&tablica[b]<=tablica[a])
    return b;
}

void kopcoj(int tablica[], int n, int i)
{
  int najwiekszy=i;
  int l=2*i+1;
  int p=2*i+2;
  if(l<n&&tablica[l]>tablica[najwiekszy])
    najwiekszy=l;
  if(p<n&&tablica[p]>tablica[najwiekszy])
    najwiekszy=p;
  if(najwiekszy!=i){
    zamien(tablica, i, najwiekszy);
    kopcoj(tablica, n, najwiekszy); 
  }
}

void sortowaniekopcowanie(int tablica[], int rozmiar)
{
  //budowanie kopca
  for(int i=rozmiar/2-1;i>=0;i--)
    kopcoj(tablica,rozmiar,i);
  //zdejmowanie elementow z kopca
  for(int i=rozmiar-1;i>=0;i--){
    zamien(tablica,0,i);
    kopcoj(tablica,i,0);
  }
}
void introsortinternal(int tablica[], int l, int p, int maxglebokosc){
  int rozmiar=p-l;
  /* if (rozmiar<16){
    sortowaniewstawianie(tablica, l, p);
    return;
  }
  */ //Gdyby odkomentowac byloby hybrydowe, ale warunek wstawiony w innym miejscu
  
  if(maxglebokosc==0){
    sortowaniekopcowanie(tablica,p-l+1);
    return;
    }
    
  
  int pivot=medianatrzech(tablica,l,l+rozmiar/2,p);
  zamien(tablica,pivot,p);
  if(l<p){
    int i=podziel(tablica,l,p);  
  introsortinternal(tablica, l, i-1, maxglebokosc-1);  
  introsortinternal(tablica, i+1, p, maxglebokosc-1);
    }
}
  
void introsort(int tablica[], int l, int p){
  int maxglebokosc=2*log(p-l);
  introsortinternal(tablica,l,p,maxglebokosc);
}



int main(){
  int rozmiarytablicy[5]={10000,50000,100000,500000,1000000};
  double stopnieposortowania[8]={0, 0.25, 0.50, 0.75, 0.95, 0.99, 0.997, 1}; //gdy wybrano 1, bedzie to odwrotnie posortowana tablica
    for(int i=0;i<5;i++){
      int rozmtablicy=rozmiarytablicy[i];
      for(int j=0; j<8; j++){
	int dokadposortowac=stopnieposortowania[j]*rozmtablicy-1;
	int **tablicatablic = new int*[100];
	  for(int nrtablicy=0; nrtablicy<100; nrtablicy++){
	tablicatablic[nrtablicy]= new int[rozmtablicy];
	  
	for (int k=0; k<rozmtablicy; k++){
	  tablicatablic[nrtablicy][k]=rand()-rand();
	}
	quicksort(tablicatablic[nrtablicy], 0, dokadposortowac);
	if(stopnieposortowania[j]==1){
	  for(int l=0; l<rozmtablicy; l++){
	    tablicatablic[nrtablicy][l]=-tablicatablic[nrtablicy][l];
	  }
	}
	  }

	//TEST SZYBKOSCI
	//cout<<"Test dla rozmiaru: "<<rozmtablicy<<" i stopnia posortowania: "<<stopnieposortowania[j]<<"\n";
	//Zapis w formacie rozmiar, stopien posortowania, czas w sekundach
	  cout<<rozmtablicy<<", "<<stopnieposortowania[j]<<", ";
  
	  double roznica;
	  cout.setf(ios::fixed); //notacja zwykla
	  clock_t start, koniec; //inicjacja zmiennych zegarowych	
	  start=clock(); //zapisanie czasu startu mierzenia
	  
	  for(int nrtablicy=0; nrtablicy<100; nrtablicy++){
	  mergesort(tablicatablic[nrtablicy],0,rozmtablicy-1);
	  }
	
	  // sortowaniekopcowanie(tablicatablic[0],rozmtablicy);
	  // for(int i=0;i<rozmtablicy;i++){
	  // cout<<tablicatablic[0][i]<<endl;
	  //}
      
	koniec=clock();//zapisanie konca mierzenia	
	roznica=(koniec-start)/(double)CLOCKS_PER_SEC;	
	cout<<roznica<<endl;
      }
    }
    
}
