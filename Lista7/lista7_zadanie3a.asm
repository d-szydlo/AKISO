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
        fld dword [input]   ; s(0) = x
        fldl2e              ; s(0) = log2e, s(1) = x
        fmulp               ; s(0) = x*log2e
        fld1                ; s(0) = 1, s(1) = x*log2e
        fld st1             ; s(0) = x*log2e, s(1) = 1, s(2) = x*log2e
        fprem               ; s(0) = (x*log2e)%1, s(1) = 1, s(2) = x*log2e
        f2xm1               ; s(0) = 2^((x*log2e)%1)-1, s(1) = 1, s(2) = x*log2e
        faddp               ; s(0) = 2^((x*log2e)%1), s(1) = x*log2e
        fscale              ; s(0) = 2^((x*log2e)%1) * 2^(floor(x*log2e)) = e^x

        fld1                ; s(0) = 1, s(1) = e^(-x)
        fdiv st0, st1       ; s(0) = e^(-x), s(1) = e^x

        fsubp               ; s(0) = e^x-e^(-x)
        fld1                ; s(0) = 1.0, s(1) = -e^(-x)+e^x
        fld1                ; s(0) = 1.0, s(1) = 1.0, s(2) = -e^(-x)+e^x
        faddp               ; s(0) = 2.0, s(1) = -e^(-x)+e^x
        fdivp               ; s(0) = (-e^(-x)+e^x)/2.0

        fst qword [output]  ; *output = qword
        push dword [output+4]
        push dword [output]
        push prformat
        call printf
        add esp, 12

        xor eax,eax
        ret
        
