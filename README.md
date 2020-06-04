# CodeCounter

命令行版代码行数计算

## 简介

1. 计算代码总行数
2. 指定路径
3. 可指定扩展名
4. 可输出详细信息

## 编译

下载代码到本地
```
git clone https://github.com/ghb123/CodeCounter
```

编译
```
cd CodeCounter
// Windows
g++ -o CodeCounter.exe CodeCounter.cpp
// Linux
g++ -o CodeCounter CodeCounter.cpp
```

**推荐**：为编译好的程序配置环境变量

## 如何使用

### 指定扩展名

```
CodeCounter 目标路径 扩展名1 扩展名2 扩展名3
```
扩展名可以为一个或多个，需要用小写，程序会自动识别对应的大写扩展名文件。
例如
```
CodeCounter app/src java xml
```

### 不指定扩展名

```
CodeCounter 目标路径 *
```
所有文件都会被计算。

### 不输出详细信息

如果不想要详细信息，只想得到一个数字，可以使用参数`-a`
```
CodeCounter -a 目标路径 扩展名1 扩展名2 扩展名3
```

## License

```
MIT License

Copyright (c) 2020 关浩博

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```