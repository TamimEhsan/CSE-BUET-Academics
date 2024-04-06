# include <cstdlib>
# include "Container.cpp"

class ContainerArray{
    // Do not add any additional member variable
    Container *arrayOfContainers;
    int allocatedSize;
public:
    ContainerArray(){
        allocatedSize = 0;
        arrayOfContainers = NULL;
    }

    // overload constructor so that it receives size as a parameter
    // assign size to the appropriate variable
    // allocate memory dynamically as required

    void setAllocatedSize(int sz){
        // if arrayOfContainers already has some entries, clear them (including freeing memory)
        // assign size (i.e. sz) to the appropriate variable
        // allocate memory dynamically as required
    }

    int getAllocatedSize(){
        return allocatedSize;
    }

    Container getItemAt(int index){
        if (index >= allocatedSize){
            cout << "Cannot get item, Exception: Container Array index out of bound";
            exit(0);
        }
        // return the appropriate item from the array (i.e. arrayOfContainers);
    }

    // write a function named setItemAt, which should receive a container and an index
    // if index is out of boundary (i.e. size allocated for the array), print the following line
    // cout << "Exception: Container Array index out of bound";
    // otherwise use the setItem and getItem methods of Container class (other methods too if needed)
    // observe the main function to understand how you should type cast the items returned from getItem
    // handle all the cases that may arise for what getItem method can possibly return

    ~ContainerArray(){
        // free allocated memory and reset appropriate variables (i.e. set such a value)
    }
};

int main(){
    // the following braces indicate scope of variables declared in them
    // at the end of a brace enclosed block, object destructors will be called
    {
        Container a;
        a.print();
        if (a.getItem() == NULL){
            cout << "No value is stored in the container" << endl;
        }
        else{
            cout << "Some value is stored in the container" << endl;
        }
    }

    {
        Container a(100);
        a.print();
        if (a.getItem() == NULL){
            cout << "No value is stored in the container" << endl;
        }
        else if (a.getStoredType() == INTEGER){
            int *val = (int *) a.getItem();
            cout << "The integer value retrieved from container object is: " << *val << endl;
        }
        else{
            cout << "Some value is stored in the container" << endl;
        }
    }

    {
        int *arr = new int[3];
        arr[0] = 10;
        arr[1] = 20;
        arr[2] = 30;
        Container a(arr, 3);
        a.print();
        if (a.getItem() == NULL){
            cout << "No value is stored in the container" << endl;
        }
        else if (a.getStoredType() == INT_ARRAY){
            arr = (int *)a.getItem();
            cout << "The integer array retrieved from container object is: " << endl;
            for (int i=0; i<3; i++){
                cout << arr[i] << " ";
            }
            cout << endl;
        }
        else{
            cout << "Some value is stored in the container" << endl;
        }
    }

    {
        int **mat = new int*[2];
        mat[0] = new int[3];
        mat[0][0] = 1;
        mat[0][1] = 2;
        mat[0][2] = 3;
        mat[1] = new int[3];
        mat[1][0] = 4;
        mat[1][1] = 5;
        mat[1][2] = 6;
        Container a(mat, 2, 3);
        a.print();
        if (a.getItem() == NULL){
            cout << "No value is stored in the container" << endl;
        }
        else if (a.getStoredType() == INT_MATRIX){
            mat = (int **)a.getItem();
            cout << "The integer matrix retrieved from container object is: " << endl;
            for (int i=0; i<2; i++){
                for (int j=0; j<3; j++){
                    cout << mat[i][j] << " ";
                }
                cout << endl;
            }
        }
        else{
            cout << "Some value is stored in the container" << endl;
        }
    }

    Container a;
    Container b(100);

    int *arr = new int[3];
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    Container c(arr, 3);

    int **mat = new int*[2];
    mat[0] = new int[3];
    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[0][2] = 3;
    mat[1] = new int[3];
    mat[1][0] = 4;
    mat[1][1] = 5;
    mat[1][2] = 6;

    Container d(mat, 2, 3);

    cout << endl;
    cout << "Demonstrating objects of ContainerArray class..." << endl;
    cout << endl;

    int firstObjArraySize = 3, secondObjArraySize = 4;
    ContainerArray containerArray1;
    ContainerArray containerArray2(secondObjArraySize);
    cout << secondObjArraySize << " constructors with empty parameters are called" << endl;

    containerArray1.setAllocatedSize(firstObjArraySize);
    cout << firstObjArraySize << " constructors with empty parameters are called" << endl;

    containerArray1.setItemAt(a, 0);
    containerArray1.setItemAt(b, 2);
    containerArray1.setItemAt(c, 1);

    containerArray2.setItemAt(c, 0);
    containerArray2.setItemAt(d, 1);

    for (int i=0; i<3; i++){
        cout << i << "-th element of 1st container array:" << endl;
        containerArray1.getItemAt(i).print();
    }

    for (int i=0; i<2; i++){
        cout << i << "-th element of 2nd container array:" << endl;
        containerArray2.getItemAt(i).print();
    }

    return 0;
}
