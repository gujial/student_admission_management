# 学生信息管理系统技术文档

## 一、项目概述

本项目是一个基于 Qt 框架与 MySQL 数据库构建的学生信息管理系统。系统具备用户登录、注册、用户管理、学生信息增删改查等功能，主要面向校内教务管理员，实现对学生基本信息的统一管理。

---

## 二、开发环境

| 工具/框架 | 版本/说明                 |
| ----- | --------------------- |
| Qt    | 6.x       |
| 编程语言  | C++                   |
| 数据库   | MySQL                 |
| 构建系统  | CMake         |
| 操作系统  | Windows / Linux |

---

## 三、系统模块

### 1. 控制器模块（`controller`）

控制器类为系统的核心逻辑处理器，负责用户与学生的数据操作，包括数据库连接、数据校验、权限控制等。

#### 主要职责：

* 数据库连接管理
* 用户登录、注册、删除、修改
* 学生信息的增删改查
* 权限检查（如仅管理员可注册用户等）
* 用户类型管理

#### 数据结构：

* `user`：包含用户名、密码、邮箱、类型（type\_id）等属性。
* `student`：包含学号、姓名、出生日期、地址、院系、班级、性别等属性。

#### 权限控制：

调用 `utils::checkUserPermission(type_id)` 对当前登录用户权限进行检查，防止非法操作。

---

### 2. 数据库结构设计

#### 数据表：`user`

| 字段名      | 类型      | 说明     |
| -------- | ------- | ------ |
| username | VARCHAR | 用户名    |
| password | VARCHAR | 加密后的密码 |
| email    | VARCHAR | 唯一邮箱   |
| type\_id | INT     | 用户类型   |

#### 数据表：`user_type`

| 字段名        | 类型      | 说明     |
| ---------- | ------- | ------ |
| type\_id   | INT     | 用户类型编号 |
| type\_name | VARCHAR | 用户类型名称 |

#### 数据表：`student`

| 字段名        | 类型      | 说明      |
| ---------- | ------- | ------- |
| number     | VARCHAR | 学号（主键）  |
| name       | VARCHAR | 姓名      |
| birthday   | DATE    | 出生日期    |
| address    | VARCHAR | 地址      |
| department | VARCHAR | 院系      |
| classname  | VARCHAR | 班级      |
| gender     | ENUM    | 性别（男/女） |

---

## 四、功能说明

### 1. 用户登录

```cpp
void controller::userLogin(const QString &username, const QString &password);
```

* 检查用户名、密码格式
* 密码使用 `utils::md5()` 进行加密
* 成功登录后更新当前用户 `loggedInUser`

### 2. 用户注册

```cpp
void controller::userRegister(const QString &username, const QString &password, const QString &email, int type_id) const;
```

* 检查是否为管理员
* 校验邮箱、密码、用户名格式

### 3. 学生信息管理

* 增加：`addStudent(student)`
* 删除：`deleteStudent(const QString& studentNum)`
* 修改：`modifyStudent(const QString& studentNum, student newStudent)`
* 查询全部：`getStudents()`
* 查询单个：`getStudent(const QString& studentNum)`

### 4. 用户管理

* 获取用户：`getUser(const QString& email)`
* 修改邮箱、用户名、权限等信息：`modifyUser(...)`
* 修改密码：`modifyUserPassword(...)`
* 删除用户：`deleteUser(...)`

---

## 五、数据校验工具（`utils`）

为保证系统稳定性与数据规范性，使用 `utils` 工具类进行以下校验：

* `checkFormat()`：统一校验用户名、邮箱、密码格式
* `checkEmailFormat()` / `checkUsernameFormat()`：邮箱/用户名格式
* `checkStudentNameFormat()` / `checkStudentNumberFormat()` / `checkGenderFormat()`：学生数据规范性
* `checkUserPermission()`：是否有管理权限

---

## 六、UI 界面设计

* 使用 `QTableView` 展示学生信息表格
* 个别列使用 `QComboBox` 作为编辑器
* 支持行内编辑与保存
* 登录界面应限制未登录用户访问主功能页面

---

## 七、安全性设计

* 所有密码均通过 MD5 加密处理
* 权限控制集中在 controller 内部
* 采用预处理语句防止 SQL 注入攻击
* 禁止普通用户进行管理操作

---

## 八、运行步骤

1. 创建数据库及数据表，插入 `user_type` 类型数据
2. 修改构造函数传入的数据库连接信息
3. 构建并运行程序
4. 默认登录用户为 `"anonymous"`，权限最低
