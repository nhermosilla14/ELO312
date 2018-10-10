#include "msp430x16x.h"
#define         SPinit  0x24FA
#define         COUNTER_LOOP    R8
#define         COUNTER_ADDR   R9
#define         n       0x0007
 
main             
;-------------------------------------------------------------------------------        
                ORG	0x2500				; Direcci�n de inicio del programa
;-------------------------------------------------------------------------------
RESET           MOV	#SPinit,SP      	; Inicio del Stack
;; Se inicializa una porci�n de memoria, para probar la copia
                MOV     #n,R14            ; Inicializaci�n del contador
                
                PUSH    R10
LOOP1           MOV     #0x8881,R10
                ADD     R14,R10
                PUSH    R10                   ; A�ade el valor 0x81+R14 al stack
                DEC     R14               ; Disminuye el contador en 1
                
                JNZ     LOOP1                    ;

; Aqu� empieza la funci�n nueva

                POP     R10
                MOV     #0x2620,R12 
                MOV     SP,R13
                MOV     #n,R14
                
                CALL    #FUNCION
                
;; Parte para limpiar la memoria usada al inicio
                MOV     #n,R14
LOOP3           POP     R10                   ; A�ade el valor 0x81+R14 al stack
                DEC     R14               ; Disminuye el contador en 1  
                JNZ     LOOP3                    ;

                BR      #EXIT

FUNCION         BIS.B   #01h,&P1DIR
                BIS.B   #00h,&P1SEL
                BIS.B   #01h,&P2DIR
                BIS.B   #00h,&P2SEL
                PUSH    R10                     ; Respalda R10 en el stack
                PUSH    COUNTER_ADDR            ; Respalda COUNTER_ADDR en el stack
                PUSH    COUNTER_LOOP            ; Respalda COUNTER_LOOP en el stack
                MOV     #0x0,COUNTER_ADDR       ; Inicializa en 0 COUNTER_ADDR
                MOV     R14,COUNTER_LOOP        ; Inicializa en el valor dado el
                DEC     COUNTER_LOOP                                 ; COUNTER_LOOP
LOOP2           BIC.B   #10h,&P1OUT
                CLR.B   &P2OUT
                MOV     R13,R15                 ; COPIA R13 a R15, para operar en R15
                ADD     COUNTER_ADDR,R15        ; SUMA COUNTER_ADDR a R15
                MOV.B     @R15,R10                ; Rescata el valor de @R15 en R10
                MOV     R12,R15                 ; Reusamos R15 para seguir operando
                ADD     COUNTER_ADDR, R15  
                BIS.B   #10h,&P1OUT     
                MOV.B     R10,0x0(R15)            ; Copia el valor guardado a la
                CMP.B   #00h,R10
                JEQ     CONTINUE
                MOV.B   R10,&P2OUT
CONTINUE        INC     COUNTER_ADDR            ; nueva direcci�n.           ;
                DEC     COUNTER_LOOP            ; Sube el contador de addr, baja
                JNZ     LOOP2                   ; el del LOOP.
                MOV     R12,R12                 ; Valor de retorno a R12
                POP     COUNTER_LOOP            ; Restituye los valores respaldados
                POP     COUNTER_ADDR            ; en el stack.
                POP     R10                     
                RET
                
                
;-------------------------------------------------------------------------------
EXIT            JMP     EXIT            ;
;------------------------------------------------------------------------------ 
; Vector de interrupci�n asociado a Reset 
;------------------------------------------------------------------------------ 
                ORG 0xFFFE ; MSP430 RESET Vector 
                DW RESET
                END
 