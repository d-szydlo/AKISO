
        opt f-g-h+l+o+
        org $1050
start   lda #$01
        ldy #$01
        ldx #05
        jsr div
        brk
div     sta bta
        sty bta+1
        stx btb
        ldx #0
        stx rem
        stx rsl
        stx rsl+1
        ldx #16
div_lop asl bta+1
        rol bta
        rol rem
        lda rem
        sec
        sbc btb
        bmi div_neg
        sec
        rol rsl+1
        rol rsl
        sta rem
        bcc div_nxt
div_neg clc
        rol rsl+1
        rol rsl
div_nxt dex
        bne div_lop
        rts
bta     dta a(0)
btb     dta b(0)
rem     dta b(0)
rsl     dta a(0)
        
        org $2E0
        dta a(start)
        end of file
