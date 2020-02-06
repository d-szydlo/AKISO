.text
.global main
main:
        ldr r0, =format
        ldr r1, =x
        bl scanf
        ldr r0, =format
        ldr r1, =y
        bl scanf
        ldr r2, =x
        ldr r0, [r2]
        ldr r2, =y
        ldr r1, [r2]
        
nwd:
        cmp r0,r1
        subgt r0, r0, r1
        sublt r1, r1, r0
        bne nwd
        ldr r0, =format
        bl printf

.data
format:
        .string "%d"
x:
        .word 0
y:      
        .word 0

