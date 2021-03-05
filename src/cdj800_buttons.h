#ifndef __CDJ800_BUTTONS_H__
#define __CDJ800_BUTTONS_H__
#include "button.h"
#include "MIDI.h"
#define DEBOUNCE		50
#define BUTTON_PRESSED      BUTTON_LOW
#define BUTTON_RELEASED     BUTTON_HIGH
#define MIDI_PLAY       0x42
#define MIDI_CUE        0x43
#define CDJ_PLAY        PORTC0
#define CDJ_CUE         PORTC1
#define CDJ_TRACK       PORTC2

#define CDJ_PLAY_PORT   PORTC
#define CDJ_CUE_PORT    PORTC
#define CDJ_TRACK_PORT  PORTC

typedef struct _cdjButtons
{
    BUTTON play;
    BUTTON cue;
}CDJ800_BUTTONS;

CDJ800_BUTTONS CDJ800_Buttons_Setup();

void CDJ800_Buttons_Update(CDJ800_BUTTONS * buttons,MIDI * midi);


void CDJ800_Button_Update_Midi(BUTTON * button,MIDI * midi);
#endif