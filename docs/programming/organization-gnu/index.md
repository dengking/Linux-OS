# 前言

在Unix-like OS中进行programming，就不得不掌握[GNU Project](https://en.wikipedia.org/wiki/GNU_Project)所提供的一系列工具了。

GNU官网：[**GNU** Operating System](https://www.gnu.org/)

# 分类

GNU提供了一系列的（很多）software，有必要对这些software进行分类，在其官网的[GNU Manuals Online](https://www.gnu.org/manual/manual.html)页面中给出了一个大分类：

- [Archiving](https://www.gnu.org/manual/manual.html#Archiving) 
- [Audio](https://www.gnu.org/manual/manual.html#Audio) 
- [Business and productivity](https://www.gnu.org/manual/manual.html#Business) 
- [Database](https://www.gnu.org/manual/manual.html#Database) 
- [Dictionaries](https://www.gnu.org/manual/manual.html#Dictionaries) 
- [Documentation translation](https://www.gnu.org/manual/manual.html#Translation) 
- [Editors](https://www.gnu.org/manual/manual.html#Editors) 
- [Education](https://www.gnu.org/manual/manual.html#Education) 
- [Email](https://www.gnu.org/manual/manual.html#Email) 
- [Fonts](https://www.gnu.org/manual/manual.html#Fonts) 
- [GNU organization](https://www.gnu.org/manual/manual.html#gnuorg) 
- [Games](https://www.gnu.org/manual/manual.html#Games) 
- [Graphics](https://www.gnu.org/manual/manual.html#Graphics) 
- [Health](https://www.gnu.org/manual/manual.html#Health) 
- [Interface](https://www.gnu.org/manual/manual.html#Interface) 
- [Internet applications](https://www.gnu.org/manual/manual.html#Internet) 
- [Live communications](https://www.gnu.org/manual/manual.html#Live) 
- [Localization](https://www.gnu.org/manual/manual.html#Localization) 
- [Mathematics](https://www.gnu.org/manual/manual.html#Mathematics) 
- [Music](https://www.gnu.org/manual/manual.html#Music) 
- [Printing](https://www.gnu.org/manual/manual.html#Printing) 
- [Science](https://www.gnu.org/manual/manual.html#Science) 
- [Security](https://www.gnu.org/manual/manual.html#Security) 
- [Software development](https://www.gnu.org/manual/manual.html#Software) 
- [Software libraries](https://www.gnu.org/manual/manual.html#Libraries) 
- [Spreadsheets](https://www.gnu.org/manual/manual.html#Spreadsheets) 
- [System administration](https://www.gnu.org/manual/manual.html#Sysadmin) 
- [Telephony](https://www.gnu.org/manual/manual.html#Telephony) 
- [Text creation and manipulation](https://www.gnu.org/manual/manual.html#Text) 
- [Version control](https://www.gnu.org/manual/manual.html#Version) 
- [Video](https://www.gnu.org/manual/manual.html#Video) 
- [Web authoring](https://www.gnu.org/manual/manual.html#Web)



## [Software development](https://www.gnu.org/manual/manual.html#Software) 

可以看到，它覆盖了非常多的领域。

对于软件工程师而言，需要重点关注的是[Software development](https://www.gnu.org/manual/manual.html#Software) 这一大类。其中的工具很多是我们在日常工作中是离不开的。

# [GNU Build System](https://en.wikipedia.org/wiki/GNU_Autotools)

需要注意的是，gnu build system的另外一种说法是autotools：

官方介绍：[An Introduction to the Autotools](https://www.gnu.org/software/automake/manual/automake.html#Autotools-Introduction)



## 组成

### [GNU Autoconf](https://en.wikipedia.org/wiki/Autoconf)

官网：[Autoconf](https://www.gnu.org/software/autoconf/)

文档：[GNU Autoconf - Creating Automatic Configuration Scripts](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/index.html)

功能：创建`configure`文件

关于configure文件，参见[configure script](https://en.wikipedia.org/wiki/Configure_script)

使用configure文件来创建makefile文件

### [GNU Automake](https://en.wikipedia.org/wiki/Automake)

官网：[Automake](https://www.gnu.org/software/automake/)

文档：[automake](https://www.gnu.org/software/automake/manual/automake.html)

### [GNU Libtool](https://en.wikipedia.org/wiki/Libtool)



### [Gnulib](https://en.wikipedia.org/wiki/Gnulib)



## 学习资源

[Autotools Mythbuster](https://autotools.io/index.html)



# [GNU toolchain](https://en.wikipedia.org/wiki/GNU_toolchain)