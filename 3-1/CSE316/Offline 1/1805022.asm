.MODEL SMALL

.STACK 100h

.DATA
    CR EQU 0Dh
    LF EQU 0Ah
    
    NEWLINEM DB CR,LF,'$'
    MSG1 DB 'Enter N: $'
     
    MSG2 DB 'Not found$' 
    MSG3 DB 'Found in position $'
    
    N DW 0   
    TEN DW 10  
    KEY DW ?          
    lo DW ?
    hi DW ?
    mid DW ?
    ARR DW 100 DUP(0)

.CODE  

MAIN PROC

; initialize DS
    MOV AX,@DATA
    MOV DS,AX

; print a message
    LEA DX, MSG1  ; mov pointer of string to dx
    CALL PRINTSTRING 
    CALL NEWLINE
 

; input multivalued N       
    
    CALL INPUTNUMBER    
    MOV N,DX 
    CALL NEWLINE 
    
  
    CMP N,0
    JLE END_P
    
    MOV CX,N  
    MOV SI,0
    
    TOP: 
        CALL INPUTNUMBER 
        
        MOV ARR[SI],DX 
        CALL NEWLINE
        ADD SI,2
    
    LOOP TOP
          
    
    MOV CX,N
    SUB CX,1  
    MOV SI,2
    JCXZ  ENDTOP2
    
    TOP2: 
        
        MOV AX,ARR[SI] 
        MOV KEY,AX
        MOV DI,SI
        SUB DI,2
        
        WHILE1:
        
        CMP DI,0
        JL ENDWHILE1    
        MOV AX,ARR[DI]
        CMP AX,KEY
        JLE ENDWHILE1
        
        MOV AX,ARR[DI]
        ADD DI,2
        MOV ARR[DI],AX
        
        SUB DI,4
        JMP WHILE1 
                   
                 
        ENDWHILE1:
         
        ADD DI,2
        MOV AX,KEY
        MOV ARR[DI],AX
        
        ADD SI,2
    
    LOOP TOP2
    
    ENDTOP2:
    CALL NEWLINE
    
    MOV CX,N  
    MOV SI,0
    
    TOP3:
      
        MOV AX,ARR[SI]
        CALL PRINTNUMBER  
        CALL NEWLINE
        ADD SI,2
    
    LOOP TOP3 
    
    MOV CX,5
    
    TOP4:
        
        CALL INPUTNUMBER 
        MOV AX,DX  
        
        CALL NEWLINE
        
        MOV BX,0
        
        MOV DX,N 
        MOV DH,DL 
        MOV DL,0
        SUB DH,1
        
        WHILE2:
            CMP DL,DH
            JG ENDWHILE2
            
            MOV BL,DL
            ADD BL,DH
            SHR BL,1
            
            MOV SI,0
            MOV SI,BX
            SHL SI,1
            
            CMP ARR[SI],AX
            JNE ENDIF1
            
            LEA DX, MSG3  ; mov pointer of string to dx
            CALL PRINTSTRING
            MOV AX,BX
            ADD AX,1
            CALL PRINTNUMBER 
            CALL NEWLINE
            JMP LABEL:
            
            ENDIF1:
            
            CMP ARR[SI],AX
            JL ENDIF2
            
     
            MOV DH,BL
            SUB DH,1
            JMP WHILE2
            
            ENDIF2:
                
            MOV DL,BL
            ADD DL,1
            JMP WHILE2   
            
            ENDWHILE2:  
            
            LEA DX, MSG2  ; mov pointer of string to dx
            CALL PRINTSTRING 
            CALL NEWLINE
            
            LABEL:
    
    LOOP TOP4
    
    
    END_P:
; DOS exit
    MOV AH,4Ch
    INT 21h

MAIN ENDP   

NEWLINE PROC 
    
    PUSH AX
    PUSH DX
    
    LEA DX, NEWLINEM
    MOV AH,9
    INT 21h
    
    POP DX
    POP AX 
    RET
   
NEWLINE ENDP

PRINTSTRING PROC
                  
    MOV AH,9
    INT 21h  
    RET
    
PRINTSTRING ENDP 

INPUTNUMBER PROC 
    
    MOV AX,0 
    MOV DX,0
    PUSH AX
    MOV AH,1 
    INT 21H 
    
    CMP AL,'-' 
    JE NEGATIVE_NUMBER
    JMP SKIP_ONE_INPUT
    
    NEGATIVE_NUMBER:
     
    
    POP AX
    MOV AX,1
    PUSH AX
     
    INPUTNUMBER_LABEL:
    
    MOV AH,1 
    INT 21H 
    SKIP_ONE_INPUT:
    CMP AL,32 
    JE INPUTNUMBER_END
    CMP AL,LF
    JE INPUTNUMBER_END
    CMP AL,CR
    JE INPUTNUMBER_END
    
    MOV BH,0
    MOV BL,AL
    SUB BL,'0'
    MOV AX,DX
    
    MUL TEN
    ADD AX,BX
    MOV DX,AX
    JMP INPUTNUMBER_LABEL
    
    INPUTNUMBER_END:
    
    POP AX
    CMP AX,0
    JE NOT_NEG
    NEG DX
    
    NOT_NEG:
    
      
    RET
    
INPUTNUMBER ENDP 

PRINTNUMBER PROC
    PUSH CX
    MOV CX,0   
    
    CMP AX,0             
    JG PRINTNUMBER_START 
    
    CMP AX,0
    JNE NOT_ZERO
    MOV DX,0
    ADD DL,'0'
    MOV AH, 02H
    INT 21H 
    POP CX  
    RET
    
    
    NOT_ZERO:
    PUSH AX
    MOV DX,'-'
    MOV AH, 02H
    INT 21H 
    POP AX  
    NEG AX
    
    PRINTNUMBER_START:
    CMP AX,0
    JE PRINTNUMBER_END 
    
    XOR DX, DX
    DIV TEN
    ADD DL, '0'
    PUSH DX
    INC CX
    JMP PRINTNUMBER_START
    
    PRINTNUMBER_END:
    
    PRINTNUMBER_LOOP:
        
        POP DX
        MOV AH, 02H
        INT 21H
    
    LOOP PRINTNUMBER_LOOP 
    POP CX
    RET
    
PRINTNUMBER ENDP    

END MAIN           