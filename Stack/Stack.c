#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 64

typedef struct stack{
	char myStack[MAX];
	int top;
}STACK;

void initStack(STACK **stack){
	(*stack)->top = 0;
}

void push(STACK *stack, int value){
	if(isFull(stack) == 0)
		stack->myStack[ stack->top++ ] = value;
	else
		printf("Stack Dolu!\n");
}

char pop(STACK *stack){
	if(isEmpty(stack) == 0)
		return stack->myStack[--stack->top];
	else
		printf("Stack Bos!\n");
	return ' ';
}

char peak(STACK *stack){
	int sayi;
	sayi = stack->myStack[--stack->top];
	stack->top++;
	return sayi;
}

int isEmpty(STACK *stack){
	if(stack->top == 0)
		return 1;
	else
		return 0;
}

int isFull(STACK *stack){
	if(stack->top == MAX)
		return 1;
	else
		return 0;
}

void recursive(char *dizi, int sayi, int index, int boyut){
	
	char rakam;
	int basamak;
	
	if(index == boyut)
		return;
		
	if(sayi != 0){
		basamak = sayi % 2;
		sayi /= 2;
	}
	
	recursive(dizi, sayi, index+1, boyut);
	
	if(basamak == 1)
		strcat(dizi, "1");
	else if(basamak == 0)
		strcat(dizi, "0");
	else if(sayi == 0)
		strcat(dizi, "0");
		
}

int farkBul(char *sayi, STACK *stack, char *basamak, int boyut){
	int i;
	int fark = 0;
	for(i=boyut-1; i>=0; --i){
		if(isEmpty(stack) == 0){
			if(peak(stack) == sayi[i]){
				push(stack, sayi[i]);
			}
			else{
				pop(stack);
			}
		}
		else{
			push(stack, sayi[i]);
		}
	}
	*basamak = peak(stack);
	fark = stack->top;
	return fark;
}

void negatif(int sayi, char binary[], int boyut){
	int elde, i;
	sayi *= -1;
	
	recursive(binary, sayi, 0, boyut);
	
	for(i=0; i<boyut; ++i){
		if(binary[i] == '1')
			binary[i] = '0';
		else
			binary[i] = '1';
	}
	
	elde = 0;
	if(binary[boyut-1] == '1'){
		elde = 1;
		binary[boyut-1] = '0';
	}
	else
		binary[boyut-1] = '1';
		
	i = boyut-2;
	while(elde == 1){
		if(binary[i] == '1'){
			binary[i] = '0';
		}
		else{
			binary[i] = '1';
			elde = 0;
		}
		i--;
	}
}

int main(){

	char *binary;
	STACK *stack = (STACK*)malloc(sizeof(STACK));
	int i;
	int fark = 0;
	char basamak = 'e';
	int boyut = 8;
	int sayi;
	
	initStack(&stack);
	
	printf("Sayiyi Giriniz:");
	scanf("%d",&sayi);
	
	if(sayi < 0){
		if(sayi >= -128)
			boyut = 8;
		else if(sayi >= -32768)
			boyut = 16;
		else if(sayi >= -0x800000)
			boyut = 24;
		else
			boyut = 32;
	}
	else{
		if(sayi <= 0x7)
			boyut = 8;
		else if(sayi <= 0x7FFF)
			boyut = 16;
		else if(sayi <= 0x7FFFFF)
			boyut = 24;
		else
			boyut = 32;
	}
	
	binary = (char *)calloc(sizeof(char), boyut);
	
	if(sayi >= 0){
		recursive(binary, sayi, 0, boyut);
	}
	else{
		negatif(sayi, binary, boyut);
	}
	
	printf("\nSayinin binary karsiligi: %s\n\n",binary);
	
	
	fark = farkBul(binary, stack, &basamak, boyut);
	
	if(basamak == '1')
		printf("Output: 1'ler fazladir. Ek %d adet 0 gereklidir.\n",fark);
	else if(basamak == '0')
		printf("Output: 0'lar fazladir. Ek %d adet 1 gereklidir.\n",fark);
	else
		printf("Output: 0 ve 1'ler esit sayidadir.\n");
	return 0;
}

