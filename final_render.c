#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
/*
int atoi(char* str) 
{ 
	int res = 0; 
	for (int i = 0; str[i] != '\0'; ++i) 
	res = res * 10 + str[i] - '0'; 
	return res;
} */
int main()
{	
	char opcode[10],label1[10],code[10][10],ch,c,add[5],symadd[5],op[5],start[10],temp[30],line[20],label[20],mne[10],operand[10],symtab[10],opmne[10];; char mnemonic[10][10]={"START","LDA","ADD","MUL","SUB","STA","END"};
	int locctr,start1,i=0,j=0,address,op1[10],txtlen,txtlen1,len;
	FILE *fp1,*fp2,*fp3,*fp4,*fint,*ftab,*flen,*fsym;
	//clrscr();
 	fp1=fopen("INPUT.txt","r");
 	fp2=fopen("SYMTAB.txt","w");
	fp3=fopen("OUTPUT.txt","w");
	fp4=fopen("LENGTH.txt","w");
	fprintf(fp3,"-\t");
 	fscanf(fp1,"%s%s%s",label,opcode,operand);
	 if(strcmp(opcode,"START")==0)
  	{
		start1=atoi(operand);
 		locctr=start1;
		fprintf(fp3,"%s\t%s\t%s\n",label,opcode,operand);
		fscanf(fp1,"%s%s%s",label,opcode,operand);
	}
	else
		locctr=0;
	while(strcmp(opcode,"END")!=0)
	{
		fprintf(fp3,"%d",locctr);
	
	/*	fp4=fopen("SYMTAB.txt","w");
		fscanf(fp4,"%d%s",address,label1);
		c=fgetc(fp4);
		while(c!=EOF)
		{	
			if(strcmp(label,label1)==0)
			{	printf("Invalid Entry");
				exit(0);
			}
			fscanf(fp4,"%s%s",label1,address);
			c=fgetc(fp4);
		}
		fclose(fp4);
	*/
		if(strcmp(label,"-")!=0)
			fprintf(fp2,"%d\t%s\n",locctr,label);
		//strcpy(code[i],mnemonic[j]);
		while(strcmp(mnemonic[j],"END")!=0)
		{
			if(strcmp(opcode,mnemonic[j])==0)
			{
				locctr+=3;
				break;
			}
			//strcpy(code[i],mnemonic[j]);
			j++;
		}
  		if(strcmp(opcode,"WORD")==0)
			locctr+=3;
		else if(strcmp(opcode,"RESW")==0)
			locctr+=(3*(atoi(operand)));
		else if(strcmp(opcode,"RESB")==0)
			locctr+=(atoi(operand));
		else if(strcmp(opcode,"BYTE")==0)
			++locctr;
		fprintf(fp3,"\t%s\t%s\t%s\n",label,opcode,operand);
		fscanf(fp1,"%s%s%s",label,opcode,operand);
	}
	fprintf(fp3,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	printf("\n\nThe contents of Input Table :\n\n");
	fp1=fopen("INPUT.txt","r");
	ch=fgetc(fp1);
	while(ch!=EOF)
	{
		printf("%c",ch);
		ch=fgetc(fp1);
	}
	printf("\n\nThe contents of Output Table :\n\n");
	fp3=fopen("OUTPUT.txt","r");
	ch=fgetc(fp3);
	while(ch!=EOF)
	{
		printf("%c",ch);
		ch=fgetc(fp3);
	}
	len=locctr-start1;
	fprintf(fp4,"%d",len);
	printf("\nThe length of the program is %d.\n\n",len);
	printf("\n\nThe contents of Symbol Table :\n\n");
	fp2=fopen("SYMTAB.txt","r");
 	ch=fgetc(fp2);
	while(ch!=EOF)
	{
		printf("%c",ch);
		ch=fgetc(fp2);
	}
	printf("\n\n\n");
	fint=fopen("OUTPUT.txt","r");
	flen=fopen("LENGTH.txt","r");
	ftab=fopen("OPTAB.txt","r");
	fsym=fopen("SYMTAB.txt","r");
	fscanf(fint,"%s%s%s%s",add,label,mne,operand);
	if(strcmp(mne,"START")==0)
	{
		strcpy(start,operand);
		fscanf(flen,"%d",&len);
	}
	printf("H^%s^%s^%d\nT^00%s^",label,start,len,start);
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
			else
			{
				len=strlen(operand);
				for(i=2;i<len;i++)
				{
					printf("%d",operand[i]);
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
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	getch();
}