#include "stm32f4xx.h"                  // Device header
#include "stdio.h"

void USART2_Init(void);

int main(void)
{
		USART2_Init();
		int n;
		char str[100];
		printf("Hello from stm32\r\n");
		fprintf(stdout,"test for output\r\n");
		fprintf(stderr,"test for error\r\n");
while(1)
{
		printf("how old are you? ");
		scanf("%d",&n);
		printf("Your age is: %d \r\n",n);
		printf("what is your first name?");
		gets(str);
		printf("welcome to STM32 Mr.");
		puts(str);
		printf("\r\n");
}
}

void USART2_Init(void)
{

	RCC->AHB1ENR |=1; //Enable GPIOA clock
	RCC->APB1ENR|=0x20000; //Enable USART clock
	//configure PA3 as alternative function 
	GPIOA->AFR[0]=0x07700; //ALT7 for UART2
	GPIOA->MODER|=0x0080;  //enable PA3 as alternate function
	GPIOA->MODER|=0x0020; //enable PA2 as alterate fuction
	USART2->BRR=0x008B; // set baud rate
	USART2->CR1|=0x200C; //enable RX

}

int USART2_write(int ch)
{
//wait for TX buffer empty
while(!(USART2->SR&0x0080)){}
USART2->DR=(ch&0xFF);
return 0;
}

int USAR2_read(void)
{
while(!(USART2->SR&0x0020)){}
return USART2->DR;
}

	
//c interface code which interface embeddedC with com console 
struct FILE {int handle; };
FILE __stdin ={0};
FILE __stdout ={1};
FILE __stderr ={2};
	
int fgetc(FILE *f){
int c;
	c=USAR2_read();
	if(c=='\r'){
	USART2_write(c);
		c='\n';}
	USART2_write(c);
return c;
	}

int fputc(int c, FILE *f)	
{
return USART2_write(c);
}
