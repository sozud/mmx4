find src \( -name "*.c" -o -name "*.h" \) -print0 | xargs -0 clang-format-15 -i
