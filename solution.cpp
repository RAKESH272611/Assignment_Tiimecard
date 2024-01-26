#include <bits/stdc++.h>
using namespace std;
#define ll long long

/* Assumptions
1. all ',' seperated names are considered as a single name (Because i was confused how a single employee can work on different tasks with overlapping time).
2. if Time is not present than it will not be counted.
3. if Time out is not present and Timecard Hours is 0.00 then it will marked as present but only for 0 minute.
4. Removed first line heading and converted the sheet to tsv file.
*/

/* 
1. First converted it to tsv file
2. Now taking input as 2d array of string 
*/


int main() {
    freopen("data.tsv","r",stdin);
    freopen("output.txt","w",stdout);

    vector<vector<string>>V; // A single data structure for all input

    string str;
    string s = "";
    vector<string>temp; // This will be used for taking input of each shift.
    int ct = 0;
    while(cin>>str){
        if(ct==0 && str[0]!='W') continue;
        temp.push_back(str);
         if(ct==0){
           for(int i = 3; i<str.size(); i++){
            s+=str[i];
           }
           ct++;
         }
         else{
           if(str==s){
             ct = 0;
             V.push_back(temp);
             temp.clear();
             s = "";
           }
         }
    }

    // part 1 - who has worked for 7 consecutive days. ***************************************



    vector<int>ans; // This container will store the last index where it started working for 7 consecutive days.

    // Here each positionId has same name (According to my assumption) so i will just check the positionId
    // Exception : - have the exclude the position id which has no time/timeout

    set<string>st; // Current count for same employee
    int prevPId = -1;  // index of previous Position Id
    for(int i = 1; i<V.size(); i++){
        if(V[i][2][0]=='0' && V[i][5]!="0:00"){
        string s1 = V[i][3], s2 = V[i][5];
             if(prevPId==-1){
                  st.insert(s1);
                  st.insert(s2);
                  prevPId = i;
             }
             else{
                if(V[prevPId][0]==V[i][0]){
                    st.insert(s1);
                    st.insert(s2);
                }
                else{
                    if(st.size()>=7){
                        ans.push_back(prevPId);
                        st.clear();
                    }
                    prevPId = i;
                }
             }
          }
    }
    if(st.size()>=7){
        ans.push_back(prevPId);
    }

    // Now we will print all employees and position Id 

    cout<<"*******************Prining answer for part-1 *********************"<<endl;
    cout<<endl;

    for(int i = 0; i<ans.size(); i++){
        cout<<"Position Id: "<<V[ans[i]][0]<<" | ";
        cout<<"Employee Name: "<<" ";
        for(int j = 11; j<V[ans[i]].size()-1; j++){
            cout<<V[ans[i]][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;


    // part-2 - who have less than 10 hours of time between shifts but greater than 1 hour (even for 1 shift) ***********

    vector<int>ans1; // it will store any index of each Position Id for part-2

    for(int i = 0; i<V.size(); i++){
        if(V[i][2][0]=='0' && V[i][5]!="0:00"){ // excluding shifts where time/timeout is not present
            string s1 = V[i][3], s2 = V[i][6];  // time of time/timeout of each shift
            string s3 = V[i][4], s4 = V[i][7]; // AM or PM
            string s5 = V[i][2], s6 = V[i][5]; // date of time/timeout of each shift
            int a = 0, b = 0;
            // converting to minutes of s1
            int sum1 = 0, sum2 = 0;
            int f = 0;
            for(int j = 0; j<s1.size(); j++){
                if(s1[j]==':'){
                    f++;
                }
                else{
                    if(f==0)
                sum1 = sum1*10+(s1[j]-'0');
                    else
                sum2 = sum2*10+(s1[j]-'0');
                }
            }
            a = sum1*60+sum2;
            if(s3=="PM"){
                a = a+720;
            }
            // converting to minutes of s2
             sum1 = 0, sum2 = 0;
            f = 0;
            for(int j = 0; j<s2.size(); j++){
                if(s2[j]==':'){
                    f++;
                }
                else{
                    if(f==0)
                sum1 = sum1*10+(s2[j]-'0');
                    else
                sum2 = sum2*10+(s2[j]-'0');
                }
            }
            b = sum1*60+sum2;
            if(s4=="PM"){
                b=b+720;
            }
            if(s5[3]!=s6[3]){
                b = b+1440;
            }
            if(b-a>=60 && b-a<=600){
                if(ans1.size()==0){
                    ans1.push_back(i);
                }
                else{
                    if(V[i][0]!=V[ans1[ans1.size()-1]][0]){
                    ans1.push_back(i);
                } 
                }
            }


        }
    }

     cout<<"*******************Prining answer for part-2 *********************"<<endl;
    cout<<endl;

    for(int i = 0; i<ans1.size(); i++){
        cout<<"Position Id: "<<V[ans1[i]][0]<<" | ";
        cout<<"Employee Name: "<<" ";
        for(int j = 11; j<V[ans1[i]].size()-1; j++){
            cout<<V[ans1[i]][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;


    // part 3 - Who has worked for more than 14 hours in a single shift ************


    vector<int>ans2; // It will store any index of for each positionId part-3

       for(int i = 0; i<V.size(); i++){
        if(V[i][2][0]=='0' && V[i][5]!="0:00"){ // excluding shifts where time/timeout is not present
            string timeslot = V[i][8];
            int ct = 0;
            int j = 0;
            while(timeslot[j]!=':'){
            ct = ct*10+(timeslot[j]-'0');
            j++;
            }
            if(ct>=14){
              if(ans2.size()==0){
                ans2.push_back(i);
              }
              else{
                if(V[i][0]!=V[ans2[ans2.size()-1]][0]){
                    ans2.push_back(i);
                }
              }
            }
        }
    }
    
      cout<<"*******************Prining answer for part-3 *********************"<<endl;
    cout<<endl;

    for(int i = 0; i<ans2.size(); i++){
        cout<<"Position Id: "<<V[ans2[i]][0]<<" | ";
        cout<<"Employee Name: "<<" ";
        for(int j = 11; j<V[ans2[i]].size()-1; j++){
            cout<<V[ans2[i]][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;



   
   
    return 0; 
}

