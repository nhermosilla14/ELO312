#include "msp430x16x.h"
#define         SPinit  0x24FF
#define         COUNTER_LOOP    R8
#define         COUNTER_ADDR   R9
#define         n       0x0007
 
main             
;-------------------------------------------------------------------------------        
                ORG	0x2500				; Dirección de inicio del programa
;-------------------------------------------------------------------------------
                PUSH    R10
RESET	        MOV	#SPinit,SP      	; Inicio del Stack
                MOV     #n,R14            ; Inicialización del contador
                
LOOP1           MOV     #0x81,R10
                ADD     R14,R10
                PUSH    R10                   ; Añade el valor 0x81+R14 al stack
                DEC     R14               ; Disminuye el contador en 1
                
                JNZ     LOOP1                    ;

; Aquí empieza la función nueva

                
                MOV     #0x2620,R12 
                MOV     SP,R13
                MOV     #0x0007,R14
                
                CALL    #FUNCION
                POP     R10
                BR      #EXIT

FUNCION         PUSH    R10
                PUSH    COUNTER_ADDR
                PUSH    COUNTER_LOOP
                MOV     #0x0,COUNTER_ADDR       ; Inicializa en 0 COUNTER_ADDR
                MOV     R14,COUNTER_LOOP        ; Inicializa en el valor dado el
                                                ; COUNTER_LOOP
LOOP2           MOV     R13,R15
                ADD     COUNTER_ADDR,R15
                MOV     @R15,R10
                MOV     R12,R15
                ADD     COUNTER_ADDR, R15  
                MOV     R10,0x0(R15)
                INC     COUNTER_ADDR
                INC     COUNTER_ADDR
                DEC     COUNTER_LOOP
                JNZ     LOOP2
                MOV     R12,R12
                POP     COUNTER_LOOP
                POP     COUNTER_ADDR
                POP     R10
                RET
                
                
;-------------------------------------------------------------------------------
EXIT            JMP     EXIT            ;
;------------------------------------------------------------------------------ 
; Vector de interrupción asociado a Reset 
;------------------------------------------------------------------------------ 
                ORG 0xFFFE ; MSP430 RESET Vector 
                DW RESET
                END
 