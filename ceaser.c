#include<stdio.h>
#include<string.h>
#include<ctype.h>


#define max_length 500
#define max_key 50

void autokey_decrypt(char *ciphertext, char *key, char* planttext){
    int c_len = strlen(ciphertext);
    int k_len = strlen(key);


    //check if the output is larger enough
    if (c_len >= max_length) 
    {
        printf("ciphertext is so lonng noooooo");
        return;
    }
    

    for (int i = 0; i < c_len; i++)
    {
        //convert from the ciphertext to Number 
        int c_val = toupper(ciphertext[i]) - 'A';
        int k_val;

        if (i < k_len)
        {
            k_val = toupper(key[i]) - 'A';
        } else {
            k_val = toupper(planttext[i - k_len]) - 'A';
        }
        int p_val = (c_val - k_val + 26) % 26; 

        planttext[i] = p_val + 'A';
    }   
    planttext[c_len] = '\0';
}


int main(){
    char ciphertext[max_length], key[max_key], planttext[max_length];
    
    char user_choise[max_length] = fgets(user_choise,max_length,stdin);
    if ( user_choise == "decrypt")
    {
        printf("Input the ciphertext:");
        if (fgets(ciphertext,max_length,stdin)== NULL)  
        {
            printf("you are not input into it ");
            return 1;
        }
        ciphertext[strcspn(ciphertext,"\n")] = 0;
        
        printf("Input the key:");
        if(fgets(key,max_key,stdin)==NULL){
            printf("your not input the key ");
            return 1;
        }
        key[strcspn(key,"\n")] = 0;

        autokey_decrypt(ciphertext,key,planttext);

        printf("%s\n",planttext);

    } else if (user_choise == "encrypt"){

        printf("Input the ciphertext:");
        if (fgets(ciphertext,max_length,stdin)== NULL)  
        {
            printf("you are not input into it ");
            return 1;
        }
        ciphertext[strcspn(ciphertext,"\n")] = 0;

        printf("Input the ciphertext:");
        if (fgets(planttext,max_length,stdin)== NULL)  
        {
            printf("you are not input into it ");
            return 1;
        }
        planttext[strcspn(planttext,"\n")] = 0;
        autokey_decrypt(ciphertext,key,planttext);
    } else {
        printf("No input of user");
        return 1;
    }
    return 0;
}