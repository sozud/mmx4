import os
import argparse
from pathlib import Path
import sys
from tabulate import tabulate
import re
import concurrent.futures
import json
import requests
import sys
import zipfile
from io import BytesIO
import difflib

def are_strings_similar(str1, str2, threshold=0.4):
    similarity = difflib.SequenceMatcher(None, str1, str2).ratio()
    return similarity >= threshold

zip_cache = {}

def get_asm(slug):
    if slug in zip_cache:
        return zip_cache[slug]
    url = f'https://decomp.me/api/scratch/{slug}/export'
    response = requests.get(url)
    if response.status_code == 200:
        with zipfile.ZipFile(BytesIO(response.content)) as the_zip:
            zip_contents = the_zip.namelist()
            if 'target.s' in zip_contents:
                with the_zip.open('target.s') as file:
                    target_content = file.read().decode('utf-8')
                zip_cache[slug] = target_content
                return target_content
            else:
                print("target.s not found in the zip file")
    else:
        print(f"Failed to download the zip file: Status code {response.status_code}")
    return None

result_cache = {}

def fetch_all_results(url):
    if url in result_cache:
        return result_cache[url]

    results = []

    while url:
        response = requests.get(url)
        data = response.json()

        results.extend(data.get('results', []))

        url = data.get('next')

    result_cache[url] = results
    return results

def find_scratches(name, platform, local_asm=None, use_local=False):
    results = fetch_all_results(f"https://decomp.me/api/scratch?search={name}&page_size=100")

    best_result = None
    best_percent = 0

    for result in results:
        if not "name" in result:
            continue
        if not result["name"].startswith(name):
            continue
        if result["platform"] != platform:
            continue

        if use_local:
            remote_asm = get_asm(result['slug'])

            if not are_strings_similar(local_asm, remote_asm):
                continue

        score = result["score"]
        max_score = result["max_score"]
        percent = (max_score - score) / max_score

        if percent > best_percent:
            best_percent = percent
            best_result = result

    if best_result:
        return [f"https://decomp.me/scratch/{best_result['slug']}", round(best_percent, 3)]

    return None

parser = argparse.ArgumentParser(
    description="Create list of undecompiled functions and sort them by difficulty"
)

parser.add_argument(
    "--no-fetch",
    required=False,
    action="store_true",
    help="Disable fetching scratch links from decomp.me",
)

parser.add_argument(
    "--keywords",
    metavar="keyword",
    type=str,
    nargs="+",
    help="Only match paths with these keywords",
)

# look in asm files, read in the text and check for branches and jump tables
def get_asm_files(asm_path, og_files):
    files = []
    for path in Path(asm_path).rglob("*.s"):
        found = False
        for file, size in og_files:
            if Path(file) == path:
                found = True
        if not found:
            continue
        # ignore data
        if not "/nonmatchings" in str(path):
            continue
        f = open(f"{path}", "r")
        text = f.read()

        # check for different mips branch types and count
        branches = 0
        branch_types = [
            "b          ",
            "bczt       ",
            "bczf       ",
            "beq        ",
            "beqz       ",
            "bge        ",
            "bgeu       ",
            "bgez       ",
            "bgezal     ",
            "bgt        ",
            "bgtu       ",
            "bgtz       ",
            "ble        ",
            "bleu       ",
            "blez       ",
            "bgezal     ",
            "bltzal     ",
            "blt        ",
            "bltu       ",
            "bltz       ",
            "bne        ",
            "bnez       ",
            "j          ",
            "jal        ",
            "jalr       ",
            "jr         ",
        ]
        for branch in branch_types:
            branches = branches + text.count(branch)

        jump_table = "   "
        if "jpt_" in text or "jtbl_" in text:
            jump_table = "Yes"

        f = {"name": path, "text": text, "branches": branches, "jump_table": jump_table}

        files.append(f)

    return files

def find_wip(o):
    result = find_scratches(o[1], "ps1", o[8], True)

    if result:
        return {"link": result[0], "percent": result[1]}

    return None


