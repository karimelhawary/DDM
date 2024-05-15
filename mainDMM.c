
#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "ADC.h"
#include "lcd.h"
#include "Keypad.h"


/* Calculator Buttons
1   2   3   +
4   5   6   -
7   8   9   C
*   0   =   /
*/
#define CALC_BUTTON_0       KEYPAD_B07
#define CALC_BUTTON_1       KEYPAD_B00
#define CALC_BUTTON_2       KEYPAD_B04
#define CALC_BUTTON_3       KEYPAD_B08
#define CALC_BUTTON_4       KEYPAD_B01
#define CALC_BUTTON_5       KEYPAD_B05
#define CALC_BUTTON_6       KEYPAD_B09
#define CALC_BUTTON_7       KEYPAD_B02
#define CALC_BUTTON_8       KEYPAD_B06
#define CALC_BUTTON_9       KEYPAD_B10
#define CALC_BUTTON_PLUS    KEYPAD_B12
#define CALC_BUTTON_MINUS   KEYPAD_B13
#define CALC_BUTTON_MUL     KEYPAD_B03
#define CALC_BUTTON_DIV     KEYPAD_B15
#define CALC_BUTTON_EQUAL   KEYPAD_B11
#define CALC_BUTTON_CLR     KEYPAD_B14


static uint8 Calculator_GetActualNumber(uint8 button);

