#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void loose() {	
	printf("%s","YetiCTF{1t5_n0t_4_fl4g_4G4IN!!!}\n");
	return;
}


void win()
{
	char flag1[44] = "m4fssdtjlm3dfhjrdhhjh";
	char flag2[44] = "0f!fhi1pwn0kingwhello";
  	int counter = 0;
  	int iter=0;
  	
  	while (1) {
		unsigned int number = 0;
		printf("%s","Now, i get u realy flag !!! REALY !\n");
		printf("%s","Just a tell me integer number in the range of ten: ");
		scanf("%d", &number);
		if (number > 10)
			continue;

	  	printf("%s","YetiCTF{");
	  	if (!number) {
	  		int i=0;
	  		while (1 && !iter) {

	  			if (counter==0) {
	  				printf("%c%c", flag1[i], flag1[i+1]); i+=1;
	  			}
	  			
	  			if (counter==1 && i!=3) {
	  				i+=1; continue;
	  			}
	  			else if (counter==1 && i==3)
	  				printf("%c", flag1[i]);
	  			
	  			if (counter==2 && i!=6) {
	  				i+=1; continue;
	 			}
	 			else if (counter==2 && i==6)
	 				printf("%c", flag1[i]);
	 			
	 			if (counter==3 && i!=10) {
	 				i+=1; continue;
	 			}
	 			else if (counter==3 && i==10)
	 				printf("%c", flag1[i]);
	 			
	 			if (counter==4 && i!=15) {
	 				i+=1; continue;
	 			}
	 			else if (counter==4 && i==15) {
	 				printf("%c_",flag1[i]); iter+=1;
	 			}	
	  			if (iter) {
					i=0; counter=0; break;
				}
	  						
	  			counter +=1;
	  		}
	  		while (1 && iter==1) {
	  			if (counter==0) {
	  				printf("%c%c_", flag2[i], flag2[i+1]); i+=1;
	  			}
	  			
	  			if (counter==1 && i!=3) {
	  				i+=1; continue;
	  			}
	  			else if (counter==1 && i==3)
	  				printf("%c", flag2[i]);
	  			
	  			if (counter==2 && i!=6) {
	  				i+=1; continue;
	 			}
	 			else if (counter==2 && i==6)
	 				printf("%c", flag2[i]);
	 			
	 			if (counter==3 && i!=10) {
	 				i+=1; continue;
	 			}
	 			else if (counter==3 && i==10)
	 				printf("%c", flag2[i]);
	 			
	 			if (counter==4 && i!=15) {
	 				i+=1; continue;
	 			}
	 			else if (counter==4 && i==15) {
	 				printf("%c",flag2[i]);
	 			}
	  			
	  			if (counter==5 && i!=21) {
	  				i+=1; continue;
	  			}
	  			else if (counter==5 && i==21) {
	  				printf("%c%c", flag2[i], flag2[i+1]); i+=1;
	  				iter+=1;
	  			}	
	  			if (iter==2)
	  				break;	
	  						
	  			counter +=1;
	  		}
	  		break;
			
		}
  		else 
  			continue;
  	}
	printf("%s","}");
}

int main()
{
	printf("%s", "WARNING!!!\nBefore you start, I want to admit that there are a lot of tricks here.\nOnly the master of movement, jump and FLOW\nwill be able to identify all the traps!\nGOOD LUCK!\n\n");
	
	volatile int (*fp)();

	printf("%s", "Hello, what do you think about code flow?\nFlag should be somewhere here!\nFind him!\n");
	char buffer[64];

	printf("%s","Hm..\n");
	printf("%s", "May be its a flag or its a TRAP?\n");
	printf("%s", "YetiCTF{1f_u_g1v3_m3_th1$_fl4g_u_4r3_l00s3r_R34LY_D0nt_d0_1T!}\n");

	fp = 0;
	printf("%s", "Input D4ta:");
	gets(buffer);

	if(fp) {
		printf("Hint: Jumping to 0x%08x\n !!!", fp);
		fp();
	}
	else
		loose();

	return 0;
}
