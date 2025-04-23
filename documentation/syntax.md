### 1. Headings

    # Heading 1 → <h1>

    ## Heading 2 → <h2>

    ... up to <h6>

### 2. Paragraphs

    Any line starting with a letter becomes a paragraph (<p>)

### 3. Bold, Italic, Strikethrough

    **bold** → <b>bold</b>

    *italic* → <i>italic</i>

    ~~strikethrough~~ → <s>strikethrough</s>

### 4. Code Blocks

    Triple backticks ``` to start/end code blocks

### 5. **Blockquotes**
- `> Quote` → `<blockquote>`
- Special blockquotes:
  - `> [!NOTE]` → `<blockquote class="NOTE">quote content below this line</blockquote>`

---

### 6. **Lists**

#### ➤ Unordered Lists
- `- item`, `* item`, `+ item` → `<ul><li>item</li></ul>`
- Indented with tab or spaces → nested `<ul>`

#### ➤ Ordered Lists
- `1. item`, `a. item` → `<ol start="1"><li>item</li></ol>`
- Supports nesting by indentation

---

### 7. **Links & Images**

#### ➤ Links
- `[text](url)` → `<a href="url">text</a>`

#### ➤ Images
- `![alt](path/to/image.jpg)` → `<img src="...">`

#### ➤ Videos
- If image URL ends in `.mp4`, `.ogg`, `.webm`, converts to `<video>` tag

#### ➤ YouTube
- If link contains `youtube.com` or `youtu.be`, creates an embedded `<iframe>`

---

### 8. **Footnotes/References**
- Inline: `[^1]` → `<a class="refLink" href="#ref1"><sup>1</sup></a>`
- Reference definitions:
  - `[^1]: http://example.com` → 
    ```html
    <cite id="ref1" class="ref">
      1: <a href="http://example.com">http://example.com</a>
    </cite>
    ```

---

### 9. **Slide Separators**
- `---`, `----`, `-----`, etc.
  - Used to separate slides
  - Controls nested `<div class="slide">` blocks

---

### 10. **Escape Characters**
- Escaped asterisk `\*` → `&#42;` (HTML-safe)

---

## 🛠️ CLI Options Supported

- `-h` / `--help`: Show help
- `-v` / `--version`: Show version
- `-t <n>` / `--tab <n>`: Number of spaces per tab
- `-r` / `--references`: Show reference page at end

---


