#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int SINGLETON_OBJECT = 100;
int getSingletonObject();

typedef struct _Config {
    double PI;
    int N;
} Config;

static Config* CONFIG = NULL;
Config* getInstance();
void delete_Instance();

int main(void){
    printf("SINGLETON_OBJECT value: %d\n", getSingletonObject());

    Config* config1 = getInstance();
    printf("CONFIG1: address=%p, PI=%lf, N=%d\n", config1, config1->PI, config1->N);

    Config* config2 = getInstance();
    printf("CONFIG2: address=%p, PI=%lf, N=%d\n", config2, config2->PI, config2->N);

    if (config1 == config2) printf("Singleton OK: %p == %p\n", config1, config2);
    else printf("Singleton NG: %p != %p\n", config1, config2);

    config2->N = 3;

    printf("CONFIG1: address=%p, PI=%lf, N=%d\n", config1, config1->PI, config1->N);
    printf("CONFIG2: address=%p, PI=%lf, N=%d\n", config2, config2->PI, config2->N);

    delete_Instance();
    return 0;
}

int getSingletonObject() {
    return SINGLETON_OBJECT;
}

Config* getInstance() {
    if (CONFIG != NULL) return CONFIG;
    CONFIG = (Config*)malloc(sizeof(Config));
    CONFIG->PI = 3.14;
    CONFIG->N = 10;
    return CONFIG;
}

void delete_Instance() {
    if (CONFIG != NULL) {
        free(CONFIG);
        CONFIG = NULL;
    }
}
