#ifndef __INC_METIN_II_TELLWAIT_H__
#define __INC_METIN_II_TELLWAIT_H__

#ifndef __WIN32__

extern void TELL_WAIT();

extern void WAIT_CHILD();
extern void TELL_CHILD(pid_t pid);

extern void WAIT_PARENT();
extern void TELL_PARENT(pid_t pid);

#endif

#endif
//martysama0134's a288e6779da68f768431f9975e780da3
