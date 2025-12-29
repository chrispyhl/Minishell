#!/bin/bash

# Farben für die Shell
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${BLUE}--- Minishell Executor Build & Test System ---${NC}"

# 1. Pfade definieren
LIBFT_DIR="../../libft"
LIBFT="$LIBFT_DIR/libft.a"
INCLUDES="-I ../../includes -I $LIBFT_DIR/src" #

# 2. Libft kompilieren (Wichtig für 42!)
echo -e "${YELLOW}Prüfe Libft in $LIBFT_DIR...${NC}"
if [ -d "$LIBFT_DIR" ]; then
    make -C $LIBFT_DIR > /dev/null
    if [ $? -ne 0 ]; then
        echo -e "${RED}❌ Fehler beim Kompilieren der Libft!${NC}"
        exit 1
    fi
else
    echo -e "${RED}❌ Libft-Verzeichnis nicht gefunden unter $LIBFT_DIR${NC}"
    exit 1
fi

# 3. Executor Quelldateien
SRC_FILES="0_executor.c 1_single_cmd.c 2_piping.c 3_redirections.c \
           externals/handle_externals.c \
           builtins/handle_builtins.c builtins/handle_more_builtins.c \
           utils/0_utils.c utils/env_utils.c utils/exec_utils.c utils/env_conversion.c \
           ../gc/ft_malloc.c ../gc/gc_utils.c ../gc/gc_libft.c ../gc/gc_itoa.c ../gc/gc_split.c \
           dummy_tester.c" #

FLAGS="-Wall -Wextra -Werror -g"
LIBS="-lreadline"

echo -e "${YELLOW}Kompiliere Executor-Tester...${NC}"
gcc $FLAGS $INCLUDES $SRC_FILES $LIBFT $LIBS -o tester

# 4. Ausführung
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✅ Kompilierung erfolgreich!${NC}"
    echo "---------------------------------------------"
    ./tester
    echo "---------------------------------------------"
else
    echo -e "${RED}❌ Kompilierung fehlgeschlagen!${NC}"
    exit 1
fi