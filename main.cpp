#include <iostream>
typedef struct leaf{
    void *last_Node;
    int status[4][4];
} node;
void arrayToNode(node *leaf,int data[4][4]);
void arrayToArray(int origin[4][4],int data[4][4]);
void getAgent(int data[4][4],int &x,int &y);
int isReach(node leaf);
int target[4][4]={{0,0,0,0},{0,'A',0,0},{0,'B',0,0},{0,'C',0,0}};
int main() {
    int origin[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{'A','B','C','L'}};
    node originNode;
    node targetNode;
    arrayToNode(&originNode,origin);
    node now_leafs[1000];
    now_leafs[0] = originNode;
    int deep = 1,locat = 0,lastLocat = 0;
    int reach = 0;
    while(deep<=100) {
        //nodes为这一深度生成的节点数
        int nodes = 0,nowX,nowY;
        for(int i = lastLocat ; i <= locat ; ++i){
            //获得当前Agent的位置
            getAgent(now_leafs[i].status ,nowX,nowY);
            int tempStatus[4][4];
            //将父节点的状态值赋给一个临时数组
            arrayToArray(tempStatus,now_leafs[i].status);
            //向左上移动
            if(nowX - 1 >=0 && nowY - 1 >= 0){
                tempStatus[nowX][nowY] = tempStatus[nowX - 1][nowY - 1];
                tempStatus[nowX - 1][nowY - 1] = 'L';
                node tempNode;
                //将交换后的状态赋值予节点
                arrayToArray(tempNode.status,tempStatus);
                tempNode.last_Node = &now_leafs[i];
                if (isReach(tempNode)){
                    targetNode.last_Node =  tempNode.last_Node;
                    arrayToNode(&targetNode,tempNode.status);
                    reach = 1;
                    break;
                    //如果到达则跳出，并存储节点状态
                }else{
                    //生成的节点数加一
                    nodes ++;
                    now_leafs[locat + nodes] = tempNode;
                }
            }
            arrayToArray(tempStatus,now_leafs[i].status);
            //向左下移动
            if(nowX - 1 >=0 && nowY + 1 >= 0){
                tempStatus[nowX][nowY] = tempStatus[nowX - 1][nowY + 1];
                tempStatus[nowX - 1][nowY + 1] = 'L';
                node tempNode;
                //将交换后的状态赋值予节点
                arrayToArray(tempNode.status,tempStatus);
                tempNode.last_Node = &now_leafs[i];
                if (isReach(tempNode)){
                    targetNode.last_Node =  tempNode.last_Node;
                    arrayToNode(&targetNode,tempNode.status);
                    reach = 1;
                    break;
                    //如果到达则跳出，并存储节点状态
                }else{
                    //生成的节点数加一
                    nodes ++;
                    now_leafs[locat + nodes] = tempNode;
                }
            }
            arrayToArray(tempStatus,now_leafs[i].status);
            //向右上移动
            if(nowX + 1 >=0 && nowY - 1 >= 0){
                tempStatus[nowX][nowY] = tempStatus[nowX + 1][nowY - 1];
                tempStatus[nowX + 1][nowY - 1] = 'L';
                node tempNode;
                //将交换后的状态赋值予节点
                arrayToArray(tempNode.status,tempStatus);
                tempNode.last_Node = &now_leafs[i];
                if (isReach(tempNode)){
                    targetNode.last_Node =  tempNode.last_Node;
                    arrayToNode(&targetNode,tempNode.status);
                    reach = 1;
                    break;
                    //如果到达则跳出，并存储节点状态
                }else{
                    //生成的节点数加一
                    nodes ++;
                    now_leafs[locat + nodes] = tempNode;
                }
            }
            arrayToArray(tempStatus,now_leafs[i].status);
            //向右下移动
            if(nowX + 1 >=0 && nowY + 1 >= 0){
                tempStatus[nowX][nowY] = tempStatus[nowX + 1][nowY + 1];
                tempStatus[nowX + 1][nowY + 1] = 'L';
                node tempNode;
                //将交换后的状态赋值予节点
                arrayToArray(tempNode.status,tempStatus);
                tempNode.last_Node = &now_leafs[i];
                if (isReach(tempNode)){
                    targetNode.last_Node =  tempNode.last_Node;
                    arrayToNode(&targetNode,tempNode.status);
                    reach = 1;
                    break;
                    //如果到达则跳出，并存储节点状态
                }else{
                    //生成的节点数加一
                    nodes ++;
                    now_leafs[locat + nodes] = tempNode;
                }
            }
        }
        if(reach){
            for(int i = 0 ;i < 4;++i){
                for(int j = 0 ; j < 4 ;++j){
                    std::cout<<i<<' ';
                }
                std::cout<<std::endl;
            }
            break;
        }
        //将下一次起始点置于这一次的终点之后
        lastLocat = locat + 1;
        locat += nodes;
        deep++;
    }
    return 0;
}

//将二维数组状态赋值予节点
void arrayToNode(node *leaf,int data[4][4]){
    for(int i=0;i<4;++i){
        for (int j = 0; j < 4; ++j) {
            leaf->status[i][j] = data[i][j];
        }
    }
}
//将二维数组互相赋值
void arrayToArray(int origin[4][4],int data[4][4]){
    for(int i=0;i<4;++i){
        for (int j = 0; j < 4; ++j) {
            origin[i][j] = data[i][j];
        }
    }
}

//获得Agent的位置
void getAgent(int data[4][4],int &x,int &y){
    for(int i=0;i<4;++i){
        for (int j = 0; j < 4; ++j) {
            if(data[i][j] == 'L'){
                x = i;
                y = j;
                break;
            }
        }
    }
}

int isReach(node leaf){
    for(int i=0;i<4;++i){
        for (int j = 0; j < 4; ++j) {
            //忽略Agent的位置
            if(leaf.status[i][j] == 'L') leaf.status[i][j] = 0;
            if(leaf.status[i][j] == target[i][j]){
                if(i == 3 && j == 3){
                    return 1;
                }
            }else{
                return 0;
            }
        }
    }
}