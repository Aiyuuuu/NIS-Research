# statistics.py
# Ghidra Jython script
# Now accepts an output directory argument

import json
import os
import re
import time
import sys

from ghidra.program.model.block import BasicBlockModel
from ghidra.util.task import ConsoleTaskMonitor
from ghidra.app.decompiler import DecompInterface

monitor = ConsoleTaskMonitor()

def get_output_dir():
    """
    Retrieves the output directory from script arguments.
    Falls back to a local 'metrics' folder if no arg is provided.
    """
    # getScriptArgs() is a Ghidra built-in function
    args = getScriptArgs() 
    if len(args) > 0:
        return args[0]
    else:
        # Fallback to current directory/metrics
        return os.path.join(os.getcwd(), "metrics")

def find_main_function(program):
    fm = program.getFunctionManager()
    it = fm.getFunctions(True)
    for f in it:
        try:
            if f.getName() == "main":
                return f
        except Exception:
            pass

    try:
        ep_sym = program.getSymbolTable().getPrimarySymbol(program.getEntryPoint())
        if ep_sym:
            f = fm.getFunctionAt(ep_sym.getAddress())
            if f:
                return f
    except Exception:
        pass

    try:
        it2 = fm.getFunctions(True)
        return it2.next()
    except Exception:
        return None

def count_blocks_and_edges(program, func):
    bbm = BasicBlockModel(program)
    it = bbm.getCodeBlocksContaining(func.getBody(), monitor)
    blocks = []
    while it.hasNext():
        try:
            blocks.append(it.next())
        except Exception:
            break
    nodes = len(blocks)
    edges = 0
    for b in blocks:
        try:
            dests = b.getDestinations(monitor)
            while dests.hasNext():
                dests.next()
                edges += 1
        except Exception:
            pass
    return nodes, edges

def decompile_function(program, func, timeout=60):
    decomp = DecompInterface()
    decomp.openProgram(program)
    res = decomp.decompileFunction(func, timeout, monitor)
    if not res or not res.decompileCompleted():
        return None, []
    try:
        decomp_text = res.getDecompiledFunction().getC()
    except Exception:
        decomp_text = None
    local_names = []
    try:
        hf = res.getHighFunction()
        lsmap = hf.getLocalSymbolMap()
        try:
            local_names = [s.getName() for s in lsmap.getSymbols()]
        except Exception:
            local_names = []
    except Exception:
        local_names = []
    return decomp_text, local_names

def metricify_text(text):
    if not text:
        return {"text_len":0,"var_count":0,"switch_count":0,"goto_count":0,"if_count":0,"while_count":0}
    s = text
    tokens = set(re.findall(r'\b(local_[0-9a-fA-F_]+|iVar[0-9]+|uVar[0-9]+|[A-Za-z_][A-Za-z0-9_]{1,40})\b', s))
    keywords = set([
        "if","else","for","while","switch","case","break","return",
        "int","char","void","long","unsigned","signed","static","struct","union",
        "printf","scanf","puts","getchar","putchar","main"
    ])
    tokens = set([t for t in tokens if t not in keywords])
    var_count = len(tokens)
    switch_count = len(re.findall(r'\bswitch\s*\(', s))
    goto_count = len(re.findall(r'\bgoto\b', s))
    if_count = len(re.findall(r'\bif\s*\(', s))
    while_count = len(re.findall(r'\bwhile\s*\(', s))
    return {
        "text_len": len(s),
        "var_count": var_count,
        "switch_count": switch_count,
        "goto_count": goto_count,
        "if_count": if_count,
        "while_count": while_count
    }

def safe_get_ghidra_version():
    try:
        ver = getScriptInfo().getApplicationVersion()
        if ver: return str(ver)
    except Exception: pass
    return "unknown"

def write_json(outpath, data):
    try:
        with open(outpath, "w") as fh:
            json.dump(data, fh, indent=2)
    except Exception as e:
        print("ERROR writing JSON to", outpath, ":", str(e))

def run():
    prog = currentProgram
    
    # 1. Get output directory from arguments
    outdir = get_output_dir()
    if not os.path.exists(outdir):
        try:
            os.makedirs(outdir)
        except Exception:
            pass

    # 2. Determine Filename
    binary_path = None
    try:
        binary_path = prog.getExecutablePath()
    except Exception:
        binary_path = str(prog.getName())

    basename = os.path.splitext(os.path.basename(binary_path))[0]
    outpath = os.path.join(outdir, basename + ".json")

    # 3. Find Main
    func = find_main_function(prog)
    if func is None:
        data = {"binary": binary_path, "basename": basename, "error": "no_function_found", "timestamp": time.time()}
        write_json(outpath, data)
        print("No function found; wrote error JSON to", outpath)
        return

    # 4. Calculate Metrics
    nodes, edges = count_blocks_and_edges(prog, func)
    cyclomatic = edges - nodes + 2 

    decomp_text, local_names = decompile_function(prog, func)
    text_metrics = metricify_text(decomp_text)

    ghidra_version = safe_get_ghidra_version()

    data = {
        "binary": binary_path,
        "basename": basename,
        "function": func.getName(),
        "nodes": nodes,
        "edges": edges,
        "cyclomatic_est": cyclomatic,
        "locals_count_decompiler": len(local_names),
        "decompiled_text_len": text_metrics["text_len"],
        "var_count_text_tokens": text_metrics["var_count"],
        "switch_count": text_metrics["switch_count"],
        "goto_count": text_metrics["goto_count"],
        "if_count": text_metrics["if_count"],
        "while_count": text_metrics["while_count"],
        "ghidra_version": ghidra_version,
        "timestamp": time.time()
    }

    write_json(outpath, data)
    print("Wrote metrics to", outpath)

if __name__ == "__main__":
    run()
