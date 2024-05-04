// MAIN --------------------------------------------------------------------- //
// argv[0] -> program name
// argv[1] -> array dimension
// argv[2] -> number of processes
int main(int argc, char *argv[])
{
    // Check arguments
    if(argc != 3)
    {
        printf("Syntax wrong. Usage: $ ./vector_stat_proc <vector dimension> <number threads>");
        return -1;
    }
