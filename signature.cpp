

#include <stdlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <iostream>



#include "uECC.h"

using namespace std;

const struct uECC_Curve_t * curves[1];



int size = 32;



void vli_print( uint8_t *vli, unsigned int size) {
    for(unsigned i=0; i<size; ++i) {
        printf("%02X ", (unsigned)vli[i]);
    }
    printf("\n");
}


void substr(char s[], char sub[], int p, int l) {
   int c = 0;
   while (c < l) {
      sub[c] = s[p+c-1];
      c++;
   }
   sub[c] = '\0';
}


void from_string(char str[], uint8_t arr[]) {

  int cum = 1;
  int step = 3;
  int i;
  for (i = 0; cum < strlen(str); i++) {
    char sub[step];
    substr(str, sub,cum, step);
    if(atoi(sub) > 255) {
      substr(str, sub,cum, step-1);
      cum += step - 1;
    } else cum += step;
    arr[i] = atoi(sub);
    }
	size = i;
}

 
void to_string(uint8_t arr[], char str[]) {

  char* s_buff = (char*)malloc(sizeof(char)*3);
  for (int i = 0; i < size; i++) {
      if(arr[i] != 0) {
        sprintf(s_buff, "%d", arr[i]);
        strcat(str, s_buff);
      }
  }
}


void generatePairKey(char priv[], char pub[]){

	#if uECC_SUPPORTS_secp256r1
	    curves[0] = uECC_secp256r1();
	#endif

	uint8_t privateKeyInt[32];
	uint8_t publicKeyInt[64];

	uECC_make_key(publicKeyInt, privateKeyInt,curves[0]);

	cout << "\nPRIV INT = ";
	vli_print(privateKeyInt, sizeof(privateKeyInt));
	cout << "\nPUB INT = ";
	vli_print(publicKeyInt, sizeof(publicKeyInt));


	to_string(publicKeyInt, pub);
	to_string(privateKeyInt, priv);
}


void sign(char priv[], char hash_code[], char sig[]){

	#if uECC_SUPPORTS_secp256r1
	    curves[0] = uECC_secp256r1();
	#endif
	
	uint8_t privateKeyInt[32];
	uint8_t hashInt[32];
	uint8_t sigInt[64];

	from_string(priv,privateKeyInt);
	from_string(hash_code, hashInt);

	uECC_sign(privateKeyInt, hashInt, sizeof(hashInt), sigInt, curves[0]);


	/*cout << "\n\nPRIV INT = ";
	vli_print(privateKeyInt, sizeof(privateKeyInt));
	cout << "\nHASH INT = ";
	vli_print(hashInt, sizeof(hashInt));
	cout << "\nSIG INT = ";
	vli_print(sigInt, sizeof(sigInt));*/

	to_string(sigInt, sig);
}

bool verify(char pub[], char hash_code[], char sig[]){

	#if uECC_SUPPORTS_secp256r1
	    curves[0] = uECC_secp256r1();
	#endif

	uint8_t publicKeyInt[64];
	uint8_t hashInt[32];
	uint8_t sigInt[64];

	from_string(pub, publicKeyInt);
	from_string(hash_code, hashInt);

	if(uECC_verify(publicKeyInt, hashInt, sizeof(hashInt), sigInt, curves[0])){
		to_string(sigInt, sig);
		return true;
	}
	else{
		return false;
	}
}


int main(){
	/*char priv[100], pub[100], hash_code[100], sig[100];

	generatePairKey(priv, pub);
	std::cout << "\nPRIVATE KEY = " << priv;
	std::cout << "\n\nPUBLIC KEY = " << pub;
	sign(priv, hash_code, sig);
	std::cout << "\nSIGNATURE = " << sig;
	std::cout << verify(pub, hash_code,sig) << "\n";*/

}



