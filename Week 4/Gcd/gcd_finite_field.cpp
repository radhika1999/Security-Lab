#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

bool divisor_smaller_than_remainder(int coeff1[], int coeff2[], int m){
	for(int i=0;i<m;i++){
		if(coeff1[i]>coeff2[i]){
			return true;
		}
		else if(coeff2[i]>coeff1[i]){
			return false;
		}
	}
	//when polynomials are equal
	return true;
}
void print_polynomial(int coeff[], int m){
	int degree=m-1;
	bool first=true;
	for(int i=0;i<m;i++){
		if(coeff[i]!=0){
			if(coeff[i]!=1){
				cout<<coeff[i];
			}
			if(first){
				first=false;
			}
			else{
				cout<<" + ";
			}
			cout<<"x^"<<degree;
		}
		degree--;
	}
	cout<<endl;
}
void polynomial_division(int coeff1[], int coeff2[], int m){
	int highest_degree[2]={0};
	while(divisor_smaller_than_remainder(coeff1, coeff2, m)){
		bool f1=true,f2=true;
		for(int i=0;i<m;i++){
			if(f1&&coeff1[i]){
				highest_degree[0]=m-i-1;
				f1=false;
			}
			if(f2&&coeff2[i]){
				highest_degree[1]=m-i-1;
				f2=false;
			}
		}
		int multiply_degree=highest_degree[0]-highest_degree[1];
		int diff_poly[m]={0};
		for(int i=0;i<m;i++){
			if(coeff2[i]==1){
				diff_poly[i-multiply_degree]=1;
			}
		}
		for(int i=0;i<m;i++){
			coeff1[i]=(coeff1[i]-diff_poly[i]+2)%2;
		}
	}
}
void copy_array(int a1[], int a2[], int m){
	for(int i=0;i<m;i++){
		a1[i]=a2[i];
	}
}
void gcd(int coeff1[], int coeff2[], int m){
	bool flag=true;
	for(int i=0;i<m;i++){
		if(coeff2[i]){
			flag=false;
			break;
		}
	}
	if(flag){
		return;
	}
	int temp1[m]={0};
	copy_array(temp1, coeff1, m);
	polynomial_division(temp1, coeff2, m);
	cout<<"Remainder:\n";
	print_polynomial(temp1, m);
	copy_array(coeff1, coeff2, m);
	copy_array(coeff2, temp1, m);
	gcd(coeff1, coeff2, m);
}
int main(){
	cout<<"GCD of polynomial 1 and polynomial 2 assuming polynomial 1 is always greater than polynomial 2\n";
	int p=2;
	int m;
	cout<<"\nEnter exponent m of field GF(2^m): ";
	cin>>m;
	int coeff1[m], coeff2[m];
	cout<<"\nInput polynomial 1:\n";
	cout<<"Enter "<<m<<" coefficients from highest to lowest with integer value form 0 to "<<(p-1)<<endl;
	for(int i=0;i<m;i++){
		cin>>coeff1[i];
	}
	cout<<"\nInput polynomial 2:\n";
	cout<<"Enter "<<m<<" coefficients from highest to lowest with integer value form 0 to "<<(p-1)<<endl;
	for(int i=0;i<m;i++){
		cin>>coeff2[i];
	}
	gcd(coeff1, coeff2, m);
	cout<<"GCD is: "<<endl;
	print_polynomial(coeff1, m);
}