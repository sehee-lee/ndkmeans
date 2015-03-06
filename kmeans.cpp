#include<iostream>
#include<sstream>
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

typedef struct{
    double *means;
    int numberofdata;
}Mean;

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

    Mean *mean = new Mean[k];
    for(int i = 0; i<k; i++){
        mean[i].means = new double[d];
        mean[i].numberofdata = 0;
    }
    

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
            istringstream(token) >> datapoints[i].values[j];
            j ++;
        }
        istringstream(line) >> datapoints[i].values[j];
        i++;
        j = 0;
        datapoints[i-1].Did = i;
        datapoints[i-1].label = -1;
    }
    int flag_move = 0;
    while(1){
        flag_move = 0;
        
        for(int i = 0; i < n; i++){
           // cout << "current data id : " << i << endl;
            if(mean[k-1].means[0] == 0){
                for(int j = 0; j < d; j++)
                    mean[i].means[j] = datapoints[i].values[j];
                flag_move = 1;
                mean[i].numberofdata ++;
            }
            else{
                int check_label = datapoints[i].label;
                int closest = -1; 
                double mindis = -1;
                double dis = 0;
                for(int j = 0; j < k; j++){
                    for(int de = 0; de < d; de++)
                        dis += pow(mean[j].means[de] - datapoints[i].values[de],2);
                    dis = sqrt(dis);
                    
                    if(mindis == -1 || mindis > dis){
                        mindis = dis;
                        closest = j;
                    }
                    dis = 0;
                }
                        
                datapoints[i].label = closest;
                for(int de = 0; de < d; de++){
                    mean[closest].means[de] *= mean[closest].numberofdata;
                    mean[closest].means[de] += datapoints[i].values[de];
                    mean[closest].means[de] /= (mean[closest].numberofdata + 1);
                    if(check_label != -1)
                        mean[check_label].means[de] = ((mean[check_label].means[de] * mean[check_label].numberofdata) - datapoints[i].values[de])/(mean[check_label].numberofdata - 1);
                }
                if(check_label != -1)
                    mean[check_label].numberofdata --;
                mean[closest].numberofdata ++;
            
                if(check_label != datapoints[i].label)
                    flag_move = 1;
            }
        }
        if(flag_move == 0)
            break;
    }
    for(int j = 0; j<n; j++){
        cout << datapoints[j].Did << " ";
        for(int l = 0; l < d; l++)
            cout << datapoints[j].values[l] << " ";
        cout << datapoints[j].label << endl;
    }
            

    return 0;

}
