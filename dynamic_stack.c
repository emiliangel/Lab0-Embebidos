#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define STACKSIZE 3

typedef enum inst {  //se define la enum
    case0 = 0,
    case1,
    case2,
    case3,
    case4,
    case5,
    case6,

}Inst;

typedef struct item { // se define item
    uint8_t inPin;
    uint32_t inTime;
    int* ptr;
}Item;

typedef struct node{  //se define nodo
    Item *Data;
    struct node *sig;
}Node;

typedef struct stack { // se define stack
    Node *top;
    int size;
}Stack;

//Se definen las funciones
Item* newItem (uint8_t inPin, uint32_t inTime, int *ptr);
Node* newNode (Item * item);
Stack* newStack ();
int isEmpty (Stack *stack);
void Push (Stack *stack, Node *node);
void recorrido (Stack *stack);
Node* Pop (Stack *stack);
int Actions (Stack *stack);

size_t count; //Var tipo size_t

int main () {

//Variables de prueba
uint8_t Pin1 = 3, Pin2=2;
uint32_t Time1 = 2, Time2 = 2;
int a1=8, a2=9;
//Def de variables para stack

int z;
Stack *Stack_a;
Item *Item_a, *Item_b;
Node *Node_a, *Node_b, *Node_c;
count = 0; //Contador size_t
//Se crea pila y se hace push

Stack_a = newStack();
Push(Stack_a, newNode(newItem(Pin1, Time1, &a1)));
Push(Stack_a, newNode(newItem(Pin2, Time2, &a2)));

recorrido(Stack_a); //se recorre pila

z=Actions (Stack_a); //se ejecutan instrucciones
printf ("Fin de la función actions con valor: %d\n", z); //Valor resultante de funcion de instrucciones

return 0;

}

//Prototipo de funciones

Item* newItem (uint8_t inPin, uint32_t inTime, int *ptr){
    Item *aux = (Item*) malloc(sizeof(Item));
    aux -> inPin = inPin;
    aux -> inTime = inTime;
    aux -> ptr = ptr; 
    return aux;
}


Node* newNode (Item * item) {
    Node *aux = (Node*)malloc(sizeof(Node));
    aux -> Data= item;
    aux -> sig= NULL;
    return aux;
}

Stack* newStack () {
    Stack *aux = (Stack*)malloc (sizeof(Node)); //al ingresar primer nodo, se asigna tamaño de un nodo
    aux -> top = NULL; //
    aux -> size = 0;
    return aux;

}

int isEmpty (Stack *stack) {
    if (stack ->size == 0) {
        return 1;
    }else {
        return 0;
    }
}

void Push (Stack *stack, Node *node){
    if (isEmpty (stack)){
        stack->top = node;
        node ->sig = NULL;

    }else{
        node->sig=stack->top;
        stack->top = node;
    }
    stack ->size++;
}


Node* Pop (Stack *stack) {

    Node *aux = stack->top;
    stack->top = stack->top->sig;
  //  free (aux);  
    stack->size--;
    return aux;

}

void recorrido (Stack *stack) {
    Node *aux=stack->top;
    while (aux!=NULL){
        printf("%u, %u, %d\n", aux->Data->inPin, aux->Data->inTime, *(aux->Data->ptr));
        aux = aux->sig;
    }
}

//Funcion de instrucciones 

int Actions (Stack *stack) {
    Inst inst; //var de enum
    bool Pin1 = true; // var booleana
    Node *aux; // Nodo aux

       for (int j=0; j<STACKSIZE; j++){ //se asume que la pila tiene tamaño STACKSIZE
           if (isEmpty(stack)){
             printf ("La pila está vacía\n"); return 0; //en caso que la pila esté vacía se retorna y termina la ejecucion
           }
           else{
            aux = Pop(stack); //Se almacena item retornado al hacer pop
            inst = aux->Data->inPin; // se almacena valor de instrucción
            free (aux); // se libera memoria 
            // casos en switch
            switch (inst){
                case case0: printf("Se hace toogle del pin\n"); Pin1 = !Pin1; break;

                case case1: printf("Valor del Pin1: %s\n", Pin1 ? "true" : "false"); break;

                case case2: printf("Se aumenta valor del contador\n"); count ++; break;

                case case3: printf("El valor del contador es:%zu\n", count);  break;

                case case5:
                    if (isEmpty(stack)){                 
                        printf("La pila está vacía\n"); break;
                    }else{
                        printf("La pila tiene %d\n elementos", (stack->size)); break;
                    }
                case case6: 
                    if (stack->size == (STACKSIZE)){
                        printf("La pila está llena\n");  return 0;
                    }
                        
                default: break;
            }

           }

        } 
    
    return 0;

}

