p 'echo "odebrano SIGHUP"' SIGHUP
trap 'echo "odebrano SIGINT"' SIGINT
trap 'echo "odebrano SIGQUIT"' SIGQUIT
trap 'echo "odebrano SIGILL"' SIGILL
trap 'echo "odebrano SIGTRAP"' SIGTRAP
trap 'echo "odebrano SIGIOT"' SIGIOT
trap 'echo "odebrano SIGBUS"' SIGBUS
trap 'echo "odebrano SIFPE"' SIGFPE
trap 'echo "odebrano SIGKILL"' SIGKILL
trap 'echo "odebrano SIGUSR1"' SIGUSR1
trap 'echo "odebrano SIGSEGV"' SIGSEGV
trap 'echo "odebrano SIGUSR2"' SIGUSR2
trap 'echo "odebrano SIGSTOP"' SIGSTOP
trap 'echo "odebrano SIGCONT"' SIGCONT
trap  'echo "odebrano SIGCHLD"' SIGCHLD
trap  'echo "odebrano SIGTERM"' SIGTERM
trap  'echo "odebrano SIGABRT"' SIGABRT
trap  'echo "odebrano SIGPIPE"' SIGPIPE

while true; do date +%H:%M:%S; sleep 2s; done

