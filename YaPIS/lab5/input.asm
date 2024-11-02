START:      MOV AX, 0x1F         
            ADD BX, 0xAA           
LOOP:       SUB CX, BX           
            JMP LOOP
            NOP                  
            CMP AX, BX           
END:        MOV AX, 0x56
