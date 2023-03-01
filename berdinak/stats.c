#include <sys/stat.h>
#include <stdio.h>
int main (int argc, char *argv[]){

char *fitx_izena = argv[1];       // parametro moduan jasotako fitxategiaren izena
struct stat stat_egitura;         // erazagutu aldagaia fitxategiaren metainformazioa metadata
stat(fitx_izena, &stat_egitura);   // eskuratu fitxategiaren metadata
off_t tamaina = stat_egitura.st_size; // eskuratu tamaina
printf("Fitxategiaren tamaina %lu byte da\n", tamaina);

}
