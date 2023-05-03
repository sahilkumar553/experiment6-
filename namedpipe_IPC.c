#include <stdio.h>   //for creating pipe
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    // Create a named pipe
    char *fifo_name = "/tmp/myfifo";
    mkfifo(fifo_name, 0666);

    return 0;
}
----------------------------------------------------------------------------------------------
  
 #include <stdio.h>            //process for writing
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    // Open the named pipe for writing
    char *fifo_name = "/tmp/myfifo";
    int fd = open(fifo_name, O_WRONLY);

    // Write to the named pipe
    write(fd, "Hello, world!", 14);

    // Close the named pipe
    close(fd);

    return 0;
}
-----------------------------------------------------------------------------------------------------
#include <stdio.h>                            //read process 
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    // Open the named pipe for reading
    char *fifo_name = "/tmp/myfifo";
    int fd = open(fifo_name, O_RDONLY);

    // Read from the named pipe
    char buf[1024];
    read(fd, buf, 1024);
    printf("Received message: %s\n", buf);

    // Close the named pipe
    close(fd);

    return 0;
}

--------------------------------------------------------------------------------------------
  
  
$ gcc writer.c -o writer  ////to execute
$ gcc reader.c -o reader
$ ./writer
$ ./reader
Received message: Hello, world!


  
