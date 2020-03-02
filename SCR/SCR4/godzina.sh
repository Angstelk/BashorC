#/!/bin/bash
trap  'echo zabity' SIGHUP
trap 'echo "zabity"' SIGINT
trap 'echo "zabity"'  SIGQUIT
trap 'echo "zabity"'  SIGILL
trap 'echo "zabity"'  SIGTRAP
trap 'echo "zabity"'  SIGIOT
trap 'echo "zabity"'  SIGBUS
trap 'echo "zabity"'  SIGFPE
trap 'echo "zabity"'  SIGKILL
trap 'echo "zabity"'  SIGUSR1
trap 'echo "zabity"'  SIGSEGV
trap 'echo "zabity"'  SIGUSR2
trap 'echo "zabity"'  SIGSTOP
trap 'echo "zabity"'  SIGCONT
trap  'echo "zabity"' SIGCHLD
trap  'echo "zabity"' SIGTERM
trap  'echo "zabity"' SIGABRT
trap  'echo "zabity"' SIGPIPE

while true; do date +%H:%M:%S; sleep 2s; done

