#include <stdio.h>
#include <stddef.h>

#include "cudd.h"
#include <mpi.h>

int main(int argc, char *argv[]) {
    char filename[30];
    DdManager *gbm; /* Global BDD manager. */
    gbm = Cudd_Init(0, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, 0); /* Initialize a new BDD manager. */
    DdNode *bdd, *x1, *x2;
    x1 = Cudd_bddNewVar(gbm); /*Create a new BDD variable x1*/
    x2 = Cudd_bddNewVar(gbm); /*Create a new BDD variable x2*/
    bdd = Cudd_bddXor(gbm, x1, x2); /*Perform XOR Boolean operation*/
    Cudd_Ref(bdd);          /*Update the reference count for the node just created.*/
    bdd = Cudd_BddToAdd(gbm, bdd); /*Convert BDD to ADD for display purpose*/
//    print_dd (gbm, bdd, 2,4);   /*Print the dd to standard output*/
//    sprintf(filename, "./bdd/graph.dot"); /*Write .dot filename to a string*/
//    write_dd(gbm, bdd, filename);  /*Write the resulting cascade dd to a file*/
    Cudd_Quit(gbm);
    printf("BDD Execution finished!\n");

//  ----------------------------------------
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d out of %d processors\n",
           processor_name, world_rank, world_size);

    // Finalize the MPI environment. No more MPI calls can be made after this
    MPI_Finalize();


    return 0;
}
