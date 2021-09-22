#include<iostream>
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
void polynomial_division(int coeff1[], int coeff2[], int m, int quotient[]){
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
		for(int i=0;i<m;i++){
			if(coeff2[i]==1){
				quotient[i-multiply_degree]=1;
			}
		}
		for(int i=0;i<m;i++){
			coeff1[i]=(coeff1[i]-quotient[i]+2)%2;
		}
	}
}
void multipoly(int a1[],int a2[],int a3[], int m)
{
    for(int i=0;i<=m-1 ;i++)
    {
        for(int j=0;j<=m-1;j++)
        {
            a3[i+j]+=a1[i]*a2[j];
            a3[i+j]=a3[i+j]%2;
        }
    }
}
void copy_array(int a1[], int a2[], int m){
	for(int i=0;i<m;i++){
		a1[i]=a2[i];
	}
}
void extended_gcd(int coeff1[], int coeff2[], int m, int t0[], int t1[], int s0[], int s1[]){
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
	int temp1[m], quotient[m]={0};
	copy_array(temp1, coeff1, m);
	polynomial_division(temp1, coeff2, m, quotient);
	cout<<"Remainder:\n";
	print_polynomial(temp1, m);
	cout<<"Quotient:\n";
	print_polynomial(quotient, m);
	//s=s0+q*s1  t=t0+q*t1
	int x1[100]={0}, x2[100]={0}, s2[m]={0}, t2[m]={0};
	multipoly(quotient,s1,x1,m);
    for(int i=0;i<m;i++)
    {
        s2[i]=(s0[i] + x1[i])%2;
    }
    multipoly(quotient,t1,x2,m);
    for(int i=0;i<m;i++)
    {
        t2[i]=(t0[i] + x2[i])%2;
    }
    for(int i=0;i<m;i++)
    {
        s0[i]=s1[i];s1[i]=s2[i];
        t0[i]=t1[i];t1[i]=t2[i];
    }

	copy_array(coeff1, coeff2, m);
	copy_array(coeff2, temp1, m);
	extended_gcd(coeff1, coeff2, m, t0, t1, s0, s1);
}
int main(){
	cout<<"Inverse for polynomial 1 and polynomial 2 with polynomial 1 is always greater than polynomial 2\n";
	int p=2;
	int m;
	cout<<"\nEnter exponent m of field GF(2^m): ";
	cin>>m;
	int coeff1[m+1]={0}, coeff2[m]={0};
	cout<<"\nInput polynomial 1(Irreducible polynomial):\n";
	cout<<"Enter "<<(m+1)<<" coefficients from highest to lowest with integer value form 0 to "<<(p-1)<<endl;
	for(int i=0;i<m;i++){
		cin>>coeff1[i];
	}
	cout<<"\nInput polynomial 2:\n";
	cout<<"Enter "<<m<<" coefficients from highest to lowest with integer value form 0 to "<<(p-1)<<endl;
	for(int i=0;i<m;i++){
		cin>>coeff2[i];
	}
	cout<<"Polynomial is:\n";
	print_polynomial(coeff2, m);
	int s0[m], s1[m], t0[m], t1[m];
	for(int i=0;i<m;i++)
	{
		s0[i]=0;t0[i]=0;s1[i]=0;t1[i]=0;
	}
	s0[m-1]=1;t0[m-1]=0;
	s1[m-1]=0;t1[m-1]=1;
	extended_gcd(coeff1, coeff2, m+1, s0, s1, t0, t1);
	cout<<"Inverse is: "<<endl;
	print_polynomial(t0, m);
}