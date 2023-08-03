//
//  main.cpp
//  BoardCutter
//
//  Created by Sart Way on 9/7/23.
//

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <functional>
#include <fstream>
#include <vector>
#include <list>

using namespace std;


string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);
long boardCutting(vector<int>,vector<int>);
void merger(vector<pair<int,int>>&arr,int start,int mid,int end);
void longer(vector<pair<int,int>>&arr, int start, int end);


long boardCutting(vector<int> cost_y, vector<int> cost_x) {
    vector<pair<int,int>>venter;
    int multiplier_x = 1;
    int multiplier_y = 1;
    for(int i=0;i<(int)cost_y.size();++i)
    {
        venter.push_back(pair<int,int>(cost_y[i],0));
    }
    for(int i=0;i<(int)cost_x.size();++i)
    {
        venter.push_back(pair<int,int>(cost_x[i],1));
    }
//    for(int i=0;i<venter.size();++i)
//    {
//        cout << venter[i].first << " ";
//    }
//    cout << endl;
    longer(venter, 0, (int)venter.size()-1);
    long sum = 0l;
    int counter = 0;
    int constant = (LONG_MAX%1000000007);
    for(int i=(int)venter.size()-1;i>=0;--i)
    {
        if(venter[i].second == 0)
        {
            long y = (long)multiplier_x*venter[i].first % 1000000007;
            sum += y;
            
            multiplier_y += 1;
        } else {
            long y = (long)multiplier_y*venter[i].first % 1000000007;
            sum += y;
            //sum += (long)(multiplier_y*venter[i].first);
            multiplier_x += 1;
        }
        sum %= 1000000007;
    }
    //cout << counter << endl;
    return sum;
}

void longer(vector<pair<int,int>>&arr, int start, int end)
{
    if(start >= end)
    {
        return;
    }
    int mid = start + ((end - start)/2);
    longer(arr,start,mid);
    longer(arr,mid+1,end);
    merger(arr,start,mid,end);
}

void merger(vector<pair<int,int>>&arr, int start, int mid, int end)
{
    //cout << start << " " << mid << " " << end << endl;
    pair<int,int>* leftarr_cpy = new pair<int,int>[(mid - start) + 1];
    pair<int,int>* rightarr_cpy = new pair<int,int>[end - mid];
    int right = 0;
    int left = 0;
    
    for(int x=start;x<=mid;++x)
    {
        
        leftarr_cpy[left] = arr[x];
        //cout << leftarr_cpy[x].first << " ";
        left++;
    }
    
    for(int x=mid+1;x<=end;++x)
    {
        rightarr_cpy[right] = arr[x];
        //cout << rightarr_cpy[x].first << " ";
        right++;
    }
    //cout << endl;
    int right_ptr = 0;
    int left_ptr = 0;
    int x = start;
    while(right_ptr < right && left_ptr < left)
    {
        if(rightarr_cpy[right_ptr].first < leftarr_cpy[left_ptr].first)
        {
            //cout << rightarr_cpy[right_ptr].first << " s ";
            arr[x] = pair<int,int>(rightarr_cpy[right_ptr].first, rightarr_cpy[right_ptr].second);
            right_ptr++;
        } else {
            //cout << leftarr_cpy[left_ptr].first << " si ";
            arr[x] = pair<int,int>(leftarr_cpy[left_ptr].first, leftarr_cpy[left_ptr].second);
            left_ptr++;
        }
        ++x;
    }
    //cout << endl;
    if (left_ptr == left) {
        while (right_ptr < right) {
            arr[x] = rightarr_cpy[right_ptr];
            x++;
            right_ptr++;
        }
    }
    else {
        while (left_ptr < left) {
            arr[x] = leftarr_cpy[left_ptr];
            x++;
            left_ptr++;
        }
    }
    
//    for(int i=start;i<end;++i)
//    {
//        cout << arr[i].first << " ";
//    }
//    cout << endl;
    delete[] leftarr_cpy;
    delete[] rightarr_cpy;
    return;
}


int main(int argc, const char * argv[]) {
    fstream input("input.txt", ios::in | ios::out);
    string q_temp;
    if(input.is_open())
    {
        cout << "File is open" << endl;
    }
    getline(input, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(input, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int m = stoi(first_multiple_input[0]);

        int n = stoi(first_multiple_input[1]);

        string cost_y_temp_temp;
        getline(input, cost_y_temp_temp);

        vector<string> cost_y_temp = split(rtrim(cost_y_temp_temp));

        vector<int> cost_y(m - 1);

        for (int i = 0; i < m - 1; i++) {
            int cost_y_item = stoi(cost_y_temp[i]);

            cost_y[i] = cost_y_item;
            //cout << cost_y[i] << endl;
        }

        string cost_x_temp_temp;
        getline(input, cost_x_temp_temp);

        vector<string> cost_x_temp = split(rtrim(cost_x_temp_temp));

        vector<int> cost_x(n - 1);

        for (int i = 0; i < n - 1; i++) {
            int cost_x_item = stoi(cost_x_temp[i]);

            cost_x[i] = cost_x_item;
            //cout << cost_x[i] << endl;
        }

        int result = boardCutting(cost_y, cost_x);

        cout << result << "\n";
    }
    input.close();
        //out.close();

    return 0;
}


string ltrim(const string &str) {
    string s(str);

    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);}));
    return s;

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);}));
    return s;

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
