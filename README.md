# c++图书馆里系统

**开发语言：** C++

**开发工具：** Dev-cpp

**其他：** 录入了超过 4.6 万 条的图书信息和超过 1.5万 条的用户信息

  

## 使用

### 1. 如果你想看成果
1. 下载 `dist` 文件夹中的 `dist.zip`压缩包
2. 解压
2. 双击运行 `interlib.exe` 
3. 开始体验

### 2. 如果你想继续开发
1. 用 `git` 克隆仓库到本地
2. 开始开发

## 功能

可以用账号：`admin`，密码：`123456`进行登录

### 登录

1. 渲染界面之前自动调整窗口大小，保证页面渲染完整
2. 登录时验证用户名密码的非空性，再检查是否匹配
3. 输入框被点击时让页面中的其他元素变暗，而达到输入框聚焦效果
4. 输入密码时密码以`*`的形式显示，保护用户隐私
5. 密码只能由小写、大写字母和数字组合，其他符号无法输入
6. 密码框失去焦点后再次获取焦点时可接着编辑上次的内容（普通输入框不能）
7. 所有用户均可以通过自己的用户名和密码以管理员和普通用户两种模式登录，即用户没有身份区别

### 用户列表

8. 管理员可以通过用户名精确查到用户信息
9. 管理员可以添加新用户，添加时只需输入用户名即可，密码默认为123456
10. 添加新用户时会先验证用户名的唯一性，如果要添加的用户已经存在则提示用户已存在无法添加
11. 新用户会被插入到用户数据列表的最前面
12. 用户列表以分页的形式展现，每页展示10条，可以通过点击页面中的下一页，上一页按钮进行换页
13. 可以通过点击当前用户信息行末的操作按钮可以对用户进行删除，重置密码等操作
14. 展示用户密码时，如果用户没改过密码则直接以明文显示，如果用户已经改过密码则会以`*`的形式显示，而达到保护用户隐私的目的（就算是管理员也不能看到用户的密码，只能重置）

### 图书列表

15. 在图书管理页面中，可以通过`图书名称`精确查找到某一本书
16. 可以通过`作者`查找到该作者的所有书籍
17. 可以通过`ISBN`精确查找到某一本书，`ISBN`唯一且一旦录入后不可修改
18. 可以通过`分类号`查找到该分类里的所有书籍，支持多级分类，例如：
    - 当分类号输入框获取焦点时，会在左边列出当前分类层级下的所有分类（参考中图分类法）
    - 搜索`T`会找到所有的`工业技术`类书籍
    - 搜索`TP`会找到所有`工业技术 > 自动化技术、计算机技术`类书籍
    - 搜索`TP3`会找到所有`工业技术 > 自动化技术、计算机技术 > 计算技术、计算机技术`类书籍
    - 搜索`TP31`会找到所有`工业技术 > 自动化技术、计算机技术 > 计算技术、计算机技术 > 计算机软件`类书籍等等
    
19. 以上四条内容可以进行联合搜索，例如你可以查找某个做个分类为XX的所有书
20. 图书列表依然以分页的形式展现，每页展示10条，可以通过点击页面中的下一页，上一页按钮进行换页

### 新增修改图书

21. 点击`新增图书`按钮后会跳转到新增图书页面，可以在该页面中输入图书信息后决定添加或取消
22. 添加新书时，图书的四项基本信息都不能为空，`ISBN`不能重复
23. 通过点击列表行末的操作按钮对图书进行删除，修改操作，点击修改时会跳转到修改图书页面
24. 修改图书页面中会自动展示出该书的现有信息，ISBN不可修改，其他信息可修改

### 借阅图书

25. 点击`退出登录`按钮后会跳转到登录页面
26. 以普通用户模式登陆后会跳转到借阅图书页面，页面中的搜索功能与管理员图书管理页面一致
27. 可以点击行末的`借阅`按钮借阅图书，如果已经借过这本书并且尚未归还时不能再次借阅该书
28. 可以在借阅记录页面中通过`ISBN`精确查找到自己记录中的某一个本书
29. 借阅后尚未归还的书籍会在`状态`处标记尚未归还，并会有`归还`操作按钮，已归还的书籍的状态处显示空，操作按钮也不会显示

