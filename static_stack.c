#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STACKSIZE 3


typedef enum inst { //se define la enum
    case0 = 0,
    case1,
    case2,
    case3,
    case4,
    case5,
    case6,

}Inst;

// Def de item

typedef struct item
{
    uint8_t inPin;
    uint32_t inTime;
    int* ptr;
}Item;


// Def de stack

typedef struct stack{
    int top;
    Item vector[STACKSIZE];

}Stack;

size_t count; //Var tipo size_t

//Se definen las funciones

void newStack(Stack* stack);
void push (Stack* stack, Item a);
bool isEmpty (Stack *stack);
void recorrido (Stack *stack);
Item pop (Stack *stack);
int Actions (Stack *stack);


int main () {
//Variables de prueba 
count = 0;
Item item[2];
int z;
item[0].inPin =0;
item[0].inTime =0;

item[1].inPin = 1;
item[1].inTime = 1;

item[2].inPin = 2;
item[2].inTime = 2;

//Variable para stack
Stack stack3;

//Se crea pila y se hace push
newStack(&stack3);
push (&stack3, item[0]);
push (&stack3, item[1]);
push (&stack3, item[2]);

z= Actions (&stack3); //se ejecutan instrucciones

printf ("Fin de la función actions con valor: %d\n", z); //Valor resultante de funcion de instrucciones

return 0;

}

//Funciones

void newStack(Stack* stack){
    stack->top=-1;
}

void push (Stack* stack, Item item){
    if (stack->top == (STACKSIZE -1)){
    printf("La pila está llena");
    }else{
        stack->top ++;
        stack->vector[stack->top] = item;
    }
}


bool isEmpty (Stack *stack){
    if (stack->top == -1){
        return true;
    }else {
        return false;
    }
}

void recorrido (Stack *stack) {
    for (int j=0; j < STACKSIZE; j++){
        printf("El valor del pin de entrada en item en la pila es: %d\n", stack->vector[j].inPin);
    }
}

Item pop (Stack *stack) {
    Item a;
    if (stack->top == -1){
        printf("La pila está vacía");
    }else{
        a = stack->vector[stack->top];
        stack->top--;
        return a;
    }

}

int Actions (Stack *stack) {
    Inst inst; //var de enum
    bool Pin1 = true; // var booleana
    Item aux; // Item aux


       for (int j=0; j<STACKSIZE; j++){
           if (isEmpty(stack)){
             printf ("La pila está vacía\n"); return 0; //en caso que la pila esté vacía se retorna y termina la ejecucion
           }
           else{
            aux = pop(stack); //Se almacena item retornado por stack al hacer pop
            inst = aux.inPin; // se almacena valor de instrucción

            switch (inst){
                case case0: printf("Se hace toogle del pin\n"); Pin1 = !Pin1; break;

                case case1: printf("Valor del Pin1: %s\n", Pin1 ? "true" : "false"); break;

                case case2: printf("Se aumenta valor del contador\n"); count ++; break;

                case case3: printf("El valor del contador es:%zu\n", count);  break;

                case case5:
                    if (isEmpty(stack)){                 
                        printf("La pila está vacía\n"); break;
                    }else{
                        printf("La pila tiene %d\n elementos", (stack->top) +1); break;
                    }
                case case6: 
                    if (stack->top == (STACKSIZE -1)){
                        printf("La pila está llena\n");  return 0;
                    }
                        
                default: break;
            }

        }
       } 
    
    return 0;

}