#define F_CPU 16000000UL			/* Define CPU Frequency e.g. here 8MHz */
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>


#define KEY_PRT 	PORTA
#define KEY_DDR		DDRA
#define KEY_PIN		PINA
#define LCD_Dir  DDRB			/* Define LCD data port direction */
#define LCD_Port PORTB			/* Define LCD data port */
#define RS PB0				/* Define Register Select pin */
#define EN PB1 				/* Define Enable signal pin */

unsigned char keypad[4][4] = {	{'0','4','8','A'},
				{'1','5','9','B'},
				
				{'2','6','<','C'},
				{'3','7','E','D'}};

unsigned char colloc, rowloc,N,M;
unsigned int Number=0, pre_Number=0;
char SHOWA [3];
bool press=0;
unsigned char keypressed,gucv_swdelay;
static unsigned char gucv_mode=0;
unsigned int gucv_A,gucv_B,gucv_C,gucv_D;
bool gbv_swpress,result;
unsigned int guiv_secound_count=0;
unsigned int Num1=0,Num2=0,Pwd=0,password=1234,pre_Pwd=0;
unsigned int Vid_1=1001,Vid_2=1002,Vid_3=1003,Vid_4=1004,Vid_5=1005;
unsigned int Vid_6=1006,Vid_7=1007,Vid_8=1008,Vid_9=1009,Vid_10=1010;
static bool Vid_1_flag=0,Vid_2_flag=0,Vid_3_flag=0,Vid_4_flag=0,Vid_5_flag=0;
static bool Vid_6_flag=0,Vid_7_flag=0,Vid_8_flag=0,Vid_9_flag=0,Vid_10_flag=0,gucv_disupdate,VOTE_FLAG=0;
char SHOW_number[3];
char SHOW_password[3],count_num,a=0,c=0;
char SHOW_A[3];
char SHOW_B[3];
char SHOW_C[3];
char SHOW_D[3];

char keyfind()

{
	while(1)
	{
	    KEY_DDR = 0xF0;           /* set port direction as input-output */
	    KEY_PRT = 0xFF;

	    do
	    {
		KEY_PRT &= 0x0F;      /* mask PORT for column read only */
		asm("NOP");
		colloc = (KEY_PIN & 0x0F); /* read status of column */
	    }while(colloc != 0x0F);
		
	    do
	    {
		do
		{
	            _delay_ms(20);             /* 20ms key debounce time */
		    colloc = (KEY_PIN & 0x0F); /* read status of column */
		}while(colloc == 0x0F);        /* check for any key press */
			
		_delay_ms (40);	            /* 20 ms key debounce time */
		colloc = (KEY_PIN & 0x0F);
	    }while(colloc == 0x0F);

	   /* now check for rows */
	    KEY_PRT = 0xEF;            /* check for pressed key in 1st row */
	    asm("NOP");
	    colloc = (KEY_PIN & 0x0F);
	    if(colloc != 0x0F)
            {
		rowloc = 0;
		break;
	    }

	    KEY_PRT = 0xDF;		/* check for pressed key in 2nd row */
	    asm("NOP");
	    colloc = (KEY_PIN & 0x0F);
	    if(colloc != 0x0F)
	    {
		rowloc = 1;
		break;
	    }
		
	    KEY_PRT = 0xBF;		/* check for pressed key in 3rd row */
	    asm("NOP");
            colloc = (KEY_PIN & 0x0F);
	    if(colloc != 0x0F)
	    {
		rowloc = 2;
		break;
	    }

	    KEY_PRT = 0x7F;		/* check for pressed key in 4th row */
	    asm("NOP");
	    colloc = (KEY_PIN & 0x0F);
	    if(colloc != 0x0F)
	    {
		rowloc = 3;
		break;
	    }
	}

	if(colloc == 0x0E)
	   return(keypad[rowloc][0]);
	else if(colloc == 0x0D)
	   return(keypad[rowloc][1]);
	else if(colloc == 0x0B)
	   return(keypad[rowloc][2]);
	else
	   return(keypad[rowloc][3]);
}

