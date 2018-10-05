#include "msp430x16x.h" 
#define		SPinit	0x24FF			// Ubicaci�n en la RAM
#define         COUNTER R14

main
;-------------------------------------------------------------------------------        
                ORG	0x2500				; Direcci�n de inicio del programa
;-------------------------------------------------------------------------------
RESET	        MOV	#SPinit,SP      	; Inicio del Stack
                MOV     #0xF,COUNTER
LOOP            PUSH    #0x81
                DEC     COUNTER
                JNZ     LOOP
                BR      #EXIT			;
;-------------------------------------------------------------------------------
EXIT            JMP     EXIT            ; �Qu� realiza esta instrucci�n?
;------------------------------------------------------------------------------ 
; Vector de interrupci�n asociado a Reset 
;------------------------------------------------------------------------------ 
                ORG 0xFFFE ; MSP430 RESET Vector 
                DW RESET
                END
 
