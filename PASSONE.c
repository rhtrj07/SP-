#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
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
	char opcode[10],operand[10],label1[10],label[10],code[10][10],ch,c; char mnemonic[10][10]={"START","LDA","ADD","MUL","SUB","STA","END"};
	int locctr,start,len,i=0,j=0,address;
	FILE *fp1,*fp2,*fp3,*fp4;
	//clrscr();
 	fp1=fopen("INPUT.txt","r");
 	fp2=fopen("SYMTAB.txt","w");
	fp3=fopen("OUTPUT.txt","w");
	fprintf(fp3,"-\t");
 	fscanf(fp1,"%s%s%s",label,opcode,operand);
	 if(strcmp(opcode,"START")==0)
  	{
		start=atoi(operand);
 		locctr=start;
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
	len=locctr-start;
	printf("\nThe length of the program is %d.\n\n",len);
	printf("\n\nThe contents of Symbol Table :\n\n");
	fp2=fopen("SYMTAB.txt","r");
 	ch=fgetc(fp2);
	while(ch!=EOF)
	{
		printf("%c",ch);
		ch=fgetc(fp2);
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	getch();
}
