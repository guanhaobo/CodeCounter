//www.guanhaobo.cn
#include <io.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
vector<string> files; //存储文件路径
vector<string> type;  //指定扩展名

//获取路径path下所有的文件名（包括子文件夹里的），存储在files中
void getFiles(string path, vector<string> &files)
{
    //文件句柄
    long hFile = 0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        { //如果是目录,迭代之
            //如果不是,加入列表
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
            }
            else
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

//获取文件行数
int getLineNum(string path)
{
    int ans = 0, first = 1;
    char ch = ' ';
    FILE *fp = fopen(path.c_str(), "r");
    if (fp == NULL)
        return 0;
    while (ch != EOF)
    {
        ch = fgetc(fp);
        if (ch == '\n')
            ans++;
    }
    return ans + 1;
}

//判断是否是目标扩展名
bool isTarget(string path)
{
    if (type.size() == 0)
        return true;
    string name = path.substr(path.find_last_of(".") + 1);
    if (find(type.begin(), type.end(), name) != type.end())
        return true;
    return false;
}

int main()
{
    string filePath;
    cout << "请输入项目文件夹的路径：";
    cin >> filePath;
    //设置扩展名
    type.push_back("java");
    //读取所有文件的路径
    getFiles(filePath, files);
    int num, ans = 0;
    for (int i = 0; i < files.size(); i++)
    {
        //如果是目标扩展名，则读取行数
        if (isTarget(files[i]))
        {
            num = getLineNum(files[i]);
            ans += num;
            cout << files[i] << "    行数：" << num << endl;
        }
    }
    cout << endl
         << "总行数：" << ans << endl;
    return 0;
}