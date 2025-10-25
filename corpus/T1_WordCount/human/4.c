#include<stdio.h>
#include<stdlib.h>

int characount(char*c);
int linecount(char*l);
int wordcount(char*w);


int characount(char*c)
{
 int i=0,j=0;
 for(i=0;c[i]!='\0';i++);
 /*{
  if(c[i]>31 && c[i]<127)
  {
     j++;
  }
 }*/

 return i;
 

}

int linecount(char*l)
{
 int i=0,j=0;
 for(i=0;l[i]!='\0';i++)
 {
  if(l[i]=='\n')
  {
    j++;
  }
 }
 return j;
}

int wordcount(char*w)
{
 int i=0,j=0;
 for(i=0;w[i]!='\0';i++)
 {
  
 if(w[i]==' '||w[i]=='\n'||w[i]=='\t'||w[i]=='\r')
  {
    j++;
  }
 while(!(w[i]>32 && w[i]<127))
 {
    i++;
    if(w[i]=='\0')
    {
     break;
    }
 }
    
 }
 return j;

}

int main(int argc, char *argv[])
{
 int i;
 int multi;
 FILE*f;
 int filesize;
 char*data;
 char*basedata;
 
 for(multi=1;multi<argc;multi++)

 {
 f=fopen(argv[1],"r");
 fseek(f,0,SEEK_END);
 filesize=ftell(f);

 data=(char*)malloc(filesize);
 basedata=data;
 fseek(f,0,SEEK_SET);
 
 for(i=0;i<filesize;i++,data++)
 {
  *data=fgetc(f);
 }

 
 
 fclose(f);

  printf("%d ",linecount(basedata));
  printf("%d ",wordcount(basedata));
  printf("%d ",characount(basedata));
  printf("%s \n",argv[multi]);
 
 free(basedata);
}
}
 
