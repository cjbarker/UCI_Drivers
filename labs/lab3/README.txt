This implementation is interrupt base with a built-in delay piggy-backing off of the timer's interrupt
service routine.

Note: v2 is not used b/c of there are issues of "bouncing" when using an ISR on the switches.

As for the issues with the Line interrupts. First a general statement you probably don't want 
to use isr's attached to switches the tend to bounce (causing many isr's back to back). Also, 
from a general design aspect I would have polled the switches at the time of the ISR (timer 
overflow) and this will simplify the design quite a bit. This also acts as a simple debounce.
