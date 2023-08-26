#include<bits/stdc++.h>
#include "ASE.h"
using namespace std;
map<int,unsigned char> mp;

void map_element(){

    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            mp[i*16+j]=sbox[i][j];
        }
    }

}


void make_key(unsigned char key[4][4]){
    map_element();
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            int num=rand()%256;
            key[i][j]=mp[num];
        }
    }

}