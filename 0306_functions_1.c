#include <stdio.h>
#include <math.h>

int Factorial(int n){
    int ans = 1;
    int mul = 2;
    
    while(mul <= n){
        ans = ans * mul;
        mul = mul + 1;
    }
    return ans;
}

int IsPrime(int n){
    int factor = 2;
    
    while(factor <= sqrt(n)){
        //if n%factor is equal to 0, then return 0(false, not a prime)
        if(n % factor == 0){
            return 0;
        }
        factor = factor + 1;
        
    }
    return 1;
}

int NextPrime(int n){
    for(int i = n+1;;i = i+1){
        if(IsPrime(i) == 1){
            return i;
        }
    }
}

double DisToOrig(int x, int y){
    return sqrt(x^2 +y^2);
}

int GetHeight(int r, int x){
    return sqrt(r*r - x*x);
}

double PI1(int r){
    double area = 0;
    
    for(int x = -1*r; x <= r; x++){
        for (int y = r; y >= -1*r; y= y-1){
            if (DisToOrig(x, y) <= r){
                area = area + 1;
            }
        }
    }
    
    return area / (r*r);
}

double PI2(int r){
    double area = 0;
    
    for (int x = 0; x <= r; x= x+1){
        int y = GetHeight(r, x);
        area = area + y;
    }
    return 4.0*area / (r*r);
}

double PI3(int k){
    double sum = 0;
    
    for (double i = 1; i <= k; i++){
        sum = sum + 1.0 / (i*i);
    }
    
    return sqrt(6.0*sum);
}

double PI4(int k){
    double pi = 0;
    
    for(double i = 1; i<= k; i++){
        if((int)i % 2 == 0){
            pi -= 4.0 / (2.0*i -1.0);
        }
        else{
            pi += 4.0/(2.0*i - 1.0);
        }
    }
    
    return pi;
}

double PI5(int k){
    double pi = 3;
    
    for(double i = 1; i<= k; i++){
        double first = 2.0*i;
        if((int)i % 2 == 0){
            pi -= 4.0 / (first*(first+1)*(first+2));
        }
        else{
            pi += 4.0/(first*(first+1)*(first+2));
        }
    }
    
    return pi;
}

    
int main(){
    for(int i = 1; i <= 10000; i++){
        printf("Pi = %f %f %f %.10f\n", PI2(i), PI3(i), PI4(i), PI5(i)); //%.10f 就是小數點後印10位
    }
    getchar();
    
    for(int i = 1; i <= 10000; i++){
        printf("Pi = %f %f %f\n", PI2(i), PI3(i), PI4(i));
    }
    getchar();
    
    for(int i = 1; i <= 10000; i++){
        printf("Pi = %f %f\n", PI2(i), PI3(i));
    }
    getchar();
    
    for (int i = 1;i <= 10000; i++){
        printf("Pi = %f\n", PI2(i));
    }
    getchar();
    
    for (int i = 1;i <= 10; i++){
        printf("Pi = %f\n", PI1(i));
    }
    getchar();
    
    int prime = 2;
    for(int i = 1;i<100; i = i+1){
        printf("the %dth prime is %d\n", i, prime);
        prime = NextPrime(prime);
    }
    getchar();
    
    int n = 2;
    while(n<= 100){
        if (IsPrime(n) == 1){
            printf("%d is a prime number\n", n); // \n 就是換行的意思
        }
        else{
            printf("%d is NOT a prime number\n", n);
        }
        n++;
    }
    getchar();
    
    int n2 = 1;
    while (n <= 10){
        printf("%d! = %d\n", n2, Factorial(n));
        n2 = n2+1;
    }
        
    getchar();
    return 0;
}
