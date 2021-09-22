#include<iostream>
using namespace std;

bool divisor_smaller_than_remainder(int coeff1[], int coeff2[], int m){
	for(int i=m-1;i>=0;i--){
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
	for(int i=m-1;i>=0;i--){
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
		for(int i=m-1;i>=0;i--){
			if(f1&&coeff1[i]){
				highest_degree[0]=i;
				f1=false;
			}
			if(f2&&coeff2[i]){
				highest_degree[1]=i;
				f2=false;
			}
		}
		int multiply_degree=highest_degree[0]-highest_degree[1];
		int diff_poly[m]={0};
		for(int i=0;i<m;i++){
			if(coeff2[i]==1){
				diff_poly[i+multiply_degree]=1;
			}
		}
		for(int i=0;i<m;i++){
			coeff1[i]=(coeff1[i]-diff_poly[i]+2)%2;
		}
		cout<<"Remainder:\n";
		print_polynomial(coeff1, m);
	}
}
void multiplication(int coeff1[], int coeff2[], int irreducilble[], int m, int mul_result[]){
	int highest_degree=0;
	bool first=true;
	for(int i=m-1;i>=0;i--){
		for(int j=m-1;j>=0;j--){
			if(coeff1[i]&&coeff2[j]){
				int degree=i+j;
				mul_result[degree]=(mul_result[degree]+1)%2;
				if(first){
					highest_degree=degree;
					first=false;
				}
			}
		}
	}
	cout<<"Multiplication without reducing:\n";
	print_polynomial(mul_result, highest_degree+1);

	polynomial_division(mul_result, irreducilble, highest_degree+1);
}
int main(){
	int p=2;
	int m;
	cout<<"\nEnter exponent m of field GF(2^m): ";
	cin>>m;
	int coeff1[m], coeff2[m], irreducible[100]={0};
	cout<<"\nInput irreducible polynomial:\n";
	cout<<"Enter "<<(m+1)<<" coefficients from highest to lowest with integer value form 0 to "<<(p-1)<<endl;
	for(int i=m;i>=0;i--){
		cin>>irreducible[i];
	}
	cout<<"Irreducible polynomial is:\n";
	print_polynomial(irreducible, m+1);
	cout<<"\nInput polynomial 1:\n";
	cout<<"Enter "<<m<<" coefficients from highest to lowest with integer value form 0 to "<<(p-1)<<endl;
	for(int i=m-1;i>=0;i--){
		cin>>coeff1[i];
	}
	cout<<"Polynomial 1 is:\n";
	print_polynomial(coeff1, m);
	cout<<"\nInput polynomial 2:\n";
	cout<<"Enter "<<m<<" coefficients from highest to lowest with integer value form 0 to "<<(p-1)<<endl;
	for(int i=m-1;i>=0;i--){
		cin>>coeff2[i];
	}
	cout<<"Polynomial 2 is:\n";
	print_polynomial(coeff2, m);
	int mul_result[100]={0};
	multiplication(coeff1, coeff2, irreducible, m, mul_result);
	cout<<"Polynomial after multiplication with reducung is: "<<endl;
	print_polynomial(mul_result, m);
}