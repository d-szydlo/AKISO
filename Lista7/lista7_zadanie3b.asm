global main
extern scanf
extern printf

section .data
input:      dd 1.0
output:     dq 0.0
scformat: db "%f", 0
prformat: db "%lf",10,0

section .text
main:
        lea eax, [input]
        push eax
        push scformat
        call scanf
        add esp, 8

        finit
        fld1                ; s(0) = 1
        fld dword [input]   ; s(0) = x, s(1) = 1
        fld st0             ; s(0) = x, s(1) = x, s(2) = 1
        fmulp               ; s(0) = x^2, s(1) = 1
        fld1                ; s(0) = 1.0, s(1) = x^2, s(2) = 1
        faddp               ; s(0) = x^2+1, s(1) = 1
        fsqrt               ; s(0) = (x^2+1)^(1/2), s(1) = 1
        fld dword [input]   ; s(0) = x, s(1) = (x^2+1)^(1/2), s(1) = 1
        faddp               ; s(0) = x+(x^2+1)^(1/2), s(1) = 1
        fyl2x               ; s(0) = log2(x+(x^2+1)^(1/2))*1
        fldl2e              ; s(0) = log2(e), s(1) = log2(x+(x^2+1)^(1/2))*1
        fdivp               ; s(0) = log2(x+(x^2+1)^(1/2))*1/log2(e) = ln(x+(x^2+1)^(1/2))

        fst qword [output]  ; *output = qword
        push dword [output+4]
        push dword [output]
        push prformat
        call printf
        add esp, 12

        xor eax,eax
        ret
        
