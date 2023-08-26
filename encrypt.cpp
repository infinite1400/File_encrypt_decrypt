#include<bits/stdc++.h>
#include "ASE.h"
using namespace std;
void make_key(unsigned char key[4][4]){
    map<int,unsigned char> mp;
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            mp[i*16+j]=sbox[i][j];
        }
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            srand(time(0));
            int num=rand()%256;
            key[i][j]=mp[num];
        }
    }

}

void SubBytes(unsigned char state[4][4]){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            unsigned char temp=state[i][j];
            state[i][j]=sbox[temp/16][temp%16];
        }
    }
}

void ShiftRows(unsigned char state[4][4]){
    int left_shift=0;
    for(int i=0;i<4;i++){
        unsigned char temp[4];
        for(int j=0;j<4;j++){
            temp[j]=state[i][(j+left_shift)%4];
        }
        for(int j=0;j<4;j++){
            state[i][j]=temp[j];
        }
        left_shift++;
    }

}

void MixColumns(unsigned char state[4][4]){
    unsigned char temp[4][4];
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            temp[i][j]=state[i][j];
        }
    }
    
    for(int i=0;i<4;i++){
        for(int k=0;k<4;k++){
            for(int j=0;j<4;j++){
                if(matrix[i][k]==1){
                    temp[i][j] ^=state[k][j];
                }
                else{
                    temp[i][j] ^=GF_MUL_TABLE[matrix[i][k]][state[k][j]];
                }
            }
        }
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            state[i][j]=temp[i][j];
        }
    }

}

void AddRoundKey(unsigned char state[4][4],unsigned char key[4][4]){
    
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            state[i][j] ^=key[i][j];
        }
    }

}

void Round(unsigned char state[4][4],unsigned char key[4][4]){
    SubBytes(state);
    ShiftRows(state);
    MixColumns(state);
    AddRoundKey(state,key);
}

void LastRound(unsigned char state[4][4],unsigned char key[4][4]){
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state,key);
}

void encrypt(unsigned char state[4][4],unsigned char key[4][4],unsigned char message[4][4]){
    
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            state[i][j]=message[i][j];
        }
    }

    int number_of_rounds=10;
    AddRoundKey(state,key);
    for(int i=0;i<number_of_rounds-1;i++){
        Round(state,key);
    }

    LastRound(state,key);

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            message[i][j]=state[i][j];
        }
    }
}
int main(){
    unsigned char state[4][4];
    unsigned char message[4][4];
    unsigned char key[4][4];
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cin>>message[i][j];
        }
    }
    make_key(key);
    encrypt(state,key,message);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cout<<(int)message[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}