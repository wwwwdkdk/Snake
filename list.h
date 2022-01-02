#ifndef LIST_H
#define LIST_H
#define MAXSIZE 100
struct coordinates {
    int x;
    int y;
};
struct Food {
    struct coordinates fcd;
    bool is_eat;
};
struct Snake {
    int len;
    struct coordinates scd[MAXSIZE];
    int ch;
};

#endif // LIST_H
