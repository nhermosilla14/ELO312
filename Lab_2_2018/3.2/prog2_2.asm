#include "msp430x16x.h" 
#define		SPinit	0x24FF			// Ubicaci�n en la RAM
#define		op1	R15					// �qu� se define? d�nde?
#define		op2	R14					// �qu� se define? d�nde?

main
;-------------------------------------------------------------------------------        
                ORG	0x2500				; Direcci�n de inicio del programa
;-------------------------------------------------------------------------------
RESET	        MOV	#SPinit,SP      	; Inicio del Stack
SetupP1			bis.b #001h,&P1DIR	; P1.0 output
			bic.b #001h,&P1OUT  ; Clear Bit
                MOV     #0x02,op1 ; Reemplazo de l�nea 13
                MOV	#0x01,op2
                CALL	#OPERACION		; Se realiza operaci�n. �D�nde queda el resultado?
                BR      #EXIT			; Reemplace toda la instrucci�n por RET. �Qu� ocurre?
;-------------------------------------------------------------------------------
OPERACION       
                ADD	op2,op1         ; �Qu� operacion se realiza?
				xor.b   #001h,&P1OUT
                RET
;-------------------------------------------------------------------------------
EXIT            JMP     EXIT            ; �Qu� realiza esta instrucci�n?
;------------------------------------------------------------------------------ 
; Vector de interrupci�n asociado a Reset 
;------------------------------------------------------------------------------ 
                ORG 0xFFFE ; MSP430 RESET Vector 
                DW RESET
                END
 
