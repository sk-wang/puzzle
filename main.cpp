#include <iostream>
typedef struct leaf{
    struct leaf *last_leaf;
    int status[4][4];
} node;
void arrayToNode(node leaf,int data[4][4]);
void getAgent(int data[4][4],int *x,int *y);
int main() {
    int origin[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{'A','B','C','L'}};
    int target[4][4]={{0,0,0,0},{0,'A',0,0},{0,'B',0,0},{0,'C',0,0}};
    node originNode;
    arrayToNode(originNode,origin);
    node now_leafs[1000];
    now_leafs[0] = originNode;
    int deep = 1,locat = 0,lastLocat = 0;
    while(deep<=10) {
        lastLocat = locat;
        i = locat;
        while(){

        }


    }
    return 0;
}
void arrayToNode(node leaf,int data[4][4]){
    for(int i=0;i<4;++i){
        for (int j = 0; j < 4; ++j) {
            leaf.status[i][j] = data[i][j];
        }
    }
}
void getAgent