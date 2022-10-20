# waaijidanc
此软件为“我爱记单词”项目辅助软件，可快速查询当前页面上各个单词的中文解释

原理：

采用www.iciba.com的词库，利用adb获取手机当前页面的截图，使用Tesseract-OCR识别图中单词，使用socket+http与www.iciba.com服务器沟通，使用jsoncpp解析传回的数据。

使用方法：

1.确认手机已和电脑连接并开启usb调试

2.打开软件，能在List of devices attached找到手机

3.进入 我爱记单词 并开始测试后按下任意键，程序运行，显示英文翻译

4.若出现 漏翻译、识别错误、或提示 json解析失败 字样，请尝试再次按下任意键，再次运行

目前已知bug：

1.程序无法正常使用右上角叉号关闭，需使用 taskkill /im waaijidanc.exe /f 命令关闭，此命令已包含在 close.bat 中

2.一些以l开头的单词在OCR时易被识别为 | 导致无法正常翻译

3.少数情况下C会被识别为o导致无法正常翻译

玩的愉快
