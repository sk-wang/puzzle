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
int origin[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{'A','B','C','L'}};
int BFS();
int DFS();
int main(){
    clock_t start = clock();
    printf("DFS Searching....\n");
    DFS();
    clock_t finish = clock();
    printf("DFS executing time is %ld \n",finish - start);
    start = clock();
    printf("BFS Searching....\n");
    BFS();
    finish = clock();
    printf("BFS executing time is %ld \n",finish - start);
    return 0;
}
int DFS() {
    node originNode;
    node targetNode;
    arrayToNode(&originNode,origin);
    int reach = 0;
    int nowX,nowY,direction,depth = 1;
    node now_leafs[20];
    now_leafs[0] = originNode;
    //random seed
    srand(time(NULL));
    while(!reach) {
        //printf("searching\n");
        int i;
        for (i = 1; i < 20 ; ++i) {
            //获得上一节点位置
            getAgent(now_leafs[i - 1].status, nowX, nowY);
            int tempStatus[4][4];
            //将父节点的状态值赋给一个临时数组
            arrayToArray(tempStatus,now_leafs[i - 1].status);
            int wrong = 1;
            while(wrong){
                wrong = 0;
                direction = rand() % 4 + 0;
                switch(direction){
                    case 0:
                        if(nowX - 1 >= 0){
                            tempStatus[nowX][nowY] = tempStatus[nowX - 1][nowY];
                            tempStatus[nowX - 1][nowY] = 'L';
                            node tempNode;
                            //将交换后的状态赋值予节点
                            arrayToArray(tempNode.status,tempStatus);
                            tempNode.last_Node = &now_leafs[i - 1];
                            if (isReach(tempNode)){
                                targetNode.last_Node =  tempNode.last_Node;
                                arrayToNode(&targetNode,tempNode.status);
                                reach = 1;
                                break;
                                //如果到达则跳出，并存储节点状态
                            }else{
                                now_leafs[i] = tempNode;
                            }
                        }else{
                            wrong = 1;
                        }
                        break;
                    case 1:
                        if(nowX + 1 <= 3){
                            tempStatus[nowX][nowY] = tempStatus[nowX + 1][nowY];
                            tempStatus[nowX + 1][nowY] = 'L';
                            node tempNode;
                            //将交换后的状态赋值予节点
                            arrayToArray(tempNode.status,tempStatus);
                            tempNode.last_Node = &now_leafs[i - 1];
                            if (isReach(tempNode)){
                                targetNode.last_Node =  tempNode.last_Node;
                                arrayToNode(&targetNode,tempNode.status);
                                reach = 1;
                                break;
                                //如果到达则跳出，并存储节点状态
                            }else{
                                now_leafs[i] = tempNode;
                            }
                        }else{
                            wrong = 1;
                        }
                        break;
                    case 2:
                        if(nowY - 1 >= 0){
                            tempStatus[nowX][nowY] = tempStatus[nowX][nowY - 1];
                            tempStatus[nowX][nowY - 1] = 'L';
                            node tempNode;
                            //将交换后的状态赋值予节点
                            arrayToArray(tempNode.status,tempStatus);
                            tempNode.last_Node = &now_leafs[i - 1];
                            if (isReach(tempNode)){
                                targetNode.last_Node =  tempNode.last_Node;
                                arrayToNode(&targetNode,tempNode.status);
                                reach = 1;
                                break;
                                //如果到达则跳出，并存储节点状态
                            }else{
                                now_leafs[i] = tempNode;
                            }
                        }else{
                            wrong = 1;
                        }
                        break;
                    case 3:
                        if(nowY + 1 <= 3){
                            tempStatus[nowX][nowY] = tempStatus[nowX][nowY + 1];
                            tempStatus[nowX][nowY + 1] = 'L';
                            node tempNode;
                            //将交换后的状态赋值予节点
                            arrayToArray(tempNode.status,tempStatus);
                            tempNode.last_Node = &now_leafs[i - 1];
                            if (isReach(tempNode)){
                                targetNode.last_Node =  tempNode.last_Node;
                                arrayToNode(&targetNode,tempNode.status);
                                reach = 1;
                                break;
                                //如果到达则跳出，并存储节点状态
                            }else{
                                now_leafs[i] = tempNode;
                            }
                        }else{
                            wrong = 1;
                        }
                        break;
                    default:
                        wrong = 1;
                        break;
                }
            }
            if(reach){
                printf("BFS result is\n");
                node *trace = new node[depth];
                trace[0] = targetNode;
                for(int k = 1;k < i;++ k){
                    trace[k] = *(node*)targetNode.last_Node;
                    targetNode = trace[k];
                }
                for (int k = i - 1; k >= 0 ; --k) {
                    std::cout<<"step"<<i - k<<":"<<std::endl;
                    for(int x = 0 ;x < 4;++x){
                        for(int j = 0 ; j < 4 ;++j){
                            if(trace[k].status[x][j] == 0){
                                printf("%d ",trace[k].status[x][j]);
                            }else{
                                printf("%c ",trace[k].status[x][j]);
                            }
                        }
                        std::cout<<std::endl;
                    }
                }
                break;
            }
        }
        depth++;
    }
    return 0;
}
int BFS() {
    //int origin[4][4]={{0,0,0,0},{0,'L',0,'A'},{0,'B',0,0},{0,'C',0,0}};
    node originNode;
    node targetNode;
    arrayToNode(&originNode,origin);
    node *now_leafs = new node[100000000000];
    now_leafs[0] = originNode;
    int depth = 1,locat = 0,lastLocat = 0;
    int reach = 0;
    while(depth<=100) {
        //std::cout<<lastLocat<<','<<locat<<std::endl;
        //nodes为这一深度生成的节点数
        int nodes = 0,nowX,nowY;
        for(int i = lastLocat ; i <= locat ; ++i){
            //获得当前Agent的位置
            getAgent(now_leafs[i].status ,nowX,nowY);
            int tempStatus[4][4];
            //将父节点的状态值赋给一个临时数组
            arrayToArray(tempStatus,now_leafs[i].status);
            //向左移动
            if(nowX - 1 >= 0){
                tempStatus[nowX][nowY] = tempStatus[nowX - 1][nowY];
                tempStatus[nowX - 1][nowY] = 'L';
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
            //向右移动
            if(nowX + 1 <= 3 ){
                tempStatus[nowX][nowY] = tempStatus[nowX + 1][nowY];
                tempStatus[nowX + 1][nowY] = 'L';
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
            //向上移动
            if(nowY - 1 >= 0){
                tempStatus[nowX][nowY] = tempStatus[nowX][nowY - 1];
                tempStatus[nowX][nowY - 1] = 'L';
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
            //向下移动
            if(nowY + 1 <= 3){
                tempStatus[nowX][nowY] = tempStatus[nowX][nowY + 1];
                tempStatus[nowX][nowY + 1] = 'L';
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
            printf("BFS result is\n");
            node *trace = new node[depth];
            trace[0] = targetNode;
            for(int k = 1;k < depth;++ k){
                trace[k] = *(node*)targetNode.last_Node;
                targetNode = trace[k];
            }
            for (int k = depth - 1; k >= 0 ; --k) {
                std::cout<<"step"<<depth - k<<":"<<std::endl;
                for(int i = 0 ;i < 4;++i){
                    for(int j = 0 ; j < 4 ;++j){
                        if(trace[k].status[i][j] == 0){
                            printf("%d ",trace[k].status[i][j]);
                        }else{
                            printf("%c ",trace[k].status[i][j]);
                        }
                    }
                    std::cout<<std::endl;
                }
            }
            break;
        }
        //将下一次起始点置于这一次的终点之后
        lastLocat = locat + 1;
        locat += nodes;
        depth++;
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
                return;
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
    return 0;
}