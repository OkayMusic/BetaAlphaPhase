#! /usr/bin/env bash

mate-terminal -x bash -c \
"echo 'monte-carlo simulation running'; build/a.out; read -n1"