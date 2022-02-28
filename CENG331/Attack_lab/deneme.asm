
a.out:     file format elf64-x86-64


Disassembly of section .init:

0000000000000580 <_init>:
 580:	48 83 ec 08          	sub    $0x8,%rsp
 584:	48 8b 05 5d 0a 20 00 	mov    0x200a5d(%rip),%rax        # 200fe8 <__gmon_start__>
 58b:	48 85 c0             	test   %rax,%rax
 58e:	74 02                	je     592 <_init+0x12>
 590:	ff d0                	callq  *%rax
 592:	48 83 c4 08          	add    $0x8,%rsp
 596:	c3                   	retq   

Disassembly of section .plt:

00000000000005a0 <.plt>:
 5a0:	ff 35 0a 0a 20 00    	pushq  0x200a0a(%rip)        # 200fb0 <_GLOBAL_OFFSET_TABLE_+0x8>
 5a6:	ff 25 0c 0a 20 00    	jmpq   *0x200a0c(%rip)        # 200fb8 <_GLOBAL_OFFSET_TABLE_+0x10>
 5ac:	0f 1f 40 00          	nopl   0x0(%rax)

00000000000005b0 <__stack_chk_fail@plt>:
 5b0:	ff 25 0a 0a 20 00    	jmpq   *0x200a0a(%rip)        # 200fc0 <__stack_chk_fail@GLIBC_2.4>
 5b6:	68 00 00 00 00       	pushq  $0x0
 5bb:	e9 e0 ff ff ff       	jmpq   5a0 <.plt>

00000000000005c0 <printf@plt>:
 5c0:	ff 25 02 0a 20 00    	jmpq   *0x200a02(%rip)        # 200fc8 <printf@GLIBC_2.2.5>
 5c6:	68 01 00 00 00       	pushq  $0x1
 5cb:	e9 d0 ff ff ff       	jmpq   5a0 <.plt>

00000000000005d0 <gets@plt>:
 5d0:	ff 25 fa 09 20 00    	jmpq   *0x2009fa(%rip)        # 200fd0 <gets@GLIBC_2.2.5>
 5d6:	68 02 00 00 00       	pushq  $0x2
 5db:	e9 c0 ff ff ff       	jmpq   5a0 <.plt>

Disassembly of section .plt.got:

00000000000005e0 <__cxa_finalize@plt>:
 5e0:	ff 25 12 0a 20 00    	jmpq   *0x200a12(%rip)        # 200ff8 <__cxa_finalize@GLIBC_2.2.5>
 5e6:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

00000000000005f0 <_start>:
 5f0:	31 ed                	xor    %ebp,%ebp
 5f2:	49 89 d1             	mov    %rdx,%r9
 5f5:	5e                   	pop    %rsi
 5f6:	48 89 e2             	mov    %rsp,%rdx
 5f9:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
 5fd:	50                   	push   %rax
 5fe:	54                   	push   %rsp
 5ff:	4c 8d 05 2a 02 00 00 	lea    0x22a(%rip),%r8        # 830 <__libc_csu_fini>
 606:	48 8d 0d b3 01 00 00 	lea    0x1b3(%rip),%rcx        # 7c0 <__libc_csu_init>
 60d:	48 8d 3d 4b 01 00 00 	lea    0x14b(%rip),%rdi        # 75f <main>
 614:	ff 15 c6 09 20 00    	callq  *0x2009c6(%rip)        # 200fe0 <__libc_start_main@GLIBC_2.2.5>
 61a:	f4                   	hlt    
 61b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000000620 <deregister_tm_clones>:
 620:	48 8d 3d f1 09 20 00 	lea    0x2009f1(%rip),%rdi        # 201018 <__TMC_END__>
 627:	55                   	push   %rbp
 628:	48 8d 05 e9 09 20 00 	lea    0x2009e9(%rip),%rax        # 201018 <__TMC_END__>
 62f:	48 39 f8             	cmp    %rdi,%rax
 632:	48 89 e5             	mov    %rsp,%rbp
 635:	74 19                	je     650 <deregister_tm_clones+0x30>
 637:	48 8b 05 9a 09 20 00 	mov    0x20099a(%rip),%rax        # 200fd8 <_ITM_deregisterTMCloneTable>
 63e:	48 85 c0             	test   %rax,%rax
 641:	74 0d                	je     650 <deregister_tm_clones+0x30>
 643:	5d                   	pop    %rbp
 644:	ff e0                	jmpq   *%rax
 646:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 64d:	00 00 00 
 650:	5d                   	pop    %rbp
 651:	c3                   	retq   
 652:	0f 1f 40 00          	nopl   0x0(%rax)
 656:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 65d:	00 00 00 

