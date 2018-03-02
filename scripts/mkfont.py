#!/usr/bin/python3

characters = {
    'A': [
        "   XX",
        "  X  X",
        "  X  X",
        " X    X",
        " X    X",
        "X      X",
        "X      X",
        "XXXXXXXX",
        "X      X",
        "X      X",
        "X      X",
        "X      X",
        "X      X",
        "X      X",
        "X      X",
        "X      X",
    ],
    'B': [
        "XXXX",
        "X   X",
        "X    X",
        "X     X",
        "X     X",
        "X     X",
        "X    X",
        "XXXXX",
        "X    X",
        "X     X",
        "X      X",
        "X      X",
        "X      X",
        "X     X",
        "X    X",
        "XXXXX",
    ],
    'C': [
        "   XXX",
        "  X   X",
        "  X    X",
        " X",
        " X", #
        "X",
        "X",
        "X",
        "X",
        "X",
        "X",
        " X",
        " X",
        "  X    X",
        "  X   X",
        "   XXX", #
    ],
    'D': [
        "XXXX",
        "X   X",
        "X    X",
        "X     X",
        "X     X",
        "X      X",
        "X      X",
        "X      X",
        "X      X",
        "X      X",
        "X      X",
        "X     X",
        "X     X",
        "X    X",
        "X   X",
        "XXXX", #
    ],
    'E': [
        "XXXXX",
        "X",
        "X",
        "X",
        "X", #
        "X",
        "X",
        "XXXX",
        "X",
        "X",
        "X",
        "X",
        "X",
        "X",
        "X",
        "XXXXX", #
    ],
    'F': [
        "XXXXX",
        "X",
        "X",
        "X",
        "X", #
        "X",
        "X",
        "X",
        "XXXX",
        "X",
        "X",
        "X",
        "X",
        "X",
        "X",
        "X", #
    ],
    'G': [
        "   XXX",
        "  X   X",
        "  X    X",
        " X",
        " X", #
        "X",
        "X",
        "X",
        "X",
        "X   XXXX",
        "X       X",
        " X      X",
        " X      X",
        "  X    XX",
        "  X   X X",
        "   XXX", #
        "",
        "",
        "",
        ""
    ],
    'H': [
        "X   X",
        "X   X",
        "X   X",
        "X   X",
        "X   X", #
        "X   X",
        "X   X",
        "XXXXX",
        "X   X",
        "X   X",
        "X   X",
        "X   X",
        "X   X",
        "X   X",
        "X   X",
        "X   X", #
    ],
    'I': [
        "XXX",
        " X",
        " X",
        " X",
        " X", #
        " X",
        " X",
        " X",
        " X",
        " X",
        " X",
        " X",
        " X",
        " X",
        " X",
        "XXX", #
    ],
    'J': [
        " .XXX",
        "   X",
        "   X",
        "   X",
        "   X", #
        "   X",
        "   X",
        "   X",
        "   X",
        "   X",
        "   X",
        "   X",
        "   X",
        "X  X",
        "X  X",
        " XX", #
    ],
    'K': [
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        "X     X", #
        "X    X",
        "X   X",
        "XXXX",
        "X   X",
        "X    X",
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        "X     X", #
    ],
    'L': [
        "X",
        "X",
        "X",
        "X",
        "X", #
        "X",
        "X",
        "X",
        "X",
        "X",
        "X",
        "X",
        "X",
        "X",
        "X",
        "XXXXX", #
    ],
    'M': [
        "X       X",
        "XX     XX",
        "XX     XX",
        "X X   X X",
        "X X   X X", #
        "X  X X  X",
        "X  X X  X",
        "X  X X  X",
        "X  X X  X",
        "X   X   X",
        "X   X   X",
        "X   X   X",
        "X   X   X",
        "X   X   X",
        "X   .   X",
        "X       X", #
    ],
    'N': [
        "X    X",
        "XX   X",
        "XX   X",
        "X X  X",
        "X X  X", #
        "X  X X",
        "X  X X",
        "X  X X",
        "X  X X",
        "X  X X",
        "X   XX",
        "X   XX",
        "X    X",
        "X    X",
        "X    X",
        "X    X", #
    ],
    'O': [
        "   XXXX",
        "  X    X",
        "  X    X",
        " X      X",
        " X      X", #
        "X        X",
        "X        X",
        "X        X",
        "X        X",
        "X        X",
        "X        X",
        " X      X",
        " X      X",
        "  X    X",
        "  X    X",
        "   XXXX", #
    ],
    'P': [
        "XXXX",
        "X   X",
        "X    X",
        "X     X",
        "X     X",
        "X     X",
        "X    X",
        "XXXXX",
        "X",
        "X",
        "X",
        "X",
        "X",
        "X",
        "X",
        "X",
    ],
    'Q': [
        "   XXXX",
        "  X    X",
        "  X    X",
        " X      X",
        " X      X", #
        "X        X",
        "X        X",
        "X        X",
        "X        X",
        "X        X",
        "X        X",
        " X     XX",
        " X      X",
        "  X    . X",
        "  X    X X",
        "   XXXX   X", #
    ],
    'R': [
        "XXXX",
        "X   X",
        "X    X",
        "X     X",
        "X     X",
        "X     X",
        "X    X",
        "XXXXX",
        "X    X",
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        "X     X",
    ],
    'S': [
        "   XXX",
        "  X   X",
        " X     X",
        "X      X",
        "X     X", #
        "X",
        " X",
        "  XXXX",
        "      X",
        "       X",
        "       X",
        "X       X",
        "X      X",
        "X      X",
        " X    X",
        "  XXXX", #
    ],
    'T': [
        "XXXXXXXXX",
        "    X",
        "    X",
        "    X",
        "    X", #
        "    X",
        "    X",
        "    X",
        "    X",
        "    X",
        "    X",
        "    X",
        "    X",
        "    X",
        "    X",
        "    X", #
    ],
    'U': [
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        "X     X", #
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        " X   X",
        "  XXX", #
    ],
    'V': [
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        "X     X", #
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        " X   X",
        " X   X",
        "  X X",
        "  X X",
        "   X", #
    ],
    'W': [
        "X     X     X",
        "X     X     X",
        "X     X     X",
        "X     X     X",
        "X     X     X", #
        "X     X     X",
        "X     X     X",
        "X     X     X",
        "X     X     X",
        "X     X     X",
        "X     X     X",
        " X   X X   X",
        " X   X X   X",
        "  X X   X X",
        "  X X   X X",
        "   X     X", #
    ],
    'X': [
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        " X   X", #
        " X   X",
        "  X X",
        "  X X",
        "   X",
        "  X X",
        "  X X",
        " X   X",
        "X     X",
        "X     X",
        "X     X",
        "X     X", #
    ],
    'Y': [
        "X     X",
        "X     X",
        "X     X",
        "X     X",
        "X     X", #
        " X   X",
        " X   X",
        "  X X",
        "   X",
        "   X",
        "   X",
        "   X",
        "   X",
        "   X",
        "   X",
        "   X", #
    ],
    'Z': [
        "XXXXXX",
        "     X",
        "     X",
        "     X",
        "    X", #
        "    X",
        "   X",
        " XXXX",
        "  X",
        "  X",
        " X",
        " X",
        "X",
        "X",
        "X",
        "XXXXXX", #
    ],
    'Æ': [
        "   XXXXXXXXX",
        "  X  X",
        "  X  X",
        " X    X",
        " X    X",
        "X      X",
        "X      X",
        "XXXXXXXXXXX",
        "X      X",
        "X      X",
        "X      X",
        "X      X",
        "X      X",
        "X      X",
        "X      X",
        "X      XXXXX", #
    ],
    'Ø': [
        "   XXXX X",
        "  X    XX",
        "  X    X",
        " X    X X",
        " X    X X", #
        "X    X   X",
        "X    X   X",
        "X    X   X",
        "X   X    X",
        "X   X    X",
        "X   X    X",
        " X X    X",
        " X X    X",
        "  X    X",
        " XX    X",
        " X XXXX", #
    ],
    'Å': [
        "  .XX.",
        "  X  X",
        "  .XX.",
        "  X  X",
        " X    X",
        " X    X",
        "X      X",
        "X      X",
        "X      X",
        "XXXXXXXX",
        "X      X",
        "X      X",
        "X      X",
        "X      X",
        "X      X",
        "X      X", #
    ],
    '0': [
        "   XXX",
        "  X   X",
        "  X   X",
        " X     X",
        " X     X", #
        "X       X",
        "X       X",
        "X       X",
        "X       X",
        "X       X",
        "X       X",
        " X     X",
        " X     X",
        "  X   X",
        "  X   X",
        "   XXX", #
        ""
    ],
    '1': [
        "  X",
        " XX",
        "X X",
        "  X",
        "  X",
        "  X",
        "  X",
        "  X",
        "  X",
        "  X",
        "  X",
        "  X",
        "  X",
        "  X",
        "  X",
        "  X", #
        "",
        "",
        "",
        ""
    ],
    '2': [
        "  XXX",
        " X   X",
        "X     X",
        "X     X",
        " X    X",
        "      X",
        "     X",
        "     X",
        "    X",
        "    X",
        "   X",
        "   X",
        "  X",
        " X",
        " X",
        "XXXXXXX", #
    ],
    '3': [
        "  XX",
        " X  X",
        "X    X",
        "X    X",
        "     X",
        "     X",
        "    X",
        "  XX",
        "    X",
        "     X",
        "      X",
        "      X",
        "X     X",
        "X     X",
        " X   X",
        "  XXX",
        "", #
        "",
        "",
        "",
        ""
    ],
    '4': [
        "    XX",
        "   X X",
        "   X X",
        "  X  X",
        "  X  X",
        " X   X",
        " X   X",
        " X   X",
        "X    X",
        "X    X",
        "X    X",
        "XXXXXXX",
        "     X",
        "     X",
        "     X",
        "     X",
        "",
        "",
        "",
        ""
    ],
    '5': [
        "XXXXXXX",
        "X",
        "X",
        "X",
        "X",
        "X",
        "XXXXX",
        "     XX",
        "       X",
        "       X",
        "       X",
        "       X",
        "X      X",
        "X      X",
        " X    X",
        "  XXXX",#
    ],
    '6': [
        "     XX",
        "    X",
        "   X",
        "  X",
        " X",
        " X",
        "X",
        "X XXXX",
        "XX    X",
        "X     X",
        "X      X",
        "X      X",
        "X      X",
        " X    X",
        " X    X",
        "  XXXX",
        "",
        "",
        "",
        ""
    ],
    '7': [
        "XXXXXXX",
        "      X",
        "      X",
        "      X",
        "     X",
        "     X",
        "  XXXXX",
        "    X",
        "   X",
        "   X",
        "  X",
        "  X",
        " X",
        " X",
        "X",
        "X", #
    ],
    '8': [
        "   XXXX",
        "  X    X",
        " X      X",
        "X        X",
        "X        X",
        " X      X",
        "  X    X",
        "   XXXX",
        "  X    X",
        " X      X",
        "X        X",
        "X        X",
        "X        X",
        " X      X",
        "  X    X",
        "   XXXX",
    ],
    '9': [
        "   XXX",
        "  X   X",
        " X     X",
        "X       X",
        "X       X",
        " X      X",
        "  X     X",
        "   XXXXXX",
        "        X",
        "        X",
        "        X",
        "       X",
        "       X",
        "X     X",
        " X   X",
        "  XXX", #
    ],
}

