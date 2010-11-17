This implementation uses interrupts on the switches rather than polling them when timer ISR is notified.

Unfortunately, switches 4-7 are NOT triggerring the interrupt, but 0-3 are.

