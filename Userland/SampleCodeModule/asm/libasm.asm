GLOBAL write
GLOBAL read
GLOBAL DateTime
GLOBAL getMem
GLOBAL getReg
GLOBAL Clear
GLOBAL opCodeExc


write:
    push rbp
    mov rbp, rsp

    push rdi
    push rsi
    push rdx
    push rcx

    mov rcx, rdx
    mov rdx, rsi
    mov rsi, rdi
    mov rdi, 1
    int 80h

    pop rcx
    pop rdx
    pop rsi
    pop rdi

    mov rsp, rbp
    pop rbp
    ret

read:
    push rbp
    mov rbp, rsp

    push rdi
    push rsi
    push rdx
    push rcx

    mov rcx, rdx
    mov rdx, rsi
    mov rsi, rdi
    mov rdi, 0
    int 80h

    pop rcx
    pop rdx
    pop rsi
    pop rdi

    mov rsp, rbp
    pop rbp
    ret

DateTime:
    push rbp
    mov rbp, rsp

    push rdi
    push rsi

    mov rsi, rdi
    mov rdi, 2
    int 80h

    push rsi
    push rdi

    mov rsp, rbp
    pop rbp
    ret

getReg:
    push rbp
    mov rbp, rsp

    push rdi
    push rsi

    mov rsi, rdi
    mov rdi, 3
    int 80h

    pop rsi
    pop rdi

    mov rsp, rbp
    pop rbp
    ret

getMem:
    push rbp
    mov rbp, rsp

    push rdi
    push rsi
    push rdx
    push rcx

    mov rcx, rdx
    mov rdx, rsi
    mov rsi, rdi
    mov rdi, 4
    int 80h

    pop rcx
    pop rdx
    pop rsi
    pop rdi

    mov rsp, rbp
    pop rbp
    ret

Clear:
    push rbp
    mov rbp, rsp

    push rdi

    mov rdi, 5
    int 80h

    pop rdi

    mov rsp, rbp
    pop rbp
    ret

opCodeExc:
    UD2
    ret
    