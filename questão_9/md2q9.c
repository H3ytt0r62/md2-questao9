#include <stdio.h>
//passos 1,2 e 4
int coprimo(int a, int b){
    int vp;
    int vo;
    if(a < b){
        vp = a;
        vo = b;

    }else{
        vp = b;
        vo = a;

    }
    
    int vd;
        while (vp  != 0) {
            vd = vo % vp;
            vo = vp;
            vp = vd;
        }
       
        if (vo == 1){
            return 1;
        } else{
            return 0;
        }
    
}

int mdc_estendido(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    int x1, y1;
    int mdc = mdc_estendido(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;

    return mdc;
}

int inverso(int G, int n) {
    int x, y;
    int mdc = mdc_estendido(G, n, &x, &y);

    if (mdc != 1) {
        return -1; 
    } 

    return (x % n + n) % n;
}

//passo 3
int divi(int c,int d,int f){
    int vf = ((c % f) * (d % f))% f;
    return vf;
}

//passo 5
int primo(int a){
    int q =0;
    for(int i=1; i <= a; i++){
        if(a % i == 0){
            q ++;
        }
    }
    if(q > 2 && a != 1){
        return 0;
    } else {
        return 1;
    }
}

//passo 6
int fermat(int a){
    int x1 = a -1;
    return x1;
}

//passo 7
int euler(int a){
    int x1 = 0;
    for(int t = (a - 1); t > 0; t--){
        if(coprimo(t,a)){
            x1 ++;
        }
    }

    return x1;
}

//passo 8
int divisib(int c,int b){
    int d = 0;
    for(int r = 0; (r*c) <=  b; r++){
            d ++;
    }
    return d;
}

//passo 9
int expo(int b, int x, int m) {
    int result = 1;
    b = b % m;  
    while (x > 0) {
        if (x % 2 == 1) {       
            result = (result * b) % m;
        }
        b = (b * b) % m;        
        x = x / 2;              
    }
    return result;
}

int main(){
    printf("vamos comecar agora o exercicio 9 da primeira prova de md2\n");
    printf("insira um numero H \n");
    int H;
    scanf("%d", &H);

    printf("insira um numero G \n");
    int G;
    scanf("%d", &G);

    printf("insira um numero n \n");
    int n;
    scanf("%d", &n);

    printf("insira um numero x \n");
    int x;
    scanf("%d", &x);

    printf("insira um numero n1 \n");
    int n1;
    scanf("%d", &n1);

    int inv = 0;

    printf("primeiro verificamos se os numeros %d e %d sao coprimos por meio do algoritmo de euclides\n",G,n);
    if (coprimo(G,n)) {
        printf("os numeros %d e %d sao coprimos \n", G, n);
         inv = inverso(G,n);
        printf("a partir disso devemos, por recursividade, preucurar o numero inverso de %d no universo %d\n",G,n);
        printf("o inverso de %d em Z%d e: %d\n", G, n, inv);
        printf("Teste: %d * %d mod %d = %d\n", G, inv, n, (G * inv) % n);
        printf("podemos agora seguir para os proximos passos\n");
    } else {
        
        printf("os numeros %d e %d  nao sao coprimos\n logo nao podemos proseguir com a operaçao", G, n);
        return 0;
    }
    printf("agora multiplicamos o %d pelo numero inverso que acabamos de achar\n",H);
    
    int A = divi(H,inv,n);
    printf("fazendo ((%d mod %d )*(%d mod %d)) mod %d\n temos que o resultado sera %d\n",H,n,inv,n,n,A);


    printf("agora com o numero que achamos, podemos ir para o proximo passo\n");
    printf("verificamos agora se os numeros a (%d) e n1(%d) sao coprimos\n",A,n1);
    if (coprimo(A,n1)){
        printf("os numeros %d e %d sao coprimos \n", A, n1);
    }else {
        
        printf("os numeros %d e %d  nao sao coprimos não podemos seguir\n", A, n1);
        return 0;
    }

    int X1 = 0;
    printf("agora prisamos saber se o numero n1 (%d) e primo para saber qual teorema iremos usar\n",n1);
    if(primo(n1)){
        X1 = fermat(n1);
        printf("como %d e primo, iremos utilizar o pequeno teorema de fermat, qual x1 = n -1\n",n1);
        printf("com isso conseguimos descobrir que x1 vale %d\n", X1);

    }else{
        X1 = euler(n1); 
        printf("como %d nao é primo, iremos utilizar o teorema de euler, qual x1= a quantidade de coprimos de n menores q n\n",n1);
         printf("com isso conseguimos descobrir que x vale %d\n", X1);
    }

    int d = divisib(X1,inv);
    int R = x - X1 * d;
    if (R < 0){
        while(R<0){
            d --;
            R = x - X1 * d;
        }
    }

    printf("o expoente x pode ser escrito como: %d = %d*%d + %d\n",x,X1,d,R);
    printf("com isso podemos rescrever a equacao %d^%d mod %d como %d^%d = ((((%d^%d)^%d)mod %d)*((%d ^%d)mod %d)",A,x,n1,A,x,A,X1,d,n1,A,R,n1);
    int r1 = expo(A,X1,n1);
    int r2 = expo(r1,d,n1);
    int r3 = expo(A,R,n1);
    int F = (r2 * r3)%n1;

    printf("calculando (%d^%d)^%d)mod %d temos que o resultado e %d e calculando (%d ^%d)mod %d temos que o resultado e %d\n",A,X1,d,n1,r2,A,R,n1,r3);
    printf("com esses resultados temos que (((%d^%d)^%d)mod %d)*((%d ^%d)mod %d) mod %d) sera igual a %d\n",A,X1,d,n1,A,R,n1,n1,F);
    printf("com isso finalizamos a questao 9 da prova de md2, obrigado pela atenaoo");
    return 0;
}