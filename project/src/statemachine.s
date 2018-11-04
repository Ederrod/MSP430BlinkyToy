.text
    .balign 2
    .global led_state_update
    .type led_state_update, @function

led_state_update: 
    mov.b &switch_btn, r12
    cmp.w #2,  r12 { jeq .L4
    mov.b #2,  r13
    cmp.w r12, r13 { jl  .L2
    cmp.w #1,  r12 { jeq .L3
.L2: 
    cmp.w #4, r12 { jeq .L5
    cmp.w #8, r12 { jeq .L6
    br    #.L7
.L3:;SW1
    mov.b #1, &led_changed
    mov.b #0, &green_on
    mov.b #1, &red_on
    call  #buzzer_advance_frequency
    br    #.L7
.L4:;SW2
    mov.b #1, &led_changed
    mov.b #1, &red_on
    mov.b #0, &green_on
    call  #led_dim_state_update
    call  #buzzer_advance_frequency
    br    #.L7
.L5:;SW3
    mov.b #1, &led_changed
    mov.b #1, &green_on
    mov.b #0, &red_on
    call  #buzzer_advance_frequency
    br    #.L7
.L6: ;SW4 
    mov.b #1, &led_changed
    mov.b #0, &red_on
    mov.b #1, &green_on
    call  #led_dim_state_update
    call  #buzzer_advance_frequency
    br    #.L7

.L7: 
    mov.b #0, &switch_state_down
    mov.b #0, switch_state_up
    call #led_update
    nop
    ret
    .size led_state_update, .-led_state_update
