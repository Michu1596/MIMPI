#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "../mimpi.h"
#include "mimpi_err.h"

// #include <stdio.h>
// #include <unistd.h>

char data[21372137];

int main(int argc, char **argv)
{
    //printf("Przed mimpi\n");
    MIMPI_Init(false);
    //printf("W mimpi\n");
    int const world_rank = MIMPI_World_rank();

    memset(data, world_rank == 0 ? 42 : 7, sizeof(data));

    int const tag = 17;

    if (world_rank == 0) {
        //printf("Przed Send\n");
        // sleep(1);
        ASSERT_MIMPI_OK(MIMPI_Send(data, sizeof(data), 1, tag));
        //printf("Po send\n");
        for (int i = 0; i < sizeof(data); i += 789) {
            assert(data[789] == 42);
        }
    }
    else if (world_rank == 1)
    {
        //printf("Przed recv\n");
        // sleep(1);
        ASSERT_MIMPI_OK(MIMPI_Recv(data, sizeof(data), 0, tag));
        //printf("po recv\n");
        for (int i = 0; i < sizeof(data); i += 789) {
            assert(data[789] == 42);
        }
    }

    MIMPI_Finalize();
    return 0;
}
