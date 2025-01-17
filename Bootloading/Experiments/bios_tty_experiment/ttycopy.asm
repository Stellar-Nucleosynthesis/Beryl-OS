[BITS 16]
[ORG 0x7C00]  ; The program starts here in memory

start:
wait_key:
    xor ah, ah           ; Loading INT num
    int 0x16             ; Waiting for a key being pressed
    cmp al, 0x1B         ; Checking for "esc"
    je exit              ; If yes, exit
    cmp al, 0x20         ; Checking for a printable char
    jb wait_key          ; If not, skip
    cmp al, 0x7F         ; Checking for an ASCII char
    ja wait_key          ; If not, skip
    mov ah, 0x0E         ; Loading INT num
    int 0x10             ; Outputting the symbol
    jmp wait_key         ; To the beginning we go

exit:
    cli                  ; Prohibiting INTs
    hlt                  ; That's it

times 510-($-$$) db 0    ; Filling the rest with 0's
dw 0xAA55               ; Boot signature
