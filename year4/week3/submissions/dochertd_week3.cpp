#include <iostream>
#include <map>
//Dylan docherty POTW Week 3
int main(void){


	int n=0,f1,f2;//number of relationships, friend 1, friend 2
	while(n<1 || n>100){
	std::cin >> n;
	}
	//int frien[n][n];//the first var will be the first friend the second char will be the second friend if 1 they are friends else they are not
	std::map<int,std::map<int,int>> frien;
	for(int i=0;i<n;i++){
	std::cin >> f1;
	std::cin >> f2;
	frien[f1][f2]=1;
	frien[f2][f1]=1;
	}
	int m=0;//x is the user, y the post, z is like or not
	while(m<1 || m>100){
	std::cin >> m;
	}
	int x[m],y[m],z[m];
	std::fill_n(z, m, 0);
	int post[m][m];//holds which user liked or disliked each post
	for(int i=0;i<m;i++){
	std::cin >> x[i];//the user
	std::cin >> y[i];//the post id
	std::cin >> z[i];//the like per those ^, ^
	
	}

	int u,t;//u is the user we are helping, t is the post we are checking
	std::cin >> u;
	std::cin >> t;
	//float postLikes[m];
	std::map<int,int> map;//maps stuff to a thing
	for(int i=0;i<m;i++){
		map[y[i]]=0;
	}
	
	for(int i=0;i<m;i++){
		if(frien[u][x[i]]==1){
			map[y[i]]+=z[i];
		}
		
	}
	for(int i=0;i<m;i++){//goes through the map for each post id
		if(map[y[i]]>=t){
			std::cout << y[i] << '\n';//print the post id
			map[y[i]]=-1;
		}
	}
	return 0;
}