int main(void)
{
	unsigned char button = 0;
	unsigned char button2 = 0;

	unsigned char Actual_button = 0;

	float VOLT =0.0;
	float CURR =0.0;
	float OP_ADC =0;
    float RS =10000;
    float vin = 1.5 ;
    float range =0.0;
    float RX = 0;

    init_ADC();
	LCD_init();
	keypad_Init();

	GPIO_setupPinDirection(PORTA_ID, PIN1_ID, PIN_INPUT);
	GPIO_setupPinDirection(PORTA_ID, PIN2_ID, PIN_INPUT);
	GPIO_setupPinDirection(PORTC_ID, PIN0_ID, PIN_OUTPUT);
	GPIO_writePin(PORTC_ID, PIN0_ID, LOGIC_HIGH);

	LCD_displayStringRowColumn(0,5,"CHOOSE");
	LCD_displayStringRowColumn(1,0," VOLT/ CURR /RES");

	while(1)
	{


     button = Keypad_GetPressedButton();
	 Actual_button = Calculator_GetActualNumber(button);

			if (button == KEYPAD_INVALID)
			{
			}
			else if (Actual_button == 20)
			{

					LCD_displayStringRowColumn(0,1,"CHOOSE V RANGE");
					LCD_displayStringRowColumn(1,1,"0.2V/2V/20V/200V");

					button = Keypad_GetPressedButton();

					       while (button == KEYPAD_INVALID)
						    {
					           button = Keypad_GetPressedButton();
							}

							Actual_button = Calculator_GetActualNumber(button);
							LCD_clearScreen();

					        switch (Actual_button)
								 {
										 case 21:
										   {
										    	range= 200;
										    	button2 = KEYPAD_INVALID;

										        LCD_displayStringRowColumn(0, 4, "VOLTAGE:");
										        LCD_displayStringRowColumn(1, 14, "mV");

											     while (button2 == KEYPAD_INVALID){
											    	    LCD_displayStringRowColumn(1, 1, "    ");
													     OP_ADC = ADC_Read(2);
														 VOLT = (OP_ADC/1023) * range*0.98;
														 LCD_displayFloat(VOLT,3);
														  _delay_ms(1000);
														  button2 = Keypad_GetPressedButton();
											    	}

										    }
										        break;
										   case 22:
										     {
										    	  range= 2;
										    	  button2 = KEYPAD_INVALID;

										    	    LCD_displayStringRowColumn(0, 4, "VOLTAGE:");
										    	    LCD_displayStringRowColumn(1, 14, "V");

										    	    while (button2 == KEYPAD_INVALID){
										    	    	 LCD_displayStringRowColumn(1, 1, "    ");
												    	  OP_ADC = ADC_Read(2);
														  VOLT = (OP_ADC/1023) * range*0.98;
														  LCD_displayFloat(VOLT,3);
														  _delay_ms(1000);
														  button2 = Keypad_GetPressedButton();
										    	    }

										    	}
										        break;
										    case 23:
							                 	{
							                 		range= 20;
							                 		button2 = KEYPAD_INVALID;

							                 		LCD_displayStringRowColumn(0, 4, "VOLTAGE:");
										    	     LCD_displayStringRowColumn(1, 14, "V");


										    	    while (button2 == KEYPAD_INVALID){
										    	    	 LCD_displayStringRowColumn(1, 1, "    ");
												    	 OP_ADC = ADC_Read(2);
														 VOLT = (OP_ADC/1023) * range*0.98;
														 LCD_displayFloat(VOLT,3);
														  _delay_ms(1000);
														  button2 = Keypad_GetPressedButton();
										    	    }

							                	}
										        break;
										    case 10:
										   		{
										   			range= 200;
										   			button2 = KEYPAD_INVALID;

													LCD_displayStringRowColumn(0, 4, "VOLTAGE:");
										    	    LCD_displayStringRowColumn(1, 14, "V");

										    	    while (button2 == KEYPAD_INVALID){
										    	    	 LCD_displayStringRowColumn(1, 1, "    ");
												    	 OP_ADC = ADC_Read(2);
														 VOLT = (OP_ADC/1023) * range*0.98;
														 LCD_displayFloat(VOLT,3);
														  _delay_ms(1000);
														  button2 = Keypad_GetPressedButton();
										    	     }
										   		  }
										          break;

										    default:
										 	   break;
									}
			}
			else if (Actual_button == 'C')
		    {
					LCD_clearScreen();
					_delay_ms(500);
					LCD_displayStringRowColumn(0,5,"CHOOSE");
					LCD_displayStringRowColumn(1,0," VOLT/ CURR /RES");
		    }
			else if (Actual_button == 14)
			{
                   	LCD_displayStringRowColumn(0,1,"CHOOSE C RANGE");
			    	LCD_displayStringRowColumn(1,1,"2m/20m/200m/1 A");

					button = Keypad_GetPressedButton();

					          while (button == KEYPAD_INVALID)
									{
									  button = Keypad_GetPressedButton();
									}

										Actual_button = Calculator_GetActualNumber(button);
										LCD_clearScreen();

						                switch (Actual_button)
											 {
									    		  case 24:
													  {
														 range= 1;
														 button2 = KEYPAD_INVALID;
							     						 LCD_displayStringRowColumn(0, 4, "CURRENT:");
						    						     LCD_displayStringRowColumn(1, 14, "A");

														  while (button2 == KEYPAD_INVALID){
		    										    	      LCD_displayStringRowColumn(1, 1, "    ");
															      OP_ADC = ADC_Read(1);
															      CURR = (OP_ADC/1023) * range;
															      LCD_displayFloat(CURR,3);
						     									   _delay_ms(1000);
														    	   button2 = Keypad_GetPressedButton();
														    }
														}
														     break;

												    case 25:
														{
															range= 200;
															button2 = KEYPAD_INVALID;
										       				LCD_displayStringRowColumn(0, 4, "CURRENT:");
										    		        LCD_displayStringRowColumn(1, 14, "mA");

										    		        while (button2 == KEYPAD_INVALID){
			    									    	    	 LCD_displayStringRowColumn(1, 1, "    ");
			    									    	    	 OP_ADC = ADC_Read(1);
												    		    	 CURR = (OP_ADC/1023) * range;
												    		         LCD_displayFloat(CURR,3);
							     								    _delay_ms(1000);
															         button2 = Keypad_GetPressedButton();
														    	  }
														}
														        break;

													case 26:
											             {
											                range= 20;
											                button2 = KEYPAD_INVALID;
												            LCD_displayStringRowColumn(0, 4, "CURRENT");
														    LCD_displayStringRowColumn(1, 14, "mA");

												  		     while (button2 == KEYPAD_INVALID){
							    						    	     LCD_displayStringRowColumn(1, 1, "    ");
							    						    	     OP_ADC = ADC_Read(1);
															    	 CURR = (OP_ADC/1023) * range;
															    	  LCD_displayFloat(CURR,3);
							     									  _delay_ms(1000);
															    	    button2 = Keypad_GetPressedButton();
															    	  }
											               	}
															    break;

													 case 11:
														  {
															  range= 2;
														   	  button2 = KEYPAD_INVALID;
				    										  LCD_displayStringRowColumn(0,4,"CURRENT:");
															  LCD_displayStringRowColumn(1, 14, "mA");

														      while (button2 == KEYPAD_INVALID){
						  								    	    OP_ADC = ADC_Read(1);
															        CURR = (OP_ADC/1023) * range;
															    	 _delay_ms(1000);

							     									  if(CURR <= 1)
																		{
																		  LCD_displayStringRowColumn(0,4,"CURRENT:");
																	      LCD_displayStringRowColumn(1,0,"   ");
																		  CURR = CURR *1000.0;
																		  LCD_displayFloat(CURR,3);
																		  LCD_displayStringRowColumn(1, 14, "uA");
																		 }
																	else
																		 {
																		    LCD_displayStringRowColumn(0,4,"CURRENT:");
																		 	LCD_displayStringRowColumn(1,0,"  ");
																		 	LCD_displayFloat(CURR,3);
																		  	LCD_displayStringRowColumn(1, 14, "mA");
																		  }

																		   	button2 = Keypad_GetPressedButton();
																	  }
															   }
															        break;

																  default:
													     		 	   break;
													    }
				}

				else if (Actual_button == 13)
					{

						range = 2;
					    LCD_clearScreen();
						button2 = KEYPAD_INVALID;

				        while (button2 == KEYPAD_INVALID){
							OP_ADC = ADC_Read(2);
							VOLT = (OP_ADC/1023) * range*0.98;
							float diff = vin-VOLT;
					        float mul = RS*VOLT;
							RX = mul /diff ;
				            //r = (100000 * RX)/(100000-RX);
						    if(RX >= 10000)
							{
								LCD_displayStringRowColumn(0,2,"Resistance is");
								LCD_displayStringRowColumn(1,0,"   ");
								RX = RX /1000.0;
								LCD_displayFloat(RX,3);
								LCD_displayString(" kohm");
						    }
							else
					    	{
								LCD_displayStringRowColumn(0,2,"Resistance is");
								LCD_displayStringRowColumn(1,0,"  ");
								LCD_displayFloat(RX,3);
								LCD_displayString(" ohm");
							}

						 _delay_ms(1000);
						  button2 = Keypad_GetPressedButton();
			          	 }


		        	}

	           else if (Actual_button == 12)
	           {
			       LCD_displayStringRowColumn(0,1,"CHOOSE V RANGE");
			       LCD_displayStringRowColumn(1,1,"2V/20V/200V AC");

			       button = Keypad_GetPressedButton();

			           while (button == KEYPAD_INVALID)
						{
			        	   button = Keypad_GetPressedButton();
						}

							Actual_button = Calculator_GetActualNumber(button);
							LCD_clearScreen();

			                  switch (Actual_button)
								    {
								    case 27:
								    	{
								    		range= 200;
								    		button2 = KEYPAD_INVALID;


								    	    LCD_displayStringRowColumn(0, 4, "VOLTAGE:");

								    	     LCD_displayStringRowColumn(1, 14, "mV");


									    	    while (button2 == KEYPAD_INVALID){
									    	    	 LCD_displayStringRowColumn(1, 1, "    ");

											    	    OP_ADC = ADC_Read(2);
													    VOLT = (OP_ADC/1023) * range*1.002;
													    LCD_displayFloat(VOLT,3);

													    _delay_ms(1000);
													    button2 = Keypad_GetPressedButton();
									    	    }

								    	}

								        break;
								    case 28:
								    	{
								    		range= 2;
								    		button2 = KEYPAD_INVALID;

								    	     LCD_displayStringRowColumn(0, 4, "VOLTAGE:");
								    	     LCD_displayStringRowColumn(1, 14, "V");


								    	    while (button2 == KEYPAD_INVALID){
								    	    	 LCD_displayStringRowColumn(1, 1, "    ");

										    	    OP_ADC = ADC_Read(2);
												    VOLT = (OP_ADC/1023) * range*1.2;
												    LCD_displayFloat(VOLT,3);

												    _delay_ms(1000);
												    button2 = Keypad_GetPressedButton();
								    	    }

								    	}
								        break;
								    case 29:
					                 	{
					                 		range= 20;
					                 		button2 = KEYPAD_INVALID;

					                 		LCD_displayStringRowColumn(0, 4, "VOLTAGE:");
								    	     LCD_displayStringRowColumn(1, 14, "V");

								    	    while (button2 == KEYPAD_INVALID){
								    	    	 LCD_displayStringRowColumn(1, 1, "    ");

										    	    OP_ADC = ADC_Read(2);
												    VOLT = (OP_ADC/1023) * range*1.02;
												    LCD_displayFloat(VOLT,3);

												    _delay_ms(1000);
												    button2 = Keypad_GetPressedButton();
								    	    }

					                	}
								        break;
							       }
				 }

	}

}




static uint8 Calculator_GetActualNumber(uint8 button)
{
    uint8 number = 0;
    switch (button)
    {
    case CALC_BUTTON_0:
    	number = 20;
        break;
    case CALC_BUTTON_1:
        number = 21;
        break;
    case CALC_BUTTON_2:
        number = 22;
        break;
    case CALC_BUTTON_3:
        number = 23;
        break;
    case CALC_BUTTON_4:
        number = 24;
        break;
    case CALC_BUTTON_5:
        number = 25;
        break;
    case CALC_BUTTON_6:
        number = 26;
        break;
    case CALC_BUTTON_7:
        number = 27;
        break;
    case CALC_BUTTON_8:
        number = 28;
        break;
    case CALC_BUTTON_9:
        number = 29;
        break;
    case CALC_BUTTON_PLUS:
        number = 10;
        break;
    case CALC_BUTTON_MINUS:
        number = 11;
        break;
   case CALC_BUTTON_MUL:
	   number = 12;
	   break;
   case CALC_BUTTON_DIV:
	   number = 13;
	   break;
   case CALC_BUTTON_EQUAL:
	   number = 14;
	   break;
   case CALC_BUTTON_CLR:
	   number = 'C';
	   break;
   default:
	   break;
   }
    return number;
}







