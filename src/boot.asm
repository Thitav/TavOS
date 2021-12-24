[org 0x7c00]

;; equ is used to set constants
CODE_SEG equ code_descriptor - gdt_start
DATA_SEG equ data_descriptor - gdt_start
KERNEL_LOCATION equ 0x1000

mov [BOOT_DISK], dl ;; saving boot disk number

;; set up segment registers and stack
xor ax, ax ;; reset ax
mov es, ax
mov ds, ax
mov bp, 0x8000 ;; set the stack safely away
mov sp, bp

;; load kernel from disk
mov bx, KERNEL_LOCATION
mov dh, 20
push dx

mov ah, 2
mov al, dh 
mov ch, 0
mov dh, 0
mov cl, 2
mov dl, [BOOT_DISK]
int 0x13

;; error checking
jc disk_error
pop dx
cmp al, dh
jne disk_error

;; text mode (for clear screen)
mov ah, 0
mov al, 3
int 0x10

;; enter protected mode
cli ;; stop using bios
lgdt [gdt_descriptor] ;; read GDT
mov eax, cr0 ;; change last bit o cr0 to 1 for 32 bit protected mode
or eax, 1
mov cr0, eax
jmp CODE_SEG:start_protected_mode ;; jump to segment

jmp $

;; GDT structure
gdt_start:
  null_descriptor:
    dd 0
    dd 0
  code_descriptor:
    dw 0xffff ;; limit
    dw 0 ;; base 16 bit +
    db 0 ;; base 8 bit = 24 bit
    db 0b10011010 ;; pres priv type + type flags
    db 0b11001111 ;; other flags + 1111
    db 0 ;; last 8 bits of base
  data_descriptor:
    dw 0xffff ;; limit
    dw 0 ;; base 16 bit +
    db 0 ;; base 8 bit = 24 bit
    db 0b10010010 ;; pres priv type + type flags
    db 0b11001111 ;; other flags + 1111
    db 0 ;; last 8 bits of base
gdt_end:

gdt_descriptor:
  dw gdt_end - gdt_start - 1 ;; size
  dd gdt_start ;; start

print:
  print_loop:
    mov al, [bx]
    cmp al, 0
    je print_end
    mov ah, 0x0e
    int 0x10
    inc bx
    jmp print_loop
  print_end:
    ret

disk_error:
  mov bx, MSG_DISK_ERROR
  call print
  jmp $

;; 32 bit protected mode
start_protected_mode:
  [bits 32]
  ;; set up segment registers and stack
  mov ax, DATA_SEG
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ebp, 0x90000
  mov esp, ebp

  jmp KERNEL_LOCATION ;; start executing kernel

BOOT_DISK: db 0
MSG_DISK_ERROR:  db "Error loading kernel from disk", 0

times 510-($-$$) db 0 ;; fill with 0s
db 0x55, 0xaa ;; boot bytes
