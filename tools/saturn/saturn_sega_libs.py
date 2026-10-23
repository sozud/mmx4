import re

_HEX = re.compile(r"[Hh]'([0-9A-Fa-f]+)")
_FMOV = re.compile(r'(?<![\w])FMOV\.S(\s*)(FR\d+)\s*,\s*(FR\d+)', re.IGNORECASE)
_SECTION = re.compile(r'\.SECTION\s+([^,\s]+)\s*(?:,\s*(CODE|DATA)\s*(?:,\s*ALIGN\s*=\s*(\d+))?)?\s*$', re.IGNORECASE)
_DATA = re.compile(r'\.DATA\.([BWL])\s+(.*)$', re.IGNORECASE)


GNU_SECTIONS = {'P': '.text', 'C': '.section .rodata', 'D': '.data', 'B': '.bss'}
_LITERAL = re.compile(r'(mov\.l\s+)#([^,]+),(\s*r\d+)', re.IGNORECASE)


def shc_to_gas(text):
    out, pool, labels = [], [], 0

    def flush():
        if pool:
            out.append('.balign 4')
            for label, value in pool:
                out.append(f'{label}: .long {value}')
            pool.clear()
    for raw in text.replace('\x1a', '').splitlines():
        line = raw.rstrip('\r')
        if ';' in line:
            code, comment = line.split(';', 1)
            line = code + (' !' + comment if comment else '')
        stripped = line.strip()
        if not stripped:
            out.append('')
            continue
        upper = stripped.upper()
        if upper.startswith(('.EXPORT', '.IMPORT')) and len(stripped) > 7 and stripped[7].isspace():
            out.append(('.globl ' if upper.startswith('.EXPORT') else '.extern ') + stripped[7:].strip())
            continue
        if upper == '.POOL':
            flush()
            continue
        m = _SECTION.match(stripped)
        if m:
            flush()
            name, kind, align = m.groups()
            code = (kind or '').upper() == 'CODE' or (kind is None and name.upper() == 'P')
            gnu = GNU_SECTIONS.get(name.upper())
            if gnu:
                out.append(gnu)
            else:
                out.append(f'.section {name},"{"ax" if code else "aw"}",@progbits')
            if align:
                out.append(f'.balign {align}')
            continue
        m = _DATA.match(stripped)
        if m:
            size, value = m.groups()
            value = value.split('!', 1)[0].strip()
            out.append({'B': '.byte ', 'W': '.word ', 'L': '.long '}[size.upper()] + _HEX.sub(r'0x\1', value))
            continue
        m = re.match(r'\.MACRO\s+(\w+)\s*(.*)$', stripped, re.IGNORECASE)
        if m:
            out.append(f'.macro {m.group(1)} {m.group(2).strip()}'.rstrip())
            continue
        if upper == '.ENDM':
            out.append('.endm')
            continue
        m = re.match(r'\.(GLOBAL|ALIGN)\s+(.*)$', stripped, re.IGNORECASE)
        if m:
            out.append(('.global ' if m.group(1).upper() == 'GLOBAL' else '.balign ') + _HEX.sub(r'0x\1', m.group(2).strip()))
            continue
        if upper == '.END' or upper.startswith('.END '):
            flush()
            continue
        if stripped.startswith('.'):
            raise ValueError('unsupported SHC directive: ' + line)
        literal = _LITERAL.search(line)
        if literal:
            label = f'.Lshc_pool_{labels}'
            labels += 1
            pool.append((label, _HEX.sub(r'0x\1', literal.group(2).strip())))
            line = line[:literal.start()] + f'{literal.group(1)}{label},{literal.group(3)}' + line[literal.end():]
        out.append(_HEX.sub(r'0x\1', _FMOV.sub(r'FMOV\1\2,\3', line)))
    flush()
    return '\n'.join(out) + '\n'
