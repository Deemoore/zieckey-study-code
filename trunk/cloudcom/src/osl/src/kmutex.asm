section .text

global InterlockedCmpXchng

InterlockedCmpXchng:
        push ebx
        push ecx
        mov eax, [esp+14h]
        mov ebx, [esp+10h]
        mov ecx, [esp+0ch]
        LOCK CMPXCHG [ecx], ebx
        pop ecx
        pop ebx
        ret

global InterlockedXchng

InterlockedXchng:
        push ebx
        mov eax, [esp+0ch]
        mov ebx, [esp+08]
        LOCK XCHG [ebx], eax
        pop ebx
        ret

global InterlockedInc

InterlockedInc:
        push ebx
        mov ebx, [esp+08]
        mov eax, 1
        LOCK XADD [ebx], eax
        pop ebx
        inc eax
        ret

global InterlockedDec

InterlockedDec:
        push ebx
        mov ebx, [esp+08]
        mov eax, -1
        LOCK XADD [ebx], eax
        pop ebx
        dec eax
        ret

