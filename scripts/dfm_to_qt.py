#!/usr/bin/env python3
"""Convert the Borland C++ Builder (VCL) .dfm form files to Qt-friendly files.

This is a one-off migration tool, kept for reference.

For every form it:
  * extracts every TImage bitmap (Picture.Data) to a PNG file in
    code/resources/<FormName>/<ImageName>.png
  * writes code/ui/Ui<FormName>.h, a header with a struct that creates one
    'Image' (see code/UnitImage.h) per TImage, with the same name, position,
    size and flags as in the .dfm file
  * writes the text of TRichEdit controls to code/resources/<FormName>/<Name>.txt
Finally it writes code/resources/resources.qrc

Usage: python3 scripts/dfm_to_qt.py code/*.dfm
"""
import io
import os
import re
import sys

from PIL import Image as PilImage


class Obj:
    def __init__(self, name, cls):
        self.name = name
        self.cls = cls
        self.props = {}
        self.children = []


def tokenize_string(s):
    """Parse a Delphi string expression like 'abc'#232'def' + 'ghi'."""
    out = []
    i = 0
    while i < len(s):
        c = s[i]
        if c == "'":
            j = i + 1
            buf = []
            while True:
                if s[j] == "'":
                    if j + 1 < len(s) and s[j + 1] == "'":
                        buf.append("'")
                        j += 2
                        continue
                    break
                buf.append(s[j])
                j += 1
            out.append("".join(buf))
            i = j + 1
        elif c == "#":
            m = re.match(r"#(\d+)", s[i:])
            out.append(chr(int(m.group(1))))
            i += len(m.group(0))
        else:
            i += 1  # whitespace or '+'
    return "".join(out)


def parse(path):
    with open(path, encoding="latin-1") as f:
        lines = [l.rstrip("\n") for l in f]
    stack = []
    root = None
    i = 0
    while i < len(lines):
        line = lines[i].strip()
        i += 1
        if not line:
            continue
        m = re.match(r"(object|inherited|inline) (\w+): (\w+)", line)
        if m:
            o = Obj(m.group(2), m.group(3))
            if stack:
                stack[-1].children.append(o)
            else:
                root = o
            stack.append(o)
            continue
        if line == "end":
            stack.pop()
            continue
        m = re.match(r"([\w.]+) = (.*)", line)
        if not m:
            continue
        key, val = m.group(1), m.group(2)
        if val == "{":
            hexdata = []
            while True:
                l = lines[i].strip()
                i += 1
                if l.endswith("}"):
                    hexdata.append(l[:-1])
                    break
                hexdata.append(l)
            stack[-1].props[key] = bytes.fromhex("".join(hexdata))
        elif val == "(":
            items = []
            cur = ""
            while True:
                l = lines[i].strip()
                i += 1
                end = l.endswith(")") and not l.endswith("')") or l == ")"
                if l.endswith("')"):
                    l = l[:-1]
                    end = True
                elif end:
                    l = l[:-1]
                cur += l
                if not cur.rstrip().endswith("+") and cur.strip():
                    items.append(tokenize_string(cur))
                    cur = ""
                if end:
                    break
            stack[-1].props[key] = items
        elif val.startswith("'") or val.startswith("#"):
            while val.rstrip().endswith("+"):
                val += lines[i].strip()
                i += 1
            stack[-1].props[key] = tokenize_string(val)
        elif val == "":
            # Multi-line string continuation
            val = ""
            while True:
                l = lines[i].strip()
                i += 1
                val += l
                if not l.endswith("+"):
                    break
            stack[-1].props[key] = tokenize_string(val)
        else:
            stack[-1].props[key] = val
    return root


def walk(o, parent_names=()):
    yield o, parent_names
    for c in o.children:
        yield from walk(c, parent_names + (o.name,))


