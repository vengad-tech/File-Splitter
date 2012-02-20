#include<stdio.h>
void encrypt_data(FILE* input_file, FILE* output_file, char* key)
{
	int key_count = 0; 
	int encrypt_byte;

	
	while( (encrypt_byte = fgetc(input_file)) != EOF) 
	{
		
		fputc(encrypt_byte ^ *(key+key_count), output_file);

		
		key_count++;
		if(key_count == strlen(key))
			key_count = 0;
	}
}
void writefile(FILE* input_file,FILE *output_file,int size)
{
     int i = 0 ;
     int encrypt_byte;
     encrypt_byte = fgetc(input_file);
     while((i<=size||size==-1) && encrypt_byte!=EOF)
     {
           
	       fputc(encrypt_byte , output_file); 
           encrypt_byte = fgetc(input_file); 
           i++;      
     }
     
}
int main()
{
  FILE *old,*new,*new1,*one,*two;
  int sz;
  char *key="password12345";
  old = fopen("database.txt","r");
  new = fopen("database_enc.txt","w");
  encrypt_data(old,new,key);
  fclose(old);
  fclose(new);
  
  new = fopen("database_enc.txt","r");
  new1=fopen("database_enc.txt","r");
  one=fopen("one.txt","w");
  two=fopen("two.txt","w");
  fseek(new,0,SEEK_END);
  sz = ftell(new);
  printf("sz is %d\n",sz);
  fseek(new,0,SEEK_SET);
  
 
       writefile(new,one,sz/2);
       fseek(new1,sz/2+1, SEEK_SET);
       writefile(new1,two,sz-(sz/2));
  fclose(new);
  fclose(new1);
  fclose(one);
  fclose(two);   
     
 //joing the file to orginal file
 one=fopen("one.txt","r");
 two=fopen("two.txt","r");
 old=fopen("database_join.txt","w");
 writefile(one,old,-1);
 writefile(two,old,-1);
 fclose(one);
 fclose(two);
 fclose(old);
 old=fopen("database_join.txt","r");
 new=fopen("database_final.txt","w");
  encrypt_data(old,new,key);            
  
 return 0;   
}
