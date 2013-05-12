# Frequently Asked Questions

## 我的程序要在哪里输入和输出数据？

你的程序必须从stdin（基本输入）读入数据并且从stdout（基本输出）输出数据。例如，你使用C语言的话，使用scanf读入数据，使用printf输出数据，你使用C++语言的话，还可以使用cin和cout读入和输出数据。

** 注意：你提交的程序不能进行任何文件的读写操作，否则会返回“Wrong Answer”。 **

## 本OJ提供哪些编译器？编译环境是怎么样的？

本OJ目前提供多种语言编译器,它们的编译参数分别是：

-  `gcc     : gcc main.c -o main -Wall -lm -O2 -std=c99 --static -DONLINE_JUDGE`
-  `g++     : g++ main.cpp -O2 -Wall -lm --static -DONLINE_JUDGE -o main`
-  `java    : javac Main.java`
-  `ruby    : reek main.rb`
-  `perl    : perl -c main.pl`
-  `pascal  : fpc main.pas -O2 -Co -Ct -Ci`
-  `go      : go build -ldflags "-s -w"  main.go`
-  `lua     : luac -o main main.lua`
-  `python2 : python2 -m py_compile main.py`
-  `python3 : python3 -m py_compile main.py`
-  `haskell : ghc -o main main.hs`

目前服务器运行在Linux平台下，提供的编译器的版本分别是：

```
gcc     4.4.5
g++     4.4.5
java    1.6.2
pascal  2.4.0
ruby    2.0
lua     5.1.4
perl    5.10
python2 2.7.3
python3 3.3.0
go      1.0
ghc     7.6.2
```

## 为什么我提交的程序在OJ运行得到了Compile Error？而在我的电脑上运行得很好？

不同的编译器之间有一些语法的差异，如果你电脑上使用的编译器与本OJ提供的编译器不同，请注意它们之间的差异，提交时请使用相应的编译器进行提交。


## 我要怎么使用64-bit整型？

`C/C++` 评测程序只支持`long long`，不支持`int64`

有符号64-bit整型，取值范围为：`-9223372036854775808` 到 `9223372036854775807`。

无符号64-bit整型，取值范围为：`0` 到 `18446744073709551615`。

## OJ返回的结果分别是什么意思？

以下是OJ可能返回的结果和其意义：

- `Accepted`

恭喜！ 你的程序是正确的。

- `Presentation Error`

你的程序输出时表达错误，如果看到这样的结果，说明你的程序已经基本正确了，只是多或少打了换行符或者多或少输出了空格，检查一下你的程序和题目要求吧，胜利就在眼前！

- `Wrong Answer`

你的程序输出的结果不正确。

- `Time Limit Exceeded`

你的程序尝试使用超过题目限制的时间，可能是你的程序内存在死循环或者你的程序的算法效率太低。

- `Memory Limit Exceeded`

你的程序尝试使用超过题目限制的内存。

- `Runtime Error`

你的程序发生了运行时错误。可能是由于除以0、数组越界或指针访问出错等运行时问题。

- `Compile Error`

你的程序不能通过编译，请点击该结果可以查看编译器提示。

- `Output Limit Exceeded`

你的程序的输出过多。请检查你的程序是否存在死循环问题。

- `Waiting`

你的程序正在评测中，请稍候。


## 第1000号题目怎么解答？

以下是第1000号题目的各种语言的参考程序：

- C语言

```c
#include <stdio.h>
int main()
{
      int a,b;
      scanf("%d%d",&a,&b);
      printf("%d\n",a+b);
      return 0;
}
```

- C++

```cpp
#include <iostream>
using namespace std;
int main()
{
    int a,b;
    cin>>a>>b;
    cout<<a+b<<endl;
    return 0;
}
```

- PASCAL

```pascal
var
    a,b:integer;
begin
    readln(a,b);
    writeln(a+b);
end.
```

- Java

```java
import java.io.*;
import java.util.*;
public class Main
{
    public static void main(String[] args)
    {
       Scanner cin = new Scanner ( System.in );
       int a,b;
       a=cin.nextInt();
       b=cin.nextInt();
       System.out.println(a+b);
    }
}
```

- haskell

```haskell
main = getLine >>= print . sum . map read . words
```

- go

```go
package main
import "fmt"      
func main(){      
    var a,b int      
    fmt.Scanf("%d %d", &a,&b)      
    fmt.Printf("%d", a+b)      
}
```

- lua

```lua
a,b = io.read("*number", "*number")
print(a+b)
```

- perl

```perl
my ($a,$b) = split(/\D+/,<STDIN>);
print "$a $b " . ($a + $b) . "\n";
```

- ruby

```ruby
puts gets.split.map(&:to_i).inject(&:+)
```

- python2

```python
print sum(int(x) for x in raw_input().split())
```

- python3

```python
print(sum(int(x) for x in raw_input().split()))
```
