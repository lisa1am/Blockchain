
/* Copyright 2014, Kenneth MacKay. Licensed under the BSD 2-clause license. */

#include "uECC.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
 





void vli_print(char *str, uint8_t *vli, unsigned int size) {
    printf("%s ", str);
    for(unsigned i=0; i<size; ++i) {
        printf("%02X ", (unsigned)vli[i]);
    }
    printf("\n");
}



int main() {

    int i=0;
    int success;
    uint8_t privateA[32], privateB[32];
    uint8_t publicA[64], publicB[64];
    uint8_t public_computed[64];
    uint8_t sig[64];
    uint8_t hash[32];
    int randm;


    
    const struct uECC_Curve_t * curves[1];
    int num_curves = 0;
    #if uECC_SUPPORTS_secp256r1
        curves[num_curves++] = uECC_secp256r1();
    #endif

   
    printf("\n\n**********************GENERATE********************\n\n");


    // Generate two pai of keys A and B
	uECC_make_key(publicA, privateA, curves[0]);
    uECC_make_key(publicB, privateB, curves[0]);
    

    vli_print("Private key A = \n", privateA, sizeof(privateA));
    vli_print("Public key A = \n", publicA, sizeof(publicA));

    printf("\n");

    vli_print("Private key B = \n", privateB, sizeof(privateB));
    vli_print("Public key B = \n", publicB, sizeof(publicB));

    printf("\n");

    // takes random hash for testing
	memcpy(hash, publicB, sizeof(hash));
	vli_print("The hash to sign is = \n", hash, sizeof(hash));

    printf("\n");

	uECC_sign(privateA, hash, sizeof(hash), sig, curves[randm]);
	vli_print("Signature with private key A = \n", sig, sizeof(sig));

	printf("\n");


    printf("Verify signature with public key A : \n");
	if(uECC_verify(publicA, hash, sizeof(hash), sig, curves[0])){
		printf("VALID SIGNATURE !\n");
	}
	else{
		printf("NON VALID SIGNATURE !\n");
	}

    printf("Verify signature with public key B : \n");
    if(uECC_verify(publicB, hash, sizeof(hash), sig, curves[0])){
        printf("VALID SIGNATURE !\n");
    }
    else{
        printf("NON VALID SIGNATURE !\n");
    }


    return 0;

}

