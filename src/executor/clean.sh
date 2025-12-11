#!/bin/bash

# 1. Libft komplett bereinigen (fclean)
make -C ../../libft fclean

# 2. Tester Executable und Debug-Ordner löschen
rm -f tester
rm -rf tester.dSYM

echo "🧹 Alles sauber!"