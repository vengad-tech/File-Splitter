#include<stdio.h>
#include <mpi.h>
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
int main( int argc,char *argv[])
{
  FILE *old,*new,*new1,*one,*two;
  int sz;
  char *key="password12345";
  int rank, size;

  MPI_Init (&argc, &argv);	
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);	
  MPI_Comm_size (MPI_COMM_WORLD, &size);
if(rank==0)
{
  old = fopen("database.txt","r");
  new = fopen("database_enc.txt","w");
  encrypt_data(old,new,key);
  fclose(old);
  fclose(new);
}
MPI_Barrier(MPI_COMM_WORLD);
  
  new = fopen("database_enc.txt","r");
  new1=fopen("database_enc.txt","r");

  fseek(new,0,SEEK_END);
  sz = ftell(new);
  printf("sz is %d\n",sz);
  fseek(new,0,SEEK_SET);
    
if(rank==0)
{
 one=fopen("one.txt","w");
       writefile(new,one,sz/2);
       fclose(one);
}
if(rank==1)
{
       fseek(new1,sz/2+1, SEEK_SET);
         two=fopen("two.txt","w");
       writefile(new1,two,sz-(sz/2));
        fclose(two); 
}
  fclose(new);
  fclose(new1);
  
   
     
 //joing the file to orginal file
 if(rank==0)
 {
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
}   
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
 return 0;   
}
