//Parker Drouillard
//Visit - ParkerDrouillard.com
#include <stdio.h>


#include <unistd.h>

//Prototypes
int isFriend(int friendA, int friendB,int numFriendLines, int friendBuf[numFriendLines][2]);



///////////////////////////////
//////// MAIN FUNCTION
//////////////////////////////////////////////
int main(void){
	int numFriendLines, threshHold, toSearchFor, numLikeLines, highest;
	
	scanf("%d",&numFriendLines);
	int friendBuf[numFriendLines][2]; //Declares buffer for who's friends with who
	
	for(int i = 0; i < numFriendLines; i++){
		scanf("%d %d",&friendBuf[i][0],&friendBuf[i][1]);
	}
	
	scanf("%d",&numLikeLines);
	int likeBuf[numLikeLines][3];
	int postList[numLikeLines];
	for(int i = 0; i < numLikeLines; i++){
		postList[i] = -1; //Initialize the list to -1
		scanf("%d %d %d",&likeBuf[i][0],&likeBuf[i][1], &likeBuf[i][2]);
		if(i==0){
			highest = likeBuf[0][1];
		}else{
			if(highest < likeBuf[i][1]){
				highest=likeBuf[i][1];
			}
		}
	}
	scanf("%d %d", &toSearchFor, &threshHold);
	//printf("ThreshHold %d\n",threshHold);
	
	
	int likeDatabase[highest+1];
	for(int i = 0; i < highest+1; i++){
		likeDatabase[i] = 0;
	}
	for(int i = 0; i < numLikeLines; i++){
		//printf("Data into isFriend:\n ID: %d toSearch ID: %d numLines %d\n",likeBuf[i][0],toSearchFor,numFriendLines);
		if(isFriend(likeBuf[i][0],toSearchFor,numFriendLines, &friendBuf[0])){
			//printf("Incremented %d\n", likeBuf[i][1]);
			likeDatabase[likeBuf[i][1]]+=likeBuf[i][2];
		}
	}
	//printf("Highest: %d\n", highest);
	for(int i = 0; i < highest+1; i++){
		//printf("Value of post %d: %d\n",i, likeDatabase[i]);
		if(likeDatabase[i]>=threshHold){
			//write(1,likeDatabase[i],1);
			//write(1,i,sizeofint));
			
			printf("%d\n",i);
		}
		//printf("%d: %d\n",i, likeDatabase[i]);
	}


	//write(2,"ERROR\n",6);

	//return 1;
}

////////////////////////
//////////////FUNCTIONS
//////////////////////////////////////////////////////////////

int isFriend(int friendA, int friendB,int numFriendLines, int friendBuf[numFriendLines][2]){
	for(int i = 0; i < numFriendLines; i++){
		if((friendBuf[i][0] == friendA && friendBuf[i][1] == friendB)||(friendBuf[i][1] == friendA && friendBuf[i][0] == friendB)){
			//printf("TRUE\n");
			return 1;
		}
	}
	//printf("FALSE\n");
	return 0;
}