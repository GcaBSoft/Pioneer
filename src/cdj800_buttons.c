#include "cdj800_buttons.h"

CDJ800_BUTTONS CDJ800_Buttons_Setup()
{
    CDJ800_BUTTONS new ={0};
    new.play = Button_Setup(&CDJ_PLAY_PORT,CDJ_PLAY,MIDI_PLAY,0);
    new.cue = Button_Setup(&CDJ_CUE_PORT,CDJ_CUE,MIDI_CUE,0);

    return new;
}

void CDJ800_Buttons_Update(CDJ800_BUTTONS * buttons,MIDI * midi)
{
    CDJ800_Button_Update_Midi(&buttons->play,midi);
    CDJ800_Button_Update_Midi(&buttons->cue,midi);
}

inline void CDJ800_Button_Update_Midi(BUTTON * button,MIDI * midi)
{
    Button_Update(button);
    if(Button_Get_State(button)==BUTTON_PRESSED)
        MIDI_Send_Note_On(midi,button->id,127);
    else if(Button_Get_State(button)==BUTTON_RELEASED)
        MIDI_Send_Note_Off(midi,button->id,127);
}
