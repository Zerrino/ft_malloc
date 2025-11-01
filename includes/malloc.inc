%define SYS_read			0
%define SYS_write			1
%define SYS_open			2
%define SYS_close			3
%define SYS_pread64			17
%define SYS_pwrite64		18
%define SYS_getdents64		217
%define SYS_exit			60
%define SYS_fork			57
%define SYS_fstat			5
%define SYS_mmap			9
%define SYS_munmap			11
%define SYS_msync			10
%define SYS_ftruncate		77
%define SYS_ioctl			16
%define SYS_gettimeofday	96
%define SYS_ptrace			101
%define SYS_getrandom		318
%define SYS_time			201

%define PROT_READ			1
%define PROT_WRITE			2
%define PROT_EXEC			4
%define MAP_PRIVATE			2
%define MAP_ANONYMOUS		32
%define MAP_FIXED			16
%define MAP_SHARED			1


%define PROT_READ			1
%define PROT_WRITE			2

%define TINY_SIZE			0x400
%define SMALL_SIZE			0x4000
%define TINY_NUMBER			0x80
%define SMALL_NUMBER		0x80

; define n		0x400
; define N		0x80
; define m		0x4000
; define M		0x80


struc t_zone
	.size resq 1
	.next resq 1
endstruc

struc t_block
	.size resq 1
	.next resq 1
endstruc

;typedef struct s_zone
;{
;	struct s_zone	*next;
;	uint64_t		size;
;}	t_zone;

;typedef struct s_block
;{
;	struct s_block	*next;
;	uint64_t		size;
;} t_block;
