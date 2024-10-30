// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>

// typedef struct s_command {
//     char **args;      // Command arguments
//     pid_t pid;       // Child process ID
// } t_command;

// // Function to execute a command in a child process
// void create_child(t_command *cmd, int input_fd, int output_fd) {
//     cmd->pid = fork(); // Create a child process

//     if (cmd->pid == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE); // Error in fork
//     }

//     if (cmd->pid == 0) { // In child process
//         // Redirect input if there's a previous command
//         if (input_fd != -1) {
//             dup2(input_fd, STDIN_FILENO);
//             close(input_fd); // Close the input fd
//         }

//         // Redirect output if there's a next command
//         if (output_fd != -1) {
//             dup2(output_fd, STDOUT_FILENO);
//             close(output_fd); // Close the output fd
//         }

//         execvp(cmd->args[0], cmd->args); // Execute command
//         perror("execvp"); // If exec fails
//         exit(EXIT_FAILURE); // Exit child process on error
//     }
// }

// // Function to wait for all child processes
// void wait_children(t_command *cmds, int num_cmds) {
//     int status;
//     for (int i = 0; i < num_cmds; i++) {
//         waitpid(cmds[i].pid, &status, 0); // Wait for each child
//         if (WIFEXITED(status)) {
//             printf("Child %d exited with status %d\n", cmds[i].pid, WEXITSTATUS(status));
//         } else {
//             printf("Child %d terminated abnormally\n", cmds[i].pid);
//         }
//     }
// }

// // Main execution function
// void exec(t_command *cmds, int num_cmds) {
//     int pipe_fds[2];
//     int input_fd = -1; // Initialize input_fd to -1

//     for (int i = 0; i < num_cmds; i++) {
//         // Create a pipe for the next command, unless it's the last command
//         if (i < num_cmds - 1) {
//             if (pipe(pipe_fds) == -1) {
//                 perror("pipe");
//                 exit(EXIT_FAILURE);
//             }
//         } else {
//             pipe_fds[1] = -1; // No output pipe for the last command
//         }

//         // Create child for the current command
//         create_child(&cmds[i], input_fd, pipe_fds[1]);

//         // Close the write end of the current pipe in the parent
//         if (pipe_fds[1] != -1) {
//             close(pipe_fds[1]);
//         }

//         // Close the read end of the previous pipe
//         if (input_fd != -1) {
//             close(input_fd);
//         }

//         // The input_fd for the next command becomes the read end of the current pipe
//         input_fd = pipe_fds[0];
//     }

//     // Wait for all child processes to finish
//     wait_children(cmds, num_cmds);
// }

// int main() {
//     // Example usage
//     t_command cmds[2];
//     cmds[0].args = (char *[]){"ls", NULL}; // Command 1
//     cmds[1].args = (char *[]){"wc", NULL}; // Command 2

//     exec(cmds, 2); // Execute the commands

//     return (0);
// }