int main(void)
{
	LCD_Init();
	LCD_String_xy(0,0,"   AUTOMATIC    ");
	LCD_String_xy(1,0," VOTING MACHINE ");
	_delay_ms(2000);
	LCD_Clear();
	LCD_String_xy(0,0," PRESS ANY KEY  ");
	LCD_String_xy(1,0,"  TO CONTINUE   ");
	/*LCD_Command(0x80 + 0x40 + 8);
    itoa(number,SHOWA,10);
    LCD_String(SHOWA);
    LCD_String ("      ");
   // LCD_Command(0x80 + 0);
    //LCD_Command(number);*/
	
    while(1)
	{
	
	  
    N= keyfind();
	
	if(gucv_mode==0)
	{
	 if(c==0)
	 {
	   LCD_Clear();
	
	 c=1;
	 }
	  LCD_String_xy(0,0," ENTER VOTER-id");
	if(Number>=0 && Number<=9999)
	{
	switch(N)
			{
				case '1': 
				        
						  
				          if (Number==0)Number=1;
						   else
							    Number = (Number*10) + 1; 
						  
						  
						   break;

				
				case '2': ////count_num++;
				          //if(count_num<=4)
						  //{
				           if (Number==0)Number=2;
						   else
							    Number = (Number*10) + 2; 
						   // }
						  //count_num--;
					
							break;

				case '3': if (Number==0)Number=3;
						   else
							    Number = (Number*10) + 3; 	
							break;

                case '4': if (Number==0)Number=4;
						   else
							    Number = (Number*10) + 4; 	
							break;
				
				case '5': if (Number==0)Number=5;
						   else
							    Number = (Number*10) + 5; 	
							break;

				case '6': if (Number==0)Number=6;
						   else
							    Number = (Number*10) + 6; 	
							break;

				case '7': if (Number==0)Number=7;
						   else
							    Number = (Number*10) + 7; 	
							break;
				
				case '8': if (Number==0)Number=8;
						   else
							    Number = (Number*10) + 8; 	
							break;

				case '9':   if (Number==0)Number=9;
						   else
							    Number = (Number*10) + 9; 
					
							break;

                case '0': if (Number==0)Number=0;
						   else
							    Number = (Number*10) + 0; 	
							break;
				
				case '<': if(Number<=9)Number=0;
				          if(Number>9)
				           {
				           Number=Number/10; 
				           result=false;
						   }	
							break;

				case 'E':  c=0;
				           if(Number>0)
				          // check();
														  
								{

									 if(Number==Vid_1&& Vid_1_flag==0)
									 {
									  gucv_mode=1;
									  Vid_1_flag=1;
									 }

									 else if(Number==Vid_2&& Vid_2_flag==0)
									 {
									  gucv_mode=1;
									  Vid_2_flag=1;
									 }

									 else if(Number==Vid_3&& Vid_3_flag==0)
									 {
									  gucv_mode=1;
									  Vid_3_flag=1;
									 }

									else  if(Number==Vid_4&& Vid_4_flag==0)
									 {
									  gucv_mode=1;
									  Vid_4_flag=1;
									 }

									 else if(Number==Vid_5&& Vid_5_flag==0)
									 {
									  gucv_mode=1;
									  Vid_5_flag=1;
									 }

									else  if(Number==Vid_6&& Vid_6_flag==0)
									 {
									  gucv_mode=1;
									  Vid_6_flag=1;
									 }

									else  if(Number==Vid_7&& Vid_7_flag==0)
									 {
									  gucv_mode=1;
									  Vid_7_flag=1;
									 }

									 else if(Number==Vid_8&& Vid_8_flag==0)
									 {
									  gucv_mode=1;
									  Vid_8_flag=1;
									 }

									 else if(Number==Vid_9&& Vid_9_flag==0)
									 {
									  gucv_mode=1;
									  Vid_9_flag=1;
									 }

									 else if(Number==Vid_10&& Vid_10_flag==0)
									 {
									  gucv_mode=1;
									  Vid_10_flag=1;
									 }

									


									 /****************************////


									else if(Number==Vid_1&& Vid_1_flag==1)
									 {
									  Number=pre_Number=0;
									  VOTE_FLAG=1;
									  gucv_mode=0;

									 }

									else  if(Number==Vid_2&& Vid_2_flag==1)
									 {
									  Number=pre_Number=0;
									  VOTE_FLAG=1;
									  gucv_mode=0;
									 }

									 else if(Number==Vid_3&& Vid_3_flag==1)
									 {
									  Number=pre_Number=0;
									  VOTE_FLAG=1;
									  gucv_mode=0;
									 }

									else  if(Number==Vid_4&& Vid_4_flag==1)
									 {
									  Number=pre_Number=0;
									  VOTE_FLAG=1;
									  gucv_mode=0;
									 }

									else  if(Number==Vid_5&& Vid_5_flag==1)
									 {
									  Number=pre_Number=0;
									  VOTE_FLAG=1;
									  gucv_mode=0;
									 }

									 else if(Number==Vid_6&& Vid_6_flag==1)
									 {
									  Number=pre_Number=0;
									  VOTE_FLAG=1;
									  gucv_mode=0;
									 }

									 else if(Number==Vid_7&& Vid_7_flag==1)
									 {
									  Number=pre_Number=0;
									  VOTE_FLAG=1;
									  gucv_mode=0;
									 }

									 else if(Number==Vid_8&& Vid_8_flag==1)
									 {
									  Number=pre_Number=0;
									  VOTE_FLAG=1;
									  gucv_mode=0;
									 }

									else  if(Number==Vid_9&& Vid_9_flag==1)
									 {
									   Number=pre_Number=0;
									   VOTE_FLAG=1;
									   gucv_mode=0;
									 }

									else  if(Number==Vid_10&& Vid_10_flag==1)
									 {
									  Number=pre_Number=0;
									  VOTE_FLAG=1;
									  gucv_mode=0;
									 }


									 else
									 {
									  LCD_Clear();
				                      LCD_String_xy (0, 0, "PLEASE ENTER THE");
							          LCD_String_xy (1, 0, " VALID VOTER-ID ");
									  _delay_ms(1000);
									  Number=pre_Number=0;
									  gucv_mode=0;
									  LCD_Clear();
							          LCD_String_xy(0,0," ENTER VOTER-id");
									 }

								}	
							break;
                case 'A':   Number=pre_Number=0;
						    LCD_Clear(); 
							gucv_mode=2;
							LCD_String_xy (0, 0, " ENTER PASSWORD ");	
							break;
				case 'B':	
							break;
                case 'C':	
							break;
                case 'D':	
							break;


               }
			   
			 	if(Number>9999) Number=pre_Number; 
				pre_Number=Number;
			   
       }
	   	if(Number>0 && Number<=9999)
	      {

      LCD_Command(0xc0);    
	  itoa(Number,SHOW_number,10);
      LCD_String(SHOW_number);
      LCD_String ("      ");
    //LCD_Command(0x80 + 0);
    //LCD_Command(number);*/
	     }
        if(Number==0)
	     LCD_String_xy(1,0,"                ");
        if(VOTE_FLAG==1)
		{  
		  VOTE_FLAG=0;
		  LCD_Clear();
		  LCD_String_xy (0, 0, "  USER ALREADY  ");
		  LCD_String_xy (1, 0, "      VOTED     ");
		  _delay_ms(1000);
		  LCD_Clear();
		  LCD_String_xy(0,0," ENTER VOTER-id");
		  gucv_mode=0;
		}
		
        	
	}
	
	
	if(gucv_mode==1)
	 {
	 if(a==0)
	 {
	 LCD_Clear();
	 LCD_String_xy(0,0,"  PLEASE VOTE  ");
	 LCD_String_xy(1,0,"A    B    C    D");
	 a=1;
	 }
	 switch(N)
			{
				case '0': break;
				case '1': break;
				case '2': break;
				case '3': break;
				case '4': break;
				case '5': break;
				case '6': break;
				case '7': break;
				case '8': break;
				case '9': break;
				case '<': break;
				case 'E': break;
							
                case 'A':	gucv_A++;
				            LCD_Clear();
				            LCD_String_xy (0, 0, "   THANKS FOR   ");
							LCD_String_xy (1, 0, "   VOTING-->A   ");
							_delay_ms(500);
							Number=pre_Number=0;	   
							LCD_Clear();
							gucv_mode=0;
							LCD_String_xy(0,0," ENTER VOTER-id");
							a=0;
							break;
				case 'B':  gucv_B++;
							LCD_Clear();
				            LCD_String_xy (0, 0, "   THANKS FOR   ");
							LCD_String_xy (1, 0, "   VOTING-->B   ");
							_delay_ms(500);
							Number=pre_Number=0;	   
							LCD_Clear();
							gucv_mode=0;
							LCD_String_xy(0,0," ENTER VOTER-id");
							a=0;
							break;
                case 'C':	gucv_C++;
							LCD_Clear();
				            LCD_String_xy (0, 0, "   THANKS FOR   ");
							LCD_String_xy (1, 0, "   VOTING-->C   ");
							_delay_ms(500);
							Number=pre_Number=0;	   
							LCD_Clear();
							gucv_mode=0;
							LCD_String_xy(0,0," ENTER VOTER-id");
							a=0;
							break;
                case 'D':	gucv_D++;
							LCD_Clear();
				            LCD_String_xy (0, 0, "   THANKS FOR   ");
							LCD_String_xy (1, 0, "   VOTING-->D   ");
							_delay_ms(500);
							Number=pre_Number=0;	   
							LCD_Clear();
							gucv_mode=0;
							LCD_String_xy(0,0," ENTER VOTER-id");
							a=0;
							break;


               }
		  

	 }
	 
	if(gucv_mode==2) 
	 {
	Number=pre_Number=0;
    //LCD_Clear(); 
	LCD_String_xy (0, 0, " ENTER PASSWORD ");
	if(Pwd>=0 && Pwd<=9999)
	{
	switch(N)
			{
				case '1': 
				        
						  
				          if (Pwd==0)Pwd=1;
						   else
							    Pwd = (Pwd*10) + 1; 
						  
						  
						   break;

				
				case '2': ////count_num++;
				          //if(count_num<=4)
						  //{
				           if (Pwd==0)Pwd=2;
						   else
							    Pwd = (Pwd*10) + 2; 
						   // }
						  //count_num--;
					
							break;

				case '3': if (Pwd==0)Pwd=3;
						   else
							    Pwd = (Pwd*10) + 3; 	
							break;

                case '4': if (Pwd==0)Pwd=4;
						   else
							    Pwd = (Pwd*10) + 4; 	
							break;
				
				case '5': if (Pwd==0)Pwd=5;
						   else
							    Pwd = (Pwd*10) + 5; 	
							break;

				case '6': if (Pwd==0)Pwd=6;
						   else
							    Pwd = (Pwd*10) + 6; 	
							break;

				case '7': if (Pwd==0)Pwd=7;
						   else
							    Pwd = (Pwd*10) + 7; 	
							break;
				
				case '8': if (Pwd==0)Pwd=8;
						   else
							    Pwd = (Pwd*10) + 8; 	
							break;

				case '9':   if (Pwd==0)Pwd=9;
						   else
							    Pwd = (Pwd*10) + 9; 
					
							break;

                case '0': if (Pwd==0)Pwd=0;
						   else
							    Pwd = (Pwd*10) + 0; 	
							break;
				
				case '<': if(Pwd<=9)Pwd=0;
				          if(Pwd>9)
				           {
				           Pwd=Pwd/10; 
				           result=false;
						   }	
							break;

				case 'E': if(Pwd>0)
				            {
							   
							   if(Pwd==password)
								{
								LCD_Clear();
								LCD_String_xy (0, 0, "   THANK YOU   ");
								LCD_String_xy (1, 0, "PASSWORD MATCHED");
								gucv_mode=3;
								Pwd=pre_Pwd=0;
								_delay_ms(500);
								LCD_Clear(); 
			                    LCD_String_xy (0, 0, "  PRESS 'C' TO  ");
								LCD_String_xy (1, 0, " SEE THE RESULT ");
								
								}
							   else
								{
								LCD_Clear();
								LCD_String_xy (0, 0, " PASSWORD WRONG ");
								LCD_String_xy (1, 0, "    TRY AGAIN   ");
								gucv_mode=0;
								Pwd=pre_Pwd=0;
								_delay_ms(500);
								LCD_Clear();
			                    LCD_String_xy (0, 0, " ENTER PASSWORD ");
								}
							}
							break;
				
				case 'D':	gucv_mode=0;
							Pwd=pre_Pwd=0;
							LCD_Clear();
							LCD_String_xy(0,0," ENTER VOTER-id");
							
							break;
				case 'A':	
							break;
                case 'C':	
							break;
                case 'B':	
							break;


               }
			   
			 	if(Pwd>9999) Pwd=pre_Pwd; 
				pre_Pwd=Pwd;
			   
       }
	   
	   if(Pwd>0 && Pwd<=9999&& gucv_mode==2)
	      {

			  LCD_Command(0xc0);    
			  itoa(Pwd,SHOW_password,10);
			  LCD_String(SHOW_password);
			  LCD_String ("      ");
		   // LCD_Command(0x80 + 0);
			//LCD_Command(number);*/
	     }
        if(Pwd==0&& gucv_mode==2)
	     LCD_String_xy(1,0,"                ");

	 
	 }
	 
	 
	 
	 
	 
	if(gucv_mode==3)
	 {
	  
	 //LCD_Clear();
	 //LCD_String_xy(0,0,"  PLEASE VOTE  ");
	 //LCD_String_xy(1,0,"A    B    C    D");
	 switch(N)
			{
				case '0': break;
				case '1': break;
				case '2': break;
				case '3': break;
				case '4': break;
				case '5': break;
				case '6': break;
				case '7': break;
				case '8': break;
				case '9': break;
				case '<': break;
				case 'C': 
				          LCD_Clear();
						  LCD_String_xy(0,0,"A=");
						  LCD_String_xy(0,7,"B=");
						  LCD_String_xy(1,0,"C=");
						  LCD_String_xy(1,7,"D=");
						  
						  LCD_Command(0x80 + 2);
						  itoa(gucv_A,SHOW_A,10);
						  LCD_String(SHOW_A);
						  
						  LCD_Command(0x80 +9);
						  itoa(gucv_B,SHOW_B,10);
						  LCD_String(SHOW_B);
						  
						  LCD_Command(0x80 +0x40 +2);
						  itoa(gucv_C,SHOW_C,10);
						  LCD_String(SHOW_C);
						  
						  LCD_Command(0x80 +0x40 +9);
						  itoa(gucv_D,SHOW_D,10);
						  LCD_String(SHOW_D);
						
				          break;
						  
						  
							
                case 'A':
							break;
				case 'E':  
							break;
                case 'D':	
						    LCD_Clear();
							LCD_String_xy (0, 0, "WINNER IS-->");
							if((gucv_A>=gucv_B)&&(gucv_A>=gucv_C)&&(gucv_A>=gucv_D))
							LCD_String_xy (0, 12, "A");
							if((gucv_B>=gucv_A)&&(gucv_B>=gucv_C)&&(gucv_B>=gucv_D))
							LCD_String_xy (0, 13, "B");
							if((gucv_C>=gucv_B)&&(gucv_C>=gucv_B)&&(gucv_C>=gucv_D))
							LCD_String_xy (0, 14, "C");
							if((gucv_D>=gucv_B)&&(gucv_D>=gucv_C)&&(gucv_D>=gucv_A))
							LCD_String_xy (0, 15, "D");
							LCD_String_xy (1, 0, "   THANK YOU   ");
		
							break;
                case 'B':	   
							LCD_Clear();
							gucv_mode=0;
							LCD_String_xy(0,0," ENTER VOTER-id");
							break;
			}
			}

	
} }