def bitmap_from_picture_data(data):
    # Picture.Data = <len byte><class name><uint32 size><bitmap file>
    n = data[0]
    cls = data[1 : 1 + n].decode("ascii")
    assert cls == "TBitmap", cls
    size = int.from_bytes(data[1 + n : 5 + n], "little")
    bmp = data[5 + n : 5 + n + size]
    return PilImage.open(io.BytesIO(bmp)).convert("RGB")


def cpp_string(s):
    return '"' + s.replace("\\", "\\\\").replace('"', '\\"') + '"'


def main(paths):
    code_dir = os.path.dirname(os.path.abspath(paths[0]))
    res_dir = os.path.join(code_dir, "resources")
    ui_dir = os.path.join(code_dir, "ui")
    os.makedirs(res_dir, exist_ok=True)
    os.makedirs(ui_dir, exist_ok=True)
    qrc_files = []
    for path in sorted(paths):
        if os.path.basename(path) == "ProjectSimStagecraft.dfm":
            continue  # Duplicate of UnitFormSimStagecraftMenu.dfm
        root = parse(path)
        form = root.name
        form_dir = os.path.join(res_dir, form)
        os.makedirs(form_dir, exist_ok=True)
        members = []
        for o, parents in walk(root):
            if o is root:
                continue
            tab = next((p for p in reversed(parents) if p.startswith("TabSheet")), "")
            if o.cls == "TImage":
                p = o.props
                png = ""
                if "Picture.Data" in p:
                    img = bitmap_from_picture_data(p["Picture.Data"])
                    rel = f"{form}/{o.name}.png"
                    img.save(os.path.join(res_dir, rel), optimize=True)
                    qrc_files.append(rel)
                    png = ":/" + rel
                members.append(
                    "  Image * const {n} = Add({name}, {png}, {l}, {t}, {w}, {h}, {tr}, {vis}, {auto}); //{tab}".format(
                        n=o.name,
                        name=cpp_string(o.name),
                        png=cpp_string(png),
                        l=p.get("Left", "0"),
                        t=p.get("Top", "0"),
                        w=p.get("Width", "0"),
                        h=p.get("Height", "0"),
                        tr="true" if p.get("Transparent") == "True" else "false",
                        vis="false" if p.get("Visible") == "False" else "true",
                        auto="true" if p.get("AutoSize") == "True" else "false",
                        tab=tab or "form",
                    )
                )
            elif o.cls == "TRichEdit":
                rel = f"{form}/{o.name}.txt"
                with open(os.path.join(res_dir, rel), "w", encoding="utf-8") as f:
                    f.write("\n".join(o.props.get("Lines.Strings", [])) + "\n")
                qrc_files.append(rel)
        cw = root.props.get("ClientWidth", root.props.get("Width", "0"))
        ch = root.props.get("ClientHeight", root.props.get("Height", "0"))
        caption = root.props.get("Caption", "")
        header = os.path.join(ui_dir, f"Ui{form}.h")
        with open(header, "w", encoding="utf-8") as f:
            f.write(
                "// Generated by scripts/dfm_to_qt.py from {src}\n"
                "// The original VCL form held one TImage per member below\n"
                "#ifndef Ui{form}H\n#define Ui{form}H\n\n"
                '#include "UnitImage.h"\n\n'
                "struct Ui{form} : public ImageStore\n{{\n"
                "  static constexpr int DesignClientWidth = {cw};\n"
                "  static constexpr int DesignClientHeight = {ch};\n"
                "  static constexpr const char * DesignCaption = {cap};\n"
                "{members}\n"
                "}};\n\n#endif\n".format(
                    src=os.path.basename(path),
                    form=form,
                    cw=cw,
                    ch=ch,
                    cap=cpp_string(caption),
                    members="\n".join(members),
                )
            )
        print(f"{form}: {len(members)} images")
    with open(os.path.join(res_dir, "resources.qrc"), "w") as f:
        f.write("<RCC>\n  <qresource prefix=\"/\">\n")
        for r in sorted(qrc_files):
            f.write(f"    <file>{r}</file>\n")
        f.write("  </qresource>\n</RCC>\n")


if __name__ == "__main__":
    main(sys.argv[1:])
