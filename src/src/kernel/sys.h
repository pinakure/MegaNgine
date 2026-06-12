#ifndef SYS_H
#define SYS_H

#define false 0
#define true  1

typedef struct sSys {
    void    (*init      )(void);
    void    (*update    )(void);
    void    (*updateGfx )(void);

}Sys;

extern Sys sys;
extern void Sys_init();

#endif