charnames = {
    'A': 'A',
    'B': 'B',
    'C': 'C',
    'D': 'D',
    'E': 'E',
    'F': 'F',
    'G': 'G',
    'H': 'H',
    'I': 'I',
    'J': 'J',
    'K': 'K',
    'L': 'L',
    'M': 'M',
    'N': 'N',
    'O': 'O',
    'P': 'P',
    'Q': 'Q',
    'R': 'R',
    'S': 'S',
    'T': 'T',
    'U': 'U',
    'V': 'V',
    'W': 'W',
    'X': 'X',
    'Y': 'Y',
    'Z': 'Z',
    'Æ': 'AE',
    'Ø': 'OE',
    'Å': 'AA',
    'a': 'a',
    'b': 'b',
    'c': 'c',
    'd': 'd',
    'e': 'e',
    'f': 'f',
    'g': 'g',
    'h': 'h',
    'i': 'i',
    'j': 'j',
    'k': 'k',
    'l': 'l',
    'm': 'm',
    'n': 'n',
    'o': 'o',
    'p': 'p',
    'q': 'q',
    'r': 'r',
    's': 's',
    't': 't',
    'u': 'u',
    'v': 'v',
    'w': 'w',
    'x': 'x',
    'y': 'y',
    'z': 'z',
    'æ': 'ae',
    'ø': 'oe',
    'å': 'aa',
    '0': '0',
    '1': '1',
    '2': '2',
    '3': '3',
    '4': '4',
    '5': '5',
    '6': '6',
    '7': '7',
    '8': '8',
    '9': '9',
    '/': 'slash'
}

