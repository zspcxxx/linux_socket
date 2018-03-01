#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "error_handing.h"
#include "get_num.h"


int 
main(int argc, char *argv[])
{
    int fd, openFlags;
    //mode_t filePerms;
    
    ssize_t read_count;
    
    long mac_ath0_a, mac_ath0_b, mac_ath0_c, mac_ath0_d, mac_ath0_e, mac_ath0_f;
    long mac_eth0_a, mac_eth0_b, mac_eth0_c, mac_eth0_d, mac_eth0_e, mac_eth0_f;
    long mac_eth1_a, mac_eth1_b, mac_eth1_c, mac_eth1_d, mac_eth1_e, mac_eth1_f;

    char *mac_buf_a, *mac_buf_b, *mac_buf_c, *mac_buf_d, *mac_buf_e, *mac_buf_f;
    char *mac_ath0_w, *mac_eth0_w, *mac_eth1_w;
    char *mac_ath0_r, *mac_eth0_r, *mac_eth1_r;
			
	long mac_ath0, mac_eth0, mac_eth1;
	
    if (argc != 3 || strcmp(argv[1], "--help") == 0) {
		usageErr("%s art-file xx:xx:xx:xx:xx:xx --write mac\n", argv[0]);
        usageErr("%s art-file checkmac --check mac\n", argv[0]);
	}
        
    if (strcmp(argv[2], "checkmac") == 0) {
		
		//open written art file
		openFlags = O_RDONLY;
		fd = open(argv[1], openFlags);
		if (fd == -1)
			errExit("opening file %s", argv[1]);
			
		mac_ath0_r = malloc(6);
		mac_eth0_r = malloc(6);
		mac_eth1_r = malloc(6);
		
		if (lseek(fd, 0, SEEK_SET) == -1)
			errExit("lseek");	
		read_count = read(fd, mac_eth0_r, 6);
		if (read_count == -1)
			errExit("read");
			
		if (lseek(fd, 6, SEEK_SET) == -1)
			errExit("lseek");	
		read_count = read(fd, mac_eth1_r, 6);
		if (read_count == -1)
			errExit("read");
			
		if (lseek(fd, 4098, SEEK_SET) == -1)
			errExit("lseek");	
		read_count = read(fd, mac_ath0_r, 6);
		if (read_count == -1)
			errExit("read");
			
		printf("ath0: %x:", mac_ath0_r[0]);
		printf("%x:", mac_ath0_r[1]);
		printf("%x:", mac_ath0_r[2]);
		printf("%x:", mac_ath0_r[3]);
		printf("%x:", mac_ath0_r[4]);
		printf("%x\n", mac_ath0_r[5]);
		
		printf("eth0: %x:", mac_eth0_r[0]);
		printf("%x:", mac_eth0_r[1]);
		printf("%x:", mac_eth0_r[2]);
		printf("%x:", mac_eth0_r[3]);
		printf("%x:", mac_eth0_r[4]);
		printf("%x\n", mac_eth0_r[5]);
		
		printf("eth1: %x:", mac_eth1_r[0]);
		printf("%x:", mac_eth1_r[1]);
		printf("%x:", mac_eth1_r[2]);
		printf("%x:", mac_eth1_r[3]);
		printf("%x:", mac_eth1_r[4]);
		printf("%x\n", mac_eth1_r[5]);
			
		free(mac_ath0_r);
		free(mac_eth0_r);
		free(mac_eth1_r);	
	}
    else {   
		
		mac_buf_a = malloc(2);
		mac_buf_b = malloc(2);
		mac_buf_c = malloc(2);
		mac_buf_d = malloc(2);
		mac_buf_e = malloc(2);
		mac_buf_f = malloc(2);
		
		mac_ath0_w = malloc(6);
		mac_eth0_w = malloc(6);
		mac_eth1_w = malloc(6);

		mac_buf_a[0] = argv[2][0];
		mac_buf_a[1] = argv[2][1];
		
		mac_buf_b[0] = argv[2][3];
		mac_buf_b[1] = argv[2][4];
		
		mac_buf_c[0] = argv[2][6];
		mac_buf_c[1] = argv[2][7];
		
		mac_buf_d[0] = argv[2][9];
		mac_buf_d[1] = argv[2][10];
		
		mac_buf_e[0] = argv[2][12];
		mac_buf_e[1] = argv[2][13];
		
		mac_buf_f[0] = argv[2][15];
		mac_buf_f[1] = argv[2][16];
		
		//ath0
		mac_ath0_a = getLong(mac_buf_a, GN_BASE_16, argv[2]);
		mac_ath0_b = getLong(mac_buf_b, GN_BASE_16, argv[2]);
		mac_ath0_c = getLong(mac_buf_c, GN_BASE_16, argv[2]);
		mac_ath0_d = getLong(mac_buf_d, GN_BASE_16, argv[2]);
		mac_ath0_e = getLong(mac_buf_e, GN_BASE_16, argv[2]);
		mac_ath0_f = getLong(mac_buf_f, GN_BASE_16, argv[2]);
		
		mac_ath0 = (mac_ath0_d << 16) + (mac_ath0_e << 8) + mac_ath0_f;
		
		mac_eth0 = mac_ath0 + 1u;
		mac_eth1 = mac_ath0 + 2u;
		
		mac_ath0_w[0] = (char)mac_ath0_a;
		mac_ath0_w[1] = (char)mac_ath0_b;
		mac_ath0_w[2] = (char)mac_ath0_c;
		mac_ath0_w[3] = (char)mac_ath0_d;
		mac_ath0_w[4] = (char)mac_ath0_e;
		mac_ath0_w[5] = (char)mac_ath0_f;
		
		//eth0
		mac_eth0_a = mac_ath0_a;
		mac_eth0_b = mac_ath0_b;
		mac_eth0_c = mac_ath0_c;
		mac_eth0_d = mac_eth0 >> 16;
		mac_eth0_e = (mac_eth0 >> 8) - (mac_eth0_d << 8);
		mac_eth0_f = mac_eth0 - ((mac_eth0_d << 16) + (mac_eth0_e << 8));
		
		mac_eth0_w[0] = (char)mac_eth0_a;
		mac_eth0_w[1] = (char)mac_eth0_b;
		mac_eth0_w[2] = (char)mac_eth0_c;
		mac_eth0_w[3] = (char)mac_eth0_d;
		mac_eth0_w[4] = (char)mac_eth0_e;
		mac_eth0_w[5] = (char)mac_eth0_f;
		
		//eth1
		mac_eth1_a = mac_ath0_a;
		mac_eth1_b = mac_ath0_b;
		mac_eth1_c = mac_ath0_c;
		mac_eth1_d = mac_eth1 >> 16;
		mac_eth1_e = (mac_eth1 >> 8) - (mac_eth1_d << 8);
		mac_eth1_f = mac_eth1 - ((mac_eth1_d << 16) + (mac_eth1_e << 8));

		mac_eth1_w[0] = (char)mac_eth1_a;
		mac_eth1_w[1] = (char)mac_eth1_b;
		mac_eth1_w[2] = (char)mac_eth1_c;
		mac_eth1_w[3] = (char)mac_eth1_d;
		mac_eth1_w[4] = (char)mac_eth1_e;
		mac_eth1_w[5] = (char)mac_eth1_f;	
		//open art file
		openFlags = O_WRONLY;
		//filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

		
		fd = open(argv[1], openFlags);
		if (fd == -1)
			errExit("opening file %s", argv[1]);
			
		
		
		//write eth0
		if (lseek(fd, 0, SEEK_SET) == -1)
			errExit("lseek");
		if (write(fd, mac_eth0_w, 6) == -1)
			errExit("write");
			
		//write eth1
		if (lseek(fd, 6, SEEK_SET) == -1)
			errExit("lseek");
		if (write(fd, mac_eth1_w, 6) == -1)
			errExit("write");

		//write ath0
		if (lseek(fd, 4098, SEEK_SET) == -1)
			errExit("lseek");
		if (write(fd, mac_ath0_w, 6) == -1)
			errExit("write");

		
		free(mac_buf_a);
		free(mac_buf_b);
		free(mac_buf_c);
		free(mac_buf_d);
		free(mac_buf_e);
		free(mac_buf_f);
		
		free(mac_ath0_w);
		free(mac_eth0_w);
		free(mac_eth1_w);
	}
    
	exit(EXIT_SUCCESS);
}


