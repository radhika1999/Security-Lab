#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

void adding_finite_fields(int p, int m, int coefficients[]){
	int coeff1[m], coeff2[m];
	cout<<"\nInput polynomial 1:\n";
	cout<<"\nEnter "<<m<<" coefficients from highest coefficient to lowest with integer value form 0 to "<<(p-1)<<endl;
	for(int i=0;i<m;i++){
		cin>>coeff1[i];
	}
	cout<<"\nInput polynomial 2:\n";
	cout<<"\nEnter "<<m<<" coefficients from highest coefficient to lowest with integer value form 0 to "<<(p-1)<<endl;
	for(int i=0;i<m;i++){
		cin>>coeff2[i];
	}
	//Adding polynomials with mod 2
	for(int i=0;i<m;i++){
		coefficients[i]=(coeff1[i]+coeff2[i])%p;
	}
}
int main(){
	int p, m;
	cout<<"Enter base prime p: ";
	cin>>p;
	cout<<"Enter exponent m: ";
	cin>>m;
	int coefficients[m];
	adding_finite_fields(p, m, coefficients);
	cout<<"Coefficients after addition:\n";
	for(int i=0;i<m;i++){
		cout<<coefficients[i]<<" ";
	}
	cout<<endl;
	cout<<"Polynomial after addition:\n";
	int degree=m-1;
	for(int i=0;i<m;i++){
		if(coefficients[i]!=0){
			if(coefficients[i]!=1){
				cout<<coefficients[i];
			}
			cout<<"x^"<<degree;
			if(degree!=0){
				cout<<" + ";
			}
		}
		degree--;
	}
	cout<<endl;
}