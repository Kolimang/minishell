
///// test LINA pour REDIRECTIONS a rajouter au minishell.c
//////////////////////////////////////////// TEST HRDOC ////////////////////////////////////////
// Function to create a mock command
// t_command *create_mock_command(char **args, t_list *ls_redirs, int is_hrdoc) {
//     t_command *cmd = malloc(sizeof(t_command));
//     cmd->args = args;
//     cmd->ls_redirs = ls_redirs;
//     cmd->is_hrdoc = is_hrdoc;
//     cmd->io = malloc(sizeof(t_io_fd)); // Assuming you have an appropriate init function
//     init_io_fd(cmd->io); // Initialize the I/O structure
//     return cmd;
// }

// // Function to create a mock redirection
// t_redir *create_mock_redir(int type, char *value) {
//     t_redir *redir = malloc(sizeof(t_redir));
//     redir->type = type;
//     redir->value = value;
//     return redir;
// }

// // Function to create a linked list for redirections
// t_list *create_redir_list(t_redir *redir) {
//     t_list *list = malloc(sizeof(t_list));
//     list->content = redir;
//     list->next = NULL;
//     return list;
// }

// // Cleanup function
// void free_command(t_command *cmd) 
// {
// 	// free(cmd->args);
//     free(cmd->io);
//     free(cmd);
// }

// void free_redir(t_redir *redir) {
//     free(redir->value);
//     free(redir);
// }
// void test_pre_exec() {
//     // Prepare mock data
//     char *args[] = {NULL}; // Add command arguments here
//     t_redir *redir = create_mock_redir(HERE_DOC, "EOF");
//     t_list *redir_list = create_redir_list(redir);
    
//     t_command *cmd = create_mock_command(args, redir_list, 1);
//     t_list *cmds = malloc(sizeof(t_list));
//     cmds->content = cmd;
//     cmds->next = NULL;

//     t_env *local_env = NULL; // Mock local environment as needed
//     char **global_env = NULL; // Mock global environment

//     // Call pre_exec
//     pre_exec(cmds, local_env, global_env);

//     // Verify that fd_hrdoc is set correctly
//     if (cmd->io->fd_hrdoc == -1) {
//         printf("Test pre_exec failed: fd_hrdoc not set correctly.\n");
//     } else {
//         printf("Test pre_exec passed: fd_hrdoc is set.\n");
//     }
// 	    // Read the content from fd_hrdoc
//         char buffer[1024];
//         int bytes_read;

//         // fd_hrdoc is a pipe, so we can read from it
//         while ((bytes_read = read(cmd->io->fd_hrdoc, buffer, sizeof(buffer) - 1)) > 0) {
//             buffer[bytes_read] = '\0'; // Null-terminate the string
//             printf("Content from fd_hrdoc: %s\n", buffer);
//         }

//         if (bytes_read == -1) {
//             perror("Failed to read from fd_hrdoc");
//         }

//     // Clean up
//     free_command(cmd);
//     free(redir);
//     free(redir_list);
//     free(cmds);
// }


// int main() {
//     printf("Running tests...\n");
    
//     test_pre_exec();

//     return 0;
// }

//////////////////////////////////////////// TEST REDIR ////////////////////////////////////////

// #define STDIN_FILENO 0
// #define STDOUT_FILENO 1



// // Helper functions for testing
// t_list *create_list_node(void *content)
// {
//     t_list *node = malloc(sizeof(t_list));
//     node->content = content;
//     node->next = NULL;
//     return node;
// }

// t_command *create_command(char **args, t_io_fd *io)
// {
//     t_command *cmd = malloc(sizeof(t_command));
//     cmd->args = args;
//     cmd->io = io;
//     cmd->ls_redirs = NULL;
//     return cmd;
// }

// t_redir *create_redir(int type, const char *value)
// {
//     t_redir *redir = malloc(sizeof(t_redir));
//     redir->type = type;
//     redir->value = strdup(value);
//     return redir;
// }

// void exec(t_list *cmds, t_env *local_env, char **global_env)
// {
//     t_command *cmd;
//     (void)local_env;
//     (void)global_env;
//     while (cmds)
//     {
//         cmd = cmds->content;
// 		init_io_fd(cmd->io);
// 	    if (cmds->next == NULL && !(cmd->args[0]))
//         {
//             if (execute_redir(cmd, cmd->io) == -1)
//                 return ;
//         }
//         else
//         {
//             printf("Executing command: %s\n", cmd->args[0]);
//             if (execute_redir(cmd, cmd->io) == -1)
//             {
//                 printf("Redirection failed for command: %s\n", cmd->args[0]);
//                 return ;
//             }
//             for (int i = 0; cmd->args[i]; i++)
//                 printf("Arg %d: %s\n", i, cmd->args[i]);
//         }
//        reset_io(cmd);
//         cmds = cmds->next;
//     }
// }

