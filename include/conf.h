/* conf.h (GENERATED FILE; DO NOT EDIT) */

#ifndef _CONF_H_
#define _CONF_H_

#include <stddef.h>
#include <schedule.h>

/* Device table declarations */

/* Device table entry */
typedef struct dentry
{
	int     num;
	int     minor;
	char    *name;
	devcall (*init)(struct dentry *);
	devcall (*open)(struct dentry *, ...);
	devcall (*close)(struct dentry *);
	devcall (*read)(struct dentry *, void *, uint);
	devcall (*write)(struct dentry *, void *, uint);
	devcall (*seek)(struct dentry *, long);
	devcall (*getc)(struct dentry *);
	devcall (*putc)(struct dentry *, char);
	devcall (*control)(struct dentry *, int, long, long);
	void    *csr;
	void    (*intr)(void);
	uchar   irq;
} device;

extern const device devtab[]; /* one entry per device */

/* Device name definitions */

#define SERIAL0     0       /* type uart     */
#define SERIAL1     1       /* type uart     */
#define DEVNULL     2       /* type null     */
#define LOOP        3       /* type loopback */
#define TTYLOOP     4       /* type tty      */
#define CONSOLE     5       /* type tty      */

/* Control block sizes */

#define NLOOPBACK 1
#define NNULL 1
#define NUART 2
#define NTTY 2

#define DEVMAXNAME 20
#define NDEVS 6



/* Configuration and Size Constants */

#define LITTLE_ENDIAN 0x1234
#define BIG_ENDIAN    0x4321

#define BYTE_ORDER    LITTLE_ENDIAN

#define SCHEDULER SCH_PRIO		/* scheduling algorithm to use		*/
#define NTHREAD   100           /* number of user threads           */
#define NSEM      100           /* number of semaphores             */
#define NMAILBOX  15            /* number of mailboxes              */
#define RTCLOCK   TRUE          /* now have RTC support             */
#define NETEMU    FALSE         /* Network Emulator support         */
#define NVRAM     FALSE          /* now have nvram support           */
#define SB_BUS    FALSE         /* Silicon Backplane support        */
#define GPIO      TRUE          /* General-purpose I/O (leds)       */
#define IRQ_TIMER 4              /* timer0 IRQ is wired to VIC 4    */
//#define UHEAP_SIZE 8*1024*1024  /* size of memory for user threads  */
#define USE_TLB   FALSE         /* make use of TLB                  */
#define USE_TAR   TRUE          /* enable data archives             */
#define GPIO_BASE 0xB8000060    /* General-purpose I/O lines        */

// XXX: is an analogous constant defined already?
// This is used in uartInit.c
//#define MAIN_HEAD extern int programSwitch(void);
//#define MAIN_CALL programSwitch();

#endif /* _CONF_H_ */
