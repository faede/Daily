



# 窗口

CTRL-W j
光标切换到下一个窗口。
CTRL-W k
光标切换到上一个窗口。
CTRL-W h
光标切换到左边窗口。如果左边没有窗口，保持在当前窗口不变。
CTRL-W l
光标切换到右边窗口。
CTRL-W w
在各个窗口之间来回切换。每输入一次，切换一个窗口。不停输入，可以遍历所有窗口。在只有两个窗口时很方便来回切换。

# VSOCDE

### 选中操作多行：

`Shift+Alt+Down/Up`
1

### 快速删除整行

`ctrl+shift+k`
1

### 下一行行首 /  上一行行首

`Ctrl+Enter / Ctrl+Shift+Enter`

手动设置：

### 复制当行到下一行/上一行

`Ctrl+Shift+DownArrow/UpArrow`

https://code.visualstudio.com/docs/getstarted/tips-and-tricks

### Redo:

`Ctrl+Shift+z/Shift+Y`

### Go to Symbol in File[#](https://code.visualstudio.com/docs/getstarted/tips-and-tricks#_go-to-symbol-in-file)

Keyboard Shortcut: Ctrl+Shift+O

### Go to Symbol in Workspace[#](https://code.visualstudio.com/docs/getstarted/tips-and-tricks#_go-to-symbol-in-workspace)

Keyboard Shortcut: Ctrl+T

### Open Markdown preview[#](https://code.visualstudio.com/docs/getstarted/tips-and-tricks#_open-markdown-preview)

In a Markdown file, use

Keyboard Shortcut: Ctrl+Shift+V

### Select current line[#](https://code.visualstudio.com/docs/getstarted/tips-and-tricks#_select-current-line)

Keyboard Shortcut: Ctrl+L

### Select current line[#](https://code.visualstudio.com/docs/getstarted/tips-and-tricks#_select-current-line)

Keyboard Shortcut: Ctrl+L

## IntelliSense[#](https://code.visualstudio.com/docs/getstarted/tips-and-tricks#_intellisense)

Ctrl+Space to trigger the Suggestions widget.

### Go to Definition[#](https://code.visualstudio.com/docs/getstarted/tips-and-tricks#_go-to-definition)

Select a symbol then type F12. Alternatively, you can use the context menu or Ctrl+click (Cmd+click on macOS).

### Go to References[#](https://code.visualstudio.com/docs/getstarted/tips-and-tricks#_go-to-references)

Select a symbol then type Shift+F12. Alternatively, you can use the context menu.

### Find All References view[#](https://code.visualstudio.com/docs/getstarted/tips-and-tricks#_find-all-references-view)

Select a symbol then type Shift+Alt+F12 to open the References view showing all your file's symbols in a dedicated view.

alt+i 上 alt+k 下 alt+j 左 alt+l 右 alt+u 行首 alt+o 行末

### Rename Symbol[#](https://code.visualstudio.com/docs/getstarted/tips-and-tricks#_rename-symbol)

Select a symbol then type F2. Alternatively, you can use the context menu.

### Search and modify[#](https://code.visualstudio.com/docs/getstarted/tips-and-tricks#_search-and-modify)

Besides searching and replacing expressions, you can also search and reuse parts of what was matched, using regular expressions with capturing groups. Enable regular expressions in the search box by clicking the **Use Regular Expression** `.*` button (Alt+R) and then write a regular expression and use parenthesis to define groups. You can then reuse the content matched in each group by using `$1`, `$2`, etc. in the Replace field.





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
| CTRL + L:            | 清空屏幕                                                |
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