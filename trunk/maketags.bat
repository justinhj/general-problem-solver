find . -regex ".*\(h$\|cpp$\)" > files.txt
c:/emacs/emacs-22.3/bin/etags.exe - < files.txt
