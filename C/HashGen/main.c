#include <sodium.h>

// The central error handler.
typedef void (*errorFP)();

// Different types of errors (templates)
void execError(errorFP error);
void handleError();
void userError();
void sodiumError();

int main(int argc, char** argv)
{
    if (sodium_init() == -1)
    {
        execError(sodiumError);
    }

    if (argc < 2)
    {
        execError(userError);
    }

    FILE* file = fopen(argv[1], "rb");

    if (file == NULL)
    {
        execError(handleError);
    }

    unsigned char hash[crypto_hash_sha256_BYTES];

    crypto_hash_sha256_state state;

    crypto_hash_sha256_init(&state);

    unsigned char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), file)) > 0)
    {
        crypto_hash_sha256_update(&state, buffer, bytes_read);
    }

    crypto_hash_sha256_final(&state, hash);

    printf("Hash for %s -> ", argv[1]);

    for (size_t i = 0; i < crypto_hash_sha256_BYTES; i++)
    {
        printf("%x", hash[i]);
    }
    printf("\n");

    return 0;
}

void execError(errorFP error)
{
    printf("Error -> ");
    error();
    exit(0);
}

void handleError() { printf("Error getting file handle!\n"); }

void userError() { printf("Error in user input!\n"); }

void sodiumError() { printf("Error in init_sodium\n"); }
