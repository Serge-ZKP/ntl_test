// run with g++ -g -O2 -std=c++11 -pthread -march=native main.cpp -o foo -lntl -lgmp -lm

//#include <../NTL/ZZ_pXFactoring.h>
#include <NTL/ZZ_pXFactoring.h>
//#include <../NTL/ZZ_pEX.h>
#include <NTL/ZZ_pEX.h>
#include <ctime>

using namespace std;
using namespace NTL;

void check_mul(int degree, ZZ p){
   ZZ_p::init(p);
   ZZ_pX f,g,h;
   random(f,degree);
   random(g,degree);
   clock_t begin = clock();
   h=f*g;
   clock_t end = clock();
   double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
   cout<<elapsed_secs<<"\n";
}

void check_div(int degree, ZZ p,bool linear=false){
   ZZ_p::init(p);
   ZZ_pX a,b,q,x;

   if(linear){
      random(a,degree);
      random(b,2);
   }
   else{
      random(a,2*degree);
      random(b,degree);
   }
   clock_t begin = clock();
   divide(q,a,b);
   clock_t end = clock();
   double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
   cout<<elapsed_secs<<"\n";
}

void check_inv(int degree, ZZ p){
   ZZ_p::init(p);
   ZZ_pX a,b,q;

   random(a,degree);
   random(b,2*degree);

   clock_t begin = clock();
      InvMod(q,a,b);
   clock_t end = clock();

   double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

   cout<<elapsed_secs<<"\n";
}


int main()
{
   ZZ p=conv<ZZ>("57896044618658097711785492504343953926634992332820282019728792003956564819949"); //2^255-19
   ZZ q=conv<ZZ>("21888242871839275222246405745257275088548364400416034343698204186575808495617"); //FFT friendly prime
   GenPrime(p,256);

   //FFT unfriendly prime field arithmetic

   check_mul(100000,p);
   check_div(10000000,p,true);

   //FFT friendly prime field arithmetic

   check_mul(10000000,q);
   check_div(1000000,q);

   //Modular Inversion
   
   check_inv(10000, p);
   check_inv(10000, q);

   check_inv(100000, p);
   check_inv(100000, q);
}
