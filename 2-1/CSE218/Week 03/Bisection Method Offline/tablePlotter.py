import math
import termtables as tt

def f(x):
    return x/(1-x) * math.sqrt(6/(2+x))-0.05

def find_Root_By_Bisection_Method(lower,upper,MAX_ITERATION):
    iteration = 0
    prev_solution = 0
    table = []

    for iteration in range(MAX_ITERATION):
        mid = (lower+upper)/2
        if iteration!=0:
            error = math.fabs((mid-prev_solution)/mid)*100
            data = [iteration+1,mid,error]
        else:
            data = [iteration+1,mid,"-----"]
        table.append(data)
        prev_solution = mid
        if f(lower)*f(mid)<0:
            upper = mid
        else:
            lower = mid
    return table;

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    table = find_Root_By_Bisection_Method(0, 0.999, 20)
    header = ["iteration","value","Relative Error"]
    tt.print(table,header)

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
