import math

def f(x):
    return x/(1-x) * (6/(2+x))**0.5-0.05

def find_Root_By_Bisection_Method(lower,upper,ERROR,MAX_ITERATION):
    iteration = 0
    prev_solution = 0
    for iteration in range(MAX_ITERATION):
        mid = (lower+upper)/2
        if iteration!=1:
            error = math.fabs((mid-prev_solution)/mid)*100
            if( error<ERROR ):
                return mid,error
        prev_solution = mid
        if f(lower)*f(mid)<0:
            upper = mid
        else:
            lower = mid
    return ;

if __name__ == '__main__':
    [root,error] = find_Root_By_Bisection_Method(0, 0.999, 0.5, 15)
    if root == None:
        print("No solutions exist")
    else:
        print("Solution is ",root," with relative approximate error ",error,"%")

