#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>

int hexadecimalToDecimal(char hexVal[]) 
{    
    int len = strlen(hexVal); 
      
    // Initializing base value to 1, i.e 16^0 
    int base = 1; 
      
    int dec_val = 0; 
    //first convert all to uppercase
    // printf("\nString now is %s", strupr(hexVal));
    
      
    // Extracting characters as digits from last character 
    for (int i=len-1; i>=0; i--) 
    {    
        // if character lies in '0'-'9', converting  
        // it to integral 0-9 by subtracting 48 from 
        // ASCII value. 

      


        if (hexVal[i]>='0' && hexVal[i]<='9') 
        { 
            dec_val += (hexVal[i] - 48)*base; 
                  
            // incrementing base by power 
            base = base * 16; 
        } 
  
        // if character lies in 'A'-'F' , converting  
        // it to integral 10 - 15 by subtracting 55  
        // from ASCII value 

        

        else if ((hexVal[i]>='A' && hexVal[i]<='F') || (hexVal[i]>='a' && hexVal[i]<='f'))
        { 
            dec_val += (toupper(hexVal[i]) - 55)*base; 
          
            // incrementing base by power 
            base = base*16; 
        } 
    } 
    // printf("\nDecimal value is %d \n", dec_val);
    return dec_val; 
} 
unsigned int stringToHex(char line[])
{
	unsigned int hex=0x0;
	int n;
	n=hexadecimalToDecimal(line);
	hex=n;
	return hex;
}

// need a decimal to hex functionality
unsigned int decimal_to_hex(int dec){
    char hexadecimal[100];
    long quotient, remainder;
    quotient = dec;
    int j = 0;
    while(quotient != 0){
        remainder = quotient % 16;
        if(remainder < 10)
            hexadecimal[j++] = 48 + remainder;
        else
        {
            hexadecimal[j++] = 55 + remainder;
        }
        quotient = quotient / 16;
        
    }
    unsigned int hex = stringToHex(hexadecimal);
    return hex;
}

int main()
{
	FILE *fint,*ftab,*flen,*fsym;
	int op1[10],txtlen,txtlen1,i,j=0,len;
	char add[5],symadd[5],op[5],start[10],temp[30],line[20],label[20],mne[10],operand[10],symtab[10],opmne[10];

    unsigned int hex_len;
	//clrscr();
	fint=fopen("full_output.txt","r");
	flen=fopen("length.txt","r");
	ftab=fopen("OPTAB.txt","r");
	fsym=fopen("SYMTAB.txt","r");
	fscanf(fint,"%s%s%s%s",add,label,mne,operand);
	if(strcmp(mne,"START")==0)
	{
		strcpy(start,operand);
		fscanf(flen,"%x",&hex_len);
	}
		printf("H^%s^%s^000%x\nT^00%s^",label,start,hex_len,start);
		fscanf(fint,"%s%s%s%s",add,label,mne,operand);
		while(strcmp(mne,"END")!=0)
		{
			fscanf(ftab,"%s%s",opmne,op);
			while(!feof(ftab))
			{
				if(strcmp(mne,opmne)==0)
				{
					fclose(ftab);
					fscanf(fsym,"%s%s",symadd,symtab);
					while(!feof(fsym))
					{
						if(strcmp(operand,symtab)==0)
						{
							printf("%s%s^",op,symadd);
							break;
						}
						else
							fscanf(fsym,"%s%s",symadd,symtab);
					}
					break;
				}
				else
				fscanf(ftab,"%s%s",opmne,op);
			}
			if((strcmp(mne,"BYTE")==0)||(strcmp(mne,"WORD")==0))
			{
				if(strcmp(mne,"WORD")==0)
					printf("0000%s^",operand);
				else if(strcmp(mne, "BYTE") == 0)
				{
					len=strlen(operand);
					for(i=2;i<len;i++)
					{
						printf("%x",operand[i]);
					}
					printf("^");
				}
			}
			fscanf(fint,"%s%s%s%s",add,label,mne,operand);
			ftab=fopen("optab.txt","r");
			fseek(ftab,SEEK_SET,0);
		}
		printf("\nE^00%s",start);
		fclose(fint);
		fclose(ftab);
		fclose(fsym);
		fclose(flen);
		//fclose(fout);
		getch();
	}