/*************************************************
*   作者：关浩博
*   日期：2020-05-04
*   描述：代码行数查看器
*   链接：https://github.com/ghb123/CodeCounter
**************************************************/
#include <bits/stdc++.h>
#ifdef linux
#include <unistd.h>
#include <dirent.h>
#endif
#ifdef WIN32
#include <io.h>
#endif
using namespace std;
/* 存储文件路径 */
vector<string> files;

/* 指定扩展名 */
vector<string> type;

/* 是否不限制扩展名 */
bool allType = false;

/* 功能获取路径path下所有的文件路径（包括子文件夹里的），存储在files中 */
void getFiles(string path, vector<string> &files)
{

#ifdef WIN32
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
#endif

#ifdef linux
    DIR *dir;
    struct dirent *ptr;
    char base[1000];

    if ((dir = opendir(path.c_str())) == NULL)
    {
        perror("Open dir error...");
        exit(1);
    }

    while ((ptr = readdir(dir)) != NULL)
    {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;
        else if (ptr->d_type == 8)
            files.push_back(ptr->d_name);
        else if (ptr->d_type == 10)
            continue;
        else if (ptr->d_type == 4)
        {
            files.push_back(ptr->d_name);
        }
    }
    closedir(dir);
#endif
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
    if (type.size() == 0 || allType)
        return true;
    string name = path.substr(path.find_last_of(".") + 1);
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    if (find(type.begin(), type.end(), name) != type.end())
        return true;
    return false;
}

/* 输出详细信息 */
void run1(int argc, char **argv)
{
    string filePath = argv[1];
    //设置扩展名
    for (int i = 2; i < argc; i++)
        type.push_back(argv[i]);
    //读取所有文件的路径
    getFiles(filePath, files);
    int num, ans = 0;
    for (int i = 0; i < files.size(); i++)
    {
        if (!allType && !isTarget(files[i]))
            continue;
        num = getLineNum(files[i]);
        ans += num;
        cout << files[i] << "\tLines:" << num << endl;
    }
    cout << endl
         << "Total:" << ans << endl;
}

/* 只输出结果 */
void run2(int argc, char **argv)
{
    if (argc < 4)
    {
        cout << "error" << endl;
        return;
    }
    string filePath = argv[2];
    //设置扩展名
    for (int i = 3; i < argc; i++)
        type.push_back(argv[i]);
    //读取所有文件的路径
    getFiles(filePath, files);
    int num, ans = 0;
    for (int i = 0; i < files.size(); i++)
    {
        if (!allType && !isTarget(files[i]))
            continue;
        num = getLineNum(files[i]);
        ans += num;
    }
    cout << ans << endl;
}

/* 主函数 */
int main(int argc, char **argv)
{
    if (argc < 3)
    {
        cout << "error" << endl;
        return -1;
    }
    else if (strcmp(argv[argc - 1], "*") == 0)
        allType = true;
    if (strcmp(argv[1], "-a") == 0) //只输出结果
        run2(argc, argv);
    else
        run1(argc, argv);
    return 0;
}