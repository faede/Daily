

# VSOCDE

选中操作多行：

`Shift+Alt+Down/Up`
1
快速删除整行

`ctrl+shift+k`
1
下一行行首 /  上一行行首

`Ctrl+Enter / Ctrl+Shift+Enter`

手动设置：

复制当行到下一行/上一行

`Ctrl+Shift+DownArrow/UpArrow`

Redo:

`Ctrl+Shift+z/Shift+Y`



alt+i 上 alt+k 下 alt+j 左 alt+l 右 alt+u 行首 alt+o 行末

perference -> keyboard shortcuts

```
alt+i 上
alt+k 下
alt+j 左
alt+l 右
alt+u 行首
alt+o 行末
// Place your key bindings in this file to override the defaultsauto[]
[
    {
      "key": "alt+i",
      "command": "cursorUp",
      "when": "textInputFocus"
    },
    {
      "key": "up",
      "command": "cursorUp",
      "when": "textInputFocus"
    },
    {
      "key": "alt+i",
      "command": "selectPrevSuggestion",
      "when": "suggestWidgetMultipleSuggestions && suggestWidgetVisible && textInputFocus"
    },
    {
      "key": "up",
      "command": "selectPrevSuggestion",
      "when": "suggestWidgetMultipleSuggestions && suggestWidgetVisible && textInputFocus"
    },

    {
      "key": "alt+k",
      "command": "cursorDown",
      "when": "textInputFocus"
    },
    {
      "key": "down",
      "command": "cursorDown",
      "when": "textInputFocus"
    },
    {
      "key": "alt+k",
      "command": "selectNextSuggestion",
      "when": "suggestWidgetMultipleSuggestions && suggestWidgetVisible && textInputFocus"
    },
    {
      "key": "down",
      "command": "-selectNextSuggestion",
      "when": "suggestWidgetMultipleSuggestions && suggestWidgetVisible && textInputFocus"
    },

    {
      "key": "alt+l",
      "command": "cursorRight",
      "when": "textInputFocus"
    },
    {
      "key": "right",
      "command": "cursorRight",
      "when": "textInputFocus"
    },

    {
      "key": "alt+j",
      "command": "cursorLeft",
      "when": "textInputFocus"
    },
    {
      "key": "left",
      "command": "cursorLeft",
      "when": "textInputFocus"
    },

    {
      "key": "alt+o",
      "command": "cursorEnd",
      "when": "textInputFocus"
    },
    {
      "key": "end",
      "command": "cursorEnd",
      "when": "textInputFocus"
    },

    {
      "key": "alt+u",
      "command": "cursorHome",
      "when": "textInputFocus"
    },
    {
      "key": "home",
      "command": "cursorHome",
      "when": "textInputFocus"
    }

]
  
  

```

# Terminal

| CTRL + ALT + T:      | 打开终端                                                |
| -------------------- | ------------------------------------------------------- |
| TAB:                 | 自动补全命令或文件名                                    |
| CTRL + SHIFT + V:    | 粘贴（Linux中不需要复制的动作，文本被选择就自动被复制） |
| CTRL + SHIFT + T:    | 新建标签页                                              |
| CTRL + D:            | 关闭标签页                                              |
| CTRL + L:            | 清楚屏幕                                                |
| CTRL + R + 文本:     | 在输入历史中搜索                                        |
| CTRL + A:            | 移动到行首                                              |
| CTRL + E:            | 移动到行末                                              |
| CTRL + C:            | 终止当前任务                                            |
| CTRL + Z:            | 把当前任务放到后台运行（相当于运行命令时后面加&）       |
| ~:                   | 表示用户目录路径                                        |
| Ctrl+Left-Arrow      | 光标移动到上一个单词的词首                              |
| Ctrl+Right-Arrow     | 光标移动到下一个单词的词尾                              |
| Ctrl+a               | 光标移动到开始位置                                      |
| Ctrl+e               | 光标移动到最末尾                                        |
| Ctrl+k               | 删除此处至末尾的所有内容                                |
| Ctrl+u               | 删除此处至开始的所有内容                                |
| Ctrl+r               | 查找历史命令                                            |
| Ctrl+b               | 向回移动光标                                            |
| Ctrl+f               | 向前移动光标                                            |
| Shift+Ctrl+T         | 打开新的标签页                                          |
| Shift+Ctrl+W         | 关闭标签页                                              |
| Shift+Ctrl+C         | 复制                                                    |
| Shift+Ctrl+V         | 粘贴                                                    |
| Alt+数字             | 切换至对应的标签页                                      |
| Shift+Ctrl+N         | 打开新的终端窗口                                        |
| Shift+Ctrl+Q         | 管壁终端窗口                                            |
| Shift+Ctrl+PgUp/PgDn | 左移右移标签页                                          |
| Ctrl+PgUp/PgDn       | 切换标签页                                              |
|                      |                                                         |
|                      |                                                         |
|                      |                                                         |
|                      |                                                         |
|                      |                                                         |
|                      |                                                         |
|                      |                                                         |
|                      |                                                         |
|                      |                                                         |
|                      |                                                         |