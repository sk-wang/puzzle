#include <iostream>
#include <math.h>

#define SCALE 8
typedef struct leaf{
    int index;
    void *last_Node;
    int status[SCALE][SCALE];
    int nextIndex[4];
    int depth;
    int wrong;
    int heurstic;
    int last_index;
} node;

void arrayToNode(node *leaf,int data[SCALE][SCALE]);
void arrayToArray(int origin[SCALE][SCALE],int data[SCALE][SCALE]);
void getAgent(int data[SCALE][SCALE],int &x,int &y);
void getPos(int data[SCALE][SCALE],int &x,int &y,char agent);
void AstarSearch(node *leaf);
int getHeurstic(node leaf , char agent);
int getHeursticTotal(node leaf);
int isReach(node leaf);
int target[SCALE][SCALE]={{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,'A',0,0,0,0,0,0},{0,'B',0,0,0,0,0,0},{0,'C',0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
int origin[SCALE][SCALE]={{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{'A','B','C','L',0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
int BFS();
int DFS();
int Astar();
int IDDFS();
int main(){
    //DFS strat;
    clock_t start = clock();
    printf("DFS Searching....\n");
    DFS();
    clock_t finish = clock();
    printf("DFS executing time is %fs\n",(double)(finish - start)/CLOCKS_PER_SEC);
    //Astar start
    printf("Astar Searching....\n");
    Astar();
    finish = clock();
    printf("Astar executing time is %fs\n",(double)(finish - start)/CLOCKS_PER_SEC);
    //IDDFS strat;
    start = clock();
    printf("IDDFS Searching....\n");
    IDDFS();
    finish = clock();
    printf("IDDFS executing time is %fs\n",(double)(finish - start)/CLOCKS_PER_SEC);
    start = clock();
    printf("BFS Searching....\n");
    BFS();
    finish = clock();
    printf("BFS executing time is %fs\n",(double)(finish - start)/CLOCKS_PER_SEC);
    start = clock();
    return 0;
}
int Astar(){
    node originNode;
    arrayToNode(&originNode,origin);
    originNode.depth = 0;
    originNode.wrong = 0;
    originNode.index = 0;
    AstarSearch(&originNode);
    return 0;
}
void AstarSearch(node *leaf){
    static int depth = 1;
    static int wholeNodes = 0;
    static int complexity = 0;
    static node nodes[100000];
    int nowX,nowY;
    int tempStatus[SCALE][SCALE];
    int maxDepth = 0;
    getAgent(leaf->status, nowX, nowY);
    if (isReach(*leaf)){
        printf("Astar result is\n");
        node *trace = new node[depth];
        trace[0] = *leaf;
        for(int k = 1;k < depth;++ k){
            trace[k] = nodes[trace[k - 1].last_index];
        }
        for (int k = depth - 2; k >= 0 ; --k) {
            std::cout<<"step"<<depth - k - 1<<":"<<std::endl;
            for(int x = 0 ;x < SCALE;++x){
                for(int j = 0 ; j < SCALE ;++j){
                    if(trace[k].status[x][j] == 0){
                        printf("%d ",trace[k].status[x][j]);
                    }else{
                        printf("%c ",trace[k].status[x][j]);
                    }
                }
                std::cout<<std::endl;
            }
        }
        std::cout<<"Time complexity is "<<complexity<<std::endl;
        std::cout<<wholeNodes<<" nodes have been expanded for Astar"<<std::endl;
        return;
    }else{
        complexity++;
        arrayToArray(tempStatus,leaf->status);
        if(nowX - 1 >= 0) {
            tempStatus[nowX][nowY] = tempStatus[nowX - 1][nowY];
            tempStatus[nowX - 1][nowY] = 'L';
            wholeNodes++;
            arrayToArray(nodes[wholeNodes].status,tempStatus);
            nodes[wholeNodes].last_index = leaf->index;
            nodes[wholeNodes].heurstic = depth + getHeursticTotal(nodes[wholeNodes]);
            nodes[wholeNodes].depth = depth;
            nodes[wholeNodes].wrong = 1;
            nodes[wholeNodes].index = wholeNodes;
        }
        arrayToArray(tempStatus,leaf->status);
        if(nowX + 1 <= SCALE - 1) {
            tempStatus[nowX][nowY] = tempStatus[nowX + 1][nowY];
            tempStatus[nowX + 1][nowY] = 'L';
            wholeNodes++;
            arrayToArray(nodes[wholeNodes].status,tempStatus);
            nodes[wholeNodes].last_index = leaf->index;
            nodes[wholeNodes].heurstic = depth + getHeursticTotal(nodes[wholeNodes]);
            nodes[wholeNodes].depth = depth;
            nodes[wholeNodes].wrong = 1;
            nodes[wholeNodes].index = wholeNodes;
        }
        arrayToArray(tempStatus,leaf->status);
        if(nowY - 1 >= 0) {
            tempStatus[nowX][nowY] = tempStatus[nowX][nowY - 1];
            tempStatus[nowX][nowY - 1] = 'L';
            wholeNodes++;
            arrayToArray(nodes[wholeNodes].status,tempStatus);
            nodes[wholeNodes].last_index = leaf->index;
            nodes[wholeNodes].heurstic = depth + getHeursticTotal(nodes[wholeNodes]);
            nodes[wholeNodes].depth = depth;
            nodes[wholeNodes].wrong = 1;
            nodes[wholeNodes].index = wholeNodes;
        }
        arrayToArray(tempStatus,leaf->status);
        if(nowY + 1 <= SCALE - 1) {
            tempStatus[nowX][nowY] = tempStatus[nowX][nowY + 1];
            tempStatus[nowX][nowY + 1] = 'L';
            wholeNodes++;
            arrayToArray(nodes[wholeNodes].status,tempStatus);
            nodes[wholeNodes].last_index = leaf->index;
            nodes[wholeNodes].heurstic = depth + getHeursticTotal(nodes[wholeNodes]);
            nodes[wholeNodes].depth = depth;
            nodes[wholeNodes].wrong = 1;
            nodes[wholeNodes].index = wholeNodes;
        }
        int min = -1000000;
        int minIndex = 0;
        for(int k = 0;k < wholeNodes ;k++){
            if(nodes[k].wrong == 1){
                if(min == -1000000){
                    min = nodes[k].heurstic;
                    minIndex = k;
                    maxDepth = nodes[k].depth;
                }else if(nodes[k].heurstic < min){
                    min = nodes[k].heurstic;
                    minIndex = k;
                    maxDepth = nodes[k].depth;
                }
            }
        }
        depth = maxDepth + 1;
        nodes[minIndex].wrong = 0;
        AstarSearch(&nodes[minIndex]);
    }
}
int IDDFS(){
    node originNode;
    node targetNode;
    arrayToNode(&originNode,origin);
    int reach = 0;
    int nowX,nowY,direction,depth = 1,nodes = 0;
    int wholeNodes = 0;
    int complexity = 0;
    int lastMove = 5;
    node now_leafs[10000];
    now_leafs[0] = originNode;
    //random seed
    srand(time(NULL));
    while(!reach) {
        //printf("searching\n");
        int i;
        int depthNodes = 0;
        for (i = 1; i <= depth ; ++i) {
            //获得上一节点位置
            getAgent(now_leafs[i - 1].status, nowX, nowY);
            int tempStatus[SCALE][SCALE];
            //将父节点的状态值赋给一个临时数组
            arrayToArray(tempStatus,now_leafs[i - 1].status);
            int wrong = 1;
            while(wrong){
                complexity++;
                wrong = 0;
                direction = rand() % 4 + 0;
                switch(direction){
                    case 0:
                        if(nowX - 1 >= 0 && lastMove != 1){
                            lastMove = 0;
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
                                depthNodes++ ;
                                wholeNodes ++;
                                now_leafs[i] = tempNode;
                            }
                        }else{
                            wrong = 1;
                        }
                        break;
                    case 1:
                        if(nowX + 1 <= SCALE - 1 && lastMove != 0){
                            lastMove = 1;
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
                                wholeNodes ++;
                                depthNodes ++;
                                now_leafs[i] = tempNode;
                            }
                        }else{
                            wrong = 1;
                        }
                        break;
                    case 2:
                        if(nowY - 1 >= 0 && lastMove != 3){
                            lastMove = 2;
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
                                depthNodes ++;
                                wholeNodes ++;
                                now_leafs[i] = tempNode;
                            }
                        }else{
                            wrong = 1;
                        }
                        break;
                    case 3:
                        if(nowY + 1 <= SCALE - 1 && lastMove != 2){
                            lastMove = 3;
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
                                depthNodes ++;
                                wholeNodes ++;
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
                printf("IDDFS result is\n");
                node *trace = new node[depth];
                trace[0] = targetNode;
                for(int k = 1;k < i;++ k){
                    trace[k] = *(node*)targetNode.last_Node;
                    targetNode = trace[k];
                }
                for (int k = i - 1; k >= 0 ; --k) {
                    std::cout<<"step"<<i - k<<":"<<std::endl;
                    for(int x = 0 ;x < SCALE;++x){
                        for(int j = 0 ; j < SCALE ;++j){
                            if(trace[k].status[x][j] == 0){
                                printf("%d ",trace[k].status[x][j]);
                            }else{
                                printf("%c ",trace[k].status[x][j]);
                            }
                        }
                        std::cout<<std::endl;
                    }
                }
                std::cout<<wholeNodes<<" nodes have been expanded for IDDFS but only "<<depthNodes<<" for one depth iterative search"<<std::endl;
                std::cout<<"Time complexity is "<<complexity<<std::endl;
                break;
            }
        }
        nodes++;
        if(nodes >= pow(4.0,depth - 1)){
            depth ++;
            std::cout<<depth<<std::endl;
            nodes = 0;
        }
    }
    return 0;
}
int DFS() {
    node originNode;
    node targetNode;
    arrayToNode(&originNode,origin);
    int reach = 0;
    int nowX,nowY,direction,depth = 1;
    int wholeNodes = 0;
    node now_leafs[10000];
    now_leafs[0] = originNode;
    int complexity = 0;
    //random seed
    srand(time(NULL));
    while(!reach) {
        //printf("searching\n");
        int i;
        int depthNodes = 0;
        for (i = 1; i < 1000 ; ++i) {
            //获得上一节点位置
            getAgent(now_leafs[i - 1].status, nowX, nowY);
            int tempStatus[SCALE][SCALE];
            //将父节点的状态值赋给一个临时数组
            arrayToArray(tempStatus,now_leafs[i - 1].status);
            int wrong = 1;
            while(wrong){
                complexity++;
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
                                wholeNodes++;
                                depthNodes ++;
                                now_leafs[i] = tempNode;
                            }
                        }else{
                            wrong = 1;
                        }
                        break;
                    case 1:
                        if(nowX + 1 <= SCALE - 1){
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
                                wholeNodes++;
                                depthNodes ++;
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
                                wholeNodes++;
                                depthNodes ++;
                                now_leafs[i] = tempNode;
                            }
                        }else{
                            wrong = 1;
                        }
                        break;
                    case 3:
                        if(nowY + 1 <= SCALE - 1){
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
                                wholeNodes++;
                                depthNodes ++;
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
                printf("DFS result is\n");
                node *trace = new node[depth];
                trace[0] = targetNode;
                for(int k = 1;k < i;++ k){
                    trace[k] = *(node*)targetNode.last_Node;
                    targetNode = trace[k];
                }
                for (int k = i - 1; k >= 0 ; --k) {
                    std::cout<<"step"<<i - k<<":"<<std::endl;
                    for(int x = 0 ;x < SCALE;++x){
                        for(int j = 0 ; j < SCALE ;++j){
                            if(trace[k].status[x][j] == 0){
                                printf("%d ",trace[k].status[x][j]);
                            }else{
                                printf("%c ",trace[k].status[x][j]);
                            }
                        }
                        std::cout<<std::endl;
                    }
                }
                std::cout<<wholeNodes<<" nodes have been expanded for DFS but max only "<<depthNodes<<" for one depth search"<<std::endl;;
                std::cout<<"Time complexity is "<<complexity<<std::endl;
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
    int complexity = 0;
    int depth = 1,locat = 0,lastLocat = 0;
    int reach = 0;
    int wholeNodes = 0;
    while(depth<=100) {
        //std::cout<<lastLocat<<','<<locat<<std::endl;
        //nodes为这一深度生成的节点数
        int nodes = 0,nowX,nowY;
        for(int i = lastLocat ; i <= locat ; ++i){
            complexity++;
            //获得当前Agent的位置
            getAgent(now_leafs[i].status ,nowX,nowY);
            int tempStatus[SCALE][SCALE];
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
                    wholeNodes ++;
                    now_leafs[locat + nodes] = tempNode;
                }
            }
            arrayToArray(tempStatus,now_leafs[i].status);
            //向右移动
            if(nowX + 1 <= SCALE -1 ){
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
                    wholeNodes ++;
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
                    wholeNodes ++;
                    now_leafs[locat + nodes] = tempNode;
                }
            }
            arrayToArray(tempStatus,now_leafs[i].status);
            //向下移动
            if(nowY + 1 <= SCALE - 1){
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
                    wholeNodes ++;
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
                for(int i = 0 ;i < SCALE;++i){
                    for(int j = 0 ; j < SCALE ;++j){
                        if(trace[k].status[i][j] == 0){
                            printf("%d ",trace[k].status[i][j]);
                        }else{
                            printf("%c ",trace[k].status[i][j]);
                        }
                    }
                    std::cout<<std::endl;
                }
            }
            std::cout<<wholeNodes<<" nodes have been expanded for BFS"<<std::endl;
            std::cout<<"Time complexity is "<<complexity<<std::endl;
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
void arrayToNode(node *leaf,int data[SCALE][SCALE]){
    for(int i=0;i<SCALE;++i){
        for (int j = 0; j < SCALE; ++j) {
            leaf->status[i][j] = data[i][j];
        }
    }
}
//将二维数组互相赋值
void arrayToArray(int origin[SCALE][SCALE],int data[SCALE][SCALE]){
    for(int i=0;i<SCALE;++i){
        for (int j = 0; j < SCALE; ++j) {
            origin[i][j] = data[i][j];
        }
    }
}

//获得Agent的位置
void getAgent(int data[SCALE][SCALE],int &x,int &y){
    for(int i=0;i<SCALE;++i){
        for (int j = 0; j < SCALE; ++j) {
            if(data[i][j] == 'L'){
                x = i;
                y = j;
                return;
            }
        }
    }
}

int isReach(node leaf){
    for(int i=0;i<SCALE;++i){
        for (int j = 0; j < SCALE; ++j) {
            //忽略Agent的位置
            if(leaf.status[i][j] == 'L') leaf.status[i][j] = 0;
            if(leaf.status[i][j] == target[i][j]){
                if(i == SCALE - 1 && j == SCALE - 1){
                    return 1;
                }
            }else{
                return 0;
            }
        }
    }
    return 0;
}

int getHeursticTotal(node leaf){
    int cost1 = 0,cost2 = 0,cost3 = 0;
    int nowX,nowY;
    int nowaX,nowaY;
    int nowbX,nowbY;
    int nowcX,nowcY;
    int targetaX,targetaY;
    int targetbX,targetbY;
    int targetcX,targetcY;
    int costTarget;
    int costDis;
    getAgent(leaf.status, nowX, nowY);
    getPos(leaf.status, nowaX, nowaY,'A');
    getPos(leaf.status, nowbX, nowbY,'B');
    getPos(leaf.status, nowcX, nowcY,'C');
    getPos(target, targetaX, targetaY,'A');
    getPos(target, targetbX, targetbY,'B');
    getPos(target, targetcX, targetcY,'C');
    cost1 = getHeurstic(leaf,'A');
    cost2 = getHeurstic(leaf,'B');
    cost3 = getHeurstic(leaf,'C');
    costDis = abs(nowX - nowaX) + abs(nowY - nowaY) + abs(nowX - nowbX) + abs(nowY - nowbY) + abs(nowX - nowcX) + abs(nowY - nowcY);
    costTarget = abs(targetaX - nowaX) + abs(targetaY - nowaY) + abs(targetbX - nowbX) + abs(targetbY - nowbY) + abs(targetcX - nowcX) + abs(targetcY - nowcY);
    return (cost1+cost2+cost3) + costTarget + costDis;
    //return costTarget;
}

int getHeurstic(node leaf , char agent){
    int nowaX,nowaY;
    int nowX,nowY;
    int lastaX,lastaY;
    int targetX,targetY;
    int cost = 0;
    getPos(leaf.status,nowaX,nowaY,agent);
    getPos(target,targetX,targetY,agent);
    getAgent(leaf.status,nowX,nowY);
    lastaX = nowaX;
    lastaY = nowaY;
    if(targetX != nowaX){
        targetX > nowaX ? nowaX++ : nowaX--;
        ((abs(nowY - lastaY) == 1 && nowaX == nowX)||(abs(nowX - lastaX) == 1 && nowaY == nowY)) ?  cost += (abs(nowX - nowaX) + abs(nowY - nowaY) + 3) : cost += (abs(nowX - nowaX) + abs(nowY - nowaY) + 1);
        nowX = lastaX;
        nowY = lastaY;
        /*std::cout<<"nowaXY"<<nowaX<<","<<nowaY<<std::endl;
         std::cout<<"lastaXY"<<lastaX<<","<<lastaY<<std::endl;
         std::cout<<"nowXY"<<nowX<<","<<nowY<<std::endl;
         std::cout<<"cost"<<cost<<std::endl;*/
        lastaX = nowaX;
        lastaY = nowaY;
        while(true){
            if(targetX > nowaX){
                nowaX++;
                ((abs(nowY - lastaY) == 1 && nowaX == nowX)||(abs(nowX - lastaX) == 1 && nowaY == nowY)) ?  cost += (abs(nowX - nowaX) + abs(nowY - nowaY) + 3) : cost += (abs(nowX - nowaX) + abs(nowY - nowaY) + 1);
                nowX = lastaX;
                nowY = lastaY;
                lastaX = nowaX;
                lastaY = nowaY;
            }else if(targetX < nowaX){
                nowaX--;
                ((abs(nowY - lastaY) == 1 && nowaX == nowX)||(abs(nowX - lastaX) == 1 && nowaY == nowY)) ?  cost += (abs(nowX - nowaX) + abs(nowY - nowaY) + 3) : cost += (abs(nowX - nowaX) + abs(nowY - nowaY) + 1);
                nowX = lastaX;
                nowY = lastaY;
                lastaX = nowaX;
                lastaY = nowaY;
            }else{
                break;
            }
        }
    }
    if (targetY != nowaY){
        targetY > nowaY ? nowaY++ : nowaY--;
        ((abs(nowY - lastaY) == 1 && nowaX == nowX)||(abs(nowX - lastaX) == 1 && nowaY == nowY)) ?  cost += (abs(nowX - nowaX) + abs(nowY - nowaY) + 3) : cost += (abs(nowX - nowaX) + abs(nowY - nowaY) + 1);
        nowX = lastaX;
        nowY = lastaY;
        lastaX = nowaX;
        lastaY = nowaY;
        /*std::cout<<"nowaXY"<<nowaX<<","<<nowaY<<std::endl;
         std::cout<<"lastaXY"<<lastaX<<","<<lastaY<<std::endl;
         std::cout<<"nowXY"<<nowX<<","<<nowY<<std::endl;
         std::cout<<"cost"<<cost<<std::endl;*/
        while(true){
            if(targetY > nowaY){
                ((abs(nowY - lastaY) == 1 && nowaX == nowX)||(abs(nowX - lastaX) == 1 && nowaY == nowY)) ?  cost += (abs(nowX - nowaX) + abs(nowY - nowaY) + 3) : cost += (abs(nowX - nowaX) + abs(nowY - nowaY) + 1);
                nowX = lastaX;
                nowY = lastaY;
                lastaX = nowaX;
                lastaY = nowaY;
                nowaY++;
            }else if(targetY < nowaY){
                ((abs(nowY - lastaY) == 1 && nowaX == nowX)||(abs(nowX - lastaX) == 1 && nowaY == nowY)) ?  cost += (abs(nowX - nowaX) + abs(nowY - nowaY) + 3) : cost += (abs(nowX - nowaX) + abs(nowY - nowaY) + 1);
                nowX = lastaX;
                nowY = lastaY;
                lastaX = nowaX;
                lastaY = nowaY;
                nowaY--;
            }else{
                break;
            }
        }

    }
    return cost;
};
void getPos(int data[SCALE][SCALE],int &x,int &y,char agent){
    for(int i=0;i<SCALE;++i){
        for (int j = 0; j < SCALE; ++j) {
            if(data[i][j] == agent){
                x = i;
                y = j;
                return;
            }
        }
    }
}