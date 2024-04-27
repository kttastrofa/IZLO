%include "rw32-2022.inc"

section .data

x dw -300
y dw 7
v dw 0
z dw 0

section .text
CMAIN:
	push ebp
	mov ebp,esp
	
    ; (I)DIV s
    ; s - reg/mem
    ; s -  8bit .... AL = AX/s, AH = AX%s
    ; s - 16bit .... AX = DX:AX/s, DX = DX:AX%s
    ; s - 32bit .... EAX = EDX:EAX/s,  EDX = EDX:EAX%s
    ; nenastavuje priznaky, zpusobi vyjimku
    ;;;; co muze byt spatne?

    mov ax, [x]
    div word [y]



    mov dx, 0
    mov ax, [x]
    div word [y]
  
    ; znamenkove deleni
    mov ax,[x]
    mov dx, 0
    idiv word[y]

    ; CBW - convert byte to word
    ; CWD - convert word to double word
    ; CDQ - convert double word to quad word
    ; rozsireni registru al/ax/eax na ax/dx:ax/edx:eax

    mov ax,[x]
    cwd
    idiv word[y]

    pop ebp
	ret
