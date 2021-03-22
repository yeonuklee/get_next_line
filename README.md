![2021-03-22 15 28 58](https://user-images.githubusercontent.com/52679439/112067266-02165180-8b25-11eb-8132-bc43fde80718.gif)
The ‘get_next_file.c’ returns one line at the time but the main function in the ‘main.c’ file is written to display all lines using a while loop until the end of file. 


# get_next_line
The goal of this project is to make you code a function that reads file from file descriptor and retruns *one line ending with a new line('/n')* without knowing the size beforehand. This project will not only allow you to add a very convenient function to your collection, but it will also allow you to learn a highly interesting new concept in C programming: static variables. You will also gain a deeper understanding of allocations, whether they happen on the stack memory or in the heap memory, the manipulation and the life cycle of a buffer, the unexpected complexity implied in the use of one or many static variables.

## Prototype 
int	get_next_line(int fd, char **line);

[get_next_line.en (dragged).pdf](https://github.com/yeonuklee/get_next_line/files/6067156/get_next_line.en.dragged.pdf)
[get_next_line.en (dragged).pdf](https://github.com/yeonuklee/get_next_line/files/6067157/get_next_line.en.dragged.pdf)
[get_next_line.en (dragged).pdf](https://github.com/yeonuklee/get_next_line/files/6067158/get_next_line.en.dragged.pdf)

