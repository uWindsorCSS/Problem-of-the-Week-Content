#include <iostream>

int main(void){


	int n;
	std::cin >> n;
	int atmos[n],cl=0,cr=0;
	float avgr=0,avgl=0;
	for(int i=0;i<n;i++){
	std::cin >> atmos[i];
	}
	if(n==1){
		
		std::cout << "0";
		return 0;
	}else if(n==0){
		//std::cin >> atmos[0];
		std::cout << "-1" << std::endl;;
		return 0;
	}
	//cout << n
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(i<j){
				avgr+=atmos[j];
				cr+=1;
			}else if(i>j){
				avgl+=atmos[j];
				cl+=1;
			}
		}
		if(cl==0){
			avgl=0;
			avgr=(avgr/cr)*0.85;
		}else if(cr==0){
			avgr=0;
			avgl=(avgl/cl)*0.85;
		}else{
		avgr=(avgr/cr)*0.85;
		avgl=(avgl/cl)*0.85;
		}
		if((atmos[i]<=avgr)&&(avgl==0)){
			std::cout << i << std::endl;;
			
			return 0;
		}else if((atmos[i]<=avgl)&&(avgr==0)){
			std::cout << i << std::endl;;
			
			return 0;
		}else if((atmos[i]<=avgr)&&(atmos[i]<=avgl)){
			std::cout << i << std::endl;;
			
			return 0;
		}
			
	avgr=0;
	avgl=0;
	cr=0;
	cl=0;		
	
	}
	std::cout << "-1";		
	return 0;
}