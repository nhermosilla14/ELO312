#include "msp430x16x.h" 
#define		SPinit	0x24FF			// Ubicación en la RAM
#define         COUNTER R14
#define         n       0x000F

main
;-------------------------------------------------------------------------------        
                ORG	0x2500				; Dirección de inicio del programa
;-------------------------------------------------------------------------------
RESET	        MOV	#SPinit,SP      	; Inicio del Stack
                MOV     #n,COUNTER            ; Inicialización del contador
                
LOOP            PUSH    #0x81                   ; Añade el valor 0x81 al stack
                DEC     COUNTER                 ; Disminuye el contador en 1
                
                JNZ     LOOP                    ; Si aun no vale cero el
                BR      #EXIT			; contador, sigue haciendo lo
                                                ; mismo.
;-------------------------------------------------------------------------------
EXIT            JMP     EXIT            ;
;------------------------------------------------------------------------------ 
; Vector de interrupción asociado a Reset 
;------------------------------------------------------------------------------ 
                ORG 0xFFFE ; MSP430 RESET Vector 
                DW RESET
                END
 
