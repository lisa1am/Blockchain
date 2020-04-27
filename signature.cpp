

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


void to_string(uint8_t arr[], char str[], int size) {
 
 char* s_buff = (char*)malloc(sizeof(char)*2);
 for (int i = 0; i < size; i++) {
 sprintf(s_buff, "%x", arr[i]);
 if(arr[i]>15) {
 strcat(str, s_buff);
 } else {

 strcat(str, "0");
  strcat(str, s_buff);
 }
 }
}
void from_string(char str[], uint8_t arr[]) {
 int cum = 1;
 int step = 2;
 int i;
 for (i = 0; cum < strlen(str); i++) {
 char sub[step];
 substr(str, sub,cum, step);
 cum +=step;
 arr[i] = strtol(sub, NULL, 16);
 }
}
void generatePairKey(char priv[], char pub[]){

	#if uECC_SUPPORTS_secp256r1
	    curves[0] = uECC_secp256r1();
	#endif

	uint8_t privateKeyInt[32];
	uint8_t publicKeyInt[64];

	uECC_make_key(publicKeyInt, privateKeyInt,curves[0]);

	cout << "\nPUBLIC = \n";
	for(int i=0; i<64; i++){
		printf("%d,",publicKeyInt[i]);
	}
	cout << "\n";

	cout << "\nPRIVATE = \n";
	for(int i=0; i<32; i++){
		printf("%d,",privateKeyInt[i]);
	}
	cout << "\n";


	to_string(publicKeyInt, pub, 64);
	to_string(privateKeyInt, priv, 32);
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


	to_string(sigInt, sig, 64);
	std::cout << "\nSIGNATURE CHAR SIGN() = \n" << sig;


	cout << "\nSIGNATURE BASE 10 SIGN() = \n";
	for(int i=0; i<64; i++){
		printf("%d,",sigInt[i]);
	}
	cout << "\n";
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
	from_string(sig, sigInt);

	std::cout << "\nSIGNATURE CHAR VERIFY() = \n" << sig;

	cout << "\nSIGNATURE BASE 10 VERIFY() = \n";
	for(int i=0; i<64; i++){
		printf("%d,", sigInt[i]);
	}
	cout << "\n";


	uECC_verify(publicKeyInt, hashInt, sizeof(hashInt), sigInt, curves[0]);
	if(uECC_verify(publicKeyInt, hashInt, sizeof(hashInt), sigInt, curves[0])){
		cout << "\nVERIFIED!";
		return true;
	}
	else{
		return false;
	}
}


int main(){
	char priv[500], pub[500], hash_code[500], sig[500], sigTest[500];
	uint8_t sigInt[64];

	generatePairKey(priv, pub);
	cout << "-------------->\n" << priv << "\n" << pub;
	sign(priv, hash_code, sig);
	std::cout << "\nSIGNATURE MAIN = \n" << sig;
	from_string(sig, sigInt);
	cout << "\nSIGNATURE BASE 10 MAIN = \n";
	for(int i=0; i<64; i++){
		printf("%d,", sigInt[i]);
	}
	
	to_string(sigInt, sigTest, 64);
	cout << "\nSIGNATURE APRES TO_STRING MAIN = \n" << sigTest;
	cout << "\n";
	std::cout <<  verify(pub, hash_code,sig) << "\n";

}



