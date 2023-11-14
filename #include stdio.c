#include <stdio.h>
#include <pthread.h>

int barco1_x = 0, barco1_y = 0, barco2_x = 0, barco2_y = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* mover_barco(void* args) {
    int id = ((int)args);

    for (int i = 0; i < 8; ++i) {
        pthread_mutex_lock(&mutex);

        printf("Barco %d: Posición (%d, %d)\n", id, (id == 1 ? ++barco1_x : --barco2_x), ++barco1_y);

        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t id1, id2;
    int ret1, ret2;

    ret1 = pthread_create(&id1, NULL, mover_barco, &id1);
    ret2 = pthread_create(&id2, NULL, mover_barco, &id2);

    if (ret1 == 0 && ret2 == 0) {
        printf("Hilos para los barcos creados exitosamente.\n");
        pthread_join(id1, NULL);
        pthread_join(id2, NULL);
        printf("Los barcos han completado sus iteraciones.\n");
    } else {
        printf("No se pudo crear uno o ambos hilos para los barcos.\n");
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
