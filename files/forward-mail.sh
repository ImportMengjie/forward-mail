#!/bin/sh /etc/rc.common

START=65

EXTRA_COMMANDS="status"
EXTRA_HELP="        status Print the status of the service"

start() {
  if (pgrep "^forward-mail" 1>/dev/null 2>&1 )
  then
    echo "forward-mail is running"
    return 0
  fi
  /usr/bin/forward-mail /etc/config/forward-mail 1>>logs.txt 2>>error.txt &
}

stop() {
  killall forward-mail 1>/dev/null 2>&1
}

status() {
	if (pgrep "^forward-mail" 1>/dev/null 2>&1 )
	then
		echo "forward-mail is running"
		return 0
	elf
		echo "forward-mail is not running"
		return 1
	fi
}