#include<cstdlib>
#include "Container.cpp"

# define INTEGER 1
# define INT_ARRAY 2
# define INT_MATRIX 3

class ContainerOp{
    Container first;
    Container second;
    int op;
public:
    void setFirst(Container f){
        first = f;
    }
    Container getFirst(){
        return first;
    }
    void setSecond(Container s){
        second = s;
    }
    Container getSecond(){
        return second;
    }
    void setOp(int o){
        op = o;
    }
    int getOp(){
        return op;
    }
    Container performOp(){
        int mul = 1;
        if( op == 1 ) mul = -1;
        if( first.getStoredType()!=INTEGER and second.getStoredType()!=INTEGER ){
            cout<<"=============Invalid operations============"<<endl;
            return first;
        }
        if( first.getStoredType() == INTEGER ){
            if( second.getStoredType() == INTEGER ){
                int val1 = *(int*)first.getItem();
                int val2 = *(int*)second.getItem();
                Container res(val1+val2*mul);
                return res;
            } else if(second.getStoredType() == INT_ARRAY){
                int val1 = *(int*)first.getItem();
                int firstDim = second.getFirstDim();
                int *arr = new int[firstDim];
                arr = (int *)second.getItem();
                for(int i=0;i<firstDim;i++)
                    arr[i]+=val1*mul;
                Container res(arr,firstDim);
                return res;
            } else{
                int val1 = *(int*)first.getItem();
                int firstDim = second.getFirstDim();
                int secondDim = second.getSecondDim();
                int **mat = new int*[firstDim];
                mat = (int **)second.getItem();
                for(int i=0;i<firstDim;i++){
                    for(int j=0;j<secondDim;j++){
                        mat[i][j]+=(val1*mul);
                    }
                }
                Container res(mat,firstDim,secondDim);
                return res;
            }
        } else{
            if( first.getStoredType() == INTEGER ){
                int val1 = *(int*)first.getItem();
                int val2 = *(int*)second.getItem();
                Container res(val1+val2*mul);
                return res;
            } else if(first.getStoredType() == INT_ARRAY){
                int val1 = *(int*)second.getItem();
                int firstDim = first.getFirstDim();
                int *arr = new int[firstDim];
                arr = (int *)second.getItem();
                for(int i=0;i<firstDim;i++)
                    arr[i]+=val1*mul;
                Container res(arr,firstDim);
                return res;
            } else{
                int val1 = *(int*)second.getItem();
                int firstDim = first.getFirstDim();
                int secondDim = first.getSecondDim();
                int **mat = new int*[firstDim];
                mat = (int **)second.getItem();
                for(int i=0;i<firstDim;i++){
                    for(int j=0;j<secondDim;j++){
                        mat[i][j]+=val1*mul;
                    }
                }
                Container res(mat,firstDim,secondDim);
                return res;
            }
        }
    }

};

int main(){
    Container a(100);
    Container b(200);
    ContainerOp cop;
    cop.setFirst(a);
    cop.setSecond(b);
    cop.setOp(0);
    Container c = cop.performOp();
    c.print();
    cop.setOp(1);
    Container c2 = cop.performOp();
    c2.print();
    cop.setOp(0);

    int *arr = new int[3];
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    Container d(arr, 3);
    cop.setSecond(d);
    Container e = cop.performOp();
    e.print();

    int **mat = new int*[2];
    mat[0] = new int[3];
    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[0][2] = 3;
    mat[1] = new int[3];
    mat[1][0] = 4;
    mat[1][1] = 5;
    mat[1][2] = 6;

    Container f(mat, 2, 3);
    cop.setSecond(f);
    Container g = cop.performOp();
    g.print();
    cop.setFirst(d);
    Container h = cop.performOp();
    h.print();

}
