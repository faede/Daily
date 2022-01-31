

# VSOCDE

选中操作多行：

`Shift+Alt+Down/Up`
1
快速删除整行

`ctrl+shift+k`
1
下一行行首 /  上一行行首

`Ctrl+Enter / Ctrl+Shift+Enter`



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

