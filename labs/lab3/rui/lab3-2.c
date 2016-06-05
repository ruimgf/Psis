#include <limits.h>
#include <stdio.h>

struct child{
	 unsigned int min;
	 unsigned int max;
	
};

int main(){
	unsigned int  m_7, m_19, m_7_19;
	int j;
	struct child filhos[3];
	filhos[0].min=0;
	filhos[0].max=UINT_MAX/3;
	filhos[1].min=UINT_MAX/3 + 1;
	filhos[1].max=(2*UINT_MAX)/3;
	filhos[2].min=(2*UINT_MAX)/3 + 1;
	filhos[2].max=UINT_MAX;
	for (j = 0; j < 3  ; j++)
	{
		m_7 = m_19 = m_7_19 = 0;
		if(fork()==0){
			for (unsigned int  i = filhos[j].min; i <  filhos[j].max; i++){
				if(i%7 == 0){ 
					m_7 ++;
				}
				if(i%19 == 0){ 
					m_19 ++;
				}
				if((i%7 == 0)	&& (i%19 == 0)){
					m_7_19++;
				}
			}	
			printf("m 7    %d\n", m_7);
			printf("m   19 %d\n", m_19);
			printf("m 7 19 %d\n", m_7_19);
			break;
		
		}
	}
	
}