### 借阅记录

30. 可以点击`归还`按钮归还该书，归还后可以再次在`借阅图书`页面中借阅该书
31. 借阅记录页面中，会通过`ISBN`自动将图书名称显示在列表中，如果图书名称被修改过了也会同步，如果图书被删除那么在图书名称处显示未找到，该图书可能已被删除！

### 修改密码

32. 可以在帐户设置页面中修改自己的密码
    - 当前密码，新密码，重复新密码均不能为空
    - 新密码，重复新密码的内容必须一致
    - 新密码不能与旧密码相同
    - 输入的当前密码要正确
33. 修改密码后会自动退出登录，然后就可以用新密码登录

## API

### 文件

#### variable.h
声明全局变量
#### listener.h
监听器，不断监听页面中的鼠标点击，并调用相应元素的被点击方法
#### util.h
提供一些全局通用的函数
#### router.h
路由，引入所有的页面文件，并提供一个切换页面的函数`checkoutPage`
#### page_[admin | user]_XXX.h
页面文件，每个页面都会有该类型的文件，在该文件中声明一个拥有与文件名相同的名称的函数，该函数内描述页面内容，调用该函数时会用自己页面中的元素替换掉全局变量`InputBoxsArr`,`TextsArr`,`LinksArr`的内容，再由`renderElements`函数渲染

### 全局变量（部分）

#### int clientWidth
在`variable.h`中声明，客户端宽度，默认值为120个字符
#### int clientHeight
在`variable.h`中声明，客户端高度 ，默认值为34个字符
#### int linksArrLen
在`variable.h`中声明， 数组`LinksArr`的长度，即当前渲染的页面中的所有`Link`类型的元素的数量，初始值为0，一般会在切换页面函数内按照当前页面中的`Link`元素数量被重新赋值
#### Link * LinksArr
在`variable.h`中声明，存储页面中所有`Link`类型的元素的数组，当某个页面要被渲染时将该页面中的所有`Link`放到一个数组后把数组地址赋给该变量，再由`renderElements`函数渲染到页面中
#### int textsArrLen
在`variable.h`中声明， 数组`TextsArr`的长度，即当前渲染的页面中的所有`Text`类型的元素的数量，初始值为0，一般会在切换页面函数内按照当前页面中的`Text`元素数量被重新赋值
#### Text * TextsArr
在`variable.h`中声明，存储页面中所有`Link`类型的元素的数组，当某个页面要被渲染时将该页面中的所有`Text`放到一个数组后把数组地址赋给该变量，再由`renderElements`函数渲染到页面中
#### int inputBoxsArrLen
在`variable.h`中声明， 数组`TextsArr`的长度，即当前渲染的页面中的所有`InputBox`类型的元素的数量，初始值为0，一般会在切换页面函数内按照当前页面中的`InputBox`元素数量被重新赋值
#### InputBox * InputBoxsArr
在`variable.h`中声明，存储页面中所有`InputBox`类型的元素的数组，当某个页面要被渲染时将该页面中的所有`InputBox`放到一个数组后把数组地址赋给该变量，再由`renderElements`函数渲染到页面中
#### string currentUser
在`variable.h`中声明，当前登录的用户的用户名，初始值为空，一般会在登录后被重新赋值。在普通用户更改自己的密码，找出当前用户的所有借阅记录时会用到该变量
#### SchoolUserList hnuer
在`variable.h`中声明，实例化一个`SchoolUserList`类，即用户列表类，所有对用户的操作将用到该变量
#### Library lib
在`variable.h`中声明，实例化一个`Library`类，即图书馆类，所有对图书的操作将用到该变量
#### Logs logs
在`variable.h`中声明，实例化一个`Logs`类，即记录类，所有对借阅记录的操作将用到该变量