0000000000000660 <register_tm_clones>:
 660:	48 8d 3d b1 09 20 00 	lea    0x2009b1(%rip),%rdi        # 201018 <__TMC_END__>
 667:	48 8d 35 aa 09 20 00 	lea    0x2009aa(%rip),%rsi        # 201018 <__TMC_END__>
 66e:	55                   	push   %rbp
 66f:	48 29 fe             	sub    %rdi,%rsi
 672:	48 89 e5             	mov    %rsp,%rbp
 675:	48 c1 fe 03          	sar    $0x3,%rsi
 679:	48 89 f0             	mov    %rsi,%rax
 67c:	48 c1 e8 3f          	shr    $0x3f,%rax
 680:	48 01 c6             	add    %rax,%rsi
 683:	48 d1 fe             	sar    %rsi
 686:	74 18                	je     6a0 <register_tm_clones+0x40>
 688:	48 8b 05 61 09 20 00 	mov    0x200961(%rip),%rax        # 200ff0 <_ITM_registerTMCloneTable>
 68f:	48 85 c0             	test   %rax,%rax
 692:	74 0c                	je     6a0 <register_tm_clones+0x40>
 694:	5d                   	pop    %rbp
 695:	ff e0                	jmpq   *%rax
 697:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
 69e:	00 00 
 6a0:	5d                   	pop    %rbp
 6a1:	c3                   	retq   
 6a2:	0f 1f 40 00          	nopl   0x0(%rax)
 6a6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 6ad:	00 00 00 

00000000000006b0 <__do_global_dtors_aux>:
 6b0:	80 3d 5d 09 20 00 00 	cmpb   $0x0,0x20095d(%rip)        # 201014 <_edata>
 6b7:	75 2f                	jne    6e8 <__do_global_dtors_aux+0x38>
 6b9:	48 83 3d 37 09 20 00 	cmpq   $0x0,0x200937(%rip)        # 200ff8 <__cxa_finalize@GLIBC_2.2.5>
 6c0:	00 
 6c1:	55                   	push   %rbp
 6c2:	48 89 e5             	mov    %rsp,%rbp
 6c5:	74 0c                	je     6d3 <__do_global_dtors_aux+0x23>
 6c7:	48 8b 3d 3a 09 20 00 	mov    0x20093a(%rip),%rdi        # 201008 <__dso_handle>
 6ce:	e8 0d ff ff ff       	callq  5e0 <__cxa_finalize@plt>
 6d3:	e8 48 ff ff ff       	callq  620 <deregister_tm_clones>
 6d8:	c6 05 35 09 20 00 01 	movb   $0x1,0x200935(%rip)        # 201014 <_edata>
 6df:	5d                   	pop    %rbp
 6e0:	c3                   	retq   
 6e1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
 6e8:	f3 c3                	repz retq 
 6ea:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000006f0 <frame_dummy>:
 6f0:	55                   	push   %rbp
 6f1:	48 89 e5             	mov    %rsp,%rbp
 6f4:	5d                   	pop    %rbp
 6f5:	e9 66 ff ff ff       	jmpq   660 <register_tm_clones>

00000000000006fa <hengirmen>:
 6fa:	55                   	push   %rbp
 6fb:	48 89 e5             	mov    %rsp,%rbp
 6fe:	89 7d fc             	mov    %edi,-0x4(%rbp)
 701:	83 7d fc 40          	cmpl   $0x40,-0x4(%rbp)
 705:	75 0c                	jne    713 <hengirmen+0x19>
 707:	c7 05 ff 08 20 00 02 	movl   $0x2,0x2008ff(%rip)        # 201010 <x>
 70e:	00 00 00 
 711:	eb 0a                	jmp    71d <hengirmen+0x23>
 713:	c7 05 f3 08 20 00 03 	movl   $0x3,0x2008f3(%rip)        # 201010 <x>
 71a:	00 00 00 
 71d:	90                   	nop
 71e:	5d                   	pop    %rbp
 71f:	c3                   	retq   

