/*
 * Keypad.c
 *
 *  Created on: Sep 3, 2022
 *      Author: abram
 */
#include "std_types.h"
#include "common_macros.h"
#include "gpio.h"
#include "Keypad.h"
#include <util/delay.h>
static void Keypad_SetColumnLevel(uint8 column, uint8 level);
static uint8 Keypad_GetRowLevel(uint8 row);
void keypad_Init(void)
{
    /******************** Define rows as input *********************************/
    GPIO_setupPinDirection(KEYPAD_PIN_R1, PIN_INPUT);
    GPIO_setupPinDirection(KEYPAD_PIN_R2, PIN_INPUT);
    GPIO_setupPinDirection(KEYPAD_PIN_R3, PIN_INPUT);
#if (KEYPAD_ROWS == 4)
    GPIO_setupPinDirection(KEYPAD_PIN_R4, PIN_INPUT);
#endif
    //******************** Activate input pull up ******************************/
    GPIO_writePin(KEYPAD_PIN_R1, LOGIC_HIGH);
    GPIO_writePin(KEYPAD_PIN_R2, LOGIC_HIGH);
    GPIO_writePin(KEYPAD_PIN_R3, LOGIC_HIGH);
#if (KEYPAD_ROWS == 4)
    GPIO_writePin(KEYPAD_PIN_R4, LOGIC_HIGH);
#endif
    /********************** Define Columns as output ****************************/
    GPIO_setupPinDirection(KEYPAD_PIN_C1, PIN_OUTPUT);
    GPIO_setupPinDirection(KEYPAD_PIN_C2, PIN_OUTPUT);
    GPIO_setupPinDirection(KEYPAD_PIN_C3, PIN_OUTPUT);
#if (KEYPAD_COLS == 4)
    GPIO_setupPinDirection(KEYPAD_PIN_C4, PIN_OUTPUT);
#endif
    /******************************************************/
    GPIO_writePin(KEYPAD_PIN_C1, LOGIC_HIGH);
    GPIO_writePin(KEYPAD_PIN_C2, LOGIC_HIGH);
    GPIO_writePin(KEYPAD_PIN_C3, LOGIC_HIGH);
#if (KEYPAD_COLS == 4)
    GPIO_writePin(KEYPAD_PIN_C4, LOGIC_HIGH);
#endif
}
Keypad_ButtonStateType Keypad_GetButtonState(Keypad_ButtonType button)
{
    Keypad_ButtonStateType state = KEYPAD_NOT_PRESSED;
    /* equation to calc the number of row and column from the number of button */
    uint8 row = button / KEYPAD_ROWS;
    uint8 column = button % KEYPAD_COLS;
    /* set the column at low level to active the button if bressed */
    Keypad_SetColumnLevel(column, LOGIC_LOW);
    /* reading row to see if there is input  */
    if (Keypad_GetRowLevel(row) == LOGIC_LOW)
    {
        _delay_ms(5);
        if (Keypad_GetRowLevel(row) == LOGIC_LOW)
        {
            state = KEYPAD_PRESSED;
        }
    }
    /* set the column at high level to disable the button */
    Keypad_SetColumnLevel(column, LOGIC_HIGH);
    return state;
}
Keypad_ButtonType Keypad_GetPressedButton(void)
{
    uint8 i;
    Keypad_ButtonStateType button = KEYPAD_INVALID;
    for (i = 0; i < (KEYPAD_COLS * KEYPAD_ROWS); i++)
    {
        if (Keypad_GetButtonState(i) == KEYPAD_PRESSED)
        {
            button = i;
            break;

        }
    }
    return button;
}

static void Keypad_SetColumnLevel(uint8 column, uint8 level)
{
    switch (column)
    {
    case 0:
        GPIO_writePin(KEYPAD_PIN_C1, level);
        break;
    case 1:
        GPIO_writePin(KEYPAD_PIN_C2, level);
        break;
    case 2:
        GPIO_writePin(KEYPAD_PIN_C3, level);
        break;
    case 3:
        GPIO_writePin(KEYPAD_PIN_C4, level);
        break;
    default:
        break;
    }
}
static uint8 Keypad_GetRowLevel(uint8 row)
{
    uint8 level = LOGIC_HIGH;
    switch (row)
    {
    case 0:
        level = GPIO_readPin(KEYPAD_PIN_R1);
        break;
    case 1:
        level = GPIO_readPin(KEYPAD_PIN_R2);
        break;
    case 2:
        level = GPIO_readPin(KEYPAD_PIN_R3);
        break;
    case 3:
        level = GPIO_readPin(KEYPAD_PIN_R4);
        break;
    default:
        break;
    }
    return level;
}