### 全局函数（部分）
#### void gotoxy(short int row, short int col)
在`util.h`中声明，移动光标到第`row`行，第`col`列
#### int changeColor(int r, int g, int b)
在`util.h`中声明，更改控制台输出的颜色，当页面中的一个输入框获取焦点时会用该函数将输出颜色改为一个灰色后重新渲染页面，而达到输入框聚焦时出现一个遮挡层的效果，参数`r`,`g`,`b`分别为一个颜色的RGB值
#### void printChar(int n, char c)
在`util.h`中声明，输出`n`次`c`，一般会在清除屏幕中的某一部分时用到该函数，以输出空格的方式达到清屏效果
#### void renderFramework()
在`util.h`中声明，渲染框架，即标题，右边框，底部边框和导航栏上下边框等
#### void renderElements()
在`util.h`中声明，分别调用三个函数，`renderLinks()`渲染页面中所有`Link`元素，`renderTexts()`渲染页面中所有`Text`元素，`renderInputBoxs()`渲染页面中所有`InputBoxs`元素
#### void clearElements()
在`util.h`中声明，用于清屏（清掉除框架和信息外的所有内容)
#### void renderModel(bool isFocus)
在`util.h`中声明，产生一个遮挡层效果，参数`isFocus`为`true`是产生遮挡层，为`false`时关闭遮挡层，当一个输入框获取焦点时调用这个函数，原理是更改控制台输出颜色后重新输出除当前输入框外的所有元素
#### void msg(string str | int n)
在`util.h`中声明，在页面左下角打印一些信息
#### void lunch_listener()
在`listener.h`中声明，启动监听页面中的监听事件，发现页面中的某个`Link`类或`InputBox`类点击时调用其`click`函数，原理时得到鼠标在控制台点击的坐标，再遍历每个可点击的元素，判断鼠标点击的坐标是否在该元素的身上
#### void click_XXX(const Link & self, int row, int col)
一般会在`page_[admin | user]_XXX.h`文件中声明若干个，表示页面中`Link`类型元素的点击事件，一般功能不相同的每个`Link`类型的实例都会有自己独有的点击事件，当通过`Link`类的构造函数实例化一个`Link`类时将该函数作为实参传给`Link`的构造函数，当`listener`调用某个`Link`的`click`函数时在函数体内作为回调函数调用该函数

### 类（部分）

#### Book 类
图书类，描述一本书
1. 构造函数
    - Book() // 默认构造
    - Book(string bookName, string bookAuthor, string bookISBN, string bookType) // 有参构造
2. 公共数据成员
    - string name; // 图书名称
    - string author; // 作者
    - string ISBN; // ISBN，作为key，一旦输入不可修改且不可重复录入 
    - string type; // 分类号

#### Log 类
记录类，描述一条借阅记录
1. 构造函数
    - Log() // 默认构造
    - Log(string logUname, string logISBN, int logState) // 有参构造
2. 公共数据成员
    - string username; // 借阅图书的用户名
    - string ISBN; // 借阅的图书的ISBN
    - int state; // 借阅状态，0表示还没还，1表示已经还回去了

#### SchoolUser 类
学校用户类，描述个用户
1. 构造函数
    - SchoolUser() // 默认构造
    - SchoolUser(string uname, string pwd = "123456") // 有参构造
2. 公共数据成员
    - string password; // 用户名
    - string username; // 密码
3. 公共成员函数
    - bool checkPwd(string pwd)
    // 验证密码是否正确，正确返回true，不正确返回false
    - void changePwd(string pwd)
    // 更改密码，会在用户列表数据库文件中更新数据

#### Library 类
图书馆类，管理所有的图书
1. 构造函数
    - Library() // 默认构造
2. 私有数据成员
    - Book * booksArr; // 图书数组
3. 私有数据成员
    - int totalCount; // 图书总数
    - Book \** currentPageBooksArr; // 当前页图书数组 
    - Book \** tempBooksArr; // 临时数组，搜索时使用 
    - int tempBooksArrLen; 
    - int updatePageMode; // 换页模式：0表示从总表中切换，1表示从当前结果中切换 
    - int currentPageIndex; // 当前在页面中展示的页面index
    - int currentPageCount; // 当前页面中展示的图书数量 
