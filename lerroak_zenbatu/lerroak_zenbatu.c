#include <stdio.h>
#include <string.h>
#define STDIN_FILEN0 0
#define STDOUT_FILEN0 1 
#define BUFSIZE 512
int main (int argc, char *argv[]){
char a[BUFSIZE];
int c = 0;
int n;
char text[10];
 while ((n = read(STDIN_FILEN0, a, BUFSIZE)) > 0){
	 c++;
	 sprintf(text, "%d", c);
	 write(STDOUT_FILEN0,  text , strlen(text));
	 write(STDOUT_FILEN0, " ", 1);
	 write(STDOUT_FILEN0, a, n);

}
return 0;
}
