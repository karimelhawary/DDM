/*
 * Keypad.h
 *
 *  Created on: Sep 3, 2022
 *      Author: abram
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_
#define KEYPAD_COLS 4
#define KEYPAD_ROWS 4

#define KEYPAD_PIN_R1 PORTB_ID, PIN0_ID
#define KEYPAD_PIN_R2 PORTB_ID, PIN1_ID
#define KEYPAD_PIN_R3 PORTB_ID, PIN2_ID
#if (KEYPAD_ROWS == 4)
#define KEYPAD_PIN_R4 PORTB_ID, PIN3_ID
#endif
/******************************************/
#define KEYPAD_PIN_C1 PORTB_ID, PIN4_ID
#define KEYPAD_PIN_C2 PORTB_ID, PIN5_ID
#define KEYPAD_PIN_C3 PORTB_ID, PIN6_ID
#if (KEYPAD_COLS == 4)
#define KEYPAD_PIN_C4 PORTB_ID, PIN7_ID
#endif

typedef enum
{
    KEYPAD_B00,
    KEYPAD_B01,
    KEYPAD_B02,
    KEYPAD_B03,
    KEYPAD_B04,
    KEYPAD_B05,
    KEYPAD_B06,
    KEYPAD_B07,
    KEYPAD_B08,
    KEYPAD_B09,
    KEYPAD_B10,
    KEYPAD_B11,
    KEYPAD_B12,
    KEYPAD_B13,
    KEYPAD_B14,
    KEYPAD_B15,
    KEYPAD_INVALID
} Keypad_ButtonType;
typedef enum
{
    KEYPAD_NOT_PRESSED,
    KEYPAD_PRESSED
} Keypad_ButtonStateType;
void keypad_Init(void);
Keypad_ButtonStateType Keypad_GetButtonState(Keypad_ButtonType button);
Keypad_ButtonType Keypad_GetPressedButton(void);

#endif /* INC_KEYPAD_H_ */