3. 公共成员函数
    - void readDataFromFile()
    // 读取文件中的图书数据并更新到属性booksArr中
    - int searchBook(Book book)
    // 搜索图书，接受一个`Book`类型的参数，按照该`Book`的属性筛选出`booksArr`中相应的数据后把它们保存到`tempBooksArr`中，并按照搜索内容切换换页模式`updatePageMode`，没有找到任何符合条件的内容时返回0，找到了就返回找到的数据数量
    - string getBookNameByISBN(string ISBN)
    // 通过ISBN拿到图书名称，主要用于借阅记录页面
    - int updateCurrentPage(int pageIndex, int count = 10)
    切换页面，`pageIndex`表示跳转到第几页，`count`表示每页显示几条记录，按照参数的内容更新`currentPageBooksArr`的内容，再由页面负责渲染到页面中
    - int getTotalPageCount(int count = 10) 
    // 获取总页数，返回每页展示`count`条数据时话共可以分多少页
    - void removeBook(int index)
    // 删除图书，传入`currentPageBooksArr`中的`index`，删除直接从数据文件中删除
    - int addBook(Book book)
    // 新增图书，传入一个`Book`类型，新增成功返回当前页图书数量 ,失败了返回-1，直接将图书信息写入到数据文件
    - int modifyBook(Book book)
    // 修改图书，修改成功返回当前页图书数量，失败了返回-1，一般失败的原因为ISBN不存在
    
#### Logs 类
借阅记录们类，管理所有的记录
1. 构造函数
    - Logs() // 默认构造
2. 私有数据成员
    - Log * logsArr; // 记录数组
3. 私有数据成员
    - int totalCount; // 记录总数
    - Log \** currentPageLogsArr; // 当前页记录数组 
    - Log \** tempLogsArr; // 临时数组，文件读取完成后请把该用户的所有记录找出来放到这个数组中
    - int tempLogsArrLen; 
    - int currentPageIndex; // 当前在页面中展示的页面index
    - int currentPageCount; // 当前页面中展示的记录数量 
3. 公共成员函数
    - void readDataFromFile()
    // 读取文件中的记录数据并更新到属性logsArr中
    - int searchLogByISBN(string ISBN)
    // 通过条件查找，返回找到的数量，没找到就是0
    - int updateCurrentPage(int pageIndex, int count = 10)
    切换页面，`pageIndex`表示跳转到第几页，`count`表示每页显示几条记录，按照参数的内容更新`tempLogsArr`的内容，再由页面负责渲染到页面中
    - int getTotalPageCount(int count = 10) 
    // 获取总页数，返回每页展示`count`条数据时话共可以分多少页
    - int borrowBook(string ISBN)
    // 借阅图书，传入ISBN，用户默认为当前用户，借阅失败返回-1，该用户以借阅该书并尚未归还时会借阅失败
    - int returnBook(string ISBN)
    // 归还图书
    
#### SchoolUserList 类
学校用户们类，管理所有的用户
1. 构造函数
    - SchoolUserList() // 默认构造
2. 私有数据成员
    - SchoolUser * usersArr; // 用户数组
3. 私有数据成员
    - int totalCount; // 用户总数
    - SchoolUser \** currentPageUsersArr; // 当前页用户数组 
    - int currentPageIndex; // 当前在页面中展示的页面index
    - int currentPageCount; // 当前页面中展示的用户数量 
3. 公共成员函数
    - void readDataFromFile()
    // 读取文件中的记录数据并更新到属性usersArr中
    - int searchUserByUname(string uname)
    // 通过用户名找到唯一的用户，找到了返回1，未找到返回0;
    - int updateCurrentPage(int pageIndex, int count = 10)
    切换页面，`pageIndex`表示跳转到第几页，`count`表示每页显示几条记录，按照参数的内容更新`tempLogsArr`的内容，再由页面负责渲染到页面中
    - int getTotalPageCount(int count = 10) 
    // 获取总页数，返回每页展示`count`条数据时话共可以分多少页
    - int userLogin(string username, string pwd)
    // 用户登录,-1该用户不存在，0密码不正确，1登录成功 
    - int userChangePwd(string username, string pwd, string newPwd)
    // 修改密码，-1输入的当前密码不正确，1修改成功
    -  void resetPassword(int index)
    // 重置密码，传入currentPageUsersArr中的index
    - void removeUser(int index)
    // 删除用户，传入currentPageUsersArr中的index 
    - int addUserByUname(string uname)
    // 新增用户，新增成功返回当前页用户数量 ,失败了返回-1 