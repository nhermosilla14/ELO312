#include "msp430x16x.h"
#define         SPinit  0x24FA
#define         COUNTER_LOOP    R8
#define         COUNTER_ADDR   R9
#define         n       0x0007
 
main             
;-------------------------------------------------------------------------------        
                ORG	0x2500				; Dirección de inicio del programa
;-------------------------------------------------------------------------------
RESET           MOV	#SPinit,SP      	; Inicio del Stack
;; Se inicializa una porción de memoria, para probar la copia
                MOV     #n,R14            ; Inicialización del contador
                
                PUSH    R10
LOOP1           MOV     #0x8881,R10
                ADD     R14,R10
                PUSH    R10                   ; Añade el valor 0x81+R14 al stack
                DEC     R14               ; Disminuye el contador en 1
                
                JNZ     LOOP1                    ;

; Aquí empieza la función nueva

                POP     R10
                MOV     #0x2620,R12 
                MOV     SP,R13
                MOV     #n,R14
                
                CALL    #FUNCION
                
;; Parte para limpiar la memoria usada al inicio
                MOV     #n,R14
LOOP3           POP     R10                   ; Añade el valor 0x81+R14 al stack
                DEC     R14               ; Disminuye el contador en 1  
                JNZ     LOOP3                    ;

                BR      #EXIT

FUNCION         BIS.B   #01h,&P1DIR
                BIS.B   #00h,&P1SEL
                BIS.B   #01h,&P2DIR
                BIS.B   #00h,&P2SEL
                PUSH    R10                     ; Respalda R10 en el stack

;                PUSH    COUNTER_ADDR            ; Respalda COUNTER_ADDR en el stack
                PUSH    R12
                PUSH    COUNTER_LOOP            ; Respalda COUNTER_LOOP en el stack
                MOV     R14,COUNTER_LOOP        ; Inicializa en el valor dado el
                DEC     COUNTER_LOOP                                 ; COUNTER_LOOP
LOOP2           BIC.B   #10h,&P1OUT
                CLR.B   &P2OUT
                
PAUSA           MOV.B   &P1IN,R10
                AND.B   #01h,R10
                CMP.B   #01h,R10
                JEQ     PAUSA
           
                CMP.B   0x0(R13),00h
                JEQ     CONTINUA
                MOV.B   R12,&P2OUT
CONTINUA        MOV.B   @R13+,0x0(R12)                ; COPIA R13 a R15, para operar en R15
                INC     R12
                BIS.B   #10h,&P1OUT    
                DEC     COUNTER_LOOP            ; Sube el contador de addr, baja
                JNZ     LOOP2                   ; el del LOOP.
                
                
                POP     COUNTER_LOOP            ; Restituye los valores respaldados
                POP     R12                     ; en el stack.
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
 