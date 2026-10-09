"""Render tonal-pill badges from badges.yml (Geist 500, text outlined to paths).

    pip install fonttools pyyaml
    python badges/build.py

Lives on the `badge` branch (master is untouched). SVGs are written to the branch
root, so they are served from
    https://raw.githubusercontent.com/SoongE/SoongE/badge/<name>.svg
"""
import math
import re
import sys
from pathlib import Path

import yaml
from fontTools.pens.svgPathPen import SVGPathPen
from fontTools.pens.transformPen import TransformPen
from fontTools.ttLib import TTFont
from fontTools.varLib.instancer import instantiateVariableFont

ROOT = Path(__file__).resolve().parent
SRC = ROOT / "_src"
REPO = "SoongE/SoongE"
BRANCH = "badge"
OUT = Path(sys.argv[1]).resolve() if len(sys.argv) > 1 else ROOT.parent  # branch root
RAW = f"https://raw.githubusercontent.com/{REPO}/{BRANCH}"

H, FS, ICON, PL, PR, GAP = 28, 14.5, 16.5, 10.5, 13, 7  # px
PL_NOICON = 13

# --- font ---------------------------------------------------------------------
FONT = TTFont(SRC / "fonts" / "Geist[wght].ttf")
instantiateVariableFont(FONT, {"wght": 500}, inplace=True)
GLYPHS, CMAP, UPM = FONT.getGlyphSet(), FONT.getBestCmap(), FONT["head"].unitsPerEm


def _pair_subtables():
    for lookup in FONT["GPOS"].table.LookupList.Lookup if "GPOS" in FONT else []:
        for st in lookup.SubTable:
            if lookup.LookupType == 9:
                st = st.ExtSubTable
            if getattr(st, "LookupType", lookup.LookupType) == 2:
                yield st


PAIRS = list(_pair_subtables())


def kern(a, b):
    """X-advance adjustment between glyphs a and b from GPOS pair positioning."""
    for st in PAIRS:
        cov = st.Coverage.glyphs
        if a not in cov:
            continue
        if st.Format == 1:
            for rec in st.PairSet[cov.index(a)].PairValueRecord:
                if rec.SecondGlyph == b:
                    return getattr(rec.Value1, "XAdvance", 0) or 0
        else:
            c1 = st.ClassDef1.classDefs.get(a, 0)
            c2 = st.ClassDef2.classDefs.get(b, 0)
            v = getattr(st.Class1Record[c1].Class2Record[c2].Value1, "XAdvance", 0) or 0
            if v:
                return v
    return 0


def outline(text, x, baseline):
    k = FS / UPM
    parts, cx, prev = [], x, None
    for ch in text:
        g = CMAP[ord(ch)]
        if prev:
            cx += kern(prev, g) * k
        pen = SVGPathPen(GLYPHS, ntos=lambda v: f"{v:.2f}".rstrip("0").rstrip("."))
        GLYPHS[g].draw(TransformPen(pen, (k, 0, 0, -k, cx, baseline)))
        if pen.getCommands():
            parts.append(pen.getCommands())
        cx += GLYPHS[g].width * k
        prev = g
    return " ".join(parts), cx - x


# --- tones ----------------------------------------------------------------------
# A tone is either [light ink, light bg, dark ink, dark bg] or a single brand hex,
# from which the four colours are derived in OKLCH with WCAG-contrast targets.
def _lin(c): return c / 12.92 if c <= 0.04045 else ((c + 0.055) / 1.055) ** 2.4
def _gam(c): return 12.92 * c if c <= 0.0031308 else 1.055 * c ** (1 / 2.4) - 0.055


def hex2rgb(h):
    h = h.lstrip("#")
    return [int(h[i:i + 2], 16) / 255 for i in (0, 2, 4)]


def rgb2oklch(rgb):
    r, g, b = map(_lin, rgb)
    l = (0.4122214708 * r + 0.5363325363 * g + 0.0514459929 * b) ** (1 / 3)
    m = (0.2119034982 * r + 0.6806995451 * g + 0.1073969566 * b) ** (1 / 3)
    s = (0.0883024619 * r + 0.2817188376 * g + 0.6299787005 * b) ** (1 / 3)
    L = 0.2104542553 * l + 0.7936177850 * m - 0.0040720468 * s
    a = 1.9779984951 * l - 2.4285922050 * m + 0.4505937099 * s
    bb = 0.0259040371 * l + 0.7827717662 * m - 0.8086757660 * s
    return L, math.hypot(a, bb), math.atan2(bb, a)


def oklch2rgb(L, C, h):
    a, b = C * math.cos(h), C * math.sin(h)
    l = (L + 0.3963377774 * a + 0.2158037573 * b) ** 3
    m = (L - 0.1055613458 * a - 0.0638541728 * b) ** 3
    s = (L - 0.0894841775 * a - 1.2914855480 * b) ** 3
    return [_gam(v) if v > 0 else -1 for v in (
        4.0767416621 * l - 3.3077115913 * m + 0.2309699292 * s,
        -1.2684380046 * l + 2.6097574011 * m - 0.3413193965 * s,
        -0.0041960863 * l - 0.7034186147 * m + 1.7076147010 * s)]