void LCD_String_xy (char row, char pos, char *str)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	LCD_String(str);		/* Call LCD string function */
}

void LCD_Init (void)			/* LCD Initialize function */
{
	LCD_Dir = 0xFF;			/* Make LCD port direction as o/p */
	_delay_ms(20);			/* LCD Power ON delay always >15ms */
	
	LCD_Command(0x02);		/* send for 4 bit initialization of LCD  */
	LCD_Command(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
	LCD_Command(0x0c);              /* Display on cursor off*/
	LCD_Command(0x06);              /* Increment cursor (shift cursor to right)*/
	LCD_Command(0x01);              /* Clear display screen*/
	_delay_ms(2);
}

void LCD_Command( unsigned char cmnd )
{
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0); /* sending upper nibble */
	LCD_Port &= ~ (1<<RS);		/* RS=0, command reg. */
	LCD_Port |= (1<<EN);		/* Enable pulse */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);  /* sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}


void LCD_Char( unsigned char data )
{
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); /* sending upper nibble */
	LCD_Port |= (1<<RS);		/* RS=1, data reg. */
	LCD_Port|= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (data << 4); /* sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void LCD_String (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}
void send_a_string(char *string_of_characters)
{
    while(*string_of_characters > 0)
    {
        LCD_Char(*string_of_characters++);
    }
}

void LCD_Clear()
{
	LCD_Command (0x01);		/* Clear display */
	_delay_ms(2);
	LCD_Command (0x80);		/* Cursor at home position */
}




