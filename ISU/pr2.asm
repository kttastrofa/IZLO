%include "rw32-2022.inc"

section .data
    
x dw 20
y dw 100
z dd 0

section .text
CMAIN:
	push ebp
	mov ebp,esp

    ;(I)MUL s
    ; s - reg/mem
    ; s -  8bit .... AX = AL * s
    ; s - 16bit .... DX:AX = AX*s
    ; s - 32bit .... EDX:EAX = EAX*s
    ; MUL: CF=OF = sizeof(AL/AX/EAX * s) > sizeof (AL/AX/EAX)
    ;      CF=OF = (AH/DX/EDX ==0) ? 0 :1
    ; IMUL: ((AX -32bit) == (DX:AX)) ? 0 : 1
    ; pokud se soucin nevleze do poctu bitu "s" - vysledek je i v druhem registru
    ; IMUL d,s .... d = d*s - zahodi se vyssi cast vysledku
    ; IMUL d,s,i    d = s*i 
   
    ; z = x*y
    mov ax, [x]
    mul word [y]
    mov [z],ax

    mov ax, [x]
    mul word [y]
    mov [z],ax
    mov [z+2], dx

    mov eax, [x] ; spatne, nacita se word do doublew
    mov bx, [y]
    mul ebx
    mov [z], eax





    movzx eax, word[x] ; pro bezznamenkove cislo - rozsizeni nulami
    movzx ebx, word[y]
    mul ebx
    mov [z], eax

 
    ; operace se znamenkem
    mov ax, [x]
    imul word [y]
    mov [z], ax
    mov [z+2], dx


    movsx eax, word[x] ; znamenkove rozsireni
    movsx ebx, word[y]
    imul ebx
    mov [z], eax


	pop ebp
	ret
