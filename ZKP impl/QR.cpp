//
// Created by JL on 10/05/2017.
//

#include <cstdlib>
#include "QR.h"


void Prover_FirstProtocolStep(mpz_t N, mpz_t &r, mpz_t &u){
/*
    Elegir aleatoriamente r entre 1 y N-1.
*   Calcular u = r*r mod N.
    Devolver (r,u).
 */
    mpz_init(r);
    gmp_randstate_t state; gmp_randinit_default(state); // Generador de números aleatorios
    mpz_urandomm (r, state, N); // Obtener un r aleatorio entre 1 y N-1
    gmp_randclear(state);   // Liberar memoria del RNG

    mpz_init(u);
    mpz_mul(u, r, r);
    mpz_mod(u,u,N);
}

short Verifier_SecondProtocolStep(){
//    Elegir b aleatoriamente entre 0 y 1.
//    Devolver b.
    return rand() & 1;   // srand() se llama en main()
}

mpz_t Prover_ThirdProtocolStep(mpz_t s, mpz_t N, mpz_t r, short b){
/*
    SI b=0
    ENTONCES
        Devolver w=r.
    SI NO
*       Calcular w = r * s mod N.
        Devolver w.
    FIN_SI
*/

    if(b==0){
        return r;
    }else{
        mpz_t w; mpz_init(w);
        mpz_mul(w,r,s);
        mpz_mod(w,w,N);
        return w;
    }

}

bool Verifier_CheckProof(mpz_t x, mpz_t N, mpz_t u, short b, mpz_t w){
/*
*   Calcular w2 = w*w mod N
    SI b=1
    ENTONCES
*       Calcular v = u*x mod N
    SI NO
*       Calcular v = u mod N
    FIN_SI
    Devolver si w2 == v.
 */

    mpz_t w2; mpz_init(w2);
    mpz_t v; mpz_init(v);
    if(b==1){
        mpz_mul(v,u,x);
        mpz_mod(v,v,N);
    }else{
        mpz_mod(v,u,N);
    }
    bool verify = false;
    if(mpz_cmp(w2,v)==0) verify=true;   // mpz_cmp devuelve 0 si son iguales, otro valor si son distintos

    mpz_clear(w2); mpz_clear(v);    // Liberamos memoria de las variables creadas

    return verify;
}

bool QR_Protocol(mpz_t s, mpz_t N, int rondas){
//  Instancia (x,N) tal que x = s^2 mod N
/*
*   Calcular x = s*s mod N
    Vista = nueva lista.
    REPETIR t VECES:
        (r,u) = Prover_FirstProtocolStep(s,N)
        b = Verifier_SecondProtocolStep(x,N,u)
        w = Prover_ThirdProtocolStep(s,N,r,b)
        SI Verifier_CheckProof(x,N,u,b,w) == TRUE
        ENTONCES
            Añadir (u,b,w) a Vista // o imprimir los valores
        SI NO
            Devolver FALSE.
        FIN_SI
    FIN_REPETIR
    Devolver TRUE.
*/

    mpz_t x; mpz_init(x);   // El residuo cuadrático x = s^2 mod N
    mpz_mul(x,s,s); mpz_mod(x,x,N);

    mpz_t r, u, w;

    int i;
    for(i=0; i<rondas; i++){
        Prover_FirstProtocolStep(N,r,u);
        short b = Verifier_SecondProtocolStep();
        w = Prover_ThirdProtocolStep(s,N,r,b);

        if(Verifier_CheckProof(x,N,u,b,w)){
            //TODO
        }else{
            // print error
            break;
        }
    }

    mpz_clear(x); mpz_clear(r); mpz_clear(u); mpz_clear(w);

    if(i<rondas)
        return false;
    else
        return true;
}