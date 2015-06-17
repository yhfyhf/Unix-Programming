ls: ls1.c
	gcc ls1.c -o bin/ls1

ls: filesize.c
	gcc filesize.c -o bin/filesize

ls: fileinfo.c
	gcc fileinfo.c -o bin/fileinfo

ls: ls2.c
	gcc ls2.c -o bin/ls2
