import os
import re

def format_cs_file(path):
    with open(path, "r", encoding="utf-8") as f:
        lines = f.readlines()

    new_lines = []
    i = 0
    n = len(lines)

    # 1. Handle top comment block
    while i < n and lines[i].strip().startswith("//"):
        if lines[i].strip().lower() != "echo is off.":
            new_lines.append(lines[i].rstrip() + "\n")
        i += 1
    if i < n and lines[i].strip() != "":
        new_lines.append("\n")  # exactly one blank line after comment

    # 2. Handle using block
    while i < n and lines[i].strip().startswith("using "):
        if lines[i].strip().lower() != "echo is off.":
            new_lines.append(lines[i].rstrip() + "\n")
        i += 1
    if i < n and lines[i].strip() != "":
        new_lines.append("\n")  # exactly one blank line after last using

    # 3. Append rest of file unchanged, skipping "ECHO is off."
    while i < n:
        if lines[i].strip().lower() != "echo is off.":
            new_lines.append(lines[i])
        i += 1

    # Write back
    with open(path, "w", encoding="utf-8") as f:
        f.writelines(new_lines)

def format_cs_folder(folder):
    for root, dirs, files in os.walk(folder):
        for file in files:
            if file.endswith(".cs"):
                path = os.path.join(root, file)
                format_cs_file(path)
                print(f"Formatted: {path}")

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Usage: python format_cs.py <folder>")
    else:
        format_cs_folder(sys.argv[1])
