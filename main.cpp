#include <iostream>
#include <fstream>
using namespace std;

void tokenizer(string row, string delimiter, int index = NULL){
    string temp;
    string temp_array[];
    int counter = 0;

    for (int i=0; i<(int)row.size(); i++){
        if (index == NULL){
            if (row[i] != delimiter){
                temp += row[i];
            }
            else{
                temp_array[counter] = temp;
                counter++;
                temp = "";
            }
        }
        else{
            if (row[i] != delimiter){
                temp += row[i];
            } else {
                if (counter == index){return temp;}
                counter++;
            }
        }
    }

    return (index == NULL): temp_array ? 0;
}

// void student_get_info(string student_id){
//     ifstream file;
//     string student_info;
//     file.open("si.txt");
//     while(file){
//         getline(file, student_info);
//         string temp;
// 
//         for (int i=0; i<(int)student_info.size(); i++){
//             if(student_info[i] != "-"){
//                 temp += student_info[i];
//             }
//             else{break;}
//         }
// 
//         if (temp == student_id) {
//             return student_info;
//         }
//     }
//     return 0;
// }
// 
// void self_get_info(int pk){}
// 
// void reservation_get_info(int student_id){}

int main(){
    string hamid;
    cin>>hamid;
    cout<<tokenizer(hamid, "-", 2)<<endl;
    return 0;
}
