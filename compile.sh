if [ $1 = "gcc" ]; then
  gcc ptable.c -o ptable -lncurses
elif [ $1 = "clang" ]; then 
  clang ptable.c -o ptable -lncurses
fi