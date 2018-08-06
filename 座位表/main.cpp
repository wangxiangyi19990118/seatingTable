#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

class people {//人的基本类型，包括姓名和权重
public:
	string name;
	string weight;
	people(string name, string weight) {
		this->name = name;
		this->weight = weight;
	}
	people() {}
	string getweight() {
		return this->weight;
	}
	string getname() {
		return this->name;
	}
	void setweight(int weight) {
		this->weight = weight;
	}
	void setname(string name) {
		this->name = name;
	}
};
int main()
{
	string seat[8][12];
	for (int i = 0; i < 8; i++) {//初始化座位表
		for (int j = 0; j < 12; j++) {
			seat[i][j] = "******";
		}
	}
	people person[100],person1[100];
	int tolnum = 0,tolnum1=0;
	ifstream file1;
	file1.open("./name.txt");
    string textline1[100];
	string name1;
	string weight1;
	 while(!file1.eof())//读入所有人数据（包括姓名和权重），并保存到数组里
    {
        getline(file1, textline1[tolnum], '\n');
        char str[100];
        strcpy(str, textline1[tolnum].c_str());
        const char *sep = ","; //可按多个字符来分割
        char *p;
        p = strtok(str, sep);
        int temp=1;
        while(p){
        if(temp%2!=0)
            name1=p;
        if(temp%2==0)weight1=p;
        p = strtok(NULL, sep);
            temp++;
        }
       //cout<<name<<" "<<weight<<endl;
		people newp1 = people(name1, weight1);
		person1[tolnum1] = newp1;
		tolnum1++;
	}
	tolnum1--;
	string todayname;
	ifstream file;
	file.open("./todayname.txt");
    string textline[100];
	string name;
	string weight;
	 while(!file.eof())//读入本次参会人员的名字，在所有人的数组里查找，保存该人的姓名和权重到新的数组里
    {
        getline(file, textline[tolnum], '\n');
        char str[100];
        strcpy(str, textline[tolnum].c_str());
        const char *sep = ","; //可按多个字符来分割
        char *p;
        p = strtok(str, sep);
        int temp=1;
        while(p){
        if(temp%2!=0){
            name=p;
            for (int a = 0; a < tolnum1; a++) {
            if(name==person1[a].getname()){
                people newp = people(name, person1[a].getweight());
                person[tolnum] = newp;
                tolnum++;
               // cout<<name<<" "<<person1[a].getweight()<<endl;
            }
		}
        }
        p = strtok(NULL, sep);
            temp++;
        }
	}
	tolnum--;
        for (int i = 0; i < tolnum - 1; i++){//对本次参会人员根据权重，由大到小进行冒泡排序
             for (int j = 0; j < tolnum - 1 - i; j++){
                if(person[j].getweight()<(person[j+1].getweight())){
                    swap(person[j],person[j+1]);
                }
             }
        }
        //cout<<tolnum<<endl;
        int tol2=0;
        for (int b = 0; b < tolnum; b++) {
		if(person[b].weight>="50")  tol2++;}//针对中间第一排进行排序，全部是领导，坐不满的话不考虑，坐满的话第二排接着坐
		//cout<<tol2<<endl;
    switch(tol2){
        case 1:
        seat[0][6]=person[0].getname();
        break;
        case 2:
        seat[0][6]=person[0].getname();
        seat[0][5]=person[1].getname();
        break;
        case 3:
        seat[0][6]=person[0].getname();
        seat[0][5]=person[1].getname();
        seat[0][7]=person[2].getname();
        break;
        case 4:
        seat[0][6]=person[0].getname();
        seat[0][5]=person[1].getname();
        seat[0][7]=person[2].getname();
        seat[0][4]=person[3].getname();
        break;
        case 5:
        seat[0][6]=person[0].getname();
        seat[0][5]=person[1].getname();
        seat[0][7]=person[2].getname();
        seat[0][4]=person[3].getname();
        seat[0][8]=person[4].getname();
        break;
        case 6:
        seat[0][6]=person[0].getname();
        seat[0][5]=person[1].getname();
        seat[0][7]=person[2].getname();
        seat[0][4]=person[3].getname();
        seat[0][8]=person[4].getname();
        seat[0][3]=person[5].getname();
        break;
        default:
        seat[0][6]=person[0].getname();
        seat[0][5]=person[1].getname();
        seat[0][7]=person[2].getname();
        seat[0][4]=person[3].getname();
        seat[0][8]=person[4].getname();
        seat[0][3]=person[5].getname();
        break;
    }
    int left=0;
    if(tol2<=6){
        left=tol2;
    }
    else left=6;
    int con=0;
    for(int i=1;i<8;i++){//对中间部分的座位进行安排
        for(int j=3;j<9;j++){
                if(left+con<tolnum){
                    seat[i][j]=person[left+con].getname();
                    con++;
                }
        }
    }
    int con1=0;
    int con2=0;
    if(con+left<tolnum){//如果中间坐满，安排左侧
       for(int i=1;i<8;i++){
        for(int j=0;j<3;j++){
                 if(left+con+con1<tolnum){
                     seat[i][j]=person[left+con+con1].getname();
                con1++;
                 }

        }
    }
    //cout<<con1<<endl;
    }
    if(con+con1+left<tolnum){//如果左侧坐满，安排右侧
        for(int i=0;i<8;i++){
        for(int j=9;j<12;j++){
                if(left+con+con1+con2<tolnum){
                seat[i][j]=person[left+con+con1+con2].getname();
                con2++;
                }

        }
    }
    }ofstream fout("./data.txt");//座位安排结果写入文件
    for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 12; j++) {
			cout<<seat[i][j]<<"    ";
			fout <<seat[i][j]<<"    ";
		}
		cout<<endl;
		fout<<endl;
	}
    fout.close();
	system("pause");
	return 0;
}

