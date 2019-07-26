# .bashrc

# Source global definitions
if [ -f /etc/bash.bashrc ]; then
	. /etc/bash.bashrc
fi

# Set the prompt to include usercode, host, directory
PS1="[\[\033[32m\]\w]\[\033[0m\]\n\[\033[1;36m\]JonathanEdwards\[\033[1;33m\]-> \[\033[0m\]"

# User specific aliases and functions