def do_files(files, objtypes):
    args = parser.parse_args()
    asm_files = get_asm_files("asm/us", files)

    # sort by name, then number of branches, then length
    asm_files = sorted(asm_files, key=lambda x: (x["name"]))
    asm_files = sorted(asm_files, key=lambda x: (x["branches"]))
    asm_files = sorted(asm_files, key=lambda x: len(x["text"].split("\n")))

    if args.keywords and len(args.keywords):
        # filter based on keywords
        asm_files = [
            file
            for file in asm_files
            if any(keyword in str(file["name"]) for keyword in args.keywords)
        ]

    output = []

    for f in asm_files:
        name = str(f["name"])
        length = len(f["text"].split("\n"))
        branches = f["branches"]
        jump_table = f["jump_table"]

        if "/psxsdk/" in name:
            ovl_name = name.split("/")[5]  # grab library name
            func_name = os.path.splitext(os.path.basename(name))[0]
        elif "/weapon/" in name:
            # use the weapon name
            ovl_name = name.split("/")[4]  # grab library name
            func_name = os.path.splitext(os.path.basename(name))[0]
        else:
            matches = re.search(r"\/(\w+)\/nonmatchings\/\w+\/(\w+)\.s", name)
            if matches:
                ovl_name = matches.group(1)
                func_name = matches.group(2)
            else:
                ovl_name = ""
                func_name = name

        objtypes_str = [
            'gameobj',
            '',
            '',
            'effect',
            '',
            'misc',
            'QuadObj',
            '',
            'player',
            'background',
            'engine'
        ]
        pos = 0
        objtype = []
        for objlist in objtypes:
            for func in objlist:
                match = re.search(r"(?<=\/func_)([0-9A-Fa-f]+)(?=\.s)", name)
                if match:
                    hex_part = int(match.group(1), 16)
                    if hex_part == func:
                        objtype.append(f"{pos} {objtypes_str[pos]}")

            pos += 1

        objtype = ",".join(objtype)

        wip = ""
        wip_percentage = ""
        output.append(
            [
                ovl_name,
                func_name,
                length,
                branches,
                jump_table,
                objtype,
                wip,
                wip_percentage,
                f["text"] # local asm
            ]
        )

    if not args.no_fetch:
        # we are mostly waiting on IO so run in parallel
        with concurrent.futures.ThreadPoolExecutor() as executor:
            futures = [executor.submit(find_wip, o) for o in output]
            results = [f.result() for f in futures]

        # Update output with the results
        for i, o in enumerate(output):
            # keep the in-source results as definitive
            if results[i] != None:
                o[6] = results[i]["link"]
                o[7] = results[i]["percent"]

    # delete asm text
    for o in output:
        del o[8:]

    headers = ["Ovl", "Function", "Length", "Branches", "Jtbl", "Objtype", "WIP", "%"]
    print(tabulate(output, headers=headers, tablefmt="github"))


# Function to get the path of the file in the same directory as the script
def get_file_path(filename):
    script_dir = os.path.dirname(os.path.realpath(__file__))  # Directory of the script
    return os.path.join(script_dir, filename)

# Function to read hex numbers from the file
def read_hex_numbers(filename):
    file_path = get_file_path(filename)  # Get full path to the file
    with open(file_path, 'r') as file:
        return {int(line.strip(), 16) for line in file}

# Function to find matching files and sort them by size
def find_matching_files_sorted_by_size(directory, hex_numbers):
    matching_files = []
    for root, _, files in os.walk(directory):
        for filename in files:
            if filename.startswith("func_") and filename.endswith(".s"):
                hex_part = int(filename[5:13], 16)  # Extract XXXXXXXX part from func_XXXXXXXX.s
                if hex_part in hex_numbers:
                    file_path = os.path.join(root, filename)
                    file_size = os.path.getsize(file_path)
                    matching_files.append((file_path, file_size))
    
    # Sort files by size (smallest to largest)
    matching_files.sort(key=lambda x: x[1])

    return matching_files

def read_obj_list(filename):
    objtypes = []
    cur_objtype = 0
    file_path = get_file_path(filename)
    with open(file_path, 'r') as file:
        cur_list = []
        for line in file:
            if 'objType' in line:
                continue
            else:
                try:
                    cur_list.append(int(line.strip(), 16))
                except:
                    objtypes.append(cur_list)
                    cur_list = []
                    cur_objtype += 1
                    pass
    return objtypes

# Main function
def main():
    # Read hex numbers from output.txt in the same folder as this script
    hex_numbers = read_hex_numbers('mednafen_trace.txt')

    objtypes = read_obj_list('objtypes.txt')

    # Find matching files and sort them by size
    matching_files = find_matching_files_sorted_by_size('asm', hex_numbers)

    do_files(matching_files, objtypes)

if __name__ == "__main__":
    main()
