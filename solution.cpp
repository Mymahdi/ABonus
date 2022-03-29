#include <iostream>
#include <vector>

using namespace std;

void get_input(int &m , int &n){
    cin >> m >> n;
}

void initialize_farm(int m ,int n , vector<vector<int> > &farm){
    int product;      
    for(int i = 0 ; i < m ; i++)
        for(int j = 0 ; j < n ; j++){
            cin >> product;
            farm[i][j] = product;
        }
    
}
void find_max_row(int m ,int &row ,int &max_row, vector<long int> row_sums){

     for(int i = 0; i < m; i++){
        if (row_sums[i] > max_row) {
            max_row = row_sums[i];
            row = i;
        }
    }
}


void find_max_column(int m ,int n ,int &column ,int &max_column , vector<vector<int> > farm){

    int sum = 0;

    for(int j = 0; j < n; j++){
        for(int i = 0; i < m; i++){
            sum += farm[i][j];
        }
        if(sum > max_column){
            max_column = sum;
            column = j;
        }
        sum = 0;
    }
}
//----------------
long int sum_calculate(vector<int> v){
     long int sum = 0;
    for (int i = 0; i < v.size(); i++)
    sum += v[i];
    return sum;
}

void built_row_sums(int m , vector<long int> &row_sums,vector<vector<int> > farm){
    int sum = 0;
       for(int i = 0; i < m; i++){
            sum = sum_calculate(farm[i]);
            row_sums.push_back(sum);
            sum = 0;
        }
}

void calculate_harvest(long int &harvest , int &column , int &row ,int m ,int n , int max_column ,int max_row,
    vector<vector<int> > &farm){

     if(max_column > max_row){
        harvest += max_column;
        for(int i = 0; i < m; i++){
        farm[i][column] = 0;
        }
    }
    else{
        harvest += max_row;
        for(int j = 0; j < n; j++){
            farm[row][j] = 0;
        }
    }
}
//--------------------------------
void solve(int m, int n, long int& harvest , vector<vector<int> > &farm){
    
    int max_row = 0;
    int max_column = 0;
    int row = 0;
    int column = 0;

    for(int move = 0; move < 4; move++) {
        vector<long int> row_sums;
        built_row_sums( m , row_sums ,farm);
     
        find_max_row(m ,row ,max_row ,row_sums);
       
        find_max_column(m ,n ,column ,max_column ,farm);
        
        calculate_harvest(harvest ,column ,row , m , n , max_column ,max_row,farm);
        row = 0;
        column = 0;
        max_column = 0;
        max_row = 0;
    }
}
/*----------------*/
int main() {
    int m, n;
    
    vector<vector<int> > farm;
    long int harvest = 0;
    get_input(m , n);
    farm = vector < vector < int > > (m, vector<int>(n));
    initialize_farm(m ,n , farm);
    

    
    
    // solve
    solve(m, n, harvest ,farm);
    cout << harvest;
    return 0;
    
} // main