def write_header(f):
    f.write('// Bikemaster - A bike statistics solution\n')
    f.write('// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>\n')
    f.write('// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>\n\n')
    f.write('#include "glyph.h"\n')
    f.write('#include "lut.h"\n\n')

def get_data_width(data_array):
    longest_line = 0
    for line in data_array:
        if len(line) > longest_line:
            longest_line = len(line)
    return longest_line

def get_data_height(data_array, start_offset):
    height = 0
    for line in data_array[start_offset:]:
        if len(line) == 0:
            break
        else:
            height = height + 1
    return height

def get_y_offset(data_array):
    y_offset = 0;
    for line in data_array:
        if len(line) != 0:
            return y_offset
        else:
            y_offset = y_offset + 1

def write_data(f, data, width):
    for line in data:
        f.write('\t')
        for b in line:
            if b == 'X':
                f.write('0xff, ')
            elif b == '.':
                f.write('0x20, ')
            elif b == ' ':
                f.write('0x00, ')
        for i in range(width - len(line)):
            f.write('0x00, ')
        f.write('\n')

def write_glyph(f, charname, width, height, y_offset):
    f.write('static const Glyph glyph_{}({}, {}, {}, {});\n'.format(
        charname, width, height, y_offset, 'chardata_{}'.format(charname)))

def write_lut(f):
    f.write('static const LUT<wchar_t, const Glyph *>::Entry lutEntries[] = {\n')
    for c, data in characters.items():
        f.write('\t{{ L\'{}\', &glyph_{} }},\n'.format(c, charnames[c]))
    f.write('};\n')
    f.write('LUT<wchar_t, const Glyph *> glyphs(lutEntries, {});\n'.format(len(characters.items())))

def write_chars(f):
    for c, data in characters.items():
        y_offset = get_y_offset(data)
        width = get_data_width(data)
        height = get_data_height(data, y_offset)

        f.write('static const uint8_t chardata_{}[] = {{\n'.format(charnames[c]))
        write_data(f, data[y_offset:], width)
        f.write('};\n')
        write_glyph(f, charnames[c], width, height, y_offset)
        f.write('\n')

    write_lut(f)
    f.write('\n')

if __name__ == "__main__":
    with open('src/glyphs.cpp', 'w') as outfile:
        write_header(outfile)
        write_chars(outfile)

