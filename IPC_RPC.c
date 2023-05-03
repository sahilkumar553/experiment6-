//client
#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include "addition.h"

int *add_1_svc(input *inp, struct svc_req *rqstp) {
    static int result;
    result = inp->a + inp->b;
    return &result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <prog_name>\n", argv[0]);
        exit(1);
    }

    // Register the server with the portmapper
    if (!registerrpc(atoi(argv[1]), ADDITION_PROG, ADDITION_VERS, add_1_svc, 
        (xdrproc_t)xdr_input, (xdrproc_t)xdr_int)) {
        fprintf(stderr, "Unable to register server\n");
        exit(1);
    }

    // Start the RPC server
    svc_run();

    fprintf(stderr, "Error: svc_run returned\n");
    exit(1);
}
-----------------------------------------------------------------------
  //server
  #include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include "addition.h"

int main(int argc, char *argv[]) {
    CLIENT *client;
    input inp;
    int *result;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <host> <prog_num> <prog_vers>\n", argv[0]);
        exit(1);
    }

    // Create a client handle for the server
    client = clnt_create(argv[1], atoi(argv[2]), atoi(argv[3]), "tcp");

    if (client == NULL) {
        clnt_pcreateerror(argv[1]);
        exit(1);
    }

    // Set the input arguments for the remote procedure
    inp.a = 10;
    inp.b = 20;

    // Call the remote procedure
    result = add_1(&inp, client);

    if (result == NULL) {
        clnt_perror(client, argv[1]);
        exit(1);
    }

    // Print the result
    printf("Result: %d\n", *result);

    // Free the result buffer
    clnt_freeres(client, (xdrproc_t)xdr_int, (char *)result);

    // Destroy the client handle
    clnt_destroy(client);

    exit(0);
}
