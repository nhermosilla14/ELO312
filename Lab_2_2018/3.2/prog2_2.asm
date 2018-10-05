#include "msp430x16x.h" 
#define		SPinit	0x24FF			// Ubicación en la RAM
#define		op1	R15					// ¿qué se define? dónde?
#define		op2	R14					// ¿qué se define? dónde?

main
;-------------------------------------------------------------------------------        
                ORG	0x2500				; Dirección de inicio del programa
;-------------------------------------------------------------------------------
RESET	        MOV	#SPinit,SP      	; Inicio del Stack
SetupP1			bis.b #001h,&P1DIR	; P1.0 output
			bic.b #001h,&P1OUT  ; Clear Bit
                MOV     #0x02,op1 ; Reemplazo de línea 13
                MOV	#0x01,op2
                CALL	#OPERACION		; Se realiza operación. ¿Dónde queda el resultado?
                BR      #EXIT			; Reemplace toda la instrucción por RET. ¿Qué ocurre?
;-------------------------------------------------------------------------------
OPERACION       
                ADD	op2,op1         ; ¿Qué operacion se realiza?
				xor.b   #001h,&P1OUT
                RET
;-------------------------------------------------------------------------------
EXIT            JMP     EXIT            ; ¿Qué realiza esta instrucción?
;------------------------------------------------------------------------------ 
; Vector de interrupción asociado a Reset 
;------------------------------------------------------------------------------ 
                ORG 0xFFFE ; MSP430 RESET Vector 
                DW RESET
                END
 
