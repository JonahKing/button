@jonah_king;

This document is to describe how to use the  sourcecode;

1.1 the thought of button detection 
   
    the implementation of the button detection is based on finite state machine.
    the state machine is changed according the detection voltage level and 
    you can send  any state machine to the message queue;
    
    if your code not support message queue, we can inplement it by FIFO; 

1.2  because the sourcecode support to much state machine,and some of them are conflict
   so you should initilize(configure) the support machine.

1.3

2. how to use the source code

2.1
   
   initialize the useage of the button


1.how to implement the SINGLE_CLICK

    KEY_STATE_IDLE -> KEY_STATE_SHORT_PRESS_START -> KEY_STATE_SHORT_PRESSING -> SINGLE_CLICK

2. how to implement the LONG_CLICK

    KEY_STATE_IDLE -> KEY_STATE_SHORT_PRESS_START -> KEY_STATE_SHORT_PRESSING -> KEY_STATE_LONG_PRESSING ->LONG_CLICK

    or
 
    KEY_STATE_IDLE -> KEY_STATE_SHORT_PRESS_START -> KEY_STATE_SHORT_PRESSING -> KEY_STATE_LONG_PRESSING -> LONG_CLICK -> LONG_PRESSING_FORCE_RELEASE

3. double click
   
   KEY_STATE_IDLE -> SINGLE_CLICK -> SINGLE_CLICK -> DOUBLE_CLICK



configure

    SINGLE_CLICK  = Y/N;
    SINGLE_CLICK_TYPE = PRESS_DOWN/POP_UP;
    SINGLE_CLICK_FLITER_TIME = 0/user_data;

    LONG_CLICK   = Y/N
    LONG_CLICK_TYPE = TIME_ENOUGH/POP_UP;
    LONG_CLICK_TIME = user_data;

   
    DOUBLE_CLICK   = Y/N
    LDOUBLE_CLICK_DURATION = user_data;
