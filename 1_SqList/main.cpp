/*
 * 动态分配的顺序表
 * */
#include <iostream>
using namespace std;

#define InitSize 10 //定义线性表的最大长度
typedef struct SqList{
    int* data; // Clion 查看动态数组 (int(*)[10])L.data
    int MaxSize;
    int length;
}DynamicList;

//初始化
void Init(DynamicList& L) {
    L.data = (int*)malloc(InitSize * sizeof (int));
    //判断是否分配成功
     if (!L.data) {//如果 !L->elem 为真（为空），执行下面代码
         cout << "线性表内存分配失败！退出程序。\n" << endl;
         exit(1);//函数异常退出，返回给操作系统1
     }
    L.length = 0;
    L.MaxSize = InitSize;
}

// 销毁
bool DestroyList(DynamicList &L){
    free(L.data);
    L.length = 0;
    L.MaxSize = 0;
    L.data = nullptr; // C++ 11
    if(!L.data)return true;
    return false;
}

// 增长
void IncreaseList(DynamicList& L, int n){
    int* p = L.data; // 存储原有数据
    L.data = (int*)malloc(sizeof(int)*(L.MaxSize + n)); // L.data重新分配内存
    for(int i = 0; i < L.length; i++){ // 迁移旧数据到新地址
        L.data[i] = p[i];
    }
    L.MaxSize += n;
    free(p);
}

//插入元素, 在表中第i个位置上插入x
bool Insert(DynamicList& L, int i, int x) {
    if(i < 1 || i > L.length + 1){
        cout << "位序有误" << endl;
        return false;
    }
    // 增加两倍的长度
    if(L.length >= L.MaxSize){
        IncreaseList(L, L.MaxSize);
    }

    for (int j = L.length; j >= i; --j) {
        L.data[j] = L.data[j-1];
    }
    L.data[i-1] = x;
    L.length++;
    return true;
}

// 删除
bool DeleteElemByOrder(DynamicList& L, int i, int& element){
    if(i < 1 || i > L.length + 1){
        cout << "位序有误" << endl;
        return false;
    }

    element = L.data[i-1]; // 要删除第i个元素，第i个元素(位序)对应的下标为 i - 1
    for (int j = i; j < L.length; ++j) {
        L.data[j-1] = L.data[j];
    }
    L.length--;
    return true;
}

// 查找
// 查找位序为i的元素
int FindElementByOrder(DynamicList& L, int i){
    return L.data[i-1];
}
// 查找值为value的元素的位序
int FindElementByValue(DynamicList& L, int value){
    for (int i = 0; i < L.length; ++i) {
        if(L.data[i] == value)return i+1;
    }
    cout << "未找到值为 " << value << "的元素" << endl;
    return -1; // 未找到
}

//遍历操作
void PrintList(DynamicList L) {
    cout << "L: ";
    for (int i = 0; i < L.length; i++) {
        cout << L.data[i] << " ";
    }
    cout << endl;
}

// 判空
bool IsEmpty(DynamicList& L){
    if(!L.length){
        return true;
    }
    return false;

}

bool Delete_same(DynamicList& L){
    if(L.length == 0) return false;
    int i,  // 第一个不相同的元素
         j; // 工作指针
    // 用后面不相同的元素L.dta[j]覆盖前面的L.data[i]
    for (i = 0, j = 1; j < L.length; ++j) {
        if(L.data[i] != L.data[j]){   // 查找下一个(L.data[j])与上个元素(L.data[i])不同的元素
            /*
             *  L.data[j] 与 L.data[i] 相同
             *  L.data[j+1] 与 L.data[i] 相同
             *  L.data[j+2] 与 L.data[i] 相同
             *  L.data[j+n] 与 L.data[i] 不同
             *  将 L.data[j+n] 前移到 L.data[i] 的下一个, 即 L.data[i+1] = L.data[j+n]
             * */
            i++;
            L.data[i] = L.data[j];// 找到后，将元素L.data[j]前移
        }
    }
    L.length = i + 1;
    return true;
}

int main() {
    DynamicList L;
    Init(L);

    // 判空
    if(IsEmpty(L)) {cout << "L是空表" << endl;}
    else{cout << "L非空" << endl;}
    cout << "表L长度为 " << L.length << ", 表L大小为 " << L.MaxSize << endl;

    // 插入元素
    cout << "-----------插入值1----------" << endl;
    if(Insert(L, 1, 1)){
        cout << "插入成功" << endl;
    }
    PrintList(L);
    cout << "表L长度为 " << L.length << ", 表L大小为 " << L.MaxSize << endl;

    // 循环插入9个元素
    cout << "----------插入9个元素--------------" << endl;
    for (int i = 1; i < 10; ++i) {
        Insert(L, i+1, i); // i是位序
    }
    PrintList(L); //L: 1 1 2 3 4 5 6 7 8 9
    // TODO ERROR 判断是否自动增长
    cout << "表L长度为 " << L.length << ", 表L大小为 " << L.MaxSize << endl;


    // 插入第 11 个元素，11 > MaxSize, 自动增长，不会报错
    cout << "--------------插入第11个元素 11, 会执行IncreaseList()使表大小自增------------" << endl;
    Insert(L, 11, 11);
    PrintList(L); //L: 1 1 2 3 4 5 6 7 8 9
    cout << "表L长度为 " << L.length << ", 表L大小为 " << L.MaxSize << endl;
    cout << "------------------------------------------------------------------" << endl;

    // 查找值5的位序
    cout << "值为5的位序是：" << FindElementByValue(L, 5) << endl;

    // 查找位序6的值
    cout << "位序为6的元素的值为：" << FindElementByOrder(L, 6) << endl;

    // 删除位序为6的元素
    int value;
    DeleteElemByOrder(L, 6, value);
    cout << "位序为6的为" << value << ", 已从表中删除." << endl;
    PrintList(L);


    cout << "---------Delete same--------" << endl;
    Delete_same(L);
    PrintList(L);

    // 销毁表
    cout << "--------------DestroyList L-------------" << endl;
    DestroyList(L);
    cout << "表是否为空: " << IsEmpty(L) << endl;
    cout << "表L长度为 " << L.length << ", 表L大小为 " << L.MaxSize << endl;

    return 0;
}

/*
    L是空表
    表L长度为 0, 表L大小为 10
    -----------插入值1----------
    插入成功
    L: 1
    表L长度为 1, 表L大小为 10
    ----------插入9个元素--------------
    L: 1 1 2 3 4 5 6 7 8 9
    表L长度为 10, 表L大小为 10
    --------------插入第11个元素 11, 会执行IncreaseList()使表大小自增------------
    L: 1 1 2 3 4 5 6 7 8 9 11
    表L长度为 11, 表L大小为 20
    ------------------------------------------------------------------
    值为5的位序是：6
    位序为6的元素的值为：5
    位序为6的为5, 已从表中删除.
    L: 1 1 2 3 4 6 7 8 9 11
    ---------Delete same--------
    L: 1 2 3 4 6 7 8 9 11
    --------------DestroyList L-------------
    表是否为空: 1
    表L长度为 0, 表L大小为 0
 
 * */
