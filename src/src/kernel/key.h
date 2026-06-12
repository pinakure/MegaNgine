#ifndef KEY_H
#define KEY_H

typedef struct sKey {

    int     status;

    void    (*init      )(void);
    void    (*poll      )(void);
    void    (*wait      )(int);
    bool    (*press     )(int);
    bool    (*noinput   )(void);
}Key;

extern Key key;
extern void Key_init(void);

#endif
