#include <stdio.h>

float pay(float *montant, float taux, float paiementMensuel) {
    float res =  *montant + (*montant * (taux/100/12)) - paiementMensuel;
    *montant = res;
    return res;
}

int main()
{
    float montant = 20000;
    float taux = 6;
    float paiementMensuel = 386.66;
    
    printf("1 %f\n", pay(&montant, taux, paiementMensuel));
    printf("2 %f\n", pay(&montant, taux, paiementMensuel));
    printf("3 %f\n", pay(&montant, taux, paiementMensuel));
}