// // Helper function for printing FD status
// void print_fd_status(const char *label, int fd) {
//     printf("%s: %d\n", label, fd);
// }

// // Helper function to print the content of a file
// void print_file_content(const char *filename) {
//     char buffer[1024];
//     int fd = open(filename, O_RDONLY);
//     if (fd != -1) {
//         ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
//         if (bytes_read > 0) {
//             buffer[bytes_read] = '\0';
//             printf("%s", buffer);
//         }
//         close(fd);
//     }
// }

// // Main function for testing
// int main() {
//     system("echo 'This is input file' > input.txt");
//     system("echo 'This is the first line' > output.txt");

//     // Test 1: Input redirection '<'
//     {
//         printf("\n--- Test 1: Input Redirection '<' ---\n");
//         char *args[] = {"cat", NULL};
//         t_io_fd io;
//         init_io_fd(&io);
//         t_command *cmd = create_command(args, &io);
//         cmd->ls_redirs = create_list_node(create_redir(INFILE, "input.txt"));

//         print_fd_status("Before redirection, STDIN", STDIN_FILENO);
//         execute_redir(cmd, cmd->io);
//         print_fd_status("After redirection, STDIN", cmd->io->fd_in);

//         printf("Command output:\n");
//         char buffer[1024];
//         ssize_t bytes_read = read(cmd->io->fd_in, buffer, sizeof(buffer) - 1);
//         if (bytes_read > 0) {
//             buffer[bytes_read] = '\0';
//             printf("%s", buffer);
//         }

//         reset_io(cmd);
//     }

//     // Test 2: Output redirection '>'
//     {
//         printf("\n--- Test 2: Output Redirection '>' ---\n");
//         char *args[] = {"echo", "Hello, World!", NULL};
//         t_io_fd io;
//         init_io_fd(&io);
//         t_command *cmd = create_command(args, &io);
//         cmd->ls_redirs = create_list_node(create_redir(OUTFILE, "new_output.txt"));

//         print_fd_status("Before redirection, STDOUT", STDOUT_FILENO);
//         execute_redir(cmd, cmd->io);
//         print_fd_status("After redirection, STDOUT", cmd->io->fd_out);

//         dprintf(cmd->io->fd_out, "Hello, World!\n");

//         reset_io(cmd);
        
//         printf("Content of new_output.txt:\n");
//         print_file_content("new_output.txt");
//     }
// 	// Test for here-document '<<'
//     {
//         printf("\n--- Test 3: Here-document '<<' ---\n");
//         char *args[] = {"cat", NULL};
//         t_io_fd io;
//         init_io_fd(&io);
//         t_command *cmd = create_command(args, &io);

//         // Simulate here-document by creating a temporary file
//         int temp_fd = open("temp_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
//         dprintf(temp_fd, "This is line 1 of heredoc\nThis is line 2 of heredoc\nEOF\n");
//         close(temp_fd);

//         io.fd_hrdoc = open("temp_heredoc", O_RDONLY);
//         cmd->ls_redirs = create_list_node(create_redir(HERE_DOC, "EOF"));

//         execute_redir(cmd, cmd->io);

//         printf("Content from heredoc:\n");
//         char buffer[1024];
//         ssize_t bytes_read = read(cmd->io->fd_in, buffer, sizeof(buffer) - 1);
//         if (bytes_read > 0) {
//             buffer[bytes_read] = '\0';
//             printf("%s", buffer);
//         }

//         reset_io(cmd);
//     }

//     // Test for append redirection '>>'
//     {
//         printf("\n--- Test 4: Append Redirection '>>' ---\n");
//         char *args[] = {"echo", "Append this line", NULL};
//         t_io_fd io;
//         init_io_fd(&io);
//         t_command *cmd = create_command(args, &io);
//         cmd->ls_redirs = create_list_node(create_redir(APPEND, "new_output.txt"));

//         execute_redir(cmd, cmd->io);

//         dprintf(cmd->io->fd_out, "Append this line\n");

//         reset_io(cmd);

//         printf("Content of ne_output.txt after appending:\n");
//         print_file_content("new_output.txt");
//     }
//     return 0;
// }
