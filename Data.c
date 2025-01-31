#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_NAME_SIZE 12 //máximo arreglo de 12 

//def de estructura de item

typedef struct ITEM_TYPE {
    uint8_t Bateria;
    int16_t Temperatura;
    int32_t Nivelmain;
    uint32_t Nivelreserve;
    uint16_t Checksum;

} item_type;

item_type create (uint8_t *a);

int main () {
    //Def de variables 
    uint8_t x[MAX_NAME_SIZE];
    item_type y;
    //Var de prueba

    x[0]= 0x90;
    x[1]= 0xFF; 
    x[2]= 0x00; 
    x[3]= 0xFF;
    x[4]= 0xFF;
    x[5]= 0xFF;
    x[6]= 0x80;
    x[7]= 0x00;
    x[8]= 0x00;
    x[9]= 0x01;
    x[10] = 0xFF;
    x[11] = 0xFF;

    y = create(x); //se invoca función

//se imprimen valores
    printf ("El valor de Batería es: %u\n", y.Bateria);
    printf ("El valor de la Temperatura: %d\n", y.Temperatura);
    printf ("El valor del Nivel Main: %d\n", y.Nivelmain);
    printf ("El valor del Nivel Reserva: %u\n", y.Nivelreserve);
    printf ("El valor del Checksum: %u\n", y.Checksum);
    
    return 0;
}

//función create
item_type create (uint8_t *a) {

    item_type z;
    //se hace casting y shifting de acuerdo con los requeriminetos
    z.Bateria= a[0];
    z.Temperatura = (int16_t)(a[1]<<8 | a[2]);
    z.Nivelmain = (int32_t)(a[3]<<16 | a[4]<<8 | a[5]);                
    z.Nivelreserve = (int32_t)(a[6] << 24 | a[7] << 16 | a[8] << 8 | a[9]);
    z.Checksum = (uint16_t)(a[10]<<8 | a[11]);
    return z; //se retorna estructura
   
}
