section .text

global GetCpuId

GetCpuId:
        push edx
		mov eax, 1
		cpuid
		mov eax, edx
        pop edx
        ret

