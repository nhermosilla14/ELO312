#include "msp430x16x.h" 
#define		SPinit	0x24FF			// Ubicaci�n en la RAM
#define         COUNTER R14

main
;-------------------------------------------------------------------------------        
                ORG	0x2500				; Direcci�n de inicio del programa
;-------------------------------------------------------------------------------
RESET	        MOV	#SPinit,SP      	; Inicio del Stack
                MOV     #0xF,COUNTER            ; Inicializaci�n del contador
                
LOOP            PUSH    #0x81                   ; A�ade el valor 0x81 al stack
                DEC     COUNTER                 ; Disminuye el contador en 1
                
                JNZ     LOOP                    ; Si aun no vale cero el
                BR      #EXIT			; contador, sigue haciendo lo
                                                ; mismo.
;-------------------------------------------------------------------------------
EXIT            JMP     EXIT            ;
;------------------------------------------------------------------------------ 
; Vector de interrupci�n asociado a Reset 
;------------------------------------------------------------------------------ 
                ORG 0xFFFE ; MSP430 RESET Vector 
                DW RESET
                END
 
