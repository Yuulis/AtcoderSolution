#!/usr/bin/env python3
"""Pattern 4: Fine-grained progress bar with true color gradient"""
import json, sys
if sys.platform == 'win32':
    sys.stdout.reconfigure(encoding='utf-8')

data = json.load(sys.stdin)

BLOCKS = ' ▏▎▍▌▋▊▉█'
R = '\033[0m'
DIM = '\033[2m'

def gradient(pct):
    if pct < 50:
        r = int(pct * 5.1)
        return f'\033[38;2;{r};200;80m'
    else:
        g = int(200 - (pct - 50) * 4)
        return f'\033[38;2;255;{max(g,0)};60m'

def bar(pct, width=10):
    pct = min(max(pct, 0), 100)
    filled = pct * width / 100
    full = int(filled)
    frac = int((filled - full) * 8)
    b = '█' * full
    if full < width:
        b += BLOCKS[frac]
        b += '░' * (width - full - 1)
    return b

def fmt(label, pct):
    p = round(pct)
    return f'{label} {gradient(pct)}{bar(pct)} {p}%{R}'

def get_used_percentage(payload, *path):
    current = payload
    for key in path:
        if not isinstance(current, dict):
            return None
        current = current.get(key)
    if not isinstance(current, dict):
        return None
    pct = current.get('used_percentage')
    if pct is None:
        pct = current.get('percent_used')
    if pct is None:
        used = current.get('used')
        limit = current.get('limit')
        if isinstance(used, (int, float)) and isinstance(limit, (int, float)) and limit > 0:
            pct = used / limit * 100
    return pct

model = data.get('model', {}).get('display_name', 'Claude')
parts = [model]

ctx = get_used_percentage(data, 'context_window')
if ctx is not None:
    parts.append(fmt('ctx', ctx))

five = get_used_percentage(data, 'rate_limits', 'five_hour')
if five is not None:
    parts.append(fmt('5h', five))

week = get_used_percentage(data, 'rate_limits', 'seven_day')
if week is not None:
    parts.append(fmt('7d', week))

print(f'{DIM}│{R}'.join(f' {p} ' for p in parts), end='')
