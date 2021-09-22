#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

void print_polynomial(int coeff[], int m){
	int degree=m-1;
	bool first=true;
	for(int i=m-1;i>=0;i--){
		if(coeff[i]!=0){
			if(first){
				first=false;
			}
			else{
				cout<<" + ";
			}
			if(coeff[i]!=1){
				cout<<coeff[i];
			}
			cout<<"x^"<<degree;
		}
		degree--;
	}
	cout<<endl;
}
void adding_finite_fields(int p, int m, int coefficients[]){
	int coeff1[m];
	cout<<"\nInput polynomial:\n";
	cout<<"\nEnter "<<m<<" coefficients from highest coefficient to lowest with integer value form 0 to "<<(p-1)<<endl;
	for(int i=0;i<m;i++){
		cin>>coeff1[i];
	}
	cout<<"polynomial:\n";
	print_polynomial(coeff1, m);
	
	for(int i=0;i<m;i++){
		coefficients[i]=(p-coeff1[i])%p;
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
	cout<<"Coefficients of additive inverse:\n";
	for(int i=0;i<m;i++){
		cout<<coefficients[i]<<" ";
	}
	cout<<endl;
	cout<<"Additive inverse:\n";
	print_polynomial(coefficients, m);
}