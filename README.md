# 台服伪简体工具包 (Pseudo-SC Toolkit)

## 下载地址

下载[最新版](https://github.com/nowar-fonts/Pseudo-SC/releases)工具包。

## 快速入门

1. 备份《魔兽世界》字体文件夹。
2. 打开 “台服伪简体工具包” 文件夹，将需要处理的字体文件拖动到 `一键生成(默认).bat` 或者 `一键生成(简化聊天字体).bat` 上，如果没有错误就会生成适合《魔兽世界》使用的 `Fonts` 文件夹。
   + 如果你使用[有爱字体家族](https://github.com/nowar-fonts)，推荐用 `ARKai_T.ttf`。别忘了先看看现成的 “[有爱黑体 伪简体](https://github.com/nowar-fonts/Nowar-Sans-Pseudo-SC)” 是否合适。
   + `一键生成(默认).bat` 直接把原始的字体文件复制给聊天字体，不做简化。
   + `一键生成(简化聊天字体).bat` 会简化聊天字体，可以让聊天框里的 NPC 对话、系统提示、拾取信息等也显示成简化字。但是同时也会把你输入的繁体字显示成简化字，可能导致你输入错误的字符，使得别人看起来简繁混乱。
3. 将 `Fonts` 文件夹移动到 `Wow.exe` 所在路径（`...\World of Warcraft\_retail_\` 或 `...\World of Warcraft\_classic_\`）下，即可完成字体替换。

## 特性

* 支持 TrueType 曲线字体（TrueType 或 OpenType/TT，扩展名通常为 `.ttf`）和 PostScript 曲线字体（OpenType/CFF，扩展名通常为 `.otf`）。
* 可以（但不推荐！）处理简体版字体（GB 2312 字符集），该工具包会把能找到对应简化字的繁体字码位补全。
  + 处理简体版字体需要使用 `一键生成(简化聊天字体).bat`，否则聊天字体会出现大量缺字问题。

## 编译和运行

### 编译

用 GCC 或 Clang
```bash
g++ src/pseudo-sc.cpp src/iostream.cpp -Isrc/ -std=c++2a -O2 -o pseudo-sc
```

### 运行（需要 [otfcc](https://github.com/caryll/otfcc)）

```bash
otfccdump 待处理的字体.ttf -o base.otd
./pseudo-sc base.otd
otfccbuild base.otd -O2 -o 生成的字体.ttf
```

然后按照《魔兽世界》客户端的字体文件命名规则进行复制和重命名即可。

## 感谢

[Belleve Invis](https://github.com/be5invis) 和[李阿玲](https://github.com/clerkma)编写的 [otfcc](https://github.com/caryll/otfcc) 用于解析和生成 OpenType 字体文件。

[Niels Lohmann](https://github.com/nlohmann) 的 [json](https://github.com/nlohmann/json) 库提供了非常漂亮的 C++ JSON 接口。本工具使用了修改版的 JSON 库，容许非标准编码的字符。

“繁—简” 转换规则来自[郭家寶](https://github.com/BYVoid)的 [Open Chinese Convert](https://github.com/BYVoid/OpenCC) 项目。
