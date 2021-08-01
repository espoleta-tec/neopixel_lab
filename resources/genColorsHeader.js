const fs = require('fs')
const path = require('path')

let colors = fs.readFileSync(path.resolve(__dirname, 'colorList.json'))

colors = JSON.parse(colors)

const fileHeader = "//\n" +
    "// Created by lazaroofarrill on 7/29/21.\n" +
    "//\n" +
    "\n" +
    "#ifndef NEOPIXELTESTER_COLORS_H\n" +
    "#define NEOPIXELTESTER_COLORS_H"

const fileFooter = "\n" +
    "#endif //NEOPIXELTESTER_COLORS_H\n"

const file = fileHeader +
    colors.map((color) => {
        return `#define COLOR_${color.name.split(/[ -]/).join('_')
            .split(/[( )]/).join('')
            .toUpperCase()} 0x${color.hex.slice(1)}`
    }).join('\n')
    + fileFooter

console.log(file)