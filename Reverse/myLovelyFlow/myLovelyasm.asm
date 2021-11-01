
myLovelyFlow:     формат файла elf64-x86-64


Дизассемблирование раздела .init:

0000000000001000 <.init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    rsp,0x8
    1008:	48 8b 05 d9 2f 00 00 	mov    rax,QWORD PTR [rip+0x2fd9]        # 3fe8 <gets@plt+0x2f58>
    100f:	48 85 c0             	test   rax,rax
    1012:	74 02                	je     1016 <__cxa_finalize@plt-0x4a>
    1014:	ff d0                	call   rax
    1016:	48 83 c4 08          	add    rsp,0x8
    101a:	c3                   	ret    

Дизассемблирование раздела .plt:

0000000000001020 <.plt>:
    1020:	ff 35 8a 2f 00 00    	push   QWORD PTR [rip+0x2f8a]        # 3fb0 <gets@plt+0x2f20>
    1026:	f2 ff 25 8b 2f 00 00 	bnd jmp QWORD PTR [rip+0x2f8b]        # 3fb8 <gets@plt+0x2f28>
    102d:	0f 1f 00             	nop    DWORD PTR [rax]
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	push   0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmp 1020 <__cxa_finalize@plt-0x40>
    103f:	90                   	nop
    1040:	f3 0f 1e fa          	endbr64 
    1044:	68 01 00 00 00       	push   0x1
    1049:	f2 e9 d1 ff ff ff    	bnd jmp 1020 <__cxa_finalize@plt-0x40>
    104f:	90                   	nop
    1050:	f3 0f 1e fa          	endbr64 
    1054:	68 02 00 00 00       	push   0x2
    1059:	f2 e9 c1 ff ff ff    	bnd jmp 1020 <__cxa_finalize@plt-0x40>
    105f:	90                   	nop

Дизассемблирование раздела .plt.got:

0000000000001060 <__cxa_finalize@plt>:
    1060:	f3 0f 1e fa          	endbr64 
    1064:	f2 ff 25 8d 2f 00 00 	bnd jmp QWORD PTR [rip+0x2f8d]        # 3ff8 <gets@plt+0x2f68>
    106b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]

Дизассемблирование раздела .plt.sec:

0000000000001070 <puts@plt>:
    1070:	f3 0f 1e fa          	endbr64 
    1074:	f2 ff 25 45 2f 00 00 	bnd jmp QWORD PTR [rip+0x2f45]        # 3fc0 <gets@plt+0x2f30>
    107b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]

0000000000001080 <printf@plt>:
    1080:	f3 0f 1e fa          	endbr64 
    1084:	f2 ff 25 3d 2f 00 00 	bnd jmp QWORD PTR [rip+0x2f3d]        # 3fc8 <gets@plt+0x2f38>
    108b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]

0000000000001090 <gets@plt>:
    1090:	f3 0f 1e fa          	endbr64 
    1094:	f2 ff 25 35 2f 00 00 	bnd jmp QWORD PTR [rip+0x2f35]        # 3fd0 <gets@plt+0x2f40>
    109b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]

Дизассемблирование раздела .text:

