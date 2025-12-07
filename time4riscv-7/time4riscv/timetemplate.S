#############################################################
# DTEK-V macros (för att spara/ladda register på stacken)
#############################################################
.macro PUSH reg
  addi sp, sp, -4        # gör plats på stacken
  sw   \reg, 0(sp)       # spara registervärde på stacken
.endm

.macro POP reg
  lw   \reg, 0(sp)       # hämta tillbaka registervärde
  addi sp, sp, 4         # flytta stackpekaren upp igen
.endm

#############################################################
# Data-sektion: variabler
#############################################################
    .data
    .align 2
mytime:  .word  0x5957                     # starttid (MMSS-format, ex. 59:57)
timstr:  .asciz "text more text lots of text\0"  # buffer för utskrift

#############################################################
# Kod-sektion
#############################################################
    .text
    .globl timetemplate, hexasc, delay, time2string, display_string, tick
    .type  timetemplate, @function

#############################################################
# timetemplate: huvudloop som kör klockan
#############################################################
timetemplate:
    PUSH ra               # spara returadressen

loop:

    # vänta lite (200 ms ≈ 0.2 sekunder, kalibreras med DELAY_INNER)
    li   a0, 200
    jal  delay

    # uppdatera tiden i mytime (öka med 1, fixa 60-sekunders-regler)
    la   a0, mytime
    jal  tick

    # konvertera tiden till en utskriftssträng (MM:SS)
    la   a0, timstr       # a0 = adress till buffern
    la   t0, mytime
    lw   a1, 0(t0)        # a1 = själva tiden (MMSS)
    jal  time2string

    # skriv ut tiden till terminalen
    la   a0, timstr
    li   a7, 4            # system call: print_string
    ecall
    li   a0, 10           # newline (LF)
    li   a7, 11           # system call: print_char
    ecall

    j    loop             # evig loop

    POP ra                # återställ returadress (nås aldrig)
    ret

#############################################################
# hexasc: översätter 0..15 → ASCII '0'..'9','A'..'F'
#############################################################
hexasc:
    andi a0, a0, 0xF      # behåll 4 LSB
    li   t0, 9
    ble  a0, t0, 1f       # om <=9 → gör om till '0'..'9'
    addi a0, a0, -10      # annars → 'A'..'F'
    addi a0, a0, 65       # ASCII 'A' = 65
    ret
1:  addi a0, a0, 48       # ASCII '0' = 48
    ret

#############################################################
# time2string: a0 = &timstr, a1 = tid (0xMMSS)
# skriver ut "MM:SS\0" i buffern
#############################################################
time2string:
    PUSH ra   # för att kunna hitta tillbaka
    PUSH s0   # spara pekare till bufferten
    PUSH s1   # spara tidvärdet (0xMMSS)
    mv s0, a0   # kopiera över adressen från a0 till s0 (buffert)
    mv s1, a1   # s1 innehåller själva klockslaget (0xMMSS)

    # a0 = pekare till buffer
    # mytime lagras globalt i format 0xMMSS (2 hex för minuter, 2 för sekunder)

    # Plocka ut sekunder och minuter via maskning
    andi t2, s1, 0x00FF     # sekunder = lägsta 8 bitar
    srli t3, s1, 8          # skifta ner 8 → minuter
    andi t3, t3, 0x00FF     # maska ut bara 8 bitar (för säkerhet)

    # om både minuter och sekunder = 0 → skriv "HOUR"
    beqz t2, check_min      # om sekunder = 0 → kolla minuter
    j build_time            # annars bygg "MM:SS"

check_min:
    beqz t3, skriv_hour     # om minuter också = 0 → skriv "HOUR"
    j build_time            # annars bygg "MM:SS"

skriv_hour:
    # skriv "HOUR" till bufferten
    li t4, 'H'
    sb t4, 0(s0)
    li t4, 'O'
    sb t4, 1(s0)
    li t4, 'U'
    sb t4, 2(s0)
    li t4, 'R'
    sb t4, 3(s0)
    li t4, 0               # noll-terminering
    sb t4, 4(s0)

    j done                 # hoppa till slutet (ingen vanlig utskrift)

build_time:
    # Bygg upp "MM:SS" som vanligt

    # M tiotal
    srli t0, s1, 12        # plocka minut-tiotal
    andi t0, t0, 0xF
    mv a0, t0
    jal hexasc
    sb a0, 0(s0)
    addi s0, s0, 1

    # M ental 
    srli t0, s1, 8         # plocka minut-ental
    andi t0, t0, 0xF
    mv a0, t0
    jal hexasc
    sb a0, 0(s0)
    addi s0, s0, 1
    
    # kolon (":")
    li t0, 0x3A
    sb t0, 0(s0)
    addi s0, s0, 1

    # S tiotal
    srli t0, s1, 4         # plocka sekund-tiotal
    andi t0, t0, 0xF
    mv a0, t0
    jal hexasc
    sb a0, 0(s0)
    addi s0, s0, 1

    # S ental
    andi t0, s1, 0xF       # plocka sekund-ental
    mv a0, t0
    jal hexasc
    sb a0, 0(s0)
    addi s0, s0, 1
    
    sb zero, 0(s0)         # markera att strängen är slut

done:
    POP s1               # återställ sparade register
    POP s0
    POP ra
    jr ra                  # returnera



#############################################################
# display_string: skriver ut en sträng + newline
#############################################################
display_string:
    li a7, 4         # system call: print_string
    ecall
    li a0, 10        # newline (LF)
    li a7, 11        # system call: print_char
    ecall
    ret

#############################################################
# tick: uppdaterar tiden (mytime) enligt MMSS-format
#############################################################
tick:
    lw   t0, 0(a0)     # hämta tiden
    addi t0, t0, 1     # öka med 1 (sekunder)

    # fixa entalsekunder (0–9 → A–F → tillbaka till 0)
    andi t1, t0, 0xf
    sltiu t2, t1, 0xa
    bnez t2, tiend
    addi t0, t0, 0x6

    # fixa tiotal sekunder
    andi t1, t0, 0xf0
    sltiu t2, t1, 0x60
    bnez t2, tiend
    addi t0, t0, 0xa0

    # fixa minuter ental
    li   t3, 0xF
    slli t3, t3, 8
    and  t1, t0, t3
    addi t3, x0, 0xA
    slli t3, t3, 8
    slt  t2, t1, t3
    bnez t2, tiend
    addi t0, t0, 0x600

    # fixa minuter tiotal
    li   t3, 0xF
    slli t3, t3, 12
    and  t1, t0, t3
    addi t3, x0, 0x6
    slli t3, t3, 12
    slt  t2, t1, t3
    bnez t2, tiend

    li   t3, 0xA
    slli t3, t3, 12
    add  t0, t0, t3

tiend:
    sw t0, 0(a0)       # skriv tillbaka tiden
    ret

#############################################################
# delay: väntar ~ms millisekunder
# while (ms>0) { ms--; for(i=0;i<DELAY_INNER;i++){} }
#############################################################
.equ DELAY_INNER, 80000       # kalibreringsvärde (justera vid behov!)

delay:
    mv   t0, a0              # t0 = antal ms
while_cond:
    bge  x0, t0, while_end   # om ms <= 0 → klart
    addi t0, t0, -1          # ms--

    li   t1, DELAY_INNER     # inre loop-räknare
for_loop:
    addi t1, t1, -1
    bnez t1, for_loop        # så länge t1 != 0, fortsätt loopa
    j    while_cond          # gå tillbaka till while

while_end:
    ret

