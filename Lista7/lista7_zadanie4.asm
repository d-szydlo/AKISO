bits 16
org 0x7c00

boot:
    mov ax, 0x2401
    int 0x15
    mov ax, 0x13        ; wlaczenie trybu graficznego 320x200
    int 0x10
    cli
    lgdt [gdt_pointer]  ; ustawienie tablicy GDT
    mov eax, cr0        ; wlaczenie trybu chronionego
    or eax,0x1
    mov cr0, eax
    jmp CODE_SEG:mandelbrot
gdt_start:              ; tablica GDT
    dq 0x0
gdt_code:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0
gdt_data:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0
gdt_end:
gdt_pointer:
    dw gdt_end - gdt_start
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

bits 32
.data:
    CntrA: dd 0
    CntrB: dd 0
    x: dd 0
    y: dd 0
mandelbrot:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebx,0xa0000     ; adres ekranu graficznego
    mov cx,200

    mov edi, 0xa0000
    mov dword  [CntrA],-510*256
    mov dword  [x], 0
.LoopHoriz:
    mov dword  [CntrB],-270*256
    mov dword  [y],200
.LoopVert:
    xor ecx, ecx                ; ecx = x = 0
    xor edx, edx                ; edx = y = 0
    mov si, 32-1                ; kolor
.LoopFractal:
    mov eax,ecx
    imul eax,eax                ; eax = x^2
    mov ebx,edx
    imul ebx,ebx                ; ebx = y^2
    sub eax,ebx                 ; eax = x^2 - y^2
    add eax,dword [CntrA]       ; eax = x^2 - y^2 + C
    mov ebx, ecx
    imul ebx,edx                ; ebx = xy
    sal ebx,1                   ; ebx = 2xy
    add ebx, dword [CntrB]      ; ebx = 2xy + C
    sar eax, 8                  ; eax = eax/16
    sar ebx, 8                  ; ebx = ebx/16
    mov ecx, eax                
    mov edx, ebx
    imul eax, eax               ; eax = x^2
    imul ebx, ebx               ; ebx = y^2
    add eax, ebx                ; eax = x^2 + y^2
    sar eax, 8                  ; eax = eax/16
    cmp eax, 1024               ; if (x^2 + y^2 > 1024) then break
    jg .Break
    dec si                      ; kolor--
    jnz .LoopFractal
.Break:
    mov ax, si
    mov byte [edi], al
    add dword [CntrB],720
    add edi,320
    dec dword [y]
    jnz .LoopVert
    add dword [CntrA],568
    inc dword [x]
    mov edi, 0xa0000
    add edi, dword [x]
    cmp dword [x],320
    jnz .LoopHoriz
halt:
    cli
    hlt

times 510 - ($-$$) db 0
dw 0xaa55