0000000000000720 <input>:
 720:	55                   	push   %rbp
 721:	48 89 e5             	mov    %rsp,%rbp
 724:	48 83 ec 10          	sub    $0x10,%rsp
 728:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
 72f:	00 00 
 731:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
 735:	31 c0                	xor    %eax,%eax
 737:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
 73b:	48 89 c7             	mov    %rax,%rdi
 73e:	b8 00 00 00 00       	mov    $0x0,%eax
 743:	e8 88 fe ff ff       	callq  5d0 <gets@plt>
 748:	90                   	nop
 749:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 74d:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
 754:	00 00 
 756:	74 05                	je     75d <input+0x3d>
 758:	e8 53 fe ff ff       	callq  5b0 <__stack_chk_fail@plt>
 75d:	c9                   	leaveq 
 75e:	c3                   	retq   

000000000000075f <main>:
 75f:	55                   	push   %rbp
 760:	48 89 e5             	mov    %rsp,%rbp
 763:	48 83 ec 20          	sub    $0x20,%rsp
 767:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
 76e:	00 00 
 770:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
 774:	31 c0                	xor    %eax,%eax
 776:	48 8d 45 e9          	lea    -0x17(%rbp),%rax
 77a:	48 89 c7             	mov    %rax,%rdi
 77d:	b8 00 00 00 00       	mov    $0x0,%eax
 782:	e8 49 fe ff ff       	callq  5d0 <gets@plt>
 787:	48 8d 45 e9          	lea    -0x17(%rbp),%rax
 78b:	48 89 c6             	mov    %rax,%rsi
 78e:	48 8d 3d af 00 00 00 	lea    0xaf(%rip),%rdi        # 844 <_IO_stdin_used+0x4>
 795:	b8 00 00 00 00       	mov    $0x0,%eax
 79a:	e8 21 fe ff ff       	callq  5c0 <printf@plt>
 79f:	b8 00 00 00 00       	mov    $0x0,%eax
 7a4:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
 7a8:	64 48 33 14 25 28 00 	xor    %fs:0x28,%rdx
 7af:	00 00 
 7b1:	74 05                	je     7b8 <main+0x59>
 7b3:	e8 f8 fd ff ff       	callq  5b0 <__stack_chk_fail@plt>
 7b8:	c9                   	leaveq 
 7b9:	c3                   	retq   
 7ba:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000007c0 <__libc_csu_init>:
 7c0:	41 57                	push   %r15
 7c2:	41 56                	push   %r14
 7c4:	49 89 d7             	mov    %rdx,%r15
 7c7:	41 55                	push   %r13
 7c9:	41 54                	push   %r12
 7cb:	4c 8d 25 d6 05 20 00 	lea    0x2005d6(%rip),%r12        # 200da8 <__frame_dummy_init_array_entry>
 7d2:	55                   	push   %rbp
 7d3:	48 8d 2d d6 05 20 00 	lea    0x2005d6(%rip),%rbp        # 200db0 <__init_array_end>
 7da:	53                   	push   %rbx
 7db:	41 89 fd             	mov    %edi,%r13d
 7de:	49 89 f6             	mov    %rsi,%r14
 7e1:	4c 29 e5             	sub    %r12,%rbp
 7e4:	48 83 ec 08          	sub    $0x8,%rsp
 7e8:	48 c1 fd 03          	sar    $0x3,%rbp
 7ec:	e8 8f fd ff ff       	callq  580 <_init>
 7f1:	48 85 ed             	test   %rbp,%rbp
 7f4:	74 20                	je     816 <__libc_csu_init+0x56>
 7f6:	31 db                	xor    %ebx,%ebx
 7f8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
 7ff:	00 
 800:	4c 89 fa             	mov    %r15,%rdx
 803:	4c 89 f6             	mov    %r14,%rsi
 806:	44 89 ef             	mov    %r13d,%edi
 809:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
 80d:	48 83 c3 01          	add    $0x1,%rbx
 811:	48 39 dd             	cmp    %rbx,%rbp
 814:	75 ea                	jne    800 <__libc_csu_init+0x40>
 816:	48 83 c4 08          	add    $0x8,%rsp
 81a:	5b                   	pop    %rbx
 81b:	5d                   	pop    %rbp
 81c:	41 5c                	pop    %r12
 81e:	41 5d                	pop    %r13
 820:	41 5e                	pop    %r14
 822:	41 5f                	pop    %r15
 824:	c3                   	retq   
 825:	90                   	nop
 826:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 82d:	00 00 00 

0000000000000830 <__libc_csu_fini>:
 830:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000000834 <_fini>:
 834:	48 83 ec 08          	sub    $0x8,%rsp
 838:	48 83 c4 08          	add    $0x8,%rsp
 83c:	c3                   	retq   
