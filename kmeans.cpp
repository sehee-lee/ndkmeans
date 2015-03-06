#include<iostream>
#include<string>
#include<math.h>
#include<stdio.h>
#include<fstream>
#include<stdlib.h>

using namespace std;

typedef struct{
    int Did;
    double *values;
    int label;
}DataPoint;

int main(void){

    int d=0;
    cout << "Input Dimention : ";
    cin >> d;
    int k = 0;
    cout << "Input number of Clusters : ";
    cin >> k;
    int n = 0;
    cout << "Input number of Total DataPoints : ";
    cin >> n;

    double **means = new double*[k];
    for(int i = 0; i<k; i++)
        means[i] = new double[d];
    
    for(int m = 0; m < k; m++)
        means[m] = 0;

    DataPoint *datapoints = new DataPoint[n];
    
    string filename = "data";
    ifstream datafile;
    datafile.open(filename.c_str(), ios::in);
    string line;
    string token;
    size_t pos = 0;
    int i = 0;
    int j = 0;
    string delimiter = " ";
    while(!datafile.eof()){
        getline(datafile,line);
        datapoints[i].values = new double[d];
        while ((pos = line.find(delimiter)) != std::string::npos) {
            token = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
            datapoints[i].values[j] = stoi(token);
            j ++;
        }
        datapoints[i].values[j] = stoi(line);
        i++;
        datapoints[i-1].Did = i;
    }
    int flag_move = 0;
    while(1){
        flag_move = 0;
        
        
        for(int i = 0; i < n; i++){
            
            if(means[k-1][0] == 0){
                for(int j = 0; j < d; j++)
                    means[i][j] = datapoints[i].values[j];
                flag_move = 1;
            }
            else{
                int check_label = datapoints[i].label;

                for(int j = 0; j < k; k++){
                    double mindis = -1;
                    double dis = 0;
                    
                    for(int de = 0; de < d; de++)
                        dis += pow(means[j][de] - datapoints[i].values[de],2);
                    dis = sqrt(dis);
                    
                    if(mindis == -1 || mindis > dis){
                        mindis = dis;
                        datapoints[i].label = j;
                    }
                }
                
                if(check_label != datapoints[i].label)
                    flag_move = 1;
            }
        }

        
        if(flag_move == 0)
            break;
    }
    
    string label = "cl_";
    for(int i = 0; i<k; i++){
        cout << "Cluster " << to_string(i) <<endl;
        for(int j = 0; j<n; j++){
        
            if(datapoints[j].label == i){
                cout << datapoints[j].Did;
                for(int l = 0; l < d; l++)
                    cout << datapoints[j].values[l];
                cout << endl;
            }
            
        }

    }

}