def oklch(L, C, h):
    """Nearest in-gamut sRGB hex, reducing chroma until it fits."""
    while C > 0:
        rgb = oklch2rgb(L, C, h)
        if all(0 <= v <= 1 for v in rgb):
            break
        C -= 0.002
    rgb = oklch2rgb(L, max(C, 0), h)
    return "#" + "".join(f"{round(min(max(v, 0), 1) * 255):02x}" for v in rgb)


def contrast(x, y):
    lum = lambda h: sum(w * _lin(c) for w, c in zip((0.2126, 0.7152, 0.0722), hex2rgb(h)))
    a, b = sorted((lum(x), lum(y)), reverse=True)
    return (a + 0.05) / (b + 0.05)


def derive_tone(base):
    L, C, h = rgb2oklch(hex2rgb(base))
    light_bg = oklch(0.955, min(C * 0.22, 0.035), h)
    ink_L = min(L, 0.56)
    while contrast(oklch(ink_L, C, h), light_bg) < 4.8:
        ink_L -= 0.01
    dark_bg = oklch(0.255, min(C * 0.35, 0.055), h)
    dark_L = 0.80
    while contrast(oklch(dark_L, min(C, 0.14), h), dark_bg) < 6.5:
        dark_L += 0.01
    return [oklch(ink_L, C, h), light_bg, oklch(dark_L, min(C, 0.14), h), dark_bg]


def resolve_tone(spec):
    return derive_tone(spec) if isinstance(spec, str) else spec


# --- icons --------------------------------------------------------------------
def load_icon(name):
    s = (SRC / "icons" / f"{name}.svg").read_text()
    vb = re.search(r'viewBox="([^"]+)"', s)
    if vb:
        vb = vb.group(1)
    else:
        w = re.search(r'\bwidth="([\d.]+)"', s).group(1)
        h = re.search(r'\bheight="([\d.]+)"', s).group(1)
        vb = f"0 0 {w} {h}"
    body = re.sub(r"(?s)^.*?<svg[^>]*>|</svg>\s*$|<title>.*?</title>", "", s).strip()
    multicolor = bool(re.search(r'fill="#', body))
    return vb, body, multicolor


# --- badge --------------------------------------------------------------------
def render(label, icon, ink, bg):
    left = PL + ICON + GAP if icon else PL_NOICON
    path, tw = outline(label, left, H / 2 + 0.36 * FS)
    w = round(left + tw + PR, 2)
    icon_svg = ""
    if icon:
        vb, body, multicolor = icon
        fill = "" if multicolor else f' fill="{ink}"'
        icon_svg = (f'<svg x="{PL}" y="{(H - ICON) / 2}" width="{ICON}" height="{ICON}" '
                    f'viewBox="{vb}"{fill}>{body}</svg>\n')
    return (f'<svg width="{w}" height="{H}" viewBox="0 0 {w} {H}" fill="none" '
            f'xmlns="http://www.w3.org/2000/svg" role="img" aria-label="{label}">\n'
            f"<title>{label}</title>\n"
            f'<rect width="{w}" height="{H}" rx="{H / 2}" fill="{bg}"/>\n'
            f"{icon_svg}"
            f'<path d="{path}" fill="{ink}"/>\n</svg>\n')


def snippet(name, label):
    return (f'<picture><source media="(prefers-color-scheme: dark)" srcset="{RAW}/{name}-dark.svg">'
            f'<img src="{RAW}/{name}.svg" alt="{label}"></picture>')


def main():
    cfg = yaml.safe_load((ROOT / "badges.yml").read_text())
    tones, badges = cfg["tones"], cfg["badges"]
    OUT.mkdir(parents=True, exist_ok=True)
    icons = {}
    rows = []
    for name, spec in badges.items():
        tone = resolve_tone(tones[spec["tone"]])
        icon_name = spec.get("icon") or "none"
        icon = None
        if icon_name != "none":
            icon = icons.setdefault(icon_name, load_icon(icon_name))
        (OUT / f"{name}.svg").write_text(render(spec["label"], icon, tone[0], tone[1]))
        (OUT / f"{name}-dark.svg").write_text(render(spec["label"], icon, tone[2], tone[3]))
        rows.append((name, spec["label"]))

    # drop SVGs whose entry was removed from badges.yml
    keep = {f"{n}{s}.svg" for n, _ in rows for s in ("", "-dark")}
    for f in OUT.glob("*.svg"):
        if f.name not in keep:
            f.unlink()

    lines = [
        "# Badges",
        "",
        "Generated from [`badges/badges.yml`](badges/badges.yml) by `python badges/build.py`. "
        "Do not edit the SVGs or this README by hand.",
        "",
        "Wrap a badge in a link: `<a href=\"...\">` + snippet + `</a>`. "
        "Append `?v=2` to the URLs to bust GitHub's image cache after a redesign.",
        "",
        "| Badge | Name | Snippet |",
        "| --- | --- | --- |",
    ]
    for name, label in rows:
        lines.append(f"| {snippet(name, label)} | `{name}` | `{snippet(name, label)}` |")
    (OUT / "README.md").write_text("\n".join(lines) + "\n")
    print(f"rendered {len(rows)} badges")


if __name__ == "__main__":
    main()
