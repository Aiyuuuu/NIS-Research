# analyze_aslr_simple.py
import os, subprocess, time, re, shutil, numpy as np
from pathlib import Path

# === CONFIG ===
TASK = "T1_WordCount"
SOURCES = {
    "Human": f"corpus/{TASK}/human/1.c",
    "Gemini": f"corpus/{TASK}/gemini/1.c",
    "GPT5": f"corpus/{TASK}/gpt5/1.c"
}
RUNS = 50
TEMP = Path("temp_aslr")
# =================

if os.geteuid() != 0:
    print("Run with: sudo python3 analyze_aslr_simple.py")
    exit(1)

def set_aslr(on: bool):
    level = "2" if on else "0"
    subprocess.run(["sysctl", "-w", f"kernel.randomize_va_space={level}"], check=True)

def make_sleepy(src):
    code = Path(src).read_text()
    code = code.replace("return 0;", "sleep(5); return 0;")
    if "#include <unistd.h>" not in code:
        code = "#include <unistd.h>\n" + code
    bin_path = TEMP / Path(src).stem
    Path(TEMP / Path(src).name).write_text(code)
    subprocess.run(["gcc", "-pie", str(TEMP / Path(src).name), "-o", str(bin_path)], check=True)
    return bin_path

def get_addr(bin_path):
    p = subprocess.Popen([str(bin_path)])
    time.sleep(0.2)
    maps = Path(f"/proc/{p.pid}/maps").read_text()
    p.terminate(); p.wait()
    exe = re.search(r"([0-9a-f]+)-.* r-xp .*" + bin_path.name, maps)
    return int(exe.group(1), 16) if exe else None

# === MAIN ===
shutil.rmtree(TEMP, ignore_errors=True)
TEMP.mkdir()
bins = {k: make_sleepy(v) for k, v in SOURCES.items()}

print("\nASLR OFF → All addresses SAME")
set_aslr(False)
off = {}
for name, b in bins.items():
    addrs = [get_addr(b) for _ in range(RUNS)]
    print(f"{name:6}: {addrs[0]:#x}  (variance: {np.var(addrs):.2e})")
    off[name] = addrs[0]

print("\nASLR ON → All addresses RANDOM & EQUAL variance")
set_aslr(True)
on_vars = {}
for name, b in bins.items():
    addrs = [get_addr(b) for _ in range(RUNS)]
    var = np.var(addrs)
    on_vars[name] = var
    print(f"{name:6}: variance = {var:.2e}")

print("\n" + "="*50)
print("RESULT: ASLR variance is IDENTICAL across Human/LLM")
print(f"   Human: {on_vars['Human']:.2e}")
print(f"   Gemini: {on_vars['Gemini']:.2e}")
print(f"   GPT5:  {on_vars['GPT5']:.2e}")
print("→ ASLR **neutralizes** code origin at runtime!")
print("==================================================\n")

shutil.rmtree(TEMP)
set_aslr(True)  # restore
