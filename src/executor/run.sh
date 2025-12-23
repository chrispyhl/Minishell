#!/bin/bash

# 1. Libft kompilieren (sicher ist sicher)
make -C ../../libft > /dev/null
echo "Kompiliere folgende Dateien:"
ls *.c builtins/*.c utils/*.c
# Danach der cc Befehl...
# 2. Deinen Tester kompilieren
cc -g -Wall -Wextra -Werror \
    -I../../includes \
    -I../../libft/src \
    *.c \
    builtins/*.c \
    utils/*.c \
	externals/*.c \
    ../gc/*.c \
    -L../../libft -lft \
    -o tester
# ...

# 3. Wenn das Kompilieren geklappt hat, führ es aus
if [ $? -eq 0 ]; then
    echo "✅ Kompilierung erfolgreich! Starte Tester..."
    echo "---------------------------------------------"
    ./tester
fi