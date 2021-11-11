#include <iostream>
#include <cmath> 
using namespace std; 




class Complex{ 

  private:
  double r; 
  double i; 

  public:

  // default constructor 
  Complex(){ 

    r=0; 
    i=1; 
  }



//2 parameter constructor 
  Complex(int i, int j ){

    r=i; 
    i=j;


  }

int getR(){ return r;}

int getI() { return i;}

void setR(double  i){r = i; } 

void setI( double i){ i=i;}



Complex operator+ ( Complex s ){ 

  Complex x; 

  x.r= r+s.r; 

  x.i= i+s.r;


  return x;
}


Complex operator-(Complex s ){ 

  Complex x; 

  x.r= r-s.r; 
  x.i= i-s.i; 

  return x; 
} 
Complex operator (Complex s ){ 

  Complex x; 

  x.r= (rs.r)- ( is.r); 

  x.i= (is.r)- (rs.r); 
  return x; 
}



Complex operator/ (Complex s){ 

  Complex x; 


double a= s.r;  double b= s.i; 

double denominator= (aa)+(bb); 

x.r= ((ra)+ (ib)); 
x.i=(( ia)- (rb)); 

  return x; 
}


friend ostream &operator << (ostream& os, Complex s );
friend istream & operator << ( istream & os, Complex s ); 

}; 

ostream& operator<<  ( ostream& os, Complex s){ 

  os << s.r << " + " << s.i << 'i'<<  endl; 
  return os; 


}



istream& operator << ( istream& is, Complex s ){ 

  is >> s.r >> s.i; 
}


 int main () { 


  Complex a1; 

  a1.setR(5); 
  a1.setI(6); 


  Complex a2; 
  a2.setR(12); 
  a2.setI(4); 



cout << "a1 :" << a1 << endl; 
cout << " a 1: " << a2 << endl; 
cout << "a1+a2"  << a1+a2<< endl; 
cout << "a1-a2" << a1-a2 << endl; 
cout << " a1a2 " << a1*a2 <<  endl; 
cout << " a1/a2" << a1/a2 << endl; 


return 0; 

  }
