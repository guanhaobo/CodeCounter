/*************************************************
*   作者：关浩博
*   日期：2020-05-04
*   描述：代码行数查看器
*   链接：https://github.com/ghb123/CodeCounter
**************************************************/
#include <bits/stdc++.h>
#include <io.h>
using namespace std;
/* 存储文件路径 */
vector<string> files;

/* 指定扩展名 */
vector<string> type;

/* 功能获取路径path下所有的文件路径（包括子文件夹里的），存储在files中 */
void getFiles(string path, vector<string> &files)
{
    long hFile = 0;
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
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

/* 获取文件行数 */
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

/* 判断是否是目标扩展名 */
bool isTarget(string path)
{
    if (type.size() == 0)
        return true;
    string name = path.substr(path.find_last_of(".") + 1);
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    if (find(type.begin(), type.end(), name) != type.end())
        return true;
    return false;
}

/* 主函数 */
int main(int argc, char **argv)
{
    if (argc < 3)
    {
        cout << "error" << endl;
        return -1;
    }
    string filePath = argv[1];
    //设置扩展名
    for (int i = 2; i < argc; i++)
        type.push_back(argv[i]);
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
            cout << files[i] << "\t行数：" << num << endl;
        }
    }
    cout << endl
         << "总行数：" << ans << endl;
    return 0;
}