00000000000010a0 <.text>:
    10a0:	f3 0f 1e fa          	endbr64 
    10a4:	31 ed                	xor    ebp,ebp
    10a6:	49 89 d1             	mov    r9,rdx
    10a9:	5e                   	pop    rsi
    10aa:	48 89 e2             	mov    rdx,rsp
    10ad:	48 83 e4 f0          	and    rsp,0xfffffffffffffff0
    10b1:	50                   	push   rax
    10b2:	54                   	push   rsp
    10b3:	4c 8d 05 c6 01 00 00 	lea    r8,[rip+0x1c6]        # 1280 <gets@plt+0x1f0>
    10ba:	48 8d 0d 4f 01 00 00 	lea    rcx,[rip+0x14f]        # 1210 <gets@plt+0x180>
    10c1:	48 8d 3d d8 00 00 00 	lea    rdi,[rip+0xd8]        # 11a0 <gets@plt+0x110>
    10c8:	ff 15 12 2f 00 00    	call   QWORD PTR [rip+0x2f12]        # 3fe0 <gets@plt+0x2f50>
    10ce:	f4                   	hlt    
    10cf:	90                   	nop
    10d0:	48 8d 3d 39 2f 00 00 	lea    rdi,[rip+0x2f39]        # 4010 <gets@plt+0x2f80>
    10d7:	48 8d 05 32 2f 00 00 	lea    rax,[rip+0x2f32]        # 4010 <gets@plt+0x2f80>
    10de:	48 39 f8             	cmp    rax,rdi
    10e1:	74 15                	je     10f8 <gets@plt+0x68>
    10e3:	48 8b 05 ee 2e 00 00 	mov    rax,QWORD PTR [rip+0x2eee]        # 3fd8 <gets@plt+0x2f48>
    10ea:	48 85 c0             	test   rax,rax
    10ed:	74 09                	je     10f8 <gets@plt+0x68>
    10ef:	ff e0                	jmp    rax
    10f1:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    10f8:	c3                   	ret    
    10f9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    1100:	48 8d 3d 09 2f 00 00 	lea    rdi,[rip+0x2f09]        # 4010 <gets@plt+0x2f80>
    1107:	48 8d 35 02 2f 00 00 	lea    rsi,[rip+0x2f02]        # 4010 <gets@plt+0x2f80>
    110e:	48 29 fe             	sub    rsi,rdi
    1111:	48 89 f0             	mov    rax,rsi
    1114:	48 c1 ee 3f          	shr    rsi,0x3f
    1118:	48 c1 f8 03          	sar    rax,0x3
    111c:	48 01 c6             	add    rsi,rax
    111f:	48 d1 fe             	sar    rsi,1
    1122:	74 14                	je     1138 <gets@plt+0xa8>
    1124:	48 8b 05 c5 2e 00 00 	mov    rax,QWORD PTR [rip+0x2ec5]        # 3ff0 <gets@plt+0x2f60>
    112b:	48 85 c0             	test   rax,rax
    112e:	74 08                	je     1138 <gets@plt+0xa8>
    1130:	ff e0                	jmp    rax
    1132:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    1138:	c3                   	ret    
    1139:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    1140:	f3 0f 1e fa          	endbr64 
    1144:	80 3d c5 2e 00 00 00 	cmp    BYTE PTR [rip+0x2ec5],0x0        # 4010 <gets@plt+0x2f80>
    114b:	75 2b                	jne    1178 <gets@plt+0xe8>
    114d:	55                   	push   rbp
    114e:	48 83 3d a2 2e 00 00 	cmp    QWORD PTR [rip+0x2ea2],0x0        # 3ff8 <gets@plt+0x2f68>
    1155:	00 
    1156:	48 89 e5             	mov    rbp,rsp
    1159:	74 0c                	je     1167 <gets@plt+0xd7>
    115b:	48 8b 3d a6 2e 00 00 	mov    rdi,QWORD PTR [rip+0x2ea6]        # 4008 <gets@plt+0x2f78>
    1162:	e8 f9 fe ff ff       	call   1060 <__cxa_finalize@plt>
    1167:	e8 64 ff ff ff       	call   10d0 <gets@plt+0x40>
    116c:	c6 05 9d 2e 00 00 01 	mov    BYTE PTR [rip+0x2e9d],0x1        # 4010 <gets@plt+0x2f80>
    1173:	5d                   	pop    rbp
    1174:	c3                   	ret    
    1175:	0f 1f 00             	nop    DWORD PTR [rax]
    1178:	c3                   	ret    
    1179:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    1180:	f3 0f 1e fa          	endbr64 
    1184:	e9 77 ff ff ff       	jmp    1100 <gets@plt+0x70>
    1189:	f3 0f 1e fa          	endbr64 
    118d:	55                   	push   rbp
    118e:	48 89 e5             	mov    rbp,rsp
    1191:	48 8d 3d 70 0e 00 00 	lea    rdi,[rip+0xe70]        # 2008 <gets@plt+0xf78>
    1198:	e8 d3 fe ff ff       	call   1070 <puts@plt>
    119d:	90                   	nop
    119e:	5d                   	pop    rbp
    119f:	c3                   	ret    
    11a0:	f3 0f 1e fa          	endbr64 
    11a4:	55                   	push   rbp
    11a5:	48 89 e5             	mov    rbp,rsp
    11a8:	48 83 ec 60          	sub    rsp,0x60
    11ac:	89 7d ac             	mov    DWORD PTR [rbp-0x54],edi
    11af:	48 89 75 a0          	mov    QWORD PTR [rbp-0x60],rsi
    11b3:	48 8d 3d 66 0e 00 00 	lea    rdi,[rip+0xe66]        # 2020 <gets@plt+0xf90>
    11ba:	e8 b1 fe ff ff       	call   1070 <puts@plt>
    11bf:	48 c7 45 f8 00 00 00 	mov    QWORD PTR [rbp-0x8],0x0
    11c6:	00 
    11c7:	48 8d 45 b0          	lea    rax,[rbp-0x50]
    11cb:	48 89 c7             	mov    rdi,rax
    11ce:	b8 00 00 00 00       	mov    eax,0x0
    11d3:	e8 b8 fe ff ff       	call   1090 <gets@plt>
    11d8:	48 83 7d f8 00       	cmp    QWORD PTR [rbp-0x8],0x0
    11dd:	74 23                	je     1202 <gets@plt+0x172>
    11df:	48 8b 45 f8          	mov    rax,QWORD PTR [rbp-0x8]
    11e3:	48 89 c6             	mov    rsi,rax
    11e6:	48 8d 3d 86 0e 00 00 	lea    rdi,[rip+0xe86]        # 2073 <gets@plt+0xfe3>
    11ed:	b8 00 00 00 00       	mov    eax,0x0
    11f2:	e8 89 fe ff ff       	call   1080 <printf@plt>
    11f7:	48 8b 55 f8          	mov    rdx,QWORD PTR [rbp-0x8]
    11fb:	b8 00 00 00 00       	mov    eax,0x0
    1200:	ff d2                	call   rdx
    1202:	b8 00 00 00 00       	mov    eax,0x0
    1207:	c9                   	leave  
    1208:	c3                   	ret    
    1209:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    1210:	f3 0f 1e fa          	endbr64 
    1214:	41 57                	push   r15
    1216:	4c 8d 3d 8b 2b 00 00 	lea    r15,[rip+0x2b8b]        # 3da8 <gets@plt+0x2d18>
    121d:	41 56                	push   r14
    121f:	49 89 d6             	mov    r14,rdx
    1222:	41 55                	push   r13
    1224:	49 89 f5             	mov    r13,rsi
    1227:	41 54                	push   r12
    1229:	41 89 fc             	mov    r12d,edi
    122c:	55                   	push   rbp
    122d:	48 8d 2d 7c 2b 00 00 	lea    rbp,[rip+0x2b7c]        # 3db0 <gets@plt+0x2d20>
    1234:	53                   	push   rbx
    1235:	4c 29 fd             	sub    rbp,r15
    1238:	48 83 ec 08          	sub    rsp,0x8
    123c:	e8 bf fd ff ff       	call   1000 <__cxa_finalize@plt-0x60>
    1241:	48 c1 fd 03          	sar    rbp,0x3
    1245:	74 1f                	je     1266 <gets@plt+0x1d6>
    1247:	31 db                	xor    ebx,ebx
    1249:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    1250:	4c 89 f2             	mov    rdx,r14
    1253:	4c 89 ee             	mov    rsi,r13
    1256:	44 89 e7             	mov    edi,r12d
    1259:	41 ff 14 df          	call   QWORD PTR [r15+rbx*8]
    125d:	48 83 c3 01          	add    rbx,0x1
    1261:	48 39 dd             	cmp    rbp,rbx
    1264:	75 ea                	jne    1250 <gets@plt+0x1c0>
    1266:	48 83 c4 08          	add    rsp,0x8
    126a:	5b                   	pop    rbx
    126b:	5d                   	pop    rbp
    126c:	41 5c                	pop    r12
    126e:	41 5d                	pop    r13
    1270:	41 5e                	pop    r14
    1272:	41 5f                	pop    r15
    1274:	c3                   	ret    
    1275:	66 66 2e 0f 1f 84 00 	data16 nop WORD PTR cs:[rax+rax*1+0x0]
    127c:	00 00 00 00 
    1280:	f3 0f 1e fa          	endbr64 
    1284:	c3                   	ret    

Дизассемблирование раздела .fini:

0000000000001288 <.fini>:
    1288:	f3 0f 1e fa          	endbr64 
    128c:	48 83 ec 08          	sub    rsp,0x8
    1290:	48 83 c4 08          	add    rsp,0x8
    1294:	c3                   	ret    
