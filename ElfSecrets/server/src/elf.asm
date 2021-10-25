global _start

section .text

_print:
	; write
	mov eax, 4
	mov ebx, 1
	lea ecx, dword [esp+8]
	mov edx, dword [esp+4]
	int 0x80

	ret

_start:
	; super-magic-extra-fuckmyass-crypto-magic
	mov edi, 0xaabbccdd
	xor edi, 0xeeff0011
	push 0x0
	push 0x203a7265
	push 0x77736e41
	push 9
	call _print
	and edi, 0xffff00ff
	or edi, 0xaa00

	; read
	xor eax, eax
	push eax
	mov eax, 3
	xor ebx, ebx
	lea ecx, dword [esp]
	mov edx, 4
	int 0x80

	mov esi, [esp]

	cmp esi, edi
	je _equal

	; Suc
	push 0x00
	push 0x0a637553
	push 5
	call _print

	jmp _exit

_equal:
	; Go next
	push 0x00000a74
	push 0x78656e20
	push 0x6f472021
	push 0x6c6f6f43
	push 15
	call _print

_exit:
	; exit
	mov eax, 1
	xor ebx, ebx
	int 0x80
