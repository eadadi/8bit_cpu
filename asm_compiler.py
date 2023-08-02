from struct import pack
import sys

"""
Load op-codes and prepare mapping
"""
with open("op_codes.h") as f:
    op_codes = f.read().split("\n")[1:-2]

op_codes = [code.strip() for code in op_codes]
op_codes = [code[:-1] for code in op_codes]

op_codes_map = {}
op_codes_rev_map = {}
for i,code in enumerate(op_codes):
    op_codes_map[code] = i
    op_codes_rev_map[i] = code

print(op_codes_map)
"""
Load assembly file and create program bytes

Assembly possible lines:
    CMD
    CMD,NUM
    SEQ_START  //during a sequence there are only chr:CHR or num:NUM
    SEQ_END
    STR_LINE // following it there is a string (without chr prefix)
    .ADDR:NUM //in addr ADDR put NUM, these type of lines must not follow by lines of previous type
"""
text = sys.argv[1]
print(f"processing {text}..",end=" ")
prog = []
with open(text) as fd:
    lines = fd.read().split("\n")
    i = 0
    while i < len(lines):
        line = lines[i]
        if line == "":
            break
        parts = line.split(",")
        if parts[0] == "STR_START":
            j = i+1
            s = lines[j]
            for c in s:
                prog.append(ord(c))
            prog.append(0)
            i = j
        elif parts[0] == "SEQ_START":
            j = i+1
            parts = lines[j]
            while parts != "SEQ_END":
                to_add = [v.strip() for v in parts.split(":")]
                if to_add[0] == "chr":
                    prog.append(ord(to_add[1]))
                elif to_add[0] == "num":
                    prog.append(int(to_add[1]))
                j+=1
                parts = lines[j]
            i = j
        elif parts[0][0] == ".":
            to_add = [v.strip() for v in parts[0][1:].split(":")]
            addr = int(to_add[0])
            val = int(to_add[1])
            for j in range(addr - len(prog)):
                prog.append(0)
            prog.append(val)
        else:
            prog.append(op_codes_map[parts[0]])
            if len(parts) == 1:
                i+=1
                continue
            prog.append(int(parts[1]))
        i+=1
prog = bytes(prog)

"""
Write program bytes to file
"""
with open("prog","wb") as f:
    f.write(prog)

print("done!")
