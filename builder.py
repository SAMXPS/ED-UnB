

# I want to create a program that read C source files with includes and export a joint source file
# containing all the source code needed to send to the moodle online judge
import sys
import os
import re
 
def str_remove(strObj, start, stop, midle = ""):
    if len(strObj) > stop :
        strObj = strObj[0: start:] + midle + strObj[stop + 1::]
    return strObj

def get_imports(src):
    cp = src
    list = []
    ox = 0
    while (1):
        src = cp[ox:]
        idx = src.find("#include")
        if idx == -1:
            break
        src = src[idx:]
        idx2 = src.find("\n")
        ox += idx+idx2

        newvar = src.find("\"")

        if newvar == -1 or newvar > idx2:
            continue

        inc = src[newvar+1:]
        inc = inc[:inc.find("\"")]
        if len(inc) > 0:
            rep = "/*[Py-CBuilder] including file " + inc + "*/\n"
            cp = str_remove(cp, ox-idx2, ox, rep)
            ox += len(rep) - idx2
            list.append([ox, inc])
    return list, cp

def export_c_source(fname, trace = []):
    
    try:
        with open(fname, "r") as f:
            cpath = os.path.abspath(fname)
            if cpath not in trace:
                trace.append(cpath)
                source = f.read()
                imports, ns = get_imports(source)
                acc = 0 
                for inc in imports:
                    print("[INFO] Importing " + inc[1] + " from " + fname)
                    imp, trace = export_c_source(os.path.join(os.path.dirname(cpath), inc[1]), trace)
                    imp += "\n/*[Py-CBuilder] end of file " + inc[1] + "*/\n"
                    ns = ns[:inc[0]+acc] + imp + ns[inc[0]+acc:]
                    acc+= len(imp)

                return ns, trace
            else:
                return "/*[Py-CBuilder] duplicated include of " + fname + " ignored */", trace
    except IOError:
        print("[!] [Warning] Skiping unexsisting file: " + os.path.abspath(fname))
        return '', trace



if len(sys.argv) > 2:
    fromf = sys.argv[1]
    os.mkdir("export") 
    destf = "export/" + sys.argv[2]
    print("Exporting C-source " + fromf + " into " + destf)
    f = open(destf, 'w')
    exp = export_c_source(fromf)
    f.write(exp[0])
    print("Done.")

else:
    print("expected: python .\builder.py <file: from> <file: to>")
