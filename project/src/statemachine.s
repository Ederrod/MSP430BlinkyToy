.text

jt: .word case1  ; jt[1] 
    .word case2  ; jt[2]
    .word case3  ; jt[3]
    .word case4  ; jt[4]

    .global led_state_update
    .type led_state_update, @function

led_state_update: 
    cmp.b #4, &switch_btn
    jnc   end
    
    mov.b &switch_btn, r12
    add   r12, r12
    mov   jt(r12), r0

case1: 
    mov.b #1, &led_changed
    mov.b #0, &green_on
    mov.b #1, &red_on
    call  #buzzer_advance_frequency
    jmp   end
case2: 
    mov.b #1, &led_changed
    mov.b #1, &red_on
    mov.b #0, &green_on
    call  #led_dim_state_update
    call  #buzzer_advance_frequency
    jmp   end
case3: 
    mov.b #1, &led_changed
    mov.b #1, &green_on
    mov.b #0, &red_on
    call  #buzzer_advance_frequency
    jmp   end
case4: 
    mov.b #1, &led_changed
    mov.b #0, &red_on
    mov.b #1, &green_on
    call  #led_dim_state_update
    call  #buzzer_advance_frequency
    jmp   end

end: 
    mov.b #0, &switch_state_down
    mov.b #0, switch_state_up
    call #led_state_update
    nop
    ret
    .size led_state_update, .-led_state_update
