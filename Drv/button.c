#include "ev3api.h"
#include "app.h"
#include <stdbool.h>
#include <stdio.h>

#include "button.h"

/* API enum */
//enum button_t {
//  LEFT_BUTTON = 0,
//  RIGHT_BUTTON = 1,
//  ENTER_BUTTON = 4,}


/* external functions */
bool get_buttonState(button_t button){

    return ev3_button_is_pressed(button);
}

/* Note */
// An API "ev3_button_set_on_clicked()" is not implemented.
// If there is a demand, it will be implemented.