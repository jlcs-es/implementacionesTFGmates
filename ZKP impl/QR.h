//
// Created by JL on 10/05/2017.
//

#ifndef ZKP_IMPL_QR_H
#define ZKP_IMPL_QR_H

#include <gmp.h>

/*
1. Prover_FirstProtocolStep(s,N) -> r aleatorio, u=r^2(N) residuo cuadrático.
2. Verifier_SecondProtocolStep(x,N,u) -> b un bit aleatorio. [Aquí la función podría no recibir parámetros]
3. Prover_ThirdProtocolStep(s,N,r,b) -> w = r * (s^b) (N)
4. Verifier_CheckProof(x,N,u,b,w) -> Bool
5. QR_Protocol(s,N) -> Vista de interacción entre P y V honestos.
 */

void Prover_FirstProtocolStep(mpz_t N, mpz_t &r, mpz_t &u);
short Verifier_SecondProtocolStep();
mpz_t Prover_ThirdProtocolStep(mpz_t s, mpz_t N, mpz_t r, short b);
bool Verifier_CheckProof(mpz_t x, mpz_t N, mpz_t u, short b, mpz_t w);
bool QR_Protocol(mpz_t s, mpz_t N, int rondas);

#endif //ZKP_IMPL_QR_H
