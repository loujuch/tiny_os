# 小型32位操作系统

## 系统结构

### mbr

#### 功能

加载loader与kernel进入内存，将程序控制权交给loader

### loader

作用如下：

1. 设置GDT，进入保护模式

2. 设置页表项、页目录项，开启页式内存管理

3. 解析内核，将其转化为可执行指令流

4. 获取物理内存情况

### kernel

## 附件

### 常用硬件使用

#### 硬盘

使用PATA接口的用法，磁盘分为两个通道，每个通道挂载两个磁盘

|Primary端口|Secondary端口|读操作用途|写操作用途|备注|
|---|---|---|---|---|
|0x1F0|0x170|输出数据|输入数据|表中唯一的16位寄存器，其他寄存器均为8位|
|0x1F1|0x171|错误码|写命令的参数||
|0x1F2|0x172|要读的扇区数|要写的扇区数|一个扇区大小为512B<br>类似汇编`loop`命令，指定为0时操作数不是0<br>若中途出现错误，保存未完成数量|
|0x1F3|0x173|LBA码低8位|LBA码低8位||
|0x1F4|0x174|LBA码中间8位|LBA码中间8位||
|0x1F5|0x175|LBA码高8位|LBA码高8位||
|0x1F6|0x176|device|device|0-3位：LBA最高4位<br>4位：为0操作主盘，为1操作从盘<br>6位：为0使用CHS模式，为1使用LBA模式<br>5位、7位：MBS位，固定为1|
|0x1F7|0x177|状态|命令|状态结构：0(有无错误)、3(是否完成准备/可读)、6(是否就绪)、7(是否忙)<br>常用命令：识别硬盘(0xEC)、读硬盘(0x20)、写硬盘(0x30)|