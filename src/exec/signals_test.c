// // Signal handling functions

// #include "minishell.h"

// void setup_heredoc_signals(void)
// {
//     signal(SIGINT, heredoc_sigint_handler);
//     signal(SIGQUIT, SIG_IGN);
// }

// void restore_signals(void)
// {
//     signal(SIGINT, SIG_DFL);
//     signal(SIGQUIT, SIG_DFL);
// }

// void heredoc_sigint_handler(int sig)
// {
//     (void)sig;
//     write(1, "\n", 1);
//     exit(1);
// }

// void cleanup_heredoc(t_command *cmd)
// {
//     if (cmd->fd_hrdoc > 2)
//     {
//         close(cmd->fd_hrdoc);
//         cmd->fd_hrdoc = -1;
//     }
// }