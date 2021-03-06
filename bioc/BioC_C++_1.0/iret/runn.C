#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "runn.h"
using namespace std;
namespace iret {

int mark(int pflag, long ct, int ivl, const char *what){
if(pflag&&((ct%ivl)==0)){cout << what << " count=" << ct << endl;
                                        return(1);}
else return(0);
}

int get_qflag(){
   int pflag=1;
   ifstream fin("quiet.flag",ios::in);
   if(fin.is_open()){
      fin >> pflag;
      fin.close();
      fin.clear();
   }
   return(pflag);
}

int get_pathw(char *nam,const char *pfl,const char *pex,const char *ch){
   char cnam[256];

   strcpy(cnam,"path_");
   strcat(cnam,pfl);
   strcat(cnam,"_");
   strcat(cnam,pex);
   strcat(cnam,".");
   strcat(cnam,ch);
   ifstream fin(cnam,ios::in);
   if(!fin.is_open()){
      fin.clear();
      strcpy(cnam,"path_");
      strcat(cnam,pfl);
      strcat(cnam,"_");
      strcat(cnam,pex);
      fin.open(cnam,ios::in);
      if(!fin.is_open()){
	 fin.clear();
         strcpy(cnam,"path_");
         strcat(cnam,pfl);
         fin.open(cnam,ios::in);
         if(!fin.is_open()){
           fin.clear();
           strcpy(cnam,"path");
           fin.open(cnam,ios::in);
           if(!fin.is_open()){
             cout << "Path file for type " << pfl
                  << " does not exist!" << endl;
             exit(1);
           }
         }
      }
   }

   fin.getline(nam,256);
   fin.close();
   strcat(nam,pfl);
   strcat(nam,"_");
   strcat(nam,pex);
   strcat(nam,".");
   strcat(nam,ch);
   return(1);
}

char *add_num(const char *ptr,long n,char *buf){
   char cnam[100];
   long_str(cnam,n);
   strcpy(buf,ptr);
   strcat(buf,cnam);
   return(buf);
}

long gseed(int x, char **v, const char *c){
   long seed;

   seed=clnga(x,v,c,"seed for random number generator");
   srandom((unsigned int)seed);
   return seed;
}

long zrand(long p){
   return(((long)random())%p);
}

void shuffle(long n,long *idx){
   long i,j,k;
   for(i=0;i<n;i++){
      k=zrand(n);
      j=*(idx+i);
      *(idx+i)=*(idx+k);
      *(idx+k)=j;
   }
}

void dshuffle(long n,long *idx){
   long i,j,k;
   for(i=n-1;i>0;i--){
      k=zrand(i+1);
      j=idx[i];
      idx[i]=idx[k];
      idx[k]=j;
   }
}

long clnga(int x, char **v, const char *c, const char *name){
   int i,flag=1;
   long num;

   for(i=1;i<x-1;i++)
      if(strcmp(c,*(v+i))==0){
         flag=0;
         istringstream oss(*(v+i+1) );
         oss >> num;
         if(oss.fail()){
            cout << "Enter " << name << ":" << endl;
            cin >> num;
         }
      }
   if(flag==1){
      cout << "Enter " << name << ":" << endl; 
      cin >> num;
      cin.get();
   }
   return(num);
}

long rnd(double p)
{
return((long)floor(p+.5));
}

double cdbla(int x, char **v, const char *c, const char *name){
   int i,flag=1;
   double num;

   for(i=1;i<x-1;i++)
      if(strcmp(c,*(v+i))==0){
         flag=0;
         istringstream oss(*(v+i+1));
         oss >> num;
         if(oss.fail()){
            cout << "Enter " << name << ":" << endl;
            cin >> num;
         }
      }
   if(flag==1){
      cout << "Enter " << name << ":" << endl; 
      cin >> num;
      cin.get();
   }
   return(num);
}

char *cstra(int x, char **v, const char *c, const char *name){
   int i;
   char cnam[max_str];

   for(i=1;i<x-1;i++){
      if(strcmp(c,*(v+i))==0){
         return(*(v+i+1));
      }
   }

   restart:
   cout << "Enter " << name << ":" << endl;
   cin.getline(cnam,max_str);
   if(i=cin.gcount()){
      char *pch=new char[i+1];
      strcpy(pch,cnam);
      return(pch);
   }
   else {
      cin.clear();
      goto restart;
   }
}

//Function to convert a long to a null terminated string.
void long_str(char *cnam,long n){
  ostringstream oss;
  oss << n;
  const string & str = oss.str();
  str.copy(cnam,20);
  cnam[str.length()]='\0';
}

//Function to convert a string with null termination
//to a long.
void str_long(char *cnam,long &n){
   istringstream(cnam) >> n;
}

//Function to convert first two char of string to an
//integer. Should be an ASCII null terminated string
int trac(const char *str){
   if(!(*str))return(0);
   else {
      return((int)(*(str+1))+128*((int)(*str)));
   }
}

